// trnlsp.h - Intel MKL Nonlinear Least Squares Problem with Without Constraints
#pragma once
#include "../include/ensure.h"
#ifdef _DEBUG
#include <algorithm>
#include <numeric>
#endif
#include <functional>
#include <initializer_list>
#include <vector>
#include "mkl_rci.h"
#include "mkl_types.h"
#include "mkl_service.h"
#include "jacobi.h"

namespace mkl {

	// convergence criteria
	enum { TRUST_REGION = 1, RESIDUAL, SINGULAR_JACOBIAN, TRIAL_STEP, NORM_TOLERANCE, TRIAL_STEP_PRECISION };

	template<class X>
	struct trnlsp_traits { 
		static int init(_TRNSP_HANDLE_t*, int*, int*, X*, X*, int*, int*, X*);
		// !!!Add here, in trnlsp_traits<double>, trnlsp_traits<float>, and in code below
		// delete //!!!bolunpung
		// solve //!!!bfs48
		// check //!!!cxccxlcxc
		// get //!!!dgtsx
	};
	template<>
	struct trnlsp_traits<double> {
//		constexpr int (*init)(_TRNSP_HANDLE_t*, int*, int*, double*, double*, int*, int*, double*)
//			= dtrnlsp_init; // constexpr not supported by VS 2013
		static int init(_TRNSP_HANDLE_t* h, int* m, int* n, double* x, double* eps, int* iter1, int* iter2, double* rs)
		{
			return dtrnlsp_init(h, m, n, x, eps, iter1, iter2, rs);
		}
	};
	template<>
	struct trnlsp_traits<float> {
		static int init(_TRNSP_HANDLE_t* h, int* m, int* n, float* x, float* eps, int* iter1, int* iter2, float* rs)
		{
			return strnlsp_init(h, m, n, x, eps, iter1, iter2, rs);
		}
	};

	// solve min_x ||F(x)||_2 where F: R^m -> R^n
	template<class X = double>
	class trnlsp {
		typedef std::vector<double> dvector;
		// function from vectors to vectors
		typedef std::function<dvector(const dvector&)> vfunction;

		_TRNSP_HANDLE_t h;
#ifdef _DEBUG
	public:
#endif
		int info[6];
		int m, n;
		std::vector<double> x, eps, f, df;
		int iter1, iter2;
		double rs;
		vfunction F, dF;
	public:
		trnlsp(int m, int n, const double* x, const double* eps = 0, int iter1 = 1000, int iter2 = 100, double rs = 1)
			: m(m), n(n), x(x, x + m), eps(6), iter1(iter1), iter2(iter2), rs(rs),
				f(n), df(m*n)
		{
			if (eps)
				this->eps.assign(eps, eps + 6);
			else
				this->eps.assign(6, 1e-10);

			ensure (TR_SUCCESS == trnlsp_traits<X>::init(&h, &this->m, &this->n, &this->x[0], &this->eps[0], &this->iter1, &this->iter2, &this->rs));
		}
		trnlsp(const trnlsp&) = delete;
		trnlsp operator=(const trnlsp&) = delete;
		~trnlsp()
		{
			dtrnlsp_delete(&h);
			mkl_free_buffers();
		}

		trnlsp& function(const vfunction& F)
		{
			this->F = F;

			return *this;
		}

		trnlsp& jacobian(const vfunction& dF)
		{
			this->dF = dF;

			return *this;
		}

		// expect TR_SUCCESS
		int check()
		{
			return dtrnlsp_check(&h, &m, &n, &df[0], &f[0], &eps[0], info);
		}
		// reverse communication interface
		int solve(int rci = 0)
		{
			ensure (TR_SUCCESS == dtrnlsp_solve(&h, &f[0], &df[0], &rci));
			ensure (TR_SUCCESS == check());
#ifdef _DEBUG
			int iter, cr;
			double ir, fr;
			get(iter, cr, ir, fr);
			X rr;
			rr = std::accumulate(f.begin(), f.end(), 0., [](double s, double x) { return s + x*x; });
			rr = sqrt(rr);
#endif
			return rci;
		}

		int step(int rci = 0)
		{
			rci = solve(rci);

			if (rci == 1) {
				f = F(x);
			}
			else {
				df = dF(x);
			}

			return rci;
		}

		std::vector<double> find(void)
		{
			for (int rci = step(); rci >= 0; rci = step(rci))
				; // nothing

			// -rci is now the stop criterion

			return x;
		}

		// solution status: iterations, stop criterion, initial residual, final residual
		void get(int& iter, int& cr, double& ir, double& fr)
		{
			dtrnlsp_get(&h, &iter, &cr, &ir, &fr);
		}
	};

	// matlab like version
	template<class X = double>
	inline std::vector<X> lsqnonlin(int m, int n, const std::function<std::vector<X>(const std::vector<X>&)>& f, const std::vector<X>& x,
		const double* eps = 0, int iter1 = 1000, int iter2 = 100, double rs = 1)
	{
		ensure (x.size() == (size_t)m);

		return mkl::trnlsp<X>(m, n, &x[0], eps, iter1, iter2, rs)
			.function(f)
			.jacobian(mkl::jacobian(m, n, f))
			.find();
	}

} // mkl

#ifdef _DEBUG

using namespace std;
using namespace mkl;

inline void test_mkl_trnlsp1()
{

	vector<double> x{1,1};

	trnlsp<> problem(2, 2, &x[0]);
	// F(x) = x, dF(x) = I
	problem.function([](const vector<double>& x) { return x; });
	problem.jacobian([](const vector<double>& x) { return std::vector<double>({1, 0, 0, 1}); });

	ensure (TR_SUCCESS == problem.check());
	auto x_ = problem.find();

	// same thing in one line
	auto f = [](const vector<double>& x) { return x; };
	auto x2 = trnlsp<>(2, 2, &x[0]).function(f).jacobian(mkl::jacobian<double>(2, 2, f)).find();

	ensure (x_ == x2);

	int iter, cr;
	double ir, fr;
	problem.get(iter, cr, ir, fr);

	// min ||F(x)|| at x = 0
	ensure (x_ == std::vector<double>({0,0}));
	ensure (iter == 1);
	ensure (cr == 3);
	ensure (fr == 0);
}

// Unconstrained Rosenbrock Function
inline void test_mkl_trnlsp2()
{
	auto f = [](const vector<double>& x) {
		return vector<double> { 10*(x[1] - x[0]*x[0]), 1 - x[0] };
	};
	std::vector<double> x {-1.2, 1};
	trnlsp<> p(2, 2, &x[0]);
	p.function(f);
	p.jacobian(jacobian<double>(2,2,f));
	auto x_ = p.find();

	int iter, cr;
	double ir, fr;	
	p.get(iter, cr, ir, fr);
	ensure (iter == 14);
	ensure (cr == 3);
	ensure (fr == 0);
	ensure (x_ == std::vector<double>({1,1}));
}

// http://www.mathworks.com/help/optim/ug/lsqnonlin.html
inline void test_mkl_trnlsp3()
{
	int m = 2, n = 10;
	std::vector<double> x{0.3, 0.4};
	
	trnlsp<> problem(m, n, &x[0]);
	auto f = [n](const vector<double>& x) {
		std::vector<double> y(n);

		for (int k = 1; k <= n; ++k)
			y[k - 1] = 2 + 2*k - exp(k*x[0]) - exp(k*x[1]);

		return y;
	};
	problem.function(f);
	problem.jacobian(jacobian<double>(m, n, f));

	auto x_ = problem.find();
	auto y = f(x_);
	y = f(std::vector<double>({0.2578, 0.2578}));
	x_ = lsqnonlin<double>(m, n, f, x);
	y = f(std::vector<double>({0.2578, 0.2578}));
//	ensure (fabs(x_[0] - 0.2578) < 1e-4);
//	ensure (fabs(x_[1] - 0.2578) < 1e-4);
}

inline void test_mkl_trnlsp()
{
	test_mkl_trnlsp1();
	test_mkl_trnlsp2();
	test_mkl_trnlsp3();
}

#endif // _DEBUG
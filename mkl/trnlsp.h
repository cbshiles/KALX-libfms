// trnlsp.h - Intel MKL Nonlinear Least Squares Problem with Without Constraints
#pragma once
#include "../include/ensure.h"
#include <functional>
#include <initializer_list>
#include <vector>
#include "mkl_rci.h"
#include "mkl_types.h"
#include "mkl_service.h"
#include "jacobi.h"

namespace mkl {

	// solve min_x ||F(x)||_2 where F: R^m -> R^n
	class trnlsp {
#ifdef _DEBUG
	public:
#endif
		// function from vectors to vectors
		typedef std::function<std::vector<double>(const std::vector<double>&)> vfunction;

		_TRNSP_HANDLE_t h;
		int info[6];
		int m, n;
		std::vector<double> x, eps, f, df;
		int iter1, iter2;
		double rs;
		vfunction F, dF;
	public:
		trnlsp(int m, int n, const double* x = 0, const double* eps = 0, int iter1 = 1000, int iter2 = 100, double rs = 100)
			: m(m), n(n), x(m), eps(6), iter1(iter1), iter2(iter2), rs(rs),
				f(n), df(m*n)
		{
			if (x)
				this->x.assign(x, x + m);

			if (eps)
				this->eps.assign(eps, eps + 6);
			else
				this->eps.assign(6, 1e-10);

			ensure (TR_SUCCESS == dtrnlsp_init(&h, &this->m, &this->n, &this->x[0], &this->eps[0], &this->iter1, &this->iter2, &this->rs));
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
			return dtrnlsp_check(&h, &m, &n, &df[0], &f[0], &eps[0], &info[0]);
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
#endif
			return rci;
		}

		std::vector<double> find(void)
		{
			for (int rci = solve(); rci != 0; rci = solve(rci)) {
				ensure (rci == 1 || rci ==2);

				if (rci == 1) {
					f = F(x);
				}
				else {
					df = dF(x);
				}
			}

			return x;
		}
		/*
		const std::vector<double>& find(const std::vector<double>& x)
		{
			this->x = x;

			return find();
		}
		*/

		// solution status: iterations, stop criteria, initial residual, final residual
		void get(int& iter, int& cr, double& ir, double& fr)
		{
			dtrnlsp_get(&h, &iter, &cr, &ir, &fr);
		}
	};

	// matlab like version
	inline std::vector<double> lsqnonlin(int m, int n, const std::function<std::vector<double>(const std::vector<double>&)>& f, const std::vector<double>& x)
	{
		ensure (x.size() == (size_t)m);

		return mkl::trnlsp(m, n, &x[0])
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

	trnlsp problem(2, 2, &x[0]);
	// F(x) = x, dF(x) = I
	problem.function([](const vector<double>& x) { return x; });
	problem.jacobian([](const vector<double>& x) { return std::vector<double>({1, 0, 0, 1}); });

	ensure (TR_SUCCESS == problem.check());
	auto x_ = problem.find();

	int iter, cr;
	double ir, fr;
	problem.get(iter, cr, ir, fr);
	ir = fr;

	// min ||F(x)|| at x = 0
	ensure (x_ == std::vector<double>({0,0}));
	ensure (iter == 1);
	ensure (cr == 0);
	ensure (fr == 0);
}

// Unconstrained Rosenbrock Function
inline void test_mkl_trnlsp2()
{
	auto f = [](const vector<double>& x) {
		return vector<double> { 10*(x[1] - x[0]*x[0]), 1 - x[0] };
	};
	std::vector<double> x {-1.2, 1};
	trnlsp p(2, 2, &x[0]);
	p.function(f);
	p.jacobian(jacobian(2,2,f));
	auto x_ = p.find();

}

// http://www.mathworks.com/help/optim/ug/lsqnonlin.html
inline void test_mkl_trnlsp3()
{
	int m = 2, n = 10;
	std::vector<double> x{0.3, 0.4};
	
	trnlsp problem(m, n, &x[0]);
	auto f = [n](const vector<double>& x) {
		std::vector<double> y(n);

		for (int k = 1; k <= n; ++k)
			y[k - 1] = 2 + 2*k - exp(k*x[0]) - exp(k*x[1]);

		return y;
	};
	problem.function(f);

	jacobi dF(m, n, f);
	problem.jacobian([&dF](const vector<double>& x) { return dF(x); });

	auto x_ = problem.find();
	auto y = f(x_);
	y = f(std::vector<double>({0.2578, 0.2578}));
	x_ = lsqnonlin(m, n, f, x);
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
// trnlsp.h - Intel MKL Nonlinear Least Squares Problem with Without Constraints
#pragma once
#include "../include/ensure.h"
#include <functional>
#include <initializer_list>
#include <vector>
#include "mkl_rci.h"
#include "mkl_types.h"
#include "mkl_service.h"

namespace mkl {

	// solve min_x ||F(x)||_2 where F: R^m -> R^n
	class trnlsp {
		// function from vectors to vectors
		typedef std::function<std::vector<double>(const std::vector<double>&)> vfunction;

		_TRNSP_HANDLE_t h_;
		int info_[6];
		int m_, n_;
		std::vector<double> x_, eps_, f_, df_;
		int iter1_, iter2_;
		double rs_;
		vfunction F_, dF_;
	public:
		trnlsp(int m, int n, double* x = 0, double* eps = 0, int iter1 = 1000, int iter2 = 100, double rs = 100)
			: m_(m), n_(n), x_(m), eps_(6), iter1_(iter1), iter2_(iter2), rs_(rs),
				f_(n), df_(m*n)
		{
			if (x)
				x_.assign(x, x + m);

			if (eps)
				eps_.assign(eps, eps + 6);
			else
				eps_.assign(6, 1e-10);

			ensure (TR_SUCCESS == dtrnlsp_init(&h_, &m_, &n_, &x_[0], &eps_[0], &iter1_, &iter2_, &rs_));
		}
		trnlsp(const trnlsp&) = delete;
		trnlsp operator=(const trnlsp&) = delete;
		~trnlsp()
		{
			dtrnlsp_delete(&h_);
			mkl_free_buffers();
		}

		trnlsp& function(const vfunction& F)
		{
			F_  = F;

			return *this;
		}

		trnlsp& jacobian(const vfunction& dF)
		{
			dF_  = dF;

			return *this;
		}

		// expect TR_SUCCESS
		int check()
		{
			return dtrnlsp_check(&h_, &m_, &n_, &df_[0], &f_[0], &eps_[0], &info_[0]);
		}

		int solve(int rci = 0)
		{
			ensure (TR_SUCCESS == dtrnlsp_solve(&h_, &f_[0], &df_[0], &rci));

			return rci;
		}

		const std::vector<double>& find(void)
		{
			for (int rci = solve(); rci > 0; rci = solve(rci)) {
				ensure (rci == 1 || rci ==2);

				if (rci == 1) {
					f_ = F_(x_);
				}
				else {
					df_ = dF_(x_);
				}
			}

			return x_;
		}
		/*
		const std::vector<double>& find(const std::vector<double>& x)
		{
			x_ = x;

			return find();
		}
		*/

		// solution status: iterations, stop criteria, initial residual, final residual
		void get(int& iter, int& cr, double& ir, double& fr)
		{
			dtrnlsp_get(&h_, &iter, &cr, &ir, &fr);
		}
	};

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
	const vector<double>& x_ = problem.find();

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

// http://www.mathworks.com/help/optim/ug/lsqnonlin.html
inline void test_mkl_trnlsp2()
{
	int n = 2, m = 10;
	double x[] = {0.3, 0.4};
	
	trnlsp problem(2, 10, x);
	auto f = [](const vector<double>& x) {
		std::vector<double> y(10);

		for (int k = 1; k <= 10; ++k)
			y[k - 1] = 2 + 2*k - exp(k*x[0]) - exp(k*x[1]);

		return y;
	};
	problem.function(f);

	jacobi dF(2, 10, f);
	problem.jacobian([&dF](const vector<double>& x) { return dF(x); });

	auto x_ = problem.find();
	auto y = f(x_);
	y = f(std::vector<double>({0.2578, 0.2578}));
	ensure (fabs(x_[0] - 0.2578) < 1e-4);
	ensure (fabs(x_[1] - 0.2578) < 1e-4);
}

inline void test_mkl_trnlsp()
{
	test_mkl_trnlsp1();
	test_mkl_trnlsp2();
}

#endif // _DEBUG
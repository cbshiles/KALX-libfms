// jacobi.h - MKL Jacobian Matrix Calculation Routines
#pragma once
#include "../include/ensure.h"
#include <functional>
#include <memory>
#include <vector>
#include "mkl_rci.h"

namespace mkl {

	// Jacobian of function F:R^m -> R^n
	class jacobi {
		_JACOBIMATRIX_HANDLE_t h_;
#ifdef _DEBUG
	public:
#endif
		int m_, n_;
		std::vector<double> x_, f1_, f2_, df_;
		std::function<std::vector<double>(const std::vector<double>&)> F_;
		double eps_;
	public:
		jacobi(int m, int n, const double* x = 0, double eps = 1e-9)
			: m_(m), n_(n), x_(m), f1_(n), f2_(n), df_(m*n), eps_(eps)
		{
			if (x)
				x_.assign(x, x + m);

			ensure (TR_SUCCESS == djacobi_init(&h_, &m_, &n_, &x_[0], &df_[0], &eps_));
		}
		jacobi(int m, int n, const std::function<std::vector<double>(const std::vector<double>&)>& F, double eps = 1e-9)
			: jacobi(m, n, 0, eps)
		{
			function(F);
		}
		jacobi(const jacobi&) = delete;
		jacobi& operator=(const jacobi&) = delete;
		~jacobi()
		{
			djacobi_delete(&h_);
			mkl_free_buffers();
		}

		jacobi& function(const std::function<std::vector<double>(const std::vector<double>&)>& F)
		{
			F_  = F;

			return *this;
		}
		const std::function<std::vector<double>(const std::vector<double>&)>& function(void) const
		{
			return F_;
		}

		int solve(int rci = 0)
		{
			ensure (TR_SUCCESS == djacobi_solve(&h_, &f1_[0], &f2_[0], &rci));

			return rci;
		}

		const std::vector<double>& find()
		{
			for (int rci = solve(); rci > 0; rci = solve(rci)) {
				ensure (rci == 1 || rci == 2);

				if (rci == 1)
					f1_ = F_(x_ /* + eps */);
				else
					f2_ = F_(x_ /* - eps */);
			}

			return df_;
		}
		// the n x m Jacobian matrix
		std::vector<double> operator()(const std::vector<double>& x)
		{
			x_ = x;

			return find();
		}
	};

} // mkl

#ifdef _DEBUG

#include <algorithm>
#include <random>

using namespace std;

inline void test_mkl_jacobi1()
{
	int n = 4;
	double eps = 1e-10;

	mkl::jacobi id(n, n, [](const vector<double>& x) { return x; }, eps);

	std::default_random_engine e;
	std::uniform_real_distribution<double> u;

	for (int i = 0; i < 10; ++i) {
		vector<double> v(n);
		std::generate(v.begin(), v.end(), [&e,&u](void) { return u(e); });
		auto w = id(v);
		ensure (w.size() == 16);
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k)
				;
//				ensure (fabs(w[n*j + k] - (j == k)) < 2*eps); // identity matrix
	}
}

inline void test_mkl_jacobi()
{
	test_mkl_jacobi1();
}

#endif // _DEBUG
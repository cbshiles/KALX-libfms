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
		typedef std::function<std::vector<double>(const std::vector<double>&)> vfunction;
		_JACOBIMATRIX_HANDLE_t h;
#ifdef _DEBUG
	public:
#endif
		int m, n;
		std::vector<double> x, f1, f2, df;
		vfunction F;
		double eps;
	public:
		jacobi(int m, int n, const vfunction& F, const double* x = 0, double eps = 1e-9)
			: m(m), n(n), F(F), x(m), f1(n), f2(n), df(m*n), eps(eps)
		{
			if (x)
				this->x.assign(x, x + m);

			ensure (TR_SUCCESS == djacobi_init(&h, &this->m, &this->n, &this->x[0], &df[0], &this->eps));
		}
		jacobi(const jacobi&) = delete;
		jacobi& operator=(const jacobi&) = delete;
		~jacobi()
		{
			djacobi_delete(&h);
			mkl_free_buffers();
		}

		int solve(int rci = 0)
		{
			ensure (TR_SUCCESS == djacobi_solve(&h, &f1[0], &f2[0], &rci));

			return rci;
		}

		std::vector<double> find()
		{
			for (int rci = solve(); rci > 0; rci = solve(rci)) {
				ensure (rci == 1 || rci == 2);

				if (rci == 1)
					f1 = F(x /* + eps */);
				else
					f2 = F(x /* - eps */);
			}

			return df;
		}
		// the n x m Jacobian matrix
		std::vector<double> operator()(const std::vector<double>& x)
		{
			this->x = x;

			return find();
		}
	};

	// inefficent, but don't seem to be able to reuse mkl::jacobi
	inline std::function<std::vector<double>(const std::vector<double>&)> 
	jacobian(int m, int n, const std::function<std::vector<double>(const std::vector<double>&)>& f, double eps = 1e-9)
	{
		return [m,n,f,eps](const std::vector<double>& x) {
			return mkl::jacobi(m, n, f, &x[0], eps).find();
		};
	}

} // mkl

#ifdef _DEBUG

#include <algorithm>
#include <random>

using namespace std;

inline void test_mkl_jacobi1()
{
	int n = 4;
	double eps = 1e-10;
	auto id = [](const vector<double>& x) { return x; };

	std::default_random_engine e;
	std::uniform_real_distribution<double> u;

	auto df = mkl::jacobian(n, n, id, eps);

	for (int i = 0; i < 10; ++i) {
		vector<double> v(n);
		std::generate(v.begin(), v.end(), [&e,&u](void) { return u(e); });
		mkl::jacobi id(n, n, id, &v[0], eps);
		auto w = id.find();
		auto w2 = df(v);
		ensure (w == w2);
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
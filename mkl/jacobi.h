// jacobi.h - MKL Jacobian Matrix Calculation Routines
#pragma once
#include "../include/ensure.h"
#include <array>
#include <functional>
#include <memory>
#include <vector>
#include "mkl_rci.h"

namespace mkl {

	// wrapper for pre-allocated memory
	template<class X>
	class array {
		size_t n;
		const X* x;
	public:
		array(size_t n, const X*  x)
			: n(n), x(x);
		{ }
		array(const array&) = delete;
		array& operator=(const array&) = delete;
		~array()
		{ }

		size_t size() const
		{
			return n;
		}
		/*
		operator const X*() const
		{
			return x;
		}
		*/
		const X& operator[](size_t i) const
		{
			ensure (i < n);

			return x[i];
		}
		X& operator[](size_t i)
		{
			ensure (i < n);

			return x[i];
		}
		X* begin()
		{
			return x;
		}
		const X* begin() const
		{
			return x;
		}
		X* end()
		{
			return x + n;
		}
		const X* end() const
		{
			return x + n;
		}
	};

	template<class X = double>
	struct jacobi_traits {
		static int init(_JACOBIMATRIX_HANDLE_t* h, int* n, int* m, X* x, X* df, X* eps);
		static int solve(_JACOBIMATRIX_HANDLE_t*, X*, X*, int*);
		static int destroy(_JACOBIMATRIX_HANDLE_t*);
	};
	template<>
	struct jacobi_traits<double> {
		static int init(_JACOBIMATRIX_HANDLE_t* h, int* n, int* m, double* x, double* df, double* eps)
		{
			return djacobi_init(h, n, m, x, df, eps);
		}
		static int solve(_JACOBIMATRIX_HANDLE_t* h, double* f1, double* f2, int* rci)
		{
			return djacobi_solve(h, f1, f2, rci);
		}
		static int destroy(_JACOBIMATRIX_HANDLE_t* h)
		{
			return djacobi_delete(h);
		}
	};
	template<>
	struct jacobi_traits<float> {
		static int init(_JACOBIMATRIX_HANDLE_t* h, int* n, int* m, float* x, float* df, float* eps)
		{
			return sjacobi_init(h, n, m, x, df, eps);
		}
		static int solve(_JACOBIMATRIX_HANDLE_t* h, float* f1, float* f2, int* rci)
		{
			return sjacobi_solve(h, f1, f2, rci);
		}
		static int destroy(_JACOBIMATRIX_HANDLE_t* h)
		{
			return sjacobi_delete(h);
		}
	};

	// Jacobian of function F:R^m -> R^n
	template<class X = double>
	class jacobi {
		typedef std::function<std::vector<X>(const std::vector<X>&)> vfunction;
		_JACOBIMATRIX_HANDLE_t h;
#ifdef _DEBUG
	public:
#endif
		int m, n;
		std::vector<X> x, df;
		std::array<std::vector<X>,2> f;
		vfunction F;
		X eps;
	public:
		jacobi(int n, int m, const X* x, const vfunction& F, X eps = sqrt(std::numeric_limits<X>::epsilon()))
			: m(m), n(n), F(F), x(n), f({std::vector<X>(m),std::vector<X>(m)}), df(m*n), eps(eps)
		{
			if (x)
				this->x.assign(x, x + n);

			ensure (TR_SUCCESS == jacobi_traits<X>::init(&h, &this->n, &this->m, &this->x[0], &df[0], &this->eps));
		}
		jacobi(const jacobi&) = delete;
		jacobi& operator=(const jacobi&) = delete;
		~jacobi()
		{
			jacobi_traits<X>::destroy(&h);
			mkl_free_buffers();
		}

		int solve(int rci = 0)
		{
			ensure (TR_SUCCESS == jacobi_traits<X>::solve(&h, &(f[0])[0], &(f[1])[0], &rci));

			return rci;
		}

		int step(int rci = 0)
		{
			rci = solve(rci);

			if (rci == 1)
				f[0] = F(x);
			else if (rci == 2)
				f[1] = F(x);

			return rci;
		}

		std::vector<X> find()
		{
			int rci = step();

			while (rci > 0)
				rci = step(rci);			

			return df;
		}
	};

	// inefficent, but don't seem to be able to reuse mkl::jacobi
	template<class X = double>
	inline std::function<std::vector<X>(const std::vector<X>&)> 
	jacobian(int m, int n, const std::function<std::vector<X>(const std::vector<X>&)>& f, X eps = sqrt(std::numeric_limits<X>::epsilon()))
	{
		return [m,n,f,eps](const std::vector<X>& x) {
			return mkl::jacobi<X>(m, n, &x[0], f, eps).find();
		};
	}

} // mkl

#ifdef _DEBUG

#include <algorithm>
#include <random>

using namespace std;

template<class X>
inline void test_mkl_jacobi1()
{
	int n = 4;
	X eps = sqrt(std::numeric_limits<X>::epsilon());
	auto id = [](const vector<X>& x) { return x; };

	std::default_random_engine e;
	std::uniform_real_distribution<X> u;

	auto df = mkl::jacobian<X>(n, n, id, eps);

	for (int i = 0; i < 10; ++i) {
		vector<X> v(n);
		std::generate(v.begin(), v.end(), [&e,&u](void) { return u(e); });
		mkl::jacobi<X> id(n, n, &v[0], id, eps);
		auto w = id.find();
		auto w2 = df(v);
		ensure (w == w2);
		ensure (w.size() == 16);
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				ensure (fabs(w[n*j + k] - (j == k)) < eps); // identity matrix
			}
		}
	}

}

template<class X = double>
void test_mkl_jacobi2(void)
{
}

inline void test_mkl_jacobi()
{
	test_mkl_jacobi1<double>();
	test_mkl_jacobi2<double>();
}

#endif // _DEBUG
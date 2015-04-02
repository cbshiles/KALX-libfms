// normal.h - normal distribution
#pragma once
#include "logistic.h"
#include "root/root1d.h"
#include <cmath>
#include <algorithm>

// template<typename T> constexpr T M_PI = 4*atan(T(1));
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
// template<typename T> constexpr T M_SQRT2 = sqrt(T(2));
#ifndef M_SQRT2 
#define M_SQRT2 1.41421356237309504880
#endif
// template<typename T> constexpr T M_SQRT2PI = sqrt(2*M_PI<T>);
#ifndef M_SQRT2PI
#define M_SQRT2PI 2.50662827463100050242
#endif

namespace fms {
namespace prob {

	namespace normal {
		
		template<class X>
		inline X pdf(const X& x)
		{
			return exp(-x*x/2)/X(M_SQRT2PI);
		}

		template<class X>
		inline X cdf(const X& x)
		{
			return erfc(-x/X(M_SQRT2))/2;
		}

		template<class X>
		inline X inv(const X& p)
		{
			ensure (0 < p && p < 1);

			// if (p < ?) return ?
			// if (p > ?) return ?
			auto x0 = fms::prob::logistic::inv(p);
			auto f = [p](const X& x) { return cdf(x) - p; };
			auto df = [](const X& x) { return pdf(x); };

			return fms::root1d::find::newton<X,X>(x0, f, df, 200);
		}

		// cumulant
		template <class X>
		inline X cumulant(X sigma)
		{
			return -sigma*sigma/2;
		}

		// A correlation matrix is determined by n unit row vectors.
		// The first row is assumed to be (1, 0, ...)
		// The last column is determined by earlier columns.
		// The correlation is lower triangular and packed like
		// (r_10,  r_20, r_21,  r_30, ..., r_n-1,d-2)
		template<class R, class X = double>
		inline void correlated(R& r, size_t n, size_t d, const X* rho, X* result)
		{
			std::vector<X> Z(d);
			auto z = [&r]() { return std::normal_distribution<X>()(r); };

			std::generate(Z.begin(), Z.end(), z);

			result[0] = Z[0]; // first row (1, 0, ...)

			for (size_t off = 0, i = 1; i < n; ++i) {
				size_t j;
				X r2 = 0;
				result[i] = 0;
				for (j = 0; j < (std::min)(i, d - 1); ++j) {
					r2 += rho[j + off]*rho[j + off];
					result[i] += rho[j + off]*Z[j];
				}
				ensure (r2 <= 1);
				result[i] += sqrt(1 - r2)*Z[j];

				off += j;
			}
		}
	};

} // prob
} // math

#ifdef _DEBUG
#include <random>
using namespace fms::prob;

template<class X>
inline void test_sqrt2()
{
	X two = X(M_SQRT2)*X(M_SQRT2);
	
	X sqrt2p = nextafter(X(M_SQRT2), X(2)); // next representable larger float
	ensure (fabs(2 - two) <= fabs(2 - sqrt2p*sqrt2p));
	sqrt2p = nextafter(sqrt2p, X(2));
	ensure (fabs(2 - two) < fabs(2 - sqrt2p*sqrt2p));

	X sqrt2m = nextafter(X(M_SQRT2), X(1)); // next representable smaller float
	ensure (fabs(X(2) - two) <= fabs(X(2) - sqrt2m*sqrt2m));
	sqrt2m = nextafter(sqrt2m, X(1));
	ensure (fabs(2 - two) < fabs(2 - sqrt2m*sqrt2m));
}

template<class X>
inline void test_sqrt2pi()
{
	X twopi = 2*X(M_PI);

	// !!! show M_SQRT2PI is best estimate of sqrt(2*pi) !!!
}

template<class X>
inline void test_prob_normalpdf()
{
	ensure (normal::pdf<X>(0) == 1/M_SQRT2PI);
}

template<class X>
inline void test_prob_normalcdf()
{
	ensure (normal::cdf<X>(0) == X(0.5));
}

template<class X>
inline void test_prob_normalinv(size_t n = 1000)
{
	X p, x;

	std::default_random_engine e;
	std::uniform_real_distribution<X> u(0,1);

	while (--n) {
		p = u(e);
		x = normal::inv(p);
		auto y = normal::cdf<X>(x) - p;
		ensure (fabs(y) <= std::numeric_limits<X>::epsilon());
	}
}

template<class X>
inline void test_prob_normal_correlation(size_t N = 100000)
{
	/*
	X rho[] = 
	//{1, 0, 0,
	{0.1, //sqrt(1 - 0.1^2), 0
	 0.2, 0.3};//sqrt(1 - 0.2^2 - 0.3^2)
	 */
	X x[3], x_[3] = {0, 0, 0}, xx[3] = {0, 0, 0}, xy[3] = {0, 0, 0};
	X rho[] = {0.1,0.2,0.3};
	std::default_random_engine r{};

	for (size_t n = 1; n <= N; ++n) {
		normal::correlated(r, 3, 3, rho, x);
		
		// mean
		x_[0] += (x[0] - x_[0])/n;
		x_[1] += (x[1] - x_[1])/n;
		x_[2] += (x[2] - x_[2])/n;

		// variance
		xx[0] += (x[0]*x[0] - xx[0])/n;
		xx[1] += (x[1]*x[1] - xx[1])/n;
		xx[2] += (x[2]*x[2] - xx[2])/n;

		// correlation
		xy[0] += (x[0]*x[1] - xy[0])/n;
		xy[1] += (x[0]*x[2] - xy[1])/n;
		xy[2] += (x[1]*x[2] - xy[2])/n;
	}
	for (int i = 0; i < 3; ++i)
		ensure (fabs(x_[i] - 0) < 3/sqrt(N));

	for (int i = 0; i < 3; ++i)
		ensure (fabs(xx[i] - 1) < 3/sqrt(N));

	ensure (fabs(xy[0] - rho[0]) < 3/sqrt(N));
	ensure (fabs(xy[1] - rho[1]) < 3/sqrt(N));
	X dot12 = rho[0]*rho[1] + sqrt(1 - rho[0]*rho[0])*rho[2];
	ensure (fabs(xy[2] - dot12) < 3/sqrt(N));
}

inline void test_prob_normal()
{
	test_sqrt2<double>();
	test_sqrt2<float>();
	test_prob_normalpdf<double>();
	test_prob_normalcdf<double>();
	test_prob_normalinv<float>();
	test_prob_normalinv<double>();
	test_prob_normal_correlation<double>();
}

#endif // _DEBUG

// normal.h - normal distribution
#pragma once
#include "ensure.h"
#include "logistic.h"
#include "../root/root1d.h"
#include <cmath>

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
			auto p0 = fms::prob::logistic::inv(p);
			auto f = [p](const X& x) { return cdf(x) - p; };
			auto df = [](const X& x) { return pdf(x); };

			return fms::root1d::find::newton<X,X>(p0, f, df);
		}
	};

} // prob
} // math

#ifdef _DEBUG

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
inline void test_prob_normalinv()
{
	X p, x;

	for (p = X(0.1); p <= 0.9; p += X(0.1)) {
		x = normal::inv(p);
		auto y = p - normal::cdf<X>(x);
		ensure (y == y);
	}
}

inline void test_prob_normal()
{
	test_sqrt2<double>();
	test_sqrt2<float>();
	test_prob_normalpdf<double>();
	test_prob_normalcdf<double>();
	test_prob_normalinv<float>();
	test_prob_normalinv<double>();
}

#endif // _DEBUG

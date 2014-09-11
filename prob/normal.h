// normal.h - normal distribution
#pragma once
#include "ensure.h"
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
// template<typename T> constexpr T M_CRTPISQ_3 = pow(M_PI*M_PI/3, T(1)/T(3));
#ifndef M_CRTPISQ_3
#define M_CRTPISQ_3 1.48728031630047437905
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
		// logistic approximation with mean 0, variance 1
		// int_R x^2 exp(-x)/(1 + exp(-x))^2 dx = pi^2/3
		template<class X>
		inline X cdf_logistic(const X& x)
		{
			return 1/(1 + exp(-M_CRTPISQ_3*X(x)));
		}

		template<class X>
		inline X inv(const X& p)
		{
			ensure (0 <= p && p <= 1);

			// if (p < ?) return ?
			// if (p > ?) return ?

			X x, x_ = inv_logistic(p);
			DEBUG_(int count = 0;)
			do {
				DEBUG_(++count;) 
				x = x_;
				x_ = x - (cdf(x) - p)/pdf(x);
			} while (1 + (x_ - x) != 1);

			return x;
		}
		// logistic approximation with mean 0, variance 1
		// cdf is 1/(1 + exp(-a x)) where a = (pi^2/3)^(1/3)
		template<class X>
		inline X inv_logistic(const X& p)
		{
			return -log(1/X(p) - 1)/X(M_CRTPISQ_3);
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
	
	X sqrt2p = nextafter(X(M_SQRT2), X(2));
	ensure (fabs(2 - two) <= fabs(2 - sqrt2p*sqrt2p));
	sqrt2p = nextafter(sqrt2p, X(2));
	ensure (fabs(2 - two) < fabs(2 - sqrt2p*sqrt2p));

	X sqrt2m = nextafter(X(M_SQRT2), X(1));
	ensure (fabs(2 - two) <= fabs(2 - sqrt2m*sqrt2m));
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

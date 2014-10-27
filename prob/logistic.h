// logistic.h - logistic distribution
#pragma once
#include <cmath>
#include <type_traits>
#include "include/ensure.h"

// template<typename T> constexpr T M_PI = 4*atan(T(1));
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
// template<typename T> constexpr T M_PI_SQRT3 = M_PI/sqrt(T(3));
#ifndef M_PI_SQRT3
#define M_PI_SQRT3 1.81379936423421785059
#endif

namespace fms {
namespace prob {

	namespace logistic {

#define IS_FLOATING_POINT(X) (std::is_floating_point<X>::value, "the type of " #X " must be floating point")

		template<class X>
		inline X pdf(const X& x)
		{
			static_assert IS_FLOATING_POINT(X);

			X e = exp(-x*X(M_PI_SQRT3));

			return X(M_PI_SQRT3)*e/((1 + e)*(1 + e));
		}

		template<class X>
		inline X cdf(const X& x)
		{
			static_assert IS_FLOATING_POINT(X);

			return 1/(1 + exp(-x*X(M_PI_SQRT3)));
		}

		template<class X>
		inline X inv(const X& p)
		{
			static_assert IS_FLOATING_POINT(X);

			ensure (0 < p && p < 1);

			return -log(1/X(p) - 1)/X(M_PI_SQRT3);
		}

#undef IS_FLOATING_POINT

	} // logistic
} // prob
} // fms

#ifdef _DEBUG
#include <random>

using namespace fms::prob;

template<class X>
inline void test_prob_logistic_pdf(void)
{
	ensure (logistic::pdf<X>(X(0)) == X(M_PI_SQRT3)/X(4));
}

template<class X>
inline void test_prob_logistic_cdf(void)
{
	ensure (logistic::cdf<X>(0) == 0.5);
}

template<class X>
inline void test_prob_logistic_inv(int N = 10000)
{
	for (X p = X(0.1); p < 1; p += X(0.1)) {
		X x = logistic::inv(p);
		X q = logistic::cdf(x);
		ensure (fabs(q - p) <= std::numeric_limits<X>::epsilon());
	}

	std::default_random_engine e;
	std::uniform_real_distribution<X> u(0,1);
	
	X m{0}, m2{0};
	for (int n = 1; n <= N; ++n) {
		X x = logistic::inv(u(e));
		m += (x - m)/n;
		m2 += (x*x - m2)/n;
	}
	ensure (fabs(m - 0) < 2/sqrt(N));
	ensure (fabs(m2 - 1) < 2/sqrt(N));
}

inline void test_prob_logistic(void)
{
	test_prob_logistic_pdf<double>();
	test_prob_logistic_cdf<double>();
	test_prob_logistic_inv<double>();

	test_prob_logistic_pdf<float>();
	test_prob_logistic_cdf<float>();
	test_prob_logistic_inv<float>();
}

#endif // _DEBUG

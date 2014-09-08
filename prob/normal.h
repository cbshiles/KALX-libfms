// normal.h - normal distribution
#pragma once
#include "ensure.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#endif
#ifndef M_SQRT2PI
#define M_SQRT2PI 2.50662827463100050242
#endif

namespace fms {
namespace prob {

	namespace normal {
		
		template<class X>
		inline X pdf(const X& x)
		{
			return exp(-x*x/2)/static_cast<X>(M_SQRT2PI);
		}

		template<class X>
		inline X cdf(const X& x)
		{
			return erfc(-x/M_SQRT2)/2;
		}

		// See papers/dominici-invnormal.pdf
		template<class X>
		inline X inv(const X& x)
		{
			return x;
		}
	};

} // prob
} // math

#ifdef _DEBUG

using namespace fms::prob;

template<class X>
inline void check_sqrt2()
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
inline void check_sqrt2pi()
{
	X twopi = 2*X(M_PI);

	// !!! show M_SQRT2PI is best estimate of sqrt(2*pi) !!!
}

template<class X>
inline void check_prob_pdf()
{
	ensure (normal::pdf<X>(0) == 1/M_SQRT2PI);
}

template<class X>
inline void check_prob_cdf()
{
}

template<class X>
inline void check_prob_inv()
{
}

inline void check_prob_normal()
{
	check_sqrt2<double>();
	check_sqrt2<float>();
	check_prob_pdf<double>();
	check_prob_cdf<double>();
	check_prob_inv<double>();
}

#endif // _DEBUG

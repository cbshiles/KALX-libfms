// normal.h - normal distribution
#pragma once
#include <cmath>
#include <functional>
#include <vector>
#include "ensure.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#endif
#ifndef M_SQRT2PI
#define M_SQRT2PI 2.50662827463100050242
#endif

namespace math {
namespace dist {

	namespace normal {
		template<class X>
		inline X pdf(const X& x)
		{
			return exp(-x*x/2)/static_cast<X>(M_SQRT2PI);
		}
		// Daly implementation
		template<class X>
		inline X cdf(const X& x)
		{
			// return erfc(-z(x)/M_SQRT2)/2;
			X s=x,t=0;
			double b=s,q=b*b,i=1;

			if (s < -8)
				return 0;

			if (s > 8)
				return 1;

			while (s!=t) 
				s=(t=s)+(b*=q/(i+=2));
			
			return static_cast<X>(.5+s*exp(-.5*q-.91893853320467274178L));
		}
		// See papers/dominici-invnormal.pdf
		template<class X>
		inline X inv(const X& x)
		{
			return x;
		}
	};

} // dist
} // math

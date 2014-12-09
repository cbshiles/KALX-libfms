#pragma once
#include "black.h"

namespace fms {
namespace option {

	namespace bms {

		// Black call/put option price and greeks.
		// !!!Note this *increments* the pointer values!!! Handy for portfolios.
		template<class R, class F, class S, class K, class T>
		inline auto value(R r, F s, S sigma, K k, T t, K* df = 0, K* ddf = 0, K* ds = 0, K* dt = 0)
			-> decltype(r + s + sigma + k + t)
		{
			// implement functions from final exam part 1 here!!!

			/// -5 this increments values, need to make new copies
			double bmsOV = exp(-r*t) * (black::value(exp(r*t) * s, sigma, k, t, df, ddf, ds, dt));

			*df		= *df;
			*ddf	= exp(r*t) * (*ddf);
			*ds		= exp(-r*t) * (*ds);
			/// -5 exp(-r*t) * ((*dt) - (r * bmsOV));
			*dt		= exp(-r*t) * (*dt) - (r * bmsOV);

			return bmsOV;
		}

	}
}
}

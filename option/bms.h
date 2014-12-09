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
			// Calculate forward rate according to Problem 1
			auto f = s * exp(r * t);

			// Initialize greeks
			K _df{ 0. };
			K _ddf{ 0. };
			K _ds{ 0. };
			K _dt{ 0. };

			K blackValue = fms::option::black::value(f, sigma, k, t, &_df, &_ddf, &_ds, &_dt)
			// Option value in terms of the Black model
			K bmsValue =  blackValue* exp(-r * t);

			// Delta
			*df = _df;
			// Gamma
			*ddf = _ddf * exp(r * t);
			// Vega
			*ds = _ds * exp(-r * t);
			// Theta
			*dt = exp(-r * t) * _dt - r * exp(-r * t) * bmsValue;

			return bmsValue;
		}

	}
}
}

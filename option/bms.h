#pragma once
#include "black.h"
#include <cmath>
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
			auto f = s * exp(r * t);

			K _df{ 0. }, _ddf{ 0. }, _ds{ 0. }, _dt{ 0. };
		
			K option_value = fms::option::black::value(f, sigma, k, t, &_df, &_ddf, &_ds, &_dt) * exp(-r * t);
			*df = _df;
			*ddf = _ddf * exp(r * t);
			*ds = _ds * exp(-r * t);
			*dt = exp(-r * t) * _dt - r * exp(-r * t) * option_value;
			return option_value;
		}

	}
}
}

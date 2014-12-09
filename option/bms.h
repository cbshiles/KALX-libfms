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
			auto f = exp(r*t)*s;

			K df_black = 0;
			K ddf_black = 0;
			K ds_black=0;
			K dt_black=0;

			auto v = fms::option::black::value<F, S, K, T>(f, sigma, k, t, &df_black, &ddf_black, &ds_black, &dt_black);

	

			if (df)
				*df += df_black;

			if (ddf)
				*ddf += exp(r*t)*ddf_black;

			if (ds)
				*ds += exp(-r*t)*ds_black;

			if (dt)
				*dt += exp(-r*t)*dt_black - r*exp(-r*t)*v;

			return exp(-r*t)*v;
			
		}

	}
}
}

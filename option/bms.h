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
			K df_ = 0, ddf_ = 0, ds_ = 0, dt_ = 0;
			K ert = exp(r*t);
			F f = s*ert;

			K v = fms::option::black::value(f, sigma, k, t, &df_, &ddf_, &ds_, &dt_);
		
			if (df)
				*df += df_;
			if (ddf)
				*ddf += ert*ddf_;
			if (ds)
				*ds += ds_/ert;
			if (dt)
				*dt += (dt_ - r*v)/ert;

			return v/ert;
		}

	}
}
}

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
			auto f = exp(r*t)*s;
			// -5 need to initialize to 0
			auto vol = sigma;
			auto strike = k;
			auto time = t;
			auto delta = df;
			auto gamma = ddf;
			auto vega = ds;
			auto theta = dt;

			double v = exp(-r*t)*black::value(f, vol, strike, time, delta, gamma, vega, theta);

			// -5 must assign to *df, etc
			double dBds = *df;
			double ddBdds = exp(r*t)*(*ddf);
			double dBdsigma = exp(-r*t)*(*ds);
			double dBdt = exp(-r*t)*(*dt) - r*exp(-r*t)*v;

			return v;
		}

	}
}
}

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
			/// -10 use fms::option::black instead of duplicating code
			F f;
			f = exp(r*t)*s;
			
			ensure(s >= 0);
			ensure(sigma >= 0);
			ensure(t >= 0);
			ensure(r >= 0);

			int c = 1;
			// negative strike means put
			if (k < 0) {
				c = -1;
				k = -k;
			}

			// boundary cases
			if (s == 0 || sigma == 0 || t == 0 || r == 0) {
				if (df) *df += 1.*(c*f > c*k);
				if (ddf) *ddf += f == k ? c*std::numeric_limits<K>::infinity() : 0;

				return c*f > c*k ? c*(f - k) : 0;
			}

			if (k == 0) {
				if (df) *df += 1;

				return f;
			}

			auto srt = sigma*sqrt(t);
			auto d1 = log(f / k) / srt + srt / 2;
			auto d2 = d1 - srt;
			auto Nd1 = normal::cdf<F>(c*d1);
			auto Nd2 = normal::cdf<F>(c*d2);
			K nd1{ 0 };

			if (ddf || ds || dt)
				nd1 = normal::pdf<F>(d1);

			if (df)
				*df += c*Nd1;

			if (ddf)
				*ddf += exp(r*t)*nd1 / (f*srt);

			if (ds)
				*ds += exp(-r*t)*f*srt*nd1 / sigma;

			if (dt)
				*dt += -exp(-r*t)*f*srt*nd1 / (2 * t) - r*exp(-r*t)*c*(f*Nd1 - k*Nd2);

			return exp(-r*t)*c*(f*Nd1 - k*Nd2);

		}

	}
}
}

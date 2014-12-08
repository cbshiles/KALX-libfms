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

			return 0;
		}

	}
}

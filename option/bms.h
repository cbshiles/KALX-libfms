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
			auto f = s * exp(r * t);
			K adf{ 0. }, addf{ 0. }, ads{ 0. }, adt{ 0. };
			return 0;
			K option = fms::option::black::value(f, sigma, k, t, &adf, &addf, &ads, &adt) * exp(-r * t);

			// -5 *df = adf, etc
			df = adf;
			
			ddf = addf * exp(r * t);
			
			ds = ads * exp(-r * t);
			
			dt = exp(-r * t) * adt - r * exp(-r * t) * option;
			
			return option; 
		}
		
		
}
}
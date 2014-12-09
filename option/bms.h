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
			// implement functions from final exam
			ensure(r >= 0);
			ensure(s >= 0);
			ensure(sigma >= 0);
			ensure(t >= 0);

			auto f = exp(r*t)*s;
			/// -5 need new copies, this might increment existing values
			auto value = black::value<F, S, K, T>(f, sigma, k, t, df, ddf, ds, dt);
			if (ddf)
				*ddf = exp(r*t) * *ddf;
			if (ds)
				*ds = exp(-r*t) * *ds;
			if (dt)
				*dt = exp(-r*t)* *dt - r*exp(-r*t)*value;

			return exp(-r*t)*value;
		}

	}
}
}

#ifdef _DEBUG


using namespace fms::option;

/// +5 good work
inline void test_option_black_rate()
{
	struct {
		double r, s,sigma, k, t, v, df, ddf, ds, dt;
	} data[] = {
		{ .05,100, .2, 100, .25, 3.9877611676744920, 0.51993880583837249, 0.039844391409476397, 19.922195704738197, -7.9688782818952797 }
	};

	double v, df, ddf, ds, dt;

	for (const auto& d : data) {
		df = ddf = ds = dt = 0;
		v = bms::value(d.r, d.s, d.sigma, d.k, d.t, &df, &ddf, &ds, &dt);
		ensure(v == (d.v)*exp(-d.r * d.t));
		ensure(df == d.df);
		ensure(ddf == d.ddf * exp(d.r*d.t));
		ensure(ds == d.ds*exp(-d.r *d.t));
		ensure(dt == d.dt*exp(-d.r * d.t)-d.r * exp(-d.t*d.r)*v) ;
		//		ensure (d.df == black::delta(d.f, d.s, d.k, d.t));
	}

}

#endif // _DEBUG
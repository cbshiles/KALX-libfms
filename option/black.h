// black.h - Fischer Black forward value and greeks
#pragma once
#include "ensure.h"
#include "../prob/normal.h"

namespace fms {
namespace option {

	namespace black {

		// Black call/put option price and greeks.
		// !!!Note this *increments* the pointer values!!! Handy for portfolios.
		template<class F, class S, class K, class T>
		inline auto value(F f, S s, K k, T t, K* df = 0, K* ddf = 0, K* ds = 0, K* dt = 0)
			-> decltype(f + s + k + t)
		{
			using namespace fms::prob;

			ensure (f >= 0);
			ensure (s >= 0);
			ensure (t >= 0);

			int c = 1;
			// negative strike means put
			if (k < 0) {
				c = -1;
				k = -k;
			}

			// boundary cases
			if (f == 0 || s == 0 || t == 0) {
				if (df) *df += 1.*(c*f > c*k);
				if (ddf) *ddf += 0; // really delta function at k

				return c*f > c*k ? c*(f - k) : 0;
			}

			if (k == 0) {
				if (df) *df += 1;

				return f;
			}

			auto srt = s*sqrt(t);
			auto d1 = log(f/k)/srt + srt/2;
			auto d2 = d1 - srt;
			auto Nd1 = normal::cdf<F>(c*d1);
			auto Nd2 = normal::cdf<F>(c*d2);
			K nd1{0};

			if (ddf || ds || dt)
				nd1 = normal::pdf<F>(d1);

			if (df)
				*df += c*Nd1;

			if (ddf)
				*ddf += nd1/(f*srt);

			if (ds)
				*ds += f*srt*nd1/s;

			if (dt)
				*dt += -f*srt*nd1/(2*t); // negative of dv/dt

			return c*(f*Nd1 - k*Nd2);
		}

	} // black
} // option
} // fms

#ifdef _DEBUG

using namespace fms::option;


inline void test_option_black()
{
	struct {
		double f, s, k, t, v, df, ddf, ds, dt;
	} data [] = {
	{ 100, .2, 100, .25, 3.9877748080386084, 0.519938874040193, 0.39844391409476404, 19.9221957047382, -7.968878281895281}
	};
	
	double v, df, ddf, ds, dt;

	for (const auto& d : data) {
		df = ddf = ds = dt = 0;
		v = black::value(d.f, d.s, d.k, d.t, &df, &ddf, &ds, &dt);
		ensure (v == d.v);
		ensure (df == d.df);
		ensure (ddf == d.ddf);
		ensure (ds == d.ds);
		ensure (dt == d.dt);
	}
}

#endif // _DEBUG
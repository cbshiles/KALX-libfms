// black.h - Fischer Black forward value and greeks
#pragma once
#include <limits>
#include "prob/normal.h"

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
				if (ddf) *ddf += f == k ? c*std::numeric_limits<K>::infinity() : 0;

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

		template<class X>
		inline X vega(const X& f, const X& s, const X& k, const X& t)
		{
			X ds{0};

			value<X,X,X,X>(f, s, k, t, 0, 0, &ds);

			return ds;
		}

		// Find the volatility given the option price.
		template<class X>
		inline X implied_volatility(const X& f, const X& p, const X& k, const X& t)
		{
			// ensure price in 0 - infty vol range
			ensure (t > 0);
			ensure (k > 0 ? p > (std::max)(f - k, X(0)) : p > (std::max)(-k - f, X(0)));
			ensure (k > 0 ? p < f : p < -k);

			auto F = [f,p,k,t](const X& s) -> X { return black::value(f, s, k, t) - p; };
			auto dF = [f,p,k,t](const X& s) -> X{ return black::vega(f, s, k, t); };

			return fms::root1d::find::newton<X,X>(0.2, F, dF);
		}

		// Find the forward given the option price.
		template<class X>
		inline X implied_forward(const X& p, const X& s, const X& k, const X& t)
		{
			ensure (t > 0);
			ensure (s > 0);
			ensure (p > 0)
			ensure (K > 0 ? TRUE : p < -k)

			auto F = [s, p, k, t](const X& f) -> X { return black::value(f, s, k, t) - p; };
			auto dF = [s, p, k, t](const X& f) -> X{ return black::delta(f, s, k, t); };

			return fms::root1d::find::newton<X, X>(0.2, F, dF);
			//!!!zoewangforest
		}
	} // black
	// Black-Scholes/Merton
	// bsm(r, s, vol, strike, exp) = e^{-rt}black(s*exp(r*t), ....)
} // option
} // fms

#ifdef _DEBUG
#include <algorithm>
#include <random>

using namespace fms::option;


inline void test_option_black(int N = 1000)
{
	struct {
		double f, s, k, t, v, df, ddf, ds, dt;
	} data [] = {
		{ 100, .2, 100, .25, 3.9877611676744920, 0.51993880583837249, 0.039844391409476397, 19.922195704738197, -7.9688782818952797 }
		// add more tests!!!
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

//		ensure (d.df == black::delta(d.f, d.s, d.k, d.t));
	}

	std::default_random_engine e;
	std::normal_distribution<double> X(0,1);

	double f{100}, s{.2}, k{100}, t{.25};
	double c{0}, p{0};
	double srt = s*sqrt(t);

	for (int n = 1; n < N; ++n) {
		double F = f*exp(-srt*srt/2 + srt*X(e));
		double v = (std::max)(F - k, 0.);
		c += (v - c)/n; // call mean
		v = (std::max)(k - F, 0.);
		p += (v - p)/n; // put mean
	}

	ensure (fabs(c - black::value(f, s, k, t)) < 2*c/sqrt(N));
	ensure (fabs(p - black::value(f, s, -k, t)) < 2*p/sqrt(N));
}

#endif // _DEBUG
// black.h - Fischer Black forward value and greeks
#pragma once
#include "ensure.h"
#include "../prob/normal.h"

namespace fms {
namespace option {

	namespace black {
		// Black put value given forward, volatilty, strike and expiration
		inline double value(double f, double s, double k, double t)
		{
			using namespace fms::prob;

			auto srt = s*sqrt(t);
			auto z = log(k/f)/srt - srt/2;

			return -k*normal::cdf(z) + f*normal::cdf(z + srt);
		}
		// dv/df
		inline double delta(double f, double s, double k, double t)
		{
			return 0;
		}
		// d^2v/df^2
		inline double gamma(double f, double s, double k, double t)
		{
			return 0;
		}
		// dv/ds
		inline double sigma(double f, double s, double k, double t)
		{
			return 0;
		}
		// dv/dt
		inline double theta(double f, double s, double k, double t)
		{
			return 0;
		}

	} // black
} // option
} // fms

#ifdef _DEBUG

using namespace fms::option;

inline void test_option_black()
{
	// value
	ensure (3.9877611676744920 == black::value(100, .2, 100, .25));
}

#endif // _DEBUG
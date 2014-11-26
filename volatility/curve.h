// curve.h - fit a volatiltiy curve
#pragma once
#include <tuple>
#include <vector>
#include "../mkl/trnlsp.h"

namespace fms {

	namespace volatility {

		template<class X = double>
		inline X gatheral_svi(X a, X b, X sigma, X rho, X m, X k)
		{
			return a + b*(rho*(k - m) + sqrt((k - m)*(k - m) + sigma*sigma));
		}

		template<class X = double>
		inline X kalx_svi(X z, X sigma, X m, X dm, X d)
		{
			return sigma*sigma + m*z + dm*(sqrt(z*z + d*d) - d);
		}
		
		// fit data to total variance curve
		// returns {s,m,dm,d}
		template<class X>
		std::vector<X> kalx_svi_fit(X f, const std::vector<X>& w, const std::vector<X>& k, X t, X s, X m, X dm, X d)
		{
			ensure (w.size() == k.size());

			auto F = [f,&w,&k](const std::vector<X>& x) {
				ensure (x.size() == 4);

				std::vector<X> y(w.size());

				for (size_t i = 0; i < y.size(); ++i) {
					y[i] = w[i] - kalx_svi(log(k[i]/f), x[0], x[1], x[2], x[3]);
				}

				return y;
			};
			// !!!calculate explicitly
			auto dF = mkl::jacobian<double>(4, w.size(), F);

			X x[4];
			x[0] = s;
			x[1] = m;
			x[2] = dm;
			x[3] = d;
			
			return mkl::trnlsp<>(4, w.size(), x).function(F).jacobian(dF).find();
		}

	} // volatility

} // fms

#ifdef _DEBUG

using namespace fms;

inline void test_volatility_kalx_svi_fit()
{
	double f = 100, t = 1;
	std::vector<double> w(5), k(5);

	for (size_t i = 0; i < w.size(); ++i) {
		w[i] = .2*.2*t;
		k[i] = 80 + i*10;
	}

	auto y = volatility::kalx_svi_fit<>(f, w, k, t, .2, 0., 0., 0.);

	ensure (y[0] == w[0]);
}

inline void test_volatility_curve(void)
{
	test_volatility_kalx_svi_fit();
}
#endif // _DEBUG
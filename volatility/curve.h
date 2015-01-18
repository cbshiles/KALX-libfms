// curve.h - fit a volatiltiy curve
#pragma once
#include <tuple>
#include <vector>
//#include "../mkl/trnlsp.h"

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
#if 0
		template<class X = double>
		inline std::vector<X> kalx_svi_jacobian(X z, const std::vector<X>& x)
		{
			ensure (x.size() == 4);

			X sigma = x[0];
			X m = x[1];
			X dm = x[2];
			X d = x[3];

			std::vector<X>& y(4);

			y[0] = 2*sigma;
			y[1] = z;
			y[2] = sqrt(z*z + d*d) - d;
			y[3] = dm*(d/sqrt(z*z + d*d) - 1);

			return y;
		}
		
		// fit data to total variance curve
		// returns {s,m,dm,d}
		template<class X>
		std::vector<X> kalx_svi_fit(X f, const std::vector<X>& w, const std::vector<X>& k, X s, X m, X dm, X d)
		{
			ensure (w.size() == k.size());

			auto F = [f,&w,&k](const std::vector<X>& x) {
				ensure (x.size() == 4);

				std::vector<X> y(w.size());

				for (size_t i = 0; i < y.size(); ++i) {
					y[i] = kalx_svi(log(k[i]/f), x[0], x[1], x[2], x[3]) - w[i];
				}

				return y;
			};
			// !!!calculate explicitly
			auto dF = mkl::jacobian<double>(4,static_cast<int> (w.size()), F);

			X x[4];
			x[0] = s;
			x[1] = m;
			x[2] = dm;
			x[3] = d;
			
			return mkl::trnlsp<>(4, static_cast<int>(w.size()), x).function(F).jacobian(dF).find();
		}
#endif
	} // volatility

} // fms

#ifdef _DEBUG

using namespace fms;
inline void test_volatility_curve(void)
{
	
}
#endif // _DEBUG
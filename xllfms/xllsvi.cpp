// xllsvi.cpp - Stochastic Volatility Inspired volatility curve
#include "mkl/xllmkl.h"
#include "../volatility/curve.h"
 
using namespace fms;
using namespace xll;

static AddInX xai_gatheral_svi(
	FunctionX(XLL_DOUBLEX, _T("?xll_gatheral_svi"), _T("VOLATILITY.GATHERAL.SVI"))
	.Num(_T("a"), _T("is a."), 0.04)
	.Num(_T("b"), _T("is b."), 0.4)
	.Num(_T("sigma"), _T("is sigma."), 0.1)
	.Num(_T("rho"), _T("is rho."), -0.4)
	.Num(_T("m"), _T("is m."), 0)
	.Num(_T("k"), _T("is k. "), 0)
	.Category(CATEGORY)
	.FunctionHelp(_T("Gatheral's stochastic volatility inspired formula for the square of implied volatility."))
	.Documentation("")
);
double WINAPI
xll_gatheral_svi(double a, double b, double sigma, double rho, double m, double k)
{
#pragma XLLEXPORT

	return a + b*(rho*(k - m) + sqrt((k - m)*(k - m) + sigma*sigma));
}

static AddInX xai_kalx_svi(
	FunctionX(XLL_DOUBLEX, _T("?xll_kalx_svi"), _T("VOLATILITY.KALX.SVI"))
	.Num(_T("z"), _T("is moneyness, log k/f."))
	.Num(_T("sigma"), _T("is at-the-money Black-Scholes volatility."), 0.20)
	.Num(_T("m"), _T("is the slope at 0."), 0.01)
	.Num(_T("dm"), _T("is the slope inrcrement: m - dm as x tends to -infinity, m + dm as x tends to infinity."), -0.005)
	.Num(_T("d"), _T("is a rounding parameter."), 2)
	.Category(CATEGORY)
	.FunctionHelp(_T("Stochastic Volatility Inspired formula for the square of implied volatility."))
	.Documentation("")
);
double WINAPI
xll_kalx_svi(double z, double sigma, double m, double dm, double d)
{
#pragma XLLEXPORT

	return sigma*sigma + m*z + dm*(sqrt(z*z + d*d) - d);
}

static AddInX xai_kalx_svi_fit(
	FunctionX(XLL_FPX,_T("?xll_svi_fit"),_T("VOLATILITY.KALX.SVI.FIT"))
	.Arg(XLL_DOUBLEX,_T("Forward"),_T("is an argument."))
	.Arg(XLL_FPX, _T("Variances"), _T("is an array of total variances."))
	.Arg(XLL_FPX, _T("Strikes"), _T("is an array of strikes."))
	.Arg(XLL_FPX, _T("Guess"), _T("is an array of four values as the initial parameter guess."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return parameters for KALX.SVI."))
	.Documentation(_T("Documentation."))
	);
xfp* WINAPI xll_svi_fit(double f, xfp* pk, xfp* pw, xfp* px)
{
#pragma XLLEXPORT
	static FPX o;

	try {
		ensure (size(*px) == 4);
		std::vector<double> k(begin(*pk), end(*pk)), w(begin(*pw), end(*pw));

		std::vector<double> y = volatility::kalx_svi_fit<double>(f, w, k, px->array[0], px->array[1], px->array[2], px->array[3]); 
		ensure (y.size() == 4);

		if (px->rows == 1) {
			o.resize(1, 4);
		}
		else {
			o.resize(4, 1);
		}

		std::copy(y.begin(), y.end(), o.begin()); 
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return o.get();
}

#ifdef _DEBUG

static AddInX xai_kalx_svi_function(
	FunctionX(XLL_HANDLEX,_T("?xll_kalx_svi_function"),_T("KALX.SVI.FUNCTION"))
	.Arg(XLL_DOUBLEX,_T("f"),_T("is the forward."))
	.Arg(XLL_FPX,_T("w"),_T("is an array of total variance."))
	.Arg(XLL_FPX,_T("k"),_T("is an array of strikes."))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Description."))
	.Documentation(_T("Documentation."))
	);
HANDLEX WINAPI xll_kalx_svi_function(double f, xfp* w, xfp* k)
{
#pragma XLLEXPORT

	handlex h;

	try {
		ensure (size(*w) == size(*k));

		xword n = size(*w);
		// copies to be passed into lambda
		std::vector<double> W(w->array, w->array + n);
		std::vector<double> K(k->array, k->array + n);

		handle<fun<double>> hf = new fun<double>([n,f,W,K](const vec<double>& x) {
			ensure (x.size() == 4);

			std::vector<double> y(n);
			for (xword i = 0; i < n; ++i) {
				y[i] = -W[i] + xll_kalx_svi(log(K[i]/f), x[0], x[1], x[2], x[3]);
			}

			return y; 
		});

		h = hf.get();
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_kalx_svi_jacobian(
	FunctionX(XLL_HANDLEX,_T("?xll_kalx_svi_jacobian"),_T("KALX.SVI.JACOBIAN"))
	.Arg(XLL_DOUBLEX,_T("f"),_T("is the forward."))
	.Arg(XLL_FPX,_T("w"),_T("is an array of total variance."))
	.Arg(XLL_FPX,_T("k"),_T("is an array of strikes."))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the Jacobian of {sigma, m, dm, d} -> xll_kalx_svi_function(f,w,k)({sigma, m, dm, d})"))
	.Documentation(_T("Documentation."))
	);
HANDLEX WINAPI xll_kalx_svi_jacobian(double f, xfp* w, xfp* k)
{
#pragma XLLEXPORT

	handlex h;

	try {
		ensure (size(*w) == size(*k));

		xword n = size(*w);
		// copies to be passed into lambda
		std::vector<double> W(w->array, w->array + n);
		std::vector<double> K(k->array, k->array + n);

		handle<fun<double>> hf = new fun<double>([n,f,W,K](const vec<double>& x) {
			ensure (x.size() == 4);

			double sigma = x[0];
//			double m = x[1];
			double dm = x[2];
			double d = x[3];

			std::vector<double> y(4*n); // {
			for (xword i = 0; i < n; ++i) {
			//	w(z) = sigma*sigma + m*z + dm*(sqrt(z*z + d*d) - d);
				double z = log(K[i]/f);
				y[i] = 2*sigma;
				y[n + i] = z;
				y[2*n + i] = sqrt(z*z + d*d) - d;
				y[3*n + i] = dm*(d/sqrt(z*z + d*d) - 1);
			}

			return y; 
		});

		h = hf.get();
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}


#endif // _DEBUG
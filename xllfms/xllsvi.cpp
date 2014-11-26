// xllsvi.cpp - Stochastic Volatility Inspired volatility curve
#include "xllfms.h"
 
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


static AddInX xai_svi_fit(
	FunctionX(XLL_LPOPERX,_T("?xll_svi_fit"),_T("XLL.svi_fit"))
	.Arg(XLL_DOUBLEX,_T("Forward"),_T("is an argument."))
	.Arg(XLL_DOUBLEX,_T("Expiration"),_T("is an argument."))
	.Arg(XLL_FPX, _T("Strikes"), _T("is an array of strikes."))
	.Arg(XLL_FPX, _T("Prices"), _T("is an array of prices."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Description."))
	.Documentation(_T("Documentation."))
	);
LPOPERX WINAPI xll_svi_fit(double f, double t, xfp* k, xfp* p)
{
#pragma XLLEXPORT
	static OPERX o;

	try {
		o = arg;
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		o = OPERX(xlerr::Num);
	}

	return &o;
}

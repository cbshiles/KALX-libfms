// xllblack.cpp - Black values and greeks
#include "xllfms.h"
#include "../option/black.h"

using namespace xll;
using namespace fms::option;

static AddInX xai_option_black_value(
	FunctionX(XLL_FPX,_T("?xll_option_black_value"),_T("OPTION.BLACK.VALUE"))
	.Arg(XLL_DOUBLEX,_T("Forward"),_T("is the underlying forward value."))
	.Arg(XLL_DOUBLEX,_T("Volatility"),_T("is the underlying volatility."))
	.Arg(XLL_DOUBLEX,_T("Strike"),_T("is the put option strike price."))
	.Arg(XLL_DOUBLEX,_T("Expiration"),_T("is the put option expiration in years."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return 5 column array of Black forward value, delta, gamma, vega, and theta."))
);
xfp* WINAPI xll_option_black_value(double f, double s, double k, double t)
{
#pragma XLLEXPORT
	static FPX o(1,5);

	try {
		o = 0;
		o[0] = black::value(f, s, k, t, &o[1], &o[2], &o[3], &o[4]);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0; // #NUM!
	}

	return o.get();
}

static AddInX xai_option_black_implied_volatility(
	FunctionX(XLL_DOUBLEX,_T("?xll_option_black_implied_volatility"),_T("OPTION.BLACK.IMPLIED.VOLATILITY"))
	.Arg(XLL_DOUBLEX,_T("Forward"),_T("is the underlying forward value."))
	.Arg(XLL_DOUBLEX,_T("Price"),_T("is the option price."))
	.Arg(XLL_DOUBLEX,_T("Strike"),_T("is the put option strike price."))
	.Arg(XLL_DOUBLEX,_T("Expiration"),_T("is the put option expiration in years."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the implied volatility."))
);
double WINAPI xll_option_black_implied_volatility(double f, double p, double k, double t)
{
#pragma XLLEXPORT
	double s{std::numeric_limits<double>::quiet_NaN()};

	try {
		s = black::implied_volatility(f, p, k, t);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return s;
}

static AddInX xai_gatheral_svi(
	FunctionX(XLL_DOUBLEX, _T("?xll_gatheral_svi"), _T("GATHERAL.SVI"))
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
	FunctionX(XLL_DOUBLEX, _T("?xll_kalx_svi"), _T("KALX.SVI"))
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


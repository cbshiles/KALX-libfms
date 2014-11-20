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
	.Arg(XLL_DOUBLEX, _T("_Volatility"), _T("is an optional initial guess for the implied volatility. Default is 0.2"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the implied volatility."))
);
double WINAPI xll_option_black_implied_volatility(double f, double p, double k, double t, double s0)
{
#pragma XLLEXPORT
	double s{std::numeric_limits<double>::quiet_NaN()};

	try {
		if (s0 == 0)
			s0 = 0.2;

		s = black::implied_volatility(f, p, k, t, s0);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return s;
}


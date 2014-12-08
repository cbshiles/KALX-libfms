// xllbms.cpp - Black-Merton-Scholes values and greeks
#include "xllfms.h"
#include "../option/bms.h"

using namespace xll;
using namespace fms::option;

//!!! copy and pasted from black.h
//!!! change black to bms and add interest rate argument
//!!! call fms::option::bms::value instead of fms::option::black::value

static AddInX xai_option_bms_value(
	FunctionX(XLL_FPX,_T("?xll_option_bms_value"),_T("OPTION.BMS.VALUE"))
	.Arg(XLL_DOUBLEX,_T("Rate"), _T("is the continuously compounded interest rate."))
	.Arg(XLL_DOUBLEX,_T("Spot"),_T("is the underlying spot value."))
	.Arg(XLL_DOUBLEX,_T("Volatility"),_T("is the underlying volatility."))
	.Arg(XLL_DOUBLEX,_T("Strike"),_T("is the put option strike price."))
	.Arg(XLL_DOUBLEX,_T("Expiration"),_T("is the put option expiration in years."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return 5 column array of bms value, delta, gamma, vega, and theta."))
);
xfp* WINAPI xll_option_bms_value(double r, double s, double sigma, double k, double t)
{
#pragma XLLEXPORT
	static FPX o(1,5);

	try {
		o = 0;
		o[0] = bms::value(r, s, sigma, k, t, &o[1], &o[2], &o[3], &o[4]);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0; // #NUM!
	}

	return o.get();
}


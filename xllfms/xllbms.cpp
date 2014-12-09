// xllbms.cpp - Black-Merton-Scholes values and greeks
#include "xllfms.h"
#include "../option/bms.h"

using namespace xll;
using namespace fms::option;

//!!! copy and pasted from black.h
//!!! change black to bms and add interest rate argument
//!!! call fms::option::bms::value instead of fms::option::black::value

// -5 change to xai_option_bms_value, etc
static AddInX xai_option_black_value(
	FunctionX(XLL_FPX,_T("?xll_option_black_value"),_T("OPTION.BLACK.VALUE"))
	// -5 add Rate argument
	.Arg(XLL_DOUBLEX,_T("Forward"),_T("is the underlying forward value."))
	.Arg(XLL_DOUBLEX,_T("Volatility"),_T("is the underlying volatility."))
	.Arg(XLL_DOUBLEX,_T("Strike"),_T("is the put option strike price."))
	.Arg(XLL_DOUBLEX,_T("Expiration"),_T("is the put option expiration in years."))
	.Category(CATEGORY)
	// incorrect documentation
	.FunctionHelp(_T("Return 5 column array of Black forward value, delta, gamma, vega, and theta."))
);
xfp* WINAPI xll_option_black_value(double r, double s, double sigma, double k, double t)
{
#pragma XLLEXPORT
	static FPX o(1,5);

	try {

		double dBds, ddBdds, dBdsigma, dBdt;

		// -10 returns uninitialized variables
		o[0] = bms::value(r, s, sigma, k, t);
		o[1] = dBds;
		o[2] = ddBdds;
		o[3] = dBdsigma;
		o[4] = dBdt;

	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0; // #NUM!
	}

	return o.get();
}


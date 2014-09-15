// xllblack.cpp - Black values and greeks
#include "xllfms.h"
#include "../option/black.h"

using namespace xll;
using namespace fms::option;

static AddInX xai_option_black_value(
	FunctionX(XLL_LPOPERX,_T("?xll_option_black_value"),_T("OPTION.BLACK.VALUE"))
	.Arg(XLL_DOUBLEX,_T("Forward"),_T("is the underlying forward value."))
	.Arg(XLL_DOUBLEX,_T("Volatility"),_T("is the underlying volatility."))
	.Arg(XLL_DOUBLEX,_T("Strike"),_T("is the put option strike price."))
	.Arg(XLL_DOUBLEX,_T("Expiration"),_T("is the put option expiration in years."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the Black put forward value."))
);
LPOPERX WINAPI xll_option_black_value(double f, double s, double k, double t)
{
#pragma XLLEXPORT
	static OPERX o;

	try {
		o = black::value(f, s, k, t);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		o = OPERX(xlerr::Num);
	}

	return &o;
}

//!!! implement the following add-ins !!!
//static AddInX xai_option_black_delta(
//static AddInX xai_option_black_gamma(
//static AddInX xai_option_black_vega(
//static AddInX xai_option_black_theta(

// xllpwflat.cpp - peicewise flat curves
#include "../curve/pwflat.h"
#include "xllfms.h"

using namespace xll;
using namespace fms::pwflat;

static AddInX xai_pwflat_value(
	FunctionX(XLL_DOUBLEX, _T("?xll_pwflat_value"), _T("PWFLAT.VALUE"))
	.Arg(XLL_DOUBLEX, _T("Time"), _T("is time at which the piecewise constant curve is to be evaluated"))
	.Arg(XLL_FPX, _T("Times"), _T("is an array of times"))
	.Arg(XLL_FPX, _T("Forwards"), _T("is an array of forwards"))
	.Arg(XLL_DOUBLEX, _T("_Extrapolate"), _T("is an optional value used to extrapolate. Default is 0"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Evaluate a piecewise flat curve at Time."))
);
double WINAPI xll_pwflat_value(double t, xfp* pt, xfp* pf, double f_)
{
#pragma XLLEXPORT
	double v{std::numeric_limits<double>::quiet_NaN()};

	try {
		ensure (size(*pt) == size(*pt));

		v = value(t, size(*pt), pt->array, pf->array, f_);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return v;
}

// static AddInX xai_pwflat_integral( // zoewangforest
// static AddInX xai_pwflat_spot( // zzx5008 
// static AddInX xai_pwflat_discount(

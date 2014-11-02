// xllpwflat.cpp - peicewise flat curves
#include "xllfms.h"
#include "curve/pwflat.h"

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


static AddInX xai_pwflat_integral( //!!! zoewangforest
	FunctionX(XLL_DOUBLEX, _T("?xll_pwflat_integral"), _T("PWFLAT.INTEGRAL"))
	.Arg(XLL_DOUBLEX, _T("Time"), _T("is the upper bound of the integral"))
	.Arg(XLL_FPX, _T("Times"), _T("is an array of times"))
	.Arg(XLL_FPX, _T("Forwards"), _T("is an array of forwards"))
	.Arg(XLL_DOUBLEX, __T("_Extrapolate"), _T("is an optional value used to extrapolate. Default is 0"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Integrate a piecewise flat curve from zero to Time."))
	);
double WINAPI xll_pwflat_integral(double u, xfp* pt, xfp* pf, double f_)
{
#pragma XLLEXPORT
	double I{ std::numeric_limits<double>::quiet_NaN() };

	try {
		ensure(size(*pt) == size(*pt));

		I = integral(u, size(*pt), pt->array, pf->array, f_);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return I;
}

static AddInX xai_pwflat_discount( //!!!jl2372
	FunctionX(XLL_DOUBLEX, _T("?xll_pwflat_discount"), _T("PWFLAT.DISCOUNT"))
	.Arg(XLL_DOUBLEX, _T("Time"), _T("is time at which the discount of the piecewise constant curve is to be evaluated"))
	.Arg(XLL_FPX, _T("Times"), _T("is an array of times"))
	.Arg(XLL_FPX, _T("Forwards"), _T("is an array of forwards"))
	.Arg(XLL_DOUBLEX, _T("_Extrapolate"), _T("is an optional value used to extrapolate. Default is 0"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Evaluates the discount value of a piecewise flat curve at Time."))
	);
double WINAPI xll_pwflat_discount(double t, xfp* pt, xfp* pf, double f_)
{
#pragma XLLEXPORT
	double d{ std::numeric_limits<double>::quiet_NaN() };

	try {
		ensure(size(*pt) == size(*pt));

		d = discount(t, size(*pt), pt->array, pf->array, f_);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return d;
}


//!!!zzx5008 
static AddInX xai_pwflat_spot(
FunctionX(XLL_DOUBLEX, _T("?xll_pwflat_spot"), _T("PWFLAT.SPOT"))
.Arg(XLL_DOUBLEX, _T("Time"), _T("is time at which the piecewise constant curve is to be evaluated"))
.Arg(XLL_FPX, _T("Times"), _T("is an array of times"))
.Arg(XLL_FPX, _T("Forwards"), _T("is an array of forwards"))
.Arg(XLL_DOUBLEX, _T("_Extrapolate"), _T("is an optional value used to extrapolate. Default is 0"))
.Category(CATEGORY)
.FunctionHelp(_T("Return continuously compounded spot rate at Time."))
);
double WINAPI xll_pwflat_spot(double t, xfp* pt, xfp* pf, double f_)
{
#pragma XLLEXPORT
	double s{ std::numeric_limits<double>::quiet_NaN() };

	try {
		ensure(size(*pt) == size(*pt));

		s = spot<double,double>(t, size(*pt), pt->array, pf->array, f_);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return s;
}

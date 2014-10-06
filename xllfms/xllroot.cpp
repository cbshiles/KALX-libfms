// xllroot.cpp - root finding routines
#include "xllfms.h"
#include "../root/root1d.h"

using namespace xll;
using namespace fms::root1d;

static AddInX xai_root1d_step_inverse_quadratic(
	FunctionX(XLL_DOUBLEX,_T("?xll_root1d_step_inverse_quadratic"),_T("ROOT1D.STEP.INVERSE_QUADRATIC"))
	.Arg(XLL_FPX,_T("x0"),_T("is the abscissa of a point in the x-y plane."))
	.Arg(XLL_DOUBLEX,_T("y0"),_T("is the ordinant of a point in the x-y plane."))
	.Arg(XLL_DOUBLEX,_T("x1"),_T("is the abscissa of a point in the x-y plane."))
	.Arg(XLL_DOUBLEX,_T("y1"),_T("is the ordinant of a point in the x-y plane."))
	.Arg(XLL_DOUBLEX,_T("x2"),_T("is the abscissa of a point in the x-y plane."))
	.Arg(XLL_DOUBLEX,_T("y2"),_T("is the ordinant of a point in the x-y plane."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the root of an inverse quadratic containing the three points."))
);
double WINAPI xll_root1d_step_inverse_quadratic(xfp* x0, double y0, double x1, double y1, double x2, double y2)
{
#pragma XLLEXPORT
	double x{std::numeric_limits<double>::quiet_NaN()};

	try {
		if (size(*x0) != 1) {
			ensure (size(*x0) == 6);
			y0 = x0->array[1];
			x1 = x0->array[2];
			y1 = x0->array[3];
			x2 = x0->array[4];
			y2 = x0->array[5];
		}

		x = step::inverse_quadratic(x0->array[0], y0, x1, y1, x2, y2);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

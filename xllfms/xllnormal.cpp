// xllnormal.cpp - normal distribution
#include "xllfms.h"
#include "../prob/normal.h"

using namespace xll;
using namespace fms::prob;

static AddInX xai_prob_normal_pdf(
	FunctionX(XLL_DOUBLEX,_T("?xll_prob_normal_pdf"),_T("PROB.NORMAL.PDF"))
	.Arg(XLL_DOUBLEX,_T("x"),_T("is a number."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the standard normal probability density function at x."))
);
double WINAPI xll_prob_normal_pdf(double x)
{
#pragma XLLEXPORT

	return normal::pdf(x);
}

static AddInX xai_prob_normal_cdf(
	FunctionX(XLL_DOUBLEX,_T("?xll_prob_normal_cdf"),_T("PROB.NORMAL.CDF"))
	.Arg(XLL_DOUBLEX,_T("x"),_T("is a number."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the standard normal cumulative probability distribution at x."))
);
double WINAPI xll_prob_normal_cdf(double x)
{
#pragma XLLEXPORT

	return normal::cdf(x);
}

static AddInX xai_prob_normal_inv(
	FunctionX(XLL_LPOPERX, _T("?xll_prob_normal_inv"), _T("PROB.NORMAL.INV"))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is a probability."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the inverse of the standard normal distribution."))
);
LPOPERX WINAPI xll_prob_normal_inv(double p)
{
#pragma XLLEXPORT
	static OPERX o;

	try {
		o = normal::inv(p);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		o = OPERX(xlerr::Num);
	}

	return &o;
}

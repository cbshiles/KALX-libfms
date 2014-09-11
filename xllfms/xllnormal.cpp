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
static AddInX xai_prob_normal_cdf_logistic(
	FunctionX(XLL_DOUBLEX,_T("?xll_prob_normal_cdf_logistic"),_T("PROB.NORMAL.CDF.LOGISTIC"))
	.Arg(XLL_DOUBLEX,_T("x"),_T("is a number."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the standard normal cumulative probability distribution at x."))
);
double WINAPI xll_prob_normal_cdf_logistic(double x)
{
#pragma XLLEXPORT

	return normal::cdf_logistic(x);
}

static AddIn xai_prob_normal_inv(
	FunctionX(XLL_LPOPER,"?xll_prob_normal_inv","PROB.NORMAL.INV")
	.Arg(XLL_DOUBLE,"p","is a probability.")
	.Category(CATEGORY)
	.FunctionHelp("Return the inverse of the standard normal distribution.")
);
LPOPER WINAPI xll_prob_normal_inv(double p)
{
#pragma XLLEXPORT
	static OPER o;

	try {
		o = normal::inv(p);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		o = OPER(xlerr::Num);
	}

	return &o;
}
static AddIn xai_prob_normal_inv_logistic(
	FunctionX(XLL_LPOPER,"?xll_prob_normal_inv_logistic","PROB.NORMAL.INV.LOGISTIC")
	.Arg(XLL_DOUBLE,"p","is a probability.")
	.Category(CATEGORY)
	.FunctionHelp("Return the inverse of the standard normal distribution using the logistic approximation.")
);
LPOPER WINAPI xll_prob_normal_inv_logistic(double p)
{
#pragma XLLEXPORT
	static OPER o;

	try {
		o = normal::inv_logistic(p);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		o = OPER(xlerr::Num);
	}

	return &o;
}

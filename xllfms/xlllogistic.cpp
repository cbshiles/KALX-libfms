// logistic.cpp - logistic probability distribution
#include "xllfms.h"
#include "../prob/logistic.h"

using namespace xll;

static AddInX xai_prob_logistic_pdf(
	FunctionX(XLL_DOUBLEX,_T("?xll_prob_logistic_pdf"),_T("PROB.LOGISTIC.PDF"))
	.Arg(XLL_DOUBLEX,_T("x"),_T("is a number."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the logistic probability distribution at x."))
);
double WINAPI xll_prob_logistic_pdf(double x)
{
#pragma XLLEXPORT

	return logistic::pdf(x);
}

static AddInX xai_prob_logistic_cdf(
	FunctionX(XLL_DOUBLEX,_T("?xll_prob_logistic_cdf"),_T("PROB.LOGISTIC.CDF"))
	.Arg(XLL_DOUBLEX,_T("x"),_T("is a number."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the logistic probability distribution at x."))
);
double WINAPI xll_prob_logistic_cdf(double x)
{
#pragma XLLEXPORT

	return logistic::cdf(x);
}

static AddIn xai_prob_logistic_inv(
	FunctionX(XLL_LPOPER,"?xll_prob_logistic_inv","PROB.LOGISTIC.INV")
	.Arg(XLL_DOUBLE,"p","is a probability.")
	.Category(CATEGORY)
	.FunctionHelp("Return the inverse of the standard normal distribution using the logistic approximation.")
);
LPOPER WINAPI xll_prob_logistic_inv(double p)
{
#pragma XLLEXPORT
	static OPER o;

	try {
		o = logistic::inv(p);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		o = OPER(xlerr::Num);
	}

	return &o;
}

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

static AddInX xai_prob_normal_correlated(
	FunctionX(XLL_FPX, _T("?xll_prob_normal_correlated"), _T("PROB.NORMAL.CORRELATED"))
	.Arg(XLL_WORD, _T("Size"), _T("is the number of correlated standard normal variates to generate."))
	.Arg(XLL_WORD, _T("Dimension"), _T("is the dimension of the correlation vectors."))
	.Arg(XLL_FPX, _T("Rho"), _T("is a lower diagonal matrix of correlations."))
	.Volatile()
	.Category(CATEGORY)
	.FunctionHelp(_T("Packed as r_10, r_20, r21, ..., r_n-1,d-1"))
	.Documentation()
);
xfp* WINAPI xll_prob_normal_correlated(WORD n, WORD d, xfp* prho)
{
#pragma XLLEXPORT
	static FPX result;

	try {
		result.reshape(1, n);

		ensure (size(*prho) >= n*d - d*(d+1)/2);

		normal::correlated(rng(), n, d, prho->array, result.begin());
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return result.get();
}

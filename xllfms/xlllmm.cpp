// xlllmm.cpp - LIBOR Market Model
#include "xllfms.h"
#include "../curve/lmm.h"

using namespace xll;
using namespace fms::curve;

static AddInX xai_curve_lmm(
	FunctionX(XLL_HANDLEX, _T("?xll_curve_lmm"), _T("CURVE.LMM"))
	.Arg(XLL_FPX, _T("t"), _T("is an array of curve times."))
	.Arg(XLL_FPX, _T("f"), _T("is an array of futures."))
	.Arg(XLL_FPX, _T("sigma"), _T("is an array of at-the-money caplet volatilites."))
	.Arg(XLL_WORDX, _T("d"), _T("is then number of factors to use for the model."))
	.Arg(XLL_FPX, _T("rho"), _T("is an array of correlation vectors."))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns a handle to a LIBOR Market Model object."))
	.Documentation()
);
HANDLEX WINAPI xll_curve_lmm(xfp* pt, xfp* pf, xfp* psigma, WORD d, xfp* prho)
{
#pragma XLLEXPORT
	handlex h;

	try {
		xword n = size(*pt);
		ensure (size(*pf) >= n);
		ensure (size(*psigma) >= n);
		ensure (size(*prho) >= n*d - d*(d+1)/2);

		handle<lmm<>> h_{new lmm<>(n, pt->array, pf->array, psigma->array, d, prho->array)};

		h = h_.get();

	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_curve_lmm_next(
	FunctionX(XLL_HANDLEX, _T("?xll_curve_lmm_next"), _T("CURVE.LMM.NEXT"))
	.Arg(XLL_HANDLEX, _T("Handle"), _T("is a handle returned by CURVE.LMM."))
	.Volatile()
	.Category(CATEGORY)
	.FunctionHelp(_T("Advance index by one step."))
	.Documentation()
);
HANDLEX WINAPI xll_curve_lmm_next(HANDLEX h)
{
#pragma XLLEXPORT
	try {
		handle<lmm<>> h_(h);

		h_->next(rng());

	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return handlex{};
	}

	return h;
}

static AddInX xai_curve_lmm_reset(
	FunctionX(XLL_HANDLEX, _T("?xll_curve_lmm_reset"), _T("CURVE.LMM.RESET"))
	.Arg(XLL_HANDLEX, _T("Handle"), _T("is a handle returned by CURVE.LMM."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Advance index by one step."))
	.Documentation()
);
HANDLEX WINAPI xll_curve_lmm_reset(HANDLEX h)
{
#pragma XLLEXPORT
	try {
		handle<lmm<>> h_(h);

		h_->reset();

	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return handlex{};
	}

	return h;
}

static AddInX xai_curve_lmm_to(
	FunctionX(XLL_HANDLEX, _T("?xll_curve_lmm_to"), _T("CURVE.LMM.TO"))
	.Arg(XLL_HANDLEX, _T("Handle"), _T("is a handle returned by CURVE.LMM."))
	.Arg(XLL_WORDX, _T("Index"), _T("is the time index to advance to. Default is to end of curve."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Advance index by steps."))
	.Documentation()
);
HANDLEX WINAPI xll_curve_lmm_to(HANDLEX h, WORD n)
{
#pragma XLLEXPORT
	try {
		handle<lmm<>> h_(h);

		h_->to(rng(), n);

	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return handlex{};
	}

	return h;
}

static AddInX xai_curve_lmm_forward(
	FunctionX(XLL_FPX, _T("?xll_curve_lmm_forward"), _T("CURVE.LMM.FORWARD"))
	.Arg(XLL_HANDLEX, _T("Handle"), _T("is a handle returned by CURVE.LMM."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the current forward curve."))
	.Documentation()
);
xfp* WINAPI xll_curve_lmm_forward(HANDLEX h)
{
#pragma XLLEXPORT
	static FPX result;

	try {
		handle<lmm<>> h_(h);

		const std::vector<double>& f = h_->forward();
		result.resize(1, f.size());
		std::copy(f.begin(), f.end(), result.begin());

	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return result.get();
}
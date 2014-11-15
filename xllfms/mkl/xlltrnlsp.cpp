// xlltrnlsp.cpp - non-linear least squares
#include "xllmkl.h"
#include "../../mkl/trnlsp.h"

using namespace xll;

static AddInX xai_trnlsp(
	FunctionX(XLL_FPX,_T("?xll_trnlsp"),_T("MKL.TRNLSP"))
	.Arg(XLL_HANDLEX,_T("F"),_T("is a handle to a function."))
	.Arg(XLL_LPOPERX, _T("x"), _T("is an initial guess."))
	.Arg(XLL_LPOPERX, _T("_eps"), _T("is an optional array of 6 numbers, or 0."))
	.Arg(XLL_SHORTX, _T("_iter1"), _T("is the optional number of total iterations."))
	.Arg(XLL_SHORTX, _T("_iter2"), _T("is the optional number of local iterations."))
	.Arg(XLL_DOUBLEX, _T("_rs"), _T("is the optional step size betweeen .1 and 100."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Find a value that minimizes the least squared error of a function."))
	.Documentation(_T("Documentation."))
	);
xfp* WINAPI xll_trnlsp(HANDLEX f, LPOPERX px, LPOPERX peps, SHORT iter1, SHORT iter2, double rs)
{
#pragma XLLEXPORT
	static FPX x_;

	try {
		xword m = size<XLOPERX>(*px);
		xword n = size<XLOPERX>(XLL_XL_(UDF, OPERX(f), *px));
		auto F = xllmkl::vectorize(m, n, f);
		vector<double> eps(6);
		if (peps->xltype == xltypeMissing) {
			eps.assign(6, 1e-10);
		}
		else {
			std::copy(eps.begin(), eps.end(), peps->begin());
		}
		if (iter1 == 0)
			iter1 = 1000;
		if (iter2 == 0)
			iter2 = 100;
		if (rs == 0)
			rs = 1;

		vector<double> X(m);
		std::copy(px->begin(), px->end(), X.begin());

		auto X_ = trnlsp<>(m, n, &X[0], &eps[0], iter1, iter2, rs)
			.function(F)
			.jacobian(mkl::jacobian<double>(m, n, F))
			.find();

		ensure (X_.size() == m);
		if (px->rows() == 1)
			x_.resize(1, m);
		else
			x_.resize(m, 1);
		std::copy(X_.begin(), X_.end(), x_.begin());
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return x_.get();
}





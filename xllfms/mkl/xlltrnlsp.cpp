// xlltrnlsp.cpp - non-linear least squares
#include "xllmkl.h"
#include "../../mkl/trnlsp.h"

using namespace xll;

static AddInX xai_trnlsp(
	FunctionX(XLL_FPX,_T("?xll_trnlsp"),_T("MKL.TRNLSP"))
	.Arg(XLL_WORDX, _T("n"), _T("is then dimension of the range of the function."))
	.Arg(XLL_HANDLEX,_T("F"),_T("is a handle to a function."))
	.Arg(XLL_FPX, _T("x"), _T("is an initial guess."))
	.Arg(XLL_LPOPERX, _T("_eps"), _T("is an optional array of 6 numbers, or 0."))
	.Arg(XLL_SHORTX, _T("_iter1"), _T("is the optional number of total iterations."))
	.Arg(XLL_SHORTX, _T("_iter2"), _T("is the optional number of local iterations."))
	.Arg(XLL_DOUBLEX, _T("_rs"), _T("is the optional step size betweeen .1 and 100."))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Find a value that minimizes the least squared error of a function."))
	.Documentation(_T("Documentation."))
	);
xfp* WINAPI xll_trnlsp(xword n, HANDLEX f, xfp* px, LPOPERX peps, SHORT iter1, SHORT iter2, double rs)
{
#pragma XLLEXPORT
	static FPX x_;

	try {
		xword m = size(*px);
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

		auto X_ = trnlsp<>(m, n, px->array, &eps[0], iter1, iter2, rs)
			.function(F)
			.jacobian(mkl::jacobian<double>(m, n, F))
			.find();

		ensure (X_.size() == m);
		if (px->rows == 1)
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

#ifdef _DEBUG

static AddInX xai_trnlsp_init(
	FunctionX(XLL_HANDLEX,_T("?xll_trnlsp_init"),_T("MKL.TRNLSP.INIT"))
	.Arg(XLL_WORDX, _T("n"), _T("is then dimension of the range of the function."))
	.Arg(XLL_HANDLEX,_T("F"),_T("is a handle to a function."))
	.Arg(XLL_FPX, _T("x"), _T("is an initial guess."))
	.Arg(XLL_LPOPERX, _T("_eps"), _T("is an optional array of 6 numbers. Default is 1e-10."))
	.Arg(XLL_SHORTX, _T("_iter1"), _T("is the optional number of total iterations. Default is 1000."))
	.Arg(XLL_SHORTX, _T("_iter2"), _T("is the optional number of local iterations. Default is 100."))
	.Arg(XLL_DOUBLEX, _T("_rs"), _T("is the optional step size betweeen .1 and 100."))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Find a value that minimizes the least squared error of a function. Default is 1."))
	.Documentation(_T("Documentation."))
	);
HANDLEX WINAPI xll_trnlsp_init(xword n, HANDLEX f, xfp* px, LPOPERX peps, SHORT iter1, SHORT iter2, double rs)
{
#pragma XLLEXPORT
	handlex h;

	try {
		xword m = size(*px);
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

		handle<mkl::trnlsp<>> ht {new trnlsp<>(m, n, px->array, &eps[0], iter1, iter2, rs)};

		ht->function(F).jacobian(mkl::jacobian<double>(m, n, F));

		h = ht.get();
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}

static AddInX xai_trnlsp_step(
	FunctionX(XLL_FPX,_T("?xll_trnlsp_step"),_T("MKL.TRNLSP.STEP"))
	.Arg(XLL_HANDLEX,_T("Handle"),_T("is a handle returned by MKL.TRNLSP.INIT."))
	.Arg(XLL_LONGX, _T("Rci"), _T("is the reverse communication information."))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns a one row array of the new rci and handle."))
	.Documentation(_T("Documentation."))
	);
xfp* WINAPI xll_trnlsp_step(HANDLEX h, LONG rci)
{
#pragma XLLEXPORT
	static FPX hrci(1, 2);

	try {
		handle<mkl::trnlsp<>> ht(h);
		ensure (ht);

		hrci[0] = ht->step(rci);
		hrci[1] = h;
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return hrci.get();
}

static AddInX xai_trnlsp_get(
	FunctionX(XLL_FPX,_T("?xll_trnlsp_get"),_T("MKL.TRNLSP.GET"))
	.Arg(XLL_HANDLEX,_T("Handle"),_T("is a handle returned by MKL.TRNLSP.INIT."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns a one row array of the number of iterations, stopping criterion, initial residual, and final residual "))
	.Documentation(_T("Documentation."))
	);
xfp* WINAPI xll_trnlsp_get(HANDLEX h)
{
#pragma XLLEXPORT
	static FPX get(1,4);

	try {
		handle<mkl::trnlsp<>> ht(h);
		ensure (ht);

		int iter, cr;
		double ir, fr;
		ht->get(iter, cr, ir, fr);

		get[0] = iter;
		get[1] = cr;
		get[2] = ir;
		get[3] = fr;
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return get.get();
}

static AddInX xai_trnlsp_get_x(
	FunctionX(XLL_FPX,_T("?xll_trnlsp_get_x"),_T("MKL.TRNLSP.GET.X"))
	.Arg(XLL_HANDLEX,_T("Handle"),_T("is a handle returned by MKL.TRNLSP.INIT."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the current guess of minimum."))
	.Documentation(_T("Documentation."))
	);
xfp* WINAPI xll_trnlsp_get_x(HANDLEX h)
{
#pragma XLLEXPORT
	static FPX x;

	try {
		handle<mkl::trnlsp<>> ht(h);
		ensure (ht);

		x.resize(1, static_cast<xword>(ht->m));
		std::copy(ht->x.begin(), ht->x.end(), x.begin());
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return x.get();
}

static AddInX xai_trnlsp_get_f(
	FunctionX(XLL_FPX,_T("?xll_trnlsp_get_f"),_T("MKL.TRNLSP.GET.F"))
	.Arg(XLL_HANDLEX,_T("Handle"),_T("is a handle returned by MKL.TRNLSP.INIT."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the current guess of function."))
	.Documentation(_T("Documentation."))
	);
xfp* WINAPI xll_trnlsp_get_f(HANDLEX h)
{
#pragma XLLEXPORT
	static FPX f;

	try {
		handle<mkl::trnlsp<>> ht(h);
		ensure (ht);

		f.resize(1, static_cast<xword>(ht->n));
		std::copy(ht->f.begin(), ht->f.end(), f.begin());
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return f.get();
}


#endif // _DEBUG
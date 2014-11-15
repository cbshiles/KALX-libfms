// xlljacobi.cpp - Numerically estimate the Jacobian
#include "xllmkl.h"
#include "../../mkl/jacobi.h"

using namespace xll;
using namespace xllmkl;

static AddInX xai_mkl_jacobian(
	FunctionX(XLL_FPX, _T("?xll_mkl_jacobian"), _T("MKL.JACOBIAN"))
	.Arg(XLL_USHORTX, _T("M"), _T("is the number of arguments in the domain vector."))
	.Arg(XLL_USHORTX, _T("N"), _T("is the number of arguments in the range vector."))
	.Arg(XLL_HANDLEX, _T("Function"), _T("is the function whos Jacobian is to be estmated."))
	.Arg(XLL_FPX, _T("x"), _T("is the value at which to compute the Jacobian."))
	.Arg(XLL_DOUBLEX, _T("_Eps"), _T("is the optional precision of the Jacobian matrix calculation."))
	.Category(_T("MKL"))
	.FunctionHelp(_T("Return the M x N Jacobian of Function at x."))
	.Documentation(_T("Documentation."))
);
xfp* WINAPI xll_mkl_jacobian(USHORT m, USHORT n, HANDLEX f, const xfp* x, double eps)
{
#pragma XLLEXPORT
	static xll::FPX df;

	try {
		if (eps == 0)
			eps = 1e-9;

		mkl::jacobi<double> J(m, n, vectorize(m, n, f), x->array, eps);
		auto dF = J.find();

		df.resize(m, n);
		std::copy(dF.begin(), dF.end(), df.begin());
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return df.get();
}


static AddIn xai_mkl_jacobi(
	Function(XLL_HANDLE,"?xll_mkl_jacobi","MKL.JACOBI")
	.Arg(XLL_USHORT, "M", "is the number of arguments in the domain vector.")
	.Arg(XLL_USHORT, "N", "is the number of arguments in the range vector.")
	.Arg(XLL_HANDLE, "Function", "is the function whos Jacobian is to be estmated.")
	.Arg(XLL_FP, "x", "is the value at which to compute the Jacobian.")
	.Arg(XLL_DOUBLE, "Eps", "is the precision of the Jacobian matrix calculation.")
	.Uncalced()
	.Category("MKL")
	.FunctionHelp("Description.")
	.Documentation("Documentation.")
	);
HANDLEX WINAPI xll_mkl_jacobi(USHORT m, USHORT n, HANDLEX f, const xfp* x, double eps)
{
#pragma XLLEXPORT
	handlex h;

	try {
		if (eps == 0)
			eps = 1e-9;

		handle<mkl::jacobi<double>> h_{new mkl::jacobi<double>(m, n, vectorize(m, n, f), x->array, eps)};
		h = h_.get();
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}
static AddIn xai_mkl_jacobi_solve(
	Function(XLL_SHORT, "?xll_mkl_jacobi_solve","MKL.JACOBI.SOLVE")
	.Arg(XLL_HANDLE, "Jacobi", "is the Jacobian returned by MKL.JACOBI.")
	.Arg(XLL_SHORT, "Rci", "is the reverse communication interface number.")
	.Category("MKL")
	.FunctionHelp("Description.")
	.Documentation("Documentation.")
	);
SHORT WINAPI xll_mkl_jacobi_solve(HANDLEX j, SHORT rci)
{
#pragma XLLEXPORT
	try {
		handle<mkl::jacobi<double>> hj(j);
		ensure (hj);

		rci = (SHORT)hj->solve(rci);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return rci;
}
static AddIn xai_mkl_jacobi_find(
	Function(XLL_FP, "?xll_mkl_jacobi_find","MKL.JACOBI.FIND")
	.Arg(XLL_HANDLE, "Jacobi", "is a Jacobian returned by MKL.JACOBI.")
	.Arg(XLL_BOOL, "Debug", "indicates debugging info is to be returned.")
	.Category("MKL")
	.FunctionHelp("Description.")
	.Documentation("Documentation.")
	);
xfp* WINAPI xll_mkl_jacobi_find(HANDLEX j, BOOL debug)
{
#pragma XLLEXPORT
	static xll::FP dF;

	try {
		handle<mkl::jacobi<double>> hj(j);
		ensure (hj);

		if (debug) {
			dF.resize(0,0);
			int rci = 0;
			int iter = 100;
			while (iter-- && (rci = hj->solve()) > 0) {
				ensure (rci == 1 || rci == 2);
				if (rci == 1) {
					hj->f1 = hj->F(hj->x);
					dF.push_back(hj->f1.begin(), hj->f1.end(), true);
				}
				else {
					hj->f2 = hj->F(hj->x);
					dF.push_back(hj->f2.begin(), hj->f2.end(), true);
				}
			}
		}
		else {
			const std::vector<double>& df = hj->find();
			ensure (df.size() == static_cast<xword>(hj->m * hj->n));

			dF.resize((xword)hj->m, (xword)hj->n);
			std::copy(df.begin(), df.end(), dF.begin());
		}
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return dF.get();
}


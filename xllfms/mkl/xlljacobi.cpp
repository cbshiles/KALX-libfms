// xlljacobi.cpp - Numerically estimate the Jacobian
#include "../xllfms.h"
#include "../../mkl/jacobi.h"

using namespace xll;

// F(x[0], x[1]) -> (x[0]^2, x[1]^3, x[0] + x[1])
// dF(x[0], x[1]) -> {2*x[0], 0, 1; 0, 2*x[1]^2, 1}
static AddIn xai_test_function1(
	Function(XLL_LPOPER, "?xll_test_function1", "XLL.TEST.FUNCTION1")
	.Arg(XLL_LPOPER, "Arg", "is an argument.")
	.Category(CATEGORY)
	.FunctionHelp("{x[0], x[1]} -> {x[0]^2, x[1]^3, x[0] + x[1]}")
	.Documentation("Documentation.")
	);
LPOPER WINAPI xll_test_function1(const LPOPER px)
{
#pragma XLLEXPORT
	static OPER o(1,3);

	try {
		const OPER& x{*px};

		o[0] = x[0]*x[0];
		o[1] = x[1]*x[1]*x[1];
		o[2] = x[0] + x[1];
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		o = OPER(xlerr::Num);
	}

	return &o;
}


static AddIn xai_mkl_jacobi(
	FunctionX(XLL_HANDLE,"?xll_mkl_jacobi","MKL.JACOBI")
	.Arg(XLL_USHORT, "M", "is the number of arguments in the domain argument.")
	.Arg(XLL_USHORT, "N", "is the number of arguments in the range.")
	.Arg(XLL_HANDLE, "Function", "is the function whos Jacobian is to be estmated.")
	.Arg(XLL_DOUBLE, "Eps", "is the precision of the Jacobian matrix calculation.")
	.Uncalced()
	.Category("MKL")
	.FunctionHelp("Description.")
	.Documentation("Documentation.")
	);
HANDLEX WINAPI xll_mkl_jacobi(USHORT m, USHORT n, HANDLEX f, double eps)
{
#pragma XLLEXPORT
	handlex h;

	try {
		if (eps == 0)
			eps = 1e-9;

		auto F = [m,n,f](const std::vector<double>& x) {
			ensure (x.size() == m);

			OPER X(m,1);
			for (xword i = 0; i < m; ++i)
				X[i] = x[i];
		
			OPER Y = Excel<XLOPER>(xlUDF, OPER(f), x);
			ensure (Y.size() == n);

			std::vector<double> y(n);

			for (xword j = 0; j < n; ++j)
				y[j] = Y[j];
			
			return y;
		};
		handle<mkl::jacobi> h_{new mkl::jacobi(m, n, F, eps)};
		h = h_.get();
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}
static AddIn xai_mkl_jacobi_solve(
	FunctionX(XLL_LONG, "?xll_mkl_jacobi_solve","MKL.JACOBI.SOLVE")
	.Arg(XLL_HANDLE, "Jacobi", "is the Jacobian.")
	.Arg(XLL_LONG, "Rci", "is the reverse communication interface number.")
	.Category("MKL")
	.FunctionHelp("Description.")
	.Documentation("Documentation.")
	);
LONG WINAPI xll_mkl_jacobi_solve(HANDLEX j, LONG rci)
{
#pragma XLLEXPORT
	try {
		handle<mkl::jacobi> hj(j);
		ensure (hj);

		rci = hj->solve(rci);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return rci;
}
static AddIn xai_mkl_jacobi_find(
	FunctionX(XLL_FP, "?xll_mkl_jacobi_find","MKL.JACOBI.FIND")
	.Arg(XLL_HANDLE, "Function", "is the function whos Jacobian is to be estmated.")
	.Category("MKL")
	.FunctionHelp("Description.")
	.Documentation("Documentation.")
	);
xfp* WINAPI xll_mkl_jacobi_find(HANDLEX j)
{
#pragma XLLEXPORT
	static xll::FP dF;

	try {
		handle<mkl::jacobi> hj(j);
		ensure (hj);

		std::vector<double> df = hj->find();
		ensure (df.size() ==static_cast<xword>(hj->m_ * hj->n_));

		df.resize(hj->m_, hj->n_);
		std::copy(df.begin(), df.end(), dF.begin());
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return dF.get();
}


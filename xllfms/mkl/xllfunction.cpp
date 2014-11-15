// xllfunction.cpp - first class functions in Excel
#include <regex>
#include "xllmkl.h"

using namespace xll;

// F(x[0], x[1]) -> (x[0]^2, x[1]^3, x[0] + x[1])
// dF(x[0], x[1]) -> {2*x[0], 0, 1; 0, 2*x[1]^2, 1}
static AddIn xai_test_function1(
	Function(XLL_LPOPER, "?xll_test_function1", "TEST.FUNCTION1")
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
static AddIn xai_test_function2(
	Function(XLL_LPOPER, "?xll_test_function2", "TEST.FUNCTION2")
	.Arg(XLL_LPOPER, "Arg", "is an argument.")
	.Category(CATEGORY)
	.FunctionHelp("matlab example")
	.Documentation("Documentation.")
	);
LPOPER WINAPI xll_test_function2(const LPOPER px)
{
#pragma XLLEXPORT
	static OPER o(10,1);

	try {
		const OPER& x{*px};
		for (xword k = 1; k <= 10; ++k)
			o[k-1] = 2 + 2*k - exp(k*x[0]) - exp(k*x[1]);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		o = OPER(xlerr::Num);
	}

	return &o;
}

static AddInX xai_function_make(
	FunctionX(XLL_HANDLEX, _T("?xll_function_make"), _T("FUNCTION.MAKE"))
	.Arg(XLL_LPXLOPERX, _T("Range"), _T("is a reference to a range containing functions"))
	.Uncalced()
	.FunctionHelp(_T("Return a handle to a function."))
	.Category(_T("XLL"))
);
HANDLEX WINAPI xll_function_make(LPXLOPERX pf)
{
#pragma XLLEXPORT
	handlex h;

	try {
		// 6 - formula
		handle<OPERX> hf = new OPERX(XLL_XLF(GetCell, OPERX(6), *pf));

		h = hf.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_function_call(
	FunctionX(XLL_LPOPERX, _T("?xll_function_call"), _T("FUNCTION.CALL"))
	.Arg(XLL_HANDLEX, _T("Function"), _T("is a handle returned by FUNCTION.MAKE"))
	.Arg(XLL_LPOPERX, _T("Input"), _T("is a reference to the function inputs."))
	.Uncalced()
	.FunctionHelp(_T("Evaluate a function."))
	.Category(_T("XLL"))
);
LPOPERX WINAPI xll_function_call(HANDLEX f, LPOPERX px)
{
#pragma XLLEXPORT
	static OPERX y;

	try {
		handle<OPERX> hf(f);
		ensure (hf);

		// replace A1 references in f from px;
		static std::basic_regex<xchar> re(_T("\\b[A-Z]+[0-9]+\\b"));
		static std::basic_regex<xchar> eq(_T("^=(.*)$"));
		std::basic_string<xchar> s = hf->to_string();
		for (xword i = 0; i < size<XLOPERX>(*px); ++i) {
			auto v = (*px)[i].to_string();
			v = std::regex_replace(v, eq, _T("$1"));
			// match re
			// replace all occurrences
			//s = std::regex_replace(s, re, v, std::regex_constants::format_first_only);
		}
		y = XLL_XLF(Evaluate, OPERX(s));

	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		y = OPERX(xlerr::NA);
	}

	return &y;
}


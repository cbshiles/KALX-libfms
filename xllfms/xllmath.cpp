// xllmath.cpp - <cmath> functions
#include <cmath>
#include <limits>
#include "xllfms.h"

using namespace xll;

static AddInX xai_math_epsilon(
	FunctionX(XLL_DOUBLEX, _T("?xll_math_epsilon"), _T("MATH.EPSILON"))
	.Category(CATEGORY)
	.FunctionHelp(_T("The difference between 1 and the smallest value greater than 1 that is representable as a double."))
);
double WINAPI xll_math_epsilon()
{
#pragma XLLEXPORT

	return std::numeric_limits<double>::epsilon();
}

#ifdef _DEBUG

int test_math_epsilon(void)
{
	try {
		double eps = std::numeric_limits<double>::epsilon();
		ensure (eps == xll_math_epsilon());
		ensure (OPERX(eps) == Excel<XLOPERX>(xlfEvaluate, OPERX(_T("=MATH.EPSILON()"))));
		ensure (OPERX(eps) == XLL_XLF(Evaluate, OPERX(_T("=MATH.EPSILON()"))));

		ensure (1 + eps == nextafter(1, 2));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return 1;
}
static Auto<OpenAfterX> xao_test_math_epsilon(test_math_epsilon);

#endif // _DEBUG

static AddInX xai_math_add(
	_T("?xll_math_add"), XLL_DOUBLEX XLL_DOUBLEX XLL_DOUBLEX,
	_T("MATH.ADD"), _T("x, y"),
	CATEGORY, _T("Return the sum of x and y."));
double xll_math_add(double x, double y)
{
#pragma XLLEXPORT

	return x + y;
}
static AddInX xai_math_sub(
	_T("?xll_math_sub"), XLL_DOUBLEX XLL_DOUBLEX XLL_DOUBLEX,
	_T("MATH.SUB"), _T("x, y"),
	CATEGORY, _T("Return the difference of x and y."));
double xll_math_sub(double x, double y)
{
#pragma XLLEXPORT

	return x - y;
}
static AddInX xai_math_mul(
	_T("?xll_math_mul"), XLL_DOUBLEX XLL_DOUBLEX XLL_DOUBLEX,
	_T("MATH.MUL"), _T("x, y"),
	CATEGORY, _T("Return the product of x and y."));
double xll_math_mul(double x, double y)
{
#pragma XLLEXPORT

	return x * y;
}
static AddInX xai_math_div(
	_T("?xll_math_div"), XLL_DOUBLEX XLL_DOUBLEX XLL_DOUBLEX,
	_T("MATH.DIV"), _T("x, y"),
	CATEGORY, _T("Return the quotient of x and y."));
double xll_math_div(double x, double y)
{
#pragma XLLEXPORT

	return x / y;
}

static AddInX xai_math_eq(
	_T("?xll_math_eq"), XLL_BOOLX XLL_DOUBLEX XLL_DOUBLEX,
	_T("MATH.EQ"), _T("x, y"),
	CATEGORY, _T("Return TRUE if x and y are equal."));
BOOL xll_math_eq(double x, double y)
{
#pragma XLLEXPORT

	return x == y;
}
static AddInX xai_math_ne(
	_T("?xll_math_ne"), XLL_BOOLX XLL_DOUBLEX XLL_DOUBLEX,
	_T("MATH.NE"), _T("x, y"),
	CATEGORY, _T("Return TRUE if x and y are not equal."));
BOOL xll_math_ne(double x, double y)
{
#pragma XLLEXPORT

	return x != y;
}
static AddInX xai_math_lt(
	_T("?xll_math_lt"), XLL_BOOLX XLL_DOUBLEX XLL_DOUBLEX,
	_T("MATH.LT"), _T("x, y"),
	CATEGORY, _T("Return TRUE if x is less than y."));
BOOL xll_math_lt(double x, double y)
{
#pragma XLLEXPORT

	return x < y;
}
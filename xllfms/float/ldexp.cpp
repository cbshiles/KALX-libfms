// ldexp.c - calls corresponding C library function
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xll/xll.h"

#ifndef CATEGORY
#define CATEGORY "Float"
#endif

using namespace xll;

static AddInX xai_ldexp(
	FunctionX(XLL_DOUBLEX, _T("?xll_ldexp"), _T("LDEXP"))
	.Arg(XLL_DOUBLEX, _T("sig"), _T("is the significand"))
	.Arg(XLL_LONGX, _T("exp"), _T("is the exponent "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns sig*2^exp using the C library function ldexp()"))
);
double WINAPI
xll_ldexp(double sig, LONG exp)
{
#pragma XLLEXPORT

	return ldexp(sig, exp);
}

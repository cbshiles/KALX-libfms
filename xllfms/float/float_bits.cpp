// float_bits.cpp - convert between double and bits
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xll/xll.h"

#ifndef CATEGORY
#define CATEGORY "Float"
#endif

using namespace xll;

typedef traits<XLOPERX>::xword xword;

static_assert(sizeof(double) == sizeof(long long), "long long must be 64 bits");

static AddInX xai_float_bits(
	FunctionX(XLL_FPX, _T("?xll_float_bits"), _T("FLOAT.BITS"))
	.Arg(XLL_DOUBLEX, _T("Num"), _T("is a floating point number "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns 1 x 64 array of the bits of the floating point Number"))
);
_FP* WINAPI
xll_float_bits(double x)
{
#pragma XLLEXPORT
	static char buf[sizeof(_FP) + 64*sizeof(double)];
	static _FP* pb = reinterpret_cast<_FP*>(buf);
	
	pb->rows = 1;
	pb->columns = 64;

	union { double x; long long l; } u;
	u.x = x;

	for (unsigned short i = 0; i < 64; ++i)
		pb->array[63 - i] = (u.l>>i)&1 ? 1 : 0;

	return pb;
}

static AddInX xai_bits_float(
	FunctionX(XLL_DOUBLEX, _T("?xll_bits_float"), _T("BITS.FLOAT"))
	.Arg(XLL_FPX, _T("Bits"), _T("is an array of 64 bits "))
	.Category(_T(CATEGORY))
	.FunctionHelp(_T("Converts array of 64 bits to a floating point Number"))
);
double WINAPI
xll_bits_float(const _FP* pb)
{
#pragma XLLEXPORT

	union { double x; long long l; } u;

	try {
		ensure (size(*pb) == 64);
		u.l = 0;
		for (xword i = 0; i < 64; ++i)
			if (pb->array[63 - i] != 0)
				u.l |= (1ll<<i);
	}
	catch (const std::exception& ex) {
		XLL_INFORMATION(ex.what());

		return std::numeric_limits<double>::quiet_NaN();
	}


	return u.x;
}
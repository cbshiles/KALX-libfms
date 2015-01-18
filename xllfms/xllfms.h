// xllfms.h - global header file
// Uncomment to build for Excel 2007 and later
//#define EXCEL12
#pragma once
#include "xll/xll.h"
#include <random>

#ifndef CATEGORY
#define CATEGORY _T("FMS")
#endif

typedef xll::traits<XLOPERX>::xchar xchar;
typedef xll::traits<XLOPERX>::xword xword;
typedef xll::traits<XLOPERX>::xfp xfp;

inline std::default_random_engine& rng()
{
	static std::default_random_engine r{};

	return r;
}

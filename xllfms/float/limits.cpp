// limits.cpp - numerical limits
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xll/xll.h"
#include <climits>

#ifndef CATEGORY
#define CATEGORY "Float"
#endif

using namespace xll;

#define HASH(x) #x
#define STR(x) HASH(x)

// Double
XLL_ENUM(DBL_DIG, DBL_DIG, CATEGORY, "number of decimal digits of precision [" STR(DBL_DIG) "]");
XLL_ENUM(DBL_EPSILON, DBL_EPSILON, CATEGORY, "smallest such that 1.0+DBL_EPSILON != 1.0 [" STR(DBL_EPSILON) "]");
XLL_ENUM(DBL_MANT_DIG, DBL_MANT_DIG, CATEGORY, "number of bits in mantissa [" STR(DBL_MANT_DIG) "]");
XLL_ENUM(DBL_MAX, DBL_MAX, CATEGORY, "max value [" STR(DBL_MAX) "]");
XLL_ENUM(DBL_MAX_10_EXP, DBL_MAX_10_EXP, CATEGORY, "max decimal exponent [" STR(DBL_MAX_10_EXP) "]");
XLL_ENUM(DBL_MAX_EXP, DBL_MAX_EXP, CATEGORY, "max binary exponent [" STR(DBL_MAX_EXP) "]");
XLL_ENUM(DBL_MIN, DBL_MIN, CATEGORY, "min positive value [" STR(DBL_MIN) "]");
XLL_ENUM(DBL_MIN_10_EXP, DBL_MIN_10_EXP, CATEGORY, "min decimal exponent [" STR(DBL_MIN_10_EXP) "]");
XLL_ENUM(DBL_MIN_EXP, DBL_MIN_EXP, CATEGORY, "min binary exponent [" STR(DBL_MIN_EXP) "]");

// Float
XLL_ENUM(FLT_DIG, FLT_DIG, CATEGORY, "number of decimal digits of precision [" STR(FLT_DIG) "]");
XLL_ENUM(FLT_EPSILON, FLT_EPSILON, CATEGORY, "smallest such that 1.0+FLT_EPSILON != 1.0 [" STR(FLT_EPSILON) "]");
XLL_ENUM(FLT_MANT_DIG, FLT_MANT_DIG, CATEGORY, "number of bits in mantissa [" STR(FLT_MANT_DIG) "]");
XLL_ENUM(FLT_MAX, FLT_MAX, CATEGORY, "max value [" STR(FLT_MAX) "]");
XLL_ENUM(FLT_MAX_10_EXP, FLT_MAX_10_EXP, CATEGORY, "max decimal exponent [" STR(FLT_MAX_10_EXP) "]");
XLL_ENUM(FLT_MAX_EXP, FLT_MAX_EXP, CATEGORY, "max binary exponent [" STR(FLT_MAX_EXP) "]");
XLL_ENUM(FLT_MIN, FLT_MIN, CATEGORY, "min positive value [" STR(FLT_MIN) "]");
XLL_ENUM(FLT_MIN_10_EXP, FLT_MIN_10_EXP, CATEGORY, "min decimal exponent [" STR(FLT_MIN_10_EXP) "]");
XLL_ENUM(FLT_MIN_EXP, FLT_MIN_EXP, CATEGORY, "min binary exponent [" STR(FLT_MIN_EXP) "]");

XLL_ENUM(std::numeric_limits<double>::signaling_NaN(), SNAN, CATEGORY, "signaling NaN");
XLL_ENUM(std::numeric_limits<double>::quiet_NaN(), QNAN, CATEGORY, "quiet NaN");
XLL_ENUM(std::numeric_limits<double>::infinity(), PINF, CATEGORY, "positive infinity");

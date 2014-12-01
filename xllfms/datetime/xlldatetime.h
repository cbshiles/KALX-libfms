// xlldatetime.h - common header for Excel add-ins
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
//#define EXCEL12
#include "xll/xll.h"
#include "datetime/datetime.h"

typedef xll::traits<XLOPERX>::xcstr xcstr;
typedef xll::traits<XLOPERX>::xfp xfp;
typedef xll::traits<XLOPERX>::xword xword;

#ifndef CATEGORY
#define CATEGORY _T("Date & Time")
#endif 
#ifndef CATEGORY_ENUM
#define CATEGORY_ENUM CATEGORY
#endif
#ifndef DATETIME_PREFIX
#define DATETIME_PREFIX
#endif

#define XLL_DATEX XLL_DOUBLEX

// Common arguments
#define IS_DATE   _T("is the Excel Julian date.")
#define IS_FREQ	  _T("is the frequency from the FREQ_* enumeration.")
#define IS_ROLL   _T("is the rolling convention from the ROLL_* enumeration.")
#define IS_CAL    _T("is one or more holiday calendars from the CALENDAR_* enumeration.")
#define IS_DCB    _T("is the day count basis from the DCB_* enumeration.")
#define IS_UNIT   _T("is the time unit from the UNIT_* enumeration.")
#define IS_COUNT  _T("is the count corresponding to the unit enumeration.")
#define IS_DAY    _T("is a value from the DAY_* enumeration.")

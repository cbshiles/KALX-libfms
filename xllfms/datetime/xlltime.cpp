// xlltime.cpp - <ctime> functions
#ifndef _WIN64
#define _USE_32BIT_TIME_T
#include <ctime>
#include "xll/xll.h"

#define CATEGORY _T("FMS")
#define PREFIX _T("TIME.")

using namespace xll;

typedef traits<XLOPERX>::xfp xfp;

XLL_ENUMX(CLOCKS_PER_SEC, CLOCKS_PER_SEC, CATEGORY, _T("The number of clock ticks per second."))

static AddInX xai_clock(
	FunctionX(XLL_DOUBLEX, _T("?xll_clock"), PREFIX _T("CLOCK"))
	.ThreadSafe()
	.FunctionHelp(_T("Returns the processor time consumed by the program."))
	.Category(CATEGORY)
);
double WINAPI xll_clock(void)
{
#pragma XLLEXPORT

	return ::clock();
}

static AddInX xai_difftime(
	FunctionX(XLL_DOUBLEX, _T("?xll_difftime"), PREFIX _T("DIFFTIME"))
	.Arg(XLL_DOUBLEX, _T("End"), _T("is the end time as a time_t."))
	.Arg(XLL_DOUBLEX, _T("Beg"), _T("is the beginning time as a time_t."))
	.ThreadSafe()
	.FunctionHelp(_T("Returns difference between end time and beginning time in seconds."))
	.Category(CATEGORY)
);
double WINAPI xll_difftime(double e, double b)
{
#pragma XLLEXPORT

	return ::difftime(static_cast<time_t>(e), static_cast<time_t>(b));
}

static AddInX xai_gmtime(
	FunctionX(XLL_FPX, _T("?xll_gmtime"), PREFIX _T("GMTIME"))
	.Arg(XLL_LONGX, _T("Time"), _T("is the UTC time as a time_t."))
	.FunctionHelp(_T("Returns a UTC time array of year, month, day, hour, minute, second, and a daylight savings flag."))
	.Category(CATEGORY)
);
traits<XLOPERX>::xfp* WINAPI xll_gmtime(time_t t)
{
#pragma XLLEXPORT
	static FPX result(1, 7);
	struct tm tm;

	if (0 != ::gmtime_s(&tm, &t))
		return 0;

	result[0] = tm.tm_year + 1900;
	result[1] = tm.tm_mon + 1;
	result[2] = tm.tm_mday;
	result[3] = tm.tm_hour;
	result[4] = tm.tm_min;
	result[5] = tm.tm_sec;
	result[6] = tm.tm_isdst;

	return result.get();
}

static AddInX xai_localtime(
	FunctionX(XLL_FPX, _T("?xll_localtime"), PREFIX _T("LOCALTIME"))
	.Arg(XLL_LONGX, _T("Time"), _T("is the UTC time as a time_t."))
	.FunctionHelp(_T("Returns a local time array of year, month, day, hour, minute, second, and a daylight savings flag."))
	.Category(CATEGORY)
);
xfp* WINAPI xll_localtime(time_t t)
{
#pragma XLLEXPORT
	static FPX result(1, 7);
	struct tm tm;

	if (0 != ::localtime_s(&tm, &t))
		return 0;

	result[0] = tm.tm_year + 1900;
	result[1] = tm.tm_mon + 1;
	result[2] = tm.tm_mday;
	result[3] = tm.tm_hour;
	result[4] = tm.tm_min;
	result[5] = tm.tm_sec;
	result[6] = tm.tm_isdst;

	return result.get();
}

static AddInX xai_mktime(
	FunctionX(XLL_LONGX, _T("?xll_mktime"), PREFIX _T("MKTIME"))
	.Arg(XLL_FPX, _T("Year"), _T("is the year."))
	.Arg(XLL_SHORTX, _T("Month"), _T("is the year."))
	.Arg(XLL_SHORTX, _T("Day"), _T("is the year."))
	.Arg(XLL_SHORTX, _T("Hour"), _T("is the year."))
	.Arg(XLL_SHORTX, _T("Minute"), _T("is the year."))
	.Arg(XLL_SHORTX, _T("Second"), _T("is the year."))
	.FunctionHelp(_T("Returns a UTC time_t given a broken down local time."))
	.Category(CATEGORY)
);
time_t WINAPI xll_mktime(const xfp* py, SHORT m, SHORT d, SHORT h, SHORT n, SHORT s)
{
#pragma XLLEXPORT
	time_t t{-1};
	struct tm tm;

	try {
		if (size(*py) != 1) {
			ensure (size(*py) == 6);
			m = static_cast<SHORT>(py->array[1]);
			d = static_cast<SHORT>(py->array[2]);
			h = static_cast<SHORT>(py->array[3]);
			n = static_cast<SHORT>(py->array[4]);
			s = static_cast<SHORT>(py->array[5]);
		}

		tm.tm_year = static_cast<SHORT>(py->array[0]) - 1900;
		tm.tm_mon = m - 1;
		tm.tm_mday = d;
		tm.tm_hour = h;
		tm.tm_min = n;
		tm.tm_sec = s;

		t = ::mktime(&tm);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return t;
}
#endif
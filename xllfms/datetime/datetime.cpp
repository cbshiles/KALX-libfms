// datetime.cpp - datetime routines
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "../../xll8/xll/xll.h"
#include "../../datetime/dt.h"

using namespace xll;

#define XLL_DATEX XLL_DOUBLEX
#define IS_DATE _T("is an Excel Julian date")
#define DATETIME_PREFIX _T("DATETIME.")
#define CATEGORY _T("FMS")
#if 0
#include <algorithm>
#include <string>
#pragma warning(disable: 4996 4244)
#include "xlldatetime.h"

using std::string;
using namespace xll;
using namespace datetime;
using namespace xml;

#ifdef _DEBUG
static AddInX xai_datetime(
	ArgsX(CATEGORY)
	.Documentation(xml::File(Directory::Basename(_T(__FILE__)).append(_T("datetime.xml")).c_str()))
);	
#endif

//
// Enumerations
//


//
// Date creation routines
//


static AddInX xai_date2year (
	FunctionX(XLL_FPX, _T("?xll_date2year"), DATETIME_PREFIX _T("DATE2YEAR"))   
	.Arg(XLL_FPX, _T("Dates"), _T("is an array of Excel dates."),
		_T("=TODAY()"))
	.Arg(XLL_DATEX, _T("Epoch"), _T("is the date corresponding to zero years. "),
		_T("=EXCEL_EPOCH()"))
	.Category(CATEGORY) 
	.FunctionHelp(_T("Convert Excel Dates to time in years from an Epoch date ignoring daylight savings time."))
	.Documentation()
);
xfp* WINAPI 
xll_date2year(xfp *pd, double epoch)
{
#pragma XLLEXPORT
	for (WORD i = 0; i < size(*pd); i++)
	{
		pd->array[i] = excel2years(pd->array[i], epoch);
	}

	return pd;
}

static AddInX xai_year2date (
	FunctionX(XLL_FPX, _T("?xll_year2date"), DATETIME_PREFIX _T("YEAR2DATE"))   
	.Arg(XLL_FPX, _T("Years"), _T("is an array of years from Epoch."),
		_T("=200*RAND()"))
	.Arg(XLL_DATEX, _T("Epoch"), _T("is a date in Excel format corresponding to year zero. "),
		_T("=TODAY()"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Convert time in years from Epoch to Excel dates ignoring daylight savings time."))
	.Documentation()
);

xfp* WINAPI
xll_year2date(xfp *py, double epoch)
{
#pragma XLLEXPORT
	for (int i = 0; i < size(*py); i++)
	{
		py->array[i] = years2excel(py->array[i], epoch);
	}

	return py;
}

static AddInX xai_date_incr(
	FunctionX(XLL_DATEX, _T("?xll_date_incr"), DATETIME_PREFIX _T("DATE.INCR"))
	.Arg(XLL_DATEX, _T("Date"), IS_DATE,
		_T("=TODAY()"))
	.Arg(XLL_LONGX, _T("Count"), IS_COUNT,
		_T("=INT(100*RAND())"))
	.Arg(XLL_LONGX, _T("Unit"), IS_UNIT,
		_T("=UNIT_DAYS()"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Increments Date by Count Units."))
	.Documentation(
		_T("Business days are non holiday weekdays.")
	)
);
double WINAPI
xll_date_incr(double dt, long count, time_unit unit)
{
#pragma XLLEXPORT
	double e;

	try {
		date d(dt);
		d.incr(count, unit);
		e = d.excel();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		e = std::numeric_limits<double>::quiet_NaN();
	}

	return e;
}

static AddInX xai_date_imm(
	FunctionX(XLL_DOUBLEX, _T("?xll_date_imm"), DATETIME_PREFIX _T("DATE.IMM"))
	.Arg(XLL_DATEX, _T("Date"), IS_DATE,
		_T("=TODAY()"))
	.Arg(XLL_LONGX, _T("Nth"), _T("is the ordinal for the day of week."),
		_T("=INT(4*RAND())"))
	.Arg(XLL_LONGX, _T("Day"), IS_DAY,
		_T("=DAY_WED()"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Increment Date to Nth Day of the current month."))
	.Documentation(
		_T("The second argument is required to be positive. ")
		_T("IMM stands for International Money Market, a division of the ")
		_T("Chicago Mercantile Exchange (CME) formed in 1972 to trade currency ")
		_T("and interest rate futures and options. Many contracts expire on ")
		_T("the third Wednesday of the expiration month, hence the name <codeInline>DATE.IMM</codeInline>.")
	)
);
double WINAPI
xll_date_imm(double dt, long ordinal, day_of_week day)
{
#pragma XLLEXPORT
	double ndt;

	try {
		ndt = date(dt).imm(ordinal, day).excel();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		ndt = std::numeric_limits<double>::quiet_NaN();
	}

	return ndt;
}


static AddInX xai_date_ymdhms(
	FunctionX(XLL_FPX, _T("?xll_date_ymdhms"), DATETIME_PREFIX _T("DATE.YMDHMS"))
	.Arg(XLL_DATEX, _T("Date"), IS_DATE,
		_T("=TODAY()")) 
	.Category(CATEGORY)
	.FunctionHelp(_T("Return one row array of Year, Month, Day, Hour, Minute, Second."))
	.Documentation()
	
);
xfp* WINAPI
xll_date_ymdhms(double t)
{
#pragma XLLEXPORT
	static FPX result(1, 6);
	int y, m, d, h, n, s;

	date(t).localtime(&y, &m, &d, &h, &n, &s);

	result[0] = y;
	result[1] = m;
	result[2] = d;
	result[3] = h;
	result[4] = n;
	result[5] = s;

	return result.get();
}
static AddInX xai_date_diffyears(
	FunctionX(XLL_DOUBLE, _T("?xll_date_diffyears"), DATETIME_PREFIX _T("DATE.DIFFYEARS"))
	.Arg(XLL_DATEX, _T("Start"), _T("is the first date of the period."),
		_T("=TODAY()"))
	.Arg(XLL_DATEX, _T("End"), _T("is the last date of the period."),
		_T("=R[-1]C[0] + 10*RAND()"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the difference of two dates in years."))
	.Documentation(
		_T("This function uses <codeInline>DAYS_PER_YEAR()</codeInline> = 365.25.")
	)
);
double WINAPI
xll_date_diffyears(double start, double end)
{
#pragma XLLEXPORT
	double result = std::numeric_limits<double>::quiet_NaN();

	try {
		date sd(start), ed(end);

		result = ed.diffyears(sd);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}

static AddInX xai_date_workdays(
	FunctionX(XLL_DOUBLEX, _T("?xll_date_workdays"), DATETIME_PREFIX _T("DATE.WORKDAYS"))  
	.Arg(XLL_DATEX, _T("Start"), _T("is the first date of the period."),
		_T("=TODAY()"))
	.Arg(XLL_DATEX, _T("End"), _T("is the last date of the period."),
		_T("=R[-1]C[0] + INT(20*RAND())"))
	.Arg(XLL_HANDLEX,_T("Calendar"), _T("is an array of holidays in YYYYMMDD format."),
		_T("=CALENDAR_NYB"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the number of workdays between starting date and ending date."))
	.Documentation(
		_T("This function provides the same functionality as the built-in Excel function <codeInline>NETWORKDAYS</codeInline>.")
	)
);
double WINAPI
xll_date_workdays(double t1, double t2, HANDLEX pcal)
{
#pragma XLLEXPORT
	double result = std::numeric_limits<double>::quiet_NaN();

	try {
		result = date(t2).diffworkdays(date(t1), HOLIDAY_CALENDAR(pcal));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}

static AddInX xai_date_weekday(
	FunctionX(XLL_DOUBLEX, _T("?xll_date_weekday"), DATETIME_PREFIX _T("DATE.WEEKDAY"))
	.Arg(XLL_DATEX, _T("Date"), IS_DATE,
		_T("=TODAY()"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Day of the week as in the DAY_* enumeration."))
	.Documentation()
);
double WINAPI
xll_date_weekday(double t)
{
#pragma XLLEXPORT
	double w = std::numeric_limits<double>::quiet_NaN();

	try {
		date d(t);
		w = d.weekday();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return w;
}

static AddInX xai_date_isdst(
	FunctionX(XLL_DOUBLEX, _T("?xll_date_isdst"), DATETIME_PREFIX _T("DATE.ISDST"))
	.Arg(XLL_DATEX, _T("Date"), IS_DATE,
		_T("=NOW()"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return 1 if daylight savings is in effect and 0 if not. Return -1 if no DST info is available.")) // !!!work on wording
	.Documentation(
		_T("This function uses the local time to determine daylight savings. ")
	)
);
double WINAPI
xll_date_isdst(double t)
{
#pragma XLLEXPORT
	double b = std::numeric_limits<double>::quiet_NaN();

	try {
		date d(t);
		b = d.is_dst();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	
	return b;
}
#endif // 0

using namespace fms::datetime;

#define CATEGORY_ENUM CATEGORY
// Various constants 

XLL_ENUM_DOC(DAYS_PER_YEAR, DAYS_PER_YEAR, CATEGORY_ENUM, 
	"Number of days in a year.",
	"The value 365.25 is somewhat arbitrary, but the important thing is to use it consistently.")
XLL_ENUM_DOC(SECS_PER_DAY, SECS_PER_DAY, CATEGORY_ENUM, 
	"Number of seconds per day.", "")
XLL_ENUM_DOC(EXCEL_EPOCH, EXCEL_EPOCH, CATEGORY_ENUM, 
	"Excel Julian date for unix epoch of midnight 1970/1/1.", "")

static AddInX xai_date2timet(
	FunctionX(XLL_DOUBLEX, _T("?xll_date2timet"), DATETIME_PREFIX _T("DATE2TIMET"))
	.Arg(XLL_DATEX, _T("Date"), IS_DATE,
		_T("=TODAY()"))
	.Arg(XLL_BOOLX, _T("_NoDST"), _T("is an optional argument that ignores daylight savings if TRUE."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Convert Excel Date to UTC time_t."))
	.Documentation(
		_T("Usually <codeInline>time_t</codeInline> is the time in seconds since 1 Jan, 1970 GMT. ")
	)
);
double WINAPI
xll_date2timet(double d, BOOL nodst)
{
#pragma XLLEXPORT
	double t{std::numeric_limits<double>::quiet_NaN()};

	try {
		t = static_cast<double>(fms::datetime::excel2time_t(d, !!nodst));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return t;
}

static AddInX xai_timet2date(
	FunctionX(XLL_DATEX, _T("?xll_timet2date"), DATETIME_PREFIX _T("TIMET2DATE"))
	.Arg(XLL_DOUBLEX, _T("TimeT"), _T("is a time_t."),
		1355202000)
	.Arg(XLL_BOOLX, _T("_NoDST"), _T("is an optional argument that ignores daylight savings if TRUE."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Convert UTC time_t to Excel Date."))
	.Documentation(
		_T("Usually <codeInline>time_t</codeInline> is the time in seconds since 1 Jan, 1970 GMT. ")
	)
);
double WINAPI
xll_timet2date(double t, BOOL nodst)
{
#pragma XLLEXPORT
	double d(std::numeric_limits<double>::quiet_NaN());

	try {
		d = fms::datetime::time_t2excel(static_cast<time_t>(t), !!nodst);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return d;
}
	
#if 0
/*@
	category: DATE

	function:array	DATE.INTERVAL
		Generate an interval of dates.

	argument:date	Begin
		First date in the interval.

	argument:date	End
		Last date in the interval.

	argument:integer	Incr
		Increment corresponding to time Unit. Use a negative increment
		to decrement from the End.

	argument:TIME_UNIT

	argument:ROLL_CONVENTION

	argument:HOLIDAY_CALENDAR

	argument:"enum_type	LongShort?
		Insert a long or short odd payment.

	comments:
		If no long or short odd payment is specified this routine
		generates a periodic sequence of dates with no odd payments.
		If short or long payments are requested, an additional payment
		will be generated.
@*/
::FP* WINAPI
xll_date_interval(double b, double e, long incr, time_unit unit, 
	roll_convention roll, holiday_calendar cal, enum_type ls)
{
#pragma XLLEXPORT
	static ::FP* result = 0;
	vector<double> interval;
	
	qed_error err = datetime_interval(b, e, incr, unit, roll, 
		cal, interval, ls);
	if (qed_is_error(err))
	{
		XLL_ERROR(string("DATE.INTERVAL: ") + qed_error_message(err));
		return 0;
	}

	result = reshape(result, interval.size(), 1);
	copy(interval.begin(), interval.end(), result->array);

	return result;
}
#endif



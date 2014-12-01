// date_enum.cpp - datetime enumerations
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xlldatetime.h"

using namespace xll;
using namespace fms::datetime;

/*
static AddInX xai_datetime_enum(
	ArgsX(CATEGORY_ENUM)
	.Documentation(_T("Various enumerated values associated with date and time functions."))
);	
*/

// Various constants
XLL_ENUM_DOCX(DAYS_PER_YEAR, TIME_DAYS_PER_YEAR, CATEGORY_ENUM, 
	_T("Number of days in a year."),
	_T("The value 365.25 is somewhat arbitrary, but the important thing is to use it consistently."))
XLL_ENUM_DOCX(SECS_PER_DAY, TIME_SECS_PER_DAY, CATEGORY_ENUM, 
	_T("Number of seconds per day."),
	_T(""))
XLL_ENUM_DOCX(EXCEL_EPOCH, EXCEL_EPOCH, CATEGORY_ENUM, 
	_T("Excel Julian date for unix epoch of midnight 1970/1/1."),
	_T(""))

// Units of time.
XLL_ENUM_DOCX(UNIT_SECONDS, UNIT_SECONDS, 
		CATEGORY_ENUM, _T("Time in seconds."), _T(""))
XLL_ENUM_DOCX(UNIT_MINUTES, UNIT_MINUTES,  
		CATEGORY_ENUM, _T("Time in minutes."), _T(""))
XLL_ENUM_DOCX(UNIT_HOURS, UNIT_HOURS,  
		CATEGORY_ENUM, _T("Time in hours."), _T(""))
XLL_ENUM_DOCX(UNIT_DAYS, UNIT_DAYS,  
		CATEGORY_ENUM, _T("Time in days."), _T(""))
XLL_ENUM_DOCX(UNIT_WEEKS, UNIT_WEEKS,  
		CATEGORY_ENUM, _T("Time in weeks."), _T(""))
XLL_ENUM_DOCX(UNIT_MONTHS, UNIT_MONTHS,  
		CATEGORY_ENUM, _T("Time in months."), _T(""))
XLL_ENUM_DOCX(UNIT_YEARS, UNIT_YEARS,  
		CATEGORY_ENUM, _T("Time in years."), _T(""))
XLL_ENUM_DOCX(UNIT_BUSINESS_DAY, UNIT_BUSINESS_DAY,  
		CATEGORY_ENUM, _T("Business days."), _T(""))
XLL_ENUM_DOCX(UNIT_END_OF_MONTH, UNIT_END_OF_MONTH,  
		CATEGORY_ENUM, _T("Last day of month."), _T(""))
XLL_ENUM_DOCX(UNIT_FIRST_OF_MONTH, UNIT_FIRST_OF_MONTH,  
		CATEGORY_ENUM, _T("First day of month."), _T(""))

// Day of week.
XLL_ENUM_DOCX(DAY_SUN, DAY_SUN,   
		CATEGORY_ENUM, _T("Sunday = 0."), _T(""))
XLL_ENUM_DOCX(DAY_MON, DAY_MON,   
		CATEGORY_ENUM, _T("Monday = 1."), _T(""))
XLL_ENUM_DOCX(DAY_TUE, DAY_TUE,   
		CATEGORY_ENUM, _T("Tuesday = 2."), _T(""))
XLL_ENUM_DOCX(DAY_WED, DAY_WED,   
		CATEGORY_ENUM, _T("Wednesday = 3."), _T(""))
XLL_ENUM_DOCX(DAY_THU, DAY_THU,   
		CATEGORY_ENUM, _T("Thursday = 4."), _T(""))
XLL_ENUM_DOCX(DAY_FRI, DAY_FRI,   
		CATEGORY_ENUM, _T("Friday = 5."), _T(""))
XLL_ENUM_DOCX(DAY_SAT, DAY_SAT,   
		CATEGORY_ENUM, _T("Saturday = 6."), _T(""))

// Month of year.
XLL_ENUM_DOCX(MONTH_JAN, MONTH_JAN,    
		CATEGORY_ENUM, _T("January = 1."), _T(""))
XLL_ENUM_DOCX(MONTH_FEB, MONTH_FEB,    
		CATEGORY_ENUM, _T("February = 2."), _T(""))
XLL_ENUM_DOCX(MONTH_MAR, MONTH_MAR,    
		CATEGORY_ENUM, _T("March = 3."), _T(""))
XLL_ENUM_DOCX(MONTH_APR, MONTH_APR,    
		CATEGORY_ENUM, _T("April = 4."), _T(""))
XLL_ENUM_DOCX(MONTH_MAY, MONTH_MAY,    
		CATEGORY_ENUM, _T("May = 5."), _T(""))
XLL_ENUM_DOCX(MONTH_JUN, MONTH_JUN,    
		CATEGORY_ENUM, _T("June = 6."), _T(""))
XLL_ENUM_DOCX(MONTH_JUL, MONTH_JUL,    
		CATEGORY_ENUM, _T("July = 7."), _T(""))
XLL_ENUM_DOCX(MONTH_AUG, MONTH_AUG,    
		CATEGORY_ENUM, _T("August = 8."), _T(""))
XLL_ENUM_DOCX(MONTH_SEP, MONTH_SEP,    
		CATEGORY_ENUM, _T("September = 9."), _T(""))
XLL_ENUM_DOCX(MONTH_OCT, MONTH_OCT,    
		CATEGORY_ENUM, _T("October = 10."), _T(""))
XLL_ENUM_DOCX(MONTH_NOV, MONTH_NOV,    
		CATEGORY_ENUM, _T("November = 11."), _T(""))
XLL_ENUM_DOCX(MONTH_DEC, MONTH_DEC,    
		CATEGORY_ENUM, _T("December = 12."), _T(""))

// Day counts.
XLL_ENUM_DOCX(DCB_ACTUAL_YEARS, DCB_ACTUAL_YEARS,     
		CATEGORY_ENUM, _T("Time in years between dates."), _T(""))
XLL_ENUM_DOCX(DCB_30U_360, DCB_30U_360, 
		CATEGORY_ENUM, _T("Day count with 30 days per month and 360 days per year."), _T(""))
XLL_ENUM_DOCX(DCB_30E_360, DCB_30E_360, 
		CATEGORY_ENUM, _T("European day count with 30 days per month and 360 days per year."), _T(""))
XLL_ENUM_DOCX(DCB_ACTUAL_360, DCB_ACTUAL_360, 
		CATEGORY_ENUM, _T("Day count is number of days divided by 360."), _T(""))
XLL_ENUM_DOCX(DCB_ACTUAL_365, DCB_ACTUAL_365, 
		CATEGORY_ENUM, _T("Day count is number of days divided by 365."), _T(""))
XLL_ENUM_DOCX(DCB_ACTUAL_ACTUAL_ISDA, DCB_ACTUAL_ACTUAL_ISDA, 
		CATEGORY_ENUM, _T("Day count is number of days divided by 365, or 366 for leap years. ISDA method."), _T(""))

// Payment frequency
XLL_ENUM_DOCX(FREQ_NONE, FREQ_NONE,
		CATEGORY_ENUM, _T("Not periodic."), _T(""))
XLL_ENUM_DOCX(FREQ_ANNUALLY, FREQ_ANNUALLY,
		CATEGORY_ENUM, _T("Once per year."), _T(""))
XLL_ENUM_DOCX(FREQ_SEMIANNUALLY, FREQ_SEMIANNUALLY,
		CATEGORY_ENUM, _T("Twice per year."), _T(""))
XLL_ENUM_DOCX(FREQ_QUARTERLY, FREQ_QUARTERLY,
		CATEGORY_ENUM, _T("Four times per year."), _T(""))
XLL_ENUM_DOCX(FREQ_MONTHLY, FREQ_MONTHLY,
		CATEGORY_ENUM, _T("Twelve times per year."), _T(""))
XLL_ENUM_DOCX(FREQ_WEEKLY, FREQ_WEEKLY,
		CATEGORY_ENUM, _T("Every week."), _T(""))

// Rolling conventions.
XLL_ENUM_DOCX(ROLL_NONE, ROLL_NONE, 
	CATEGORY_ENUM, _T("No roll convention."), _T(""))
XLL_ENUM_DOCX(ROLL_FOLLOWING_BUSINESS, ROLL_FOLLOWING_BUSINESS, 
	CATEGORY_ENUM, _T("The following business day."), _T(""))
XLL_ENUM_DOCX(ROLL_PREVIOUS_BUSINESS, ROLL_PREVIOUS_BUSINESS,	
	CATEGORY_ENUM, _T("The previous business day."), _T(""))
XLL_ENUM_DOCX(ROLL_MODIFIED_FOLLOWING, ROLL_MODIFIED_FOLLOWING, 
	CATEGORY_ENUM, _T("The earlier of following and last business day of month."), _T(""))
XLL_ENUM_DOCX(ROLL_MODIFIED_PREVIOUS, ROLL_MODIFIED_PREVIOUS,  
	CATEGORY_ENUM, _T("The later of the previous and first business day of month."), _T(""))

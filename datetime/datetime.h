// datetime.h - extensions to <chrono>
// http://home.roadrunner.com/~hinnant/date_algorithms.html
#pragma once
#include <chrono>
#include <tuple>

#if defined(_WIN32) && _MSC_VER <= 1700
#define constexpr inline
#define noexcept throw()
#endif

namespace datetime {

#if defined(_WIN32) && _MSC_VER <= 1700
#include "chrono_duration_cast.h"
using datetime::duration_cast;
#endif

	// round down
	template <class To, class Rep, class Period>
	To
	floor(const std::chrono::duration<Rep, Period>& d)
	{
		To t = std::chrono::duration_cast<To>(d);
		if (t > d)
			--t;
		return t;
	}

	// round to nearest, to even on tie
	template <class To, class Rep, class Period>
	To
	round(const std::chrono::duration<Rep, Period>& d)
	{
		To t0 = std::chrono::duration_cast<To>(d);
		To t1 = t0;
		++t1;
		auto diff0 = d - t0;
		auto diff1 = t1 - d;
		if (diff0 == diff1)
		{
			if (t0.count() & 1)
				return t1;
			return t0;
		}
		else if (diff0 < diff1)
			return t0;
		return t1;
	}

	// round up
	template <class To, class Rep, class Period>
	To
	ceil(const std::chrono::duration<Rep, Period>& d)
	{
		To t = std::chrono::duration_cast<To>(d);
		if (t < d)
			++t;
		return t;
	}

	// Returns number of days since civil 1970-01-01.  Negative values indicate
	//    days prior to 1970-01-01.
	// Preconditions:  y-m-d represents a date in the civil (Gregorian) calendar
	//                 m is in [1, 12]
	//                 d is in [1, last_day_of_month(y, m)]
	//                 y is "approximately" in
	//                   [numeric_limits<Int>::min()/366, numeric_limits<Int>::max()/366]
	//                 Exact range of validity is:
	//                 [civil_from_days(numeric_limits<Int>::min()),
	//                  civil_from_days(numeric_limits<Int>::max()-719468)]	
	template <class Int>
	constexpr 
	Int
	civil_to_days(Int y, unsigned m, unsigned d) noexcept
	{
		static_assert(std::numeric_limits<unsigned>::digits >= 18,
				 "This algorithm has not been ported to a 16 bit unsigned integer");
		static_assert(std::numeric_limits<Int>::digits >= 20,
				 "This algorithm has not been ported to a 16 bit signed integer");
		y -= m <= 2;
		const Int era = (y >= 0 ? y : y-399) / 400;
		const unsigned yoe = static_cast<unsigned>(y - era * 400);      // [0, 399]
		const unsigned doy = (153*(m + (m > 2 ? -3 : 9)) + 2)/5 + d-1;  // [0, 365]
		const unsigned doe = yoe * 365 + yoe/4 - yoe/100 + doy;         // [0, 146096]
		
		return era * 146097 + static_cast<Int>(doe) - 719468;
	}

	// year, month, and day from days
	// Preconditions:  z is number of days since 1970-01-01 and is in the range:
	//                   [numeric_limits<Int>::min(), numeric_limits<Int>::max()-719468].
	template <class Int>
	constexpr
	std::tuple<Int, unsigned, unsigned>
	days_to_civil(Int z) noexcept
	{
		static_assert(std::numeric_limits<unsigned>::digits >= 18,
				 "This algorithm has not been ported to a 16 bit unsigned integer");
		static_assert(std::numeric_limits<Int>::digits >= 20,
				 "This algorithm has not been ported to a 16 bit signed integer");
		z += 719468;
		const Int era = (z >= 0 ? z : z - 146096) / 146097;
		const unsigned doe = static_cast<unsigned>(z - era * 146097);          // [0, 146096]
		const unsigned yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;  // [0, 399]
		const Int y = static_cast<Int>(yoe) + era * 400;
		const unsigned doy = doe - (365*yoe + yoe/4 - yoe/100);                // [0, 365]
		const unsigned mp = (5*doy + 2)/153;                                   // [0, 11]
		const unsigned d = doy - (153*mp+2)/5 + 1;                             // [1, 31]
		const unsigned m = mp + (mp < 10 ? 3 : -9);                            // [1, 12]
		
		return std::tuple<Int, unsigned, unsigned>(y + (m <= 2), m, d);
	}

	// Returns: true if y is a leap year in the civil calendar, else false
	template <class Int>
	constexpr
	bool
	is_leap(Int y) noexcept
	{
		return  y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
	}

	// Preconditions: m is in [1, 12]
	// Returns: The number of days in the month m of year y
	// The result is always in the range [28, 31].
	template <class Int>
	constexpr
	unsigned
	last_day_of_month(Int y, unsigned m) noexcept
	{
		static unsigned char a[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

		return m != 2 || !is_leap(y) ? a[m-1] : 29u;
	}

	// Returns day of week in civil calendar [0, 6] -> [Sun, Sat]
	// Preconditions:  z is number of days since 1970-01-01 and is in the range:
	//                   [numeric_limits<Int>::min(), numeric_limits<Int>::max()-4].
	template <class Int>
	constexpr
	unsigned
	weekday_from_days(Int z) noexcept
	{
		return static_cast<unsigned>(z >= -4 ? (z+4) % 7 : (z+5) % 7 + 6);
	}

	// Preconditions: x <= 6 && y <= 6
	// Returns: The number of days from the weekday y to the weekday x.
	// The result is always in the range [0, 6].
	constexpr
	unsigned
	weekday_difference(unsigned x, unsigned y) noexcept
	{
		x -= y;

		return x <= 6 ? x : x + 7;
	}

	// Preconditions: wd <= 6
	// Returns: The weekday following wd
	// The result is always in the range [0, 6].
	constexpr
	unsigned
	next_weekday(unsigned wd) noexcept
	{
		return wd < 6 ? wd+1 : 0;
	}
	// Preconditions: wd <= 6
	// Returns: The weekday prior to wd
	// The result is always in the range [0, 6].
	constexpr
	unsigned
	prev_weekday(unsigned wd) noexcept
	{
		return wd > 0 ? wd-1 : 6;
	}	
	
	enum day_of_week {
		SUN, SUNDAY = SUN,
		MON, MONDAY = MON, 
		TUE, TUESDAY = TUE,
		WED, WEDNESDAY = WED,
		THU, THURSDAY = THU,
		FRI, FRIDAY = FRI,
		SAT, SATURDAY = SAT
	};

	template<class Int>
	struct date : public std::chrono::duration<double, std::ratio<24*60*60>> {
		date(Int y = 1970, unsigned m = 1, unsigned d = 1, int h = 0, int M = 0, int s = 0)
			: std::chrono::duration<double, std::ratio<24*60*60>>(civil_to_days<Int>(y,m,d))
		{
			operator+=(std::chrono::hours(h) + std::chrono::minutes(M) + std::chrono::seconds(s));
		}
//		date(const date&) = default;
//		date& operator=(const date&) = default;
		~date()
		{ }
	};

	typedef std::chrono::duration<double,std::ratio<1,1>> days;

	template<class Int>
	inline std::tuple<Int,unsigned,unsigned> ymd(const date<Int>& d)
	{
		return days_to_civil(static_cast<Int>(d.count()));
	}
	template<class Int>
	inline std::tuple<unsigned,unsigned,unsigned> hms(const date<Int>& d)
	{
		auto h = datetime::duration_cast<std::chrono::hours>(d);
		auto M = datetime::duration_cast<std::chrono::minutes>(d - h);
		auto s = datetime::duration_cast<std::chrono::seconds>(d - h - M);
		
		return std::make_tuple(
			static_cast<unsigned>(h.count()),
			static_cast<unsigned>(M.count()),
			static_cast<unsigned>(s.count()));
	}
	template<class Int>
	inline unsigned millisecond(const date<Int>& d)
	{
		auto s = datetime::duration_cast<std::chrono::seconds>(d);

		return static_cast<unsigned>(round<std::chrono::milliseconds>(datetime::duration_cast<std::chrono::microseconds>(d - s)).count());
	}
	template<class Int>
	inline unsigned microsecond(const date<Int>& d)
	{
		auto s = datetime::duration_cast<std::chrono::seconds>(d);

		return static_cast<unsigned>(round<std::chrono::microseconds>(datetime::duration_cast<std::chrono::nanoseconds>(d - s)).count());
	}

} // namespace datetime

#if _MSC_VER <= 1700
#undef constexpr
#undef noexcept
#endif

#ifdef _DEBUG
//#include <random>

using namespace std::chrono;
using namespace datetime;

void
test_days()
{
	int beg = -100000;
	int end =  100000;

	auto t0 = system_clock::now();
	for (int t = beg; t < end; ++t) {
		int y, m, d;

		std::tie(y,m,d) = days_to_civil(t);
		ensure (t == civil_to_days(y,m,d));

		unsigned wd = weekday_from_days(t);
		ensure (0 <= wd && wd <= 6);
		ensure (wd == prev_weekday(weekday_from_days(t + 1)));
		ensure (wd == next_weekday(weekday_from_days(t - 1)));

		if (d == last_day_of_month(y,m)) {
			++t; // next day is first of month
			ensure (1 == std::get<2>(days_to_civil(t)));
		}
	}
	auto t1 = system_clock::now();

	double count = duration<double>(t1 - t0).count();
	double cps;
	cps = count/(end - beg);

}

void
test_weekday_difference()
{
	ensure (datetime::SUN == 0);
	ensure (datetime::SATURDAY == 6);

    static unsigned a[7][7] =
    {// -    Sun Mon Tue Wed Thu Fri Sat
     /*Sun*/ {0,  6,  5,  4,  3,  2,  1},
     /*Mon*/ {1,  0,  6,  5,  4,  3,  2},
     /*Tue*/ {2,  1,  0,  6,  5,  4,  3},
     /*Wed*/ {3,  2,  1,  0,  6,  5,  4},
     /*Thu*/ {4,  3,  2,  1,  0,  6,  5},
     /*Fri*/ {5,  4,  3,  2,  1,  0,  6},
     /*Sat*/ {6,  5,  4,  3,  2,  1,  0}
    };
    for (unsigned x = 0; x < 7; ++x)
        for (unsigned y = 0; y < 7; ++y)
            ensure (weekday_difference(x, y) == a[x][y]);
}

inline void test_date()
{
	date<int> d;
	d += days(1);
	d += hours(3) + minutes(4) + seconds(5);
	ensure (ymd(d) == std::make_tuple(1970,1,2));
	ensure (hms(d) == std::make_tuple(3,4,5));

	ensure (d == date<int>(1970,1,2,3,4,5));

	d += milliseconds(4);
	ensure (millisecond(d) == 4);
	d -= milliseconds(4);
	ensure (millisecond(d) == 0);

	d = date<int>();
	for (unsigned i = 1; i < 10000; ++i) {
		d += milliseconds(1);
		ensure (millisecond(d) == i % 1000);
	}

	d = date<int>();
	for (unsigned i = 1; i < 10000000; ++i) {
		d += microseconds(1);
		ensure (microsecond(d) == i % 1000000);
	}
}

inline void check_datetime()
{
	test_days();
	test_weekday_difference();
	test_date();
	/*
	date d(2014, 7, 25);
	ensure (year(d) == 2014);
	ensure (month(d) == 7);
	ensure (day(d) == 25);

	double e = excel(d);

	date d2(e);
	ensure (year(d2) == 2014);
	ensure (month(d2) == 7);
	ensure (day(d2) == 25);

	int y, m, d;
	std::tie(y,m,d) = days(d);
	*/
}

#endif // _DEBUG

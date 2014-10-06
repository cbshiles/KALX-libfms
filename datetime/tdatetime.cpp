// tdatetime.cpp - test datetime library
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iterator>
//#include "datetime.h"
#include "calendar.h"

using namespace datetime;
using namespace std;

void
fms_test_date_adjust(void)
{
	ensure (date(2012, 1, 2).is_holiday(calendar::NYS));
	ensure (date(2012, 1, 2).weekday() == DAY_MON);

	ensure (date(2011, 12, 31).weekday() == DAY_SAT);
	ensure (!date(2011, 12, 31).is_bday(calendar::NYS));
	ensure (!date(2012, 1, 2).is_bday(calendar::NYS));

	ensure (date(2011, 12, 31).adjust(ROLL_NONE, calendar::NYS) == date(2011, 12, 31)); // only holidays rolled

	ensure (date(2011, 12, 31).adjust(ROLL_FOLLOWING_BUSINESS, calendar::NYS) == date(2012,  1,  3));
	ensure (date(2011, 12, 31).adjust(ROLL_MODIFIED_FOLLOWING, calendar::NYS) == date(2011, 12, 30));
	ensure (date(2011, 12, 31).adjust(ROLL_PREVIOUS_BUSINESS,  calendar::NYS) == date(2011, 12, 30));
	ensure (date(2012,  1,  1).adjust(ROLL_MODIFIED_PREVIOUS,  calendar::NYS) == date(2012,  1,  3));

	ensure (!date(2000,1,1).is_holiday());
}

#define NTESTS 100

int
rand_between(int a, int b)
{
	return a + rand()%(b - a + 1);
}

void
fms_test_date_date(void)
{
	double e;
	date f;
	time_t t;
	int y, m, d, h, n, s, y_, m_, d_, h_, n_, s_;
	int dst;

	date epoch(1970, 1, 1);
	e = epoch.excel();
	ensure (e == EXCEL_EPOCH);

	y = 2086;
	m = 3;
	d = 10;
	h = 2; // dst leaping forward
	n = 52;
	s = 54;

	f = date(y, m , d, h, n, s);
	f.localtime(&y_, &m_, &d_, &h_, &n_, &s_, 0, 0, &dst);
	ensure (y == y_);
	ensure (m == m_);
	ensure (d == d_);
//	ensure (h == h_); 
	ensure (h == h_ + 1); // dst
	ensure (n == n_);
	ensure (s == s_);

	t = f.time();
	date g(t);
	ensure (f == g);

	for (int i = 0; i < NTESTS; ++i) {
		y = rand_between(1970, 2100);
		m = rand_between(1, 12);
		d = rand_between(1, 28);
		h = rand_between(0, 23);
		n = rand_between(0, 59);
		s = rand_between(0, 59);

		f = date(y, m , d, h, n, s);
		f.localtime(&y_, &m_, &d_, &h_, &n_, &s_, 0, 0, &dst);
		ensure (y == y_);
		ensure (m == m_);
		ensure (d == d_);
		ensure (h == h_);
		ensure (n == n_);
		ensure (s == s_);
	}
}

void
fms_test_date_dcf(void)
{
	date d1, d2;

	d1 = date(2007, 12, 15);
	d2 = date(2008, 1, 10);
	ensure (d2.diff_actual_actual_isda(d1) == 17./365 + 9./366);

	d1 = date(2003, 10, 22);
	d2 = date(2003, 12, 23);
	ensure (d2.diff_30u_360(d1) == 2./12 + 1./360);
}

void
fms_test_datetime(void)
{
	fms_test_date_adjust();
	fms_test_date_date();
	fms_test_date_dcf();
}
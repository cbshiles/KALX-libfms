// forward_rate_agreement.h - cash deposit indicative data and cash flows
// Copyright (c) 2011 KALX, LLC. All rights reserved.
#pragma once
#include "../datetime/datetime.h"
#include "instrument.h"

namespace fms {
namespace fixed_income {

	//!!!jl2372 inherit from fixed_income::interest_rate_leg
	template<class T = double, class C = double>
	struct forward_rate_agreement : public vector::instrument<T,C,fms::datetime::date> {
		// indicative data
		int count_; fms::datetime::time_unit unit_; // e.g., 2, UNIT_WEEKS
		fms::datetime::day_count_basis dcb_;
		fms::datetime::roll_convention roll_;
		fms::datetime::holiday_calendar cal_;
		
		// typical FRA conventions
		forward_rate_agreement(
			int count = 3, fms::datetime::time_unit unit = fms::datetime::UNIT_MONTHS,
			fms::datetime::day_count_basis dcb = DCB_ACTUAL_360,
			fms::datetime::roll_convention roll = ROLL_MODIFIED_FOLLOWING,
			fms::datetime::holiday_calendar cal = CALENDAR_NONE)
		:
			count_(count), unit_(unit), dcb_(dcb), roll_(roll), cal_(cal)
		{ }
		forward_rate_agreement(const forward_rate_agreement&) = default;
		forward_rate_agreement& operator=(const forward_rate_agreement&) = default;
		~forward_rate_agreement()
		{ }

		// create cash flows given settlement, effective, and forward rate
		forward_rate_agreement& fix(const fms::datetime::date& set, const fms::datetime::date& eff, const C& forward)
		{
			fms::datetime::date d0(eff);
			add(d0.diffyears(set), -1);
			ensure (time(0) >= 0);

			fms::datetime::date d1(d0);
			d1.incr(count_, unit_).adjust(roll_, cal_);
			add(d1.diffyears(set), 1 + forward*d1.diff_dcb(d0, dcb_));

			ensure (cash(1) > 0 || !"fms::fixed_income::forward_rate_agreement: forward not arbitrage free");

			return *this;
		}

	};

} // namespace instrument
} // namespace fms

#ifdef _DEBUG

using namespace fms::fixed_income;
using namespace fms::datetime;

void test_fixed_income_forward_rate_agreement()
{
	forward_rate_agreement<> fra;

	fra.fix(date(2014, 10, 22), date(2015, 10, 22), 0.02);
	
	date d(2014, 10, 22);
	d = d.addyears(fra.time(0));
	int ymd;
	ymd = d.ymd();
	ensure(ymd == 20151022);
	
	d = d.addyears(fra.time(1));
	ymd = d.ymd();
	ensure(ymd == 20160122);
	
	double r;
	r = fra.cash(0);
	ensure(r == -1);
	r = fra.cash(1);
	ensure(r == 1 + 0.02*d.diff_dcb(date(2015, 10, 22), DCB_ACTUAL_360));

	//!!!lf343 add more tests
}

#endif // _DEBUG


// forward_rate_agreement.h - cash deposit indicative data and cash flows
// Copyright (c) 2011 KALX, LLC. All rights reserved.
#pragma once
#include "../datetime/datetime.h"
#include "instrument.h"

namespace fms {
namespace fixed_income {

	//!!!jl2372 inherit from fixed_income::interest_rate_leg
	template<class T = double, class C = double>

	struct forward_rate_agreement : public interest_rate_leg::leg<T, C> {
		// typical FRA conventions
		forward_rate_agreement(
		int count = 3, fms::datetime::time_unit unit = fms::datetime::UNIT_MONTHS,
		fms::datetime::day_count_basis dcb = DCB_ACTUAL_360,
		fms::datetime::roll_convention roll = ROLL_MODIFIED_FOLLOWING,
		fms::datetime::holiday_calendar cal = CALENDAR_NONE)
		{
			leg(count, unit, FREQ_SEMIANNUALLY, dcb, roll, cal);
		}
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

	fra.fix(date(2014, 10,22), date(2015, 10, 22), 0.02);
	//!!!lf343 add more tests
}

#endif // _DEBUG


// forward_rate_agreement.h - cash deposit indicative data and cash flows
// Copyright (c) 2011 KALX, LLC. All rights reserved.
#pragma once
#include "../datetime/datetime.h"
#include "instrument.h"

namespace fms {
namespace fixed_income {

	template<class T = double, class C = double>
	struct forward_rate_agreement : public instrument<T,C,fms::datetime::date> {
		T t_[2];
		C c_[2];
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
		forward_rate_agreement& fix(const fms::datetime::date& val, const C& forward) override
		{
			fms::datetime::date eff_{effective()};

			ensure (eff_);

			t_[0] = eff_.diffyears(val);
			ensure(t_[0] >= 0);
			c_[0] = -1;

			fms::datetime::date d(eff_);
			d.incr(count_, unit_).adjust(roll_, cal_);
			t_[1] = d.diffyears(val);
			c_[1] = 1 + forward*d.diff_dcb(eff_, dcb_);

			ensure (c_[1] > 0); // otherwise arbitrage exists

			return *this;
		}

		size_t size() const override
		{
			return 2;
		}
		const T* time() const override
		{
			return t_;
		}
		const C* cash() const override
		{
			return c_;
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

	fra.effective(date(2015, 10,22)).fix(date(2014, 10, 22), 0.02);
}

#endif // _DEBUG


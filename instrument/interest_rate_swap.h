// interest_rate_swap.h - cash deposit indicative data and cash flows
// Copyright (c) 2011 KALX, LLC. All rights reserved.
#pragma once
#include "../datetime/datetime.h"
#include "instrument.h"
/*

namespace fms {
namespace fixed_income {

	template<class T = double>
	struct interest_rate_swap : public instrument<T,date> {
		// indicative data
		datetime::date eff_;
		int count_; fms::datetime::time_unit unit_; // e.g., 10, UNIT_YEARS
		fms::datetime::payment_frequency freq_;
		fms::datetime::day_count_basis dcb_;
		fms::datetime::roll_convention roll_;
		fms::datetime::holiday_calendar cal_;
		fms::datetime::payment_frequency float_freq_;
		fms::datetime::day_count_basis float_dcb_;

		// typical swap conventions
		interest_rate_swap()
		:	count_(3), unit_(fms::datetime::UNIT_MONTHS), 
			freq_(fms::datetime::FREQ_SEMIANNUALLY),
			dcb_(fms::datetime::DCB_30U_360), 
			roll_(fms::datetime::ROLL_MODIFIED_FOLLOWING), 
			cal_(fms::datetime::CALENDAR_NONE),
			float_freq_(fms::datetime::FREQ_QUARTERLY),
			float_dcb_(fms::datetime::DCB_ACTUAL_360)
		{ }
		interest_rate_swap(
			const date& eff,
			int count, fms::datetime::time_unit unit,
			fms::datetime::payment_frequency freq = FREQ_SEMIANNUALLY,
			fms::datetime::day_count_basis dcb = DCB_30U_360,
			fms::datetime::roll_convention roll = ROLL_MODIFIED_FOLLOWING,
			fms::datetime::holiday_calendar cal = CALENDAR_NONE,
			fms::datetime::payment_frequency float_freq = FREQ_QUARTERLY,
			fms::datetime::day_count_basis float_dcb= DCB_ACTUAL_360)
		: 
		  eff_(eff), count_(count), unit_(unit), freq_(freq),
		  dcb_(dcb), roll_(roll), cal_(cal),
		  float_freq_(float_freq), float_dcb_(float_dcb)
		{
			ensure (0 < freq_ && freq_ <= FREQ_MONTHLY);
		}
		virtual ~interest_rate_swap()
		{ }

		// create cash flows given settlement date and fixed coupon
		const interest_rate_swap<T>& fix(const date& val, double coupon)
		{
			std::vector<T> u_;
			std::vector<C> c_;

			date mat(eff_);
			mat.incr(count_, unit_);
			mat.adjust(roll_, cal_);

			t_.push_back(eff_.diffyears(val));
			c_.push_back(-1.);

			date d0(eff_);
			for (int i = 1; d0 < mat; ++i) {
				date d1(eff_);
				d1.incr(12*i/freq_, fms::datetime::UNIT_MONTHS).adjust(roll_, cal_);
				t_.push_back(d1.diffyears(val));
				c_.push_back(coupon*d1.diff_dcb(d0, dcb_));
				d0 = d1;
			}

			// principal
			if (d0 == mat)
				c_.back() += 1.0;
			else {
				t_.push_back(mat.diffyears(val));
				c_.push_back(1. + coupon*mat.diff_dcb(d0, dcb_));
			}

			set(t_, c_);

			return *this;
		}
	};

} // namespace instrument
} // namespace fms
*/
#ifdef _DEBUG

using namespace fms::fixed_income;

void test_fixed_income_interest_rate_swap()
{
//	interest_rate_swap<> irs;
}

#endif // _DEBUG

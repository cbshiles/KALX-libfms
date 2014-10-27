// interest_rate_leg.h - fixed and floating legs of an interest rate swap
#pragma once
#include "../datetime/datetime.h"
#include "instrument.h"

namespace fms {
namespace fixed_income {

	template<class T = double, class C = double, class D = void*>
	class interest_rate_leg : public insturment<T,C,D> {
		std::vector<T> t_;
		std::vector<C> c_;
	public:
		iterest_rate_leg(size_t n = 0, const T* t = 0, const C* c = 0)
			: t_(t, t + n), c_(c + n)
		{ }
		interest_rate_leg(const interest_rate_leg&) = default;
		interest_rate_leg& operator=(const interest_rate_leg&) = default;
		virtual ~interest_rate_leg()
		{ }

		// add single cash flow
		virtual fix(const D& d, const C& c = 1) override
		{
			ensure (effective());

			t_.push_back(d.diffyears(effective()));
			c_.push_back(c);

			ensure (increasing(t_.begin(), t_.end()));
		}
		size_t size() const override
		{
			return t_.size();
		}
		const T* time() const override
		{
			return t_.data();
		}
		const C* cash() const override
		{
			return c_.data();
		}

	};

	//!!! move to interest_rate_leg_fixed.h
	// fixed payments
	template<class T = double, class C = double>
	class interest_rate_leg_fixed : public interest_rate_leg<T,C,fms::datetime::date> {
		std::vector<T> t_;
		std::vector<C> c_;
	public:
		// indicative data
		int count_; fms::datetime::time_unit unit_; // e.g., 10, UNIT_YEARS
		fms::datetime::payment_frequency freq_;
		fms::datetime::day_count_basis dcb_;
		fms::datetime::roll_convention roll_;
		fms::datetime::holiday_calendar cal_;
		// typical swap conventions
		interest_rate_leg_fixed(
			int count = 3, fms::datetime::time_unit unit = fms::datetime::UNIT_MONTHS,
			fms::datetime::payment_frequency freq = FREQ_SEMIANNUALLY,
			fms::datetime::day_count_basis dcb = DCB_30U_360,
			fms::datetime::roll_convention roll = ROLL_MODIFIED_FOLLOWING,
			fms::datetime::holiday_calendar cal = CALENDAR_NONE,
			fms::datetime::payment_frequency float_freq = FREQ_QUARTERLY,
			fms::datetime::day_count_basis float_dcb= DCB_ACTUAL_360)
		: 
		  count_(count), unit_(unit), freq_(freq),
		  dcb_(dcb), roll_(roll), cal_(cal),
		{
			ensure (0 < freq_ && freq_ <= FREQ_MONTHLY);
		}
		virtual ~interest_rate_leg_fixed()
		{ }

		// create cash flows given settlement date and fixed coupon
		const interest_rate_leg_fixed<T,C>& fix(const date& val, double coupon)
		{
			fms::datetime::date eff_{effective());

			ensure (eff_);

			date mat(eff_);
			mat.incr(count_, unit_);
			mat.adjust(roll_, cal_);

			date d0(eff_);
			for (int i = 1; d0 <= mat; ++i) {
				date d1(eff_);
				d1.incr(12*i/freq_, fms::datetime::UNIT_MONTHS).adjust(roll_, cal_);
				add(d1, coupon*d1.diff_dcb(d0, dcb_));
				d0 = d1;
			}

			return *this;
		}
	};

	//!!! move to interest_rate_leg_float.h
	template<class T = double, class C = double>
	class interest_rate_leg_float : public interest_rate_leg<T,C,fms::datetime::date> {
	public:
		// indicative data
		int count_; fms::datetime::time_unit unit_; // e.g., 10, UNIT_YEARS
		fms::datetime::payment_frequency freq_;
		fms::datetime::day_count_basis dcb_;
		fms::datetime::roll_convention roll_;
		fms::datetime::holiday_calendar cal_;
		// typical swap conventions
		interest_rate_leg_float(
			int count = 3, fms::datetime::time_unit unit = fms::datetime::UNIT_MONTHS,
			fms::datetime::payment_frequency freq = FREQ_SEMIANNUALLY,
			fms::datetime::day_count_basis dcb = DCB_30U_360,
			fms::datetime::roll_convention roll = ROLL_MODIFIED_FOLLOWING,
			fms::datetime::holiday_calendar cal = CALENDAR_NONE,
			fms::datetime::payment_frequency float_freq = FREQ_QUARTERLY,
			fms::datetime::day_count_basis float_dcb= DCB_ACTUAL_360)
		: 
		  count_(count), unit_(unit), freq_(freq),
		  dcb_(dcb), roll_(roll), cal_(cal),
		{
			ensure (0 < freq_ && freq_ <= FREQ_MONTHLY);
		}
		virtual ~interest_rate_leg_float()
		{ }

		// create cash flows given settlement date and fixed coupon
		const interest_rate_leg_float<T,C>& fix(const fms::datetime::date& val, double coupon)
		{
			fms::datetime::date eff_{effective());

			ensure (eff_);

			date mat(eff_);
			mat.incr(count_, unit_);
			mat.adjust(roll_, cal_);

			// long the floating leg
			fix(eff_, 1);
			// short the fixed leg
			fix(mat, -1);

			return *this;
		}
	};

} // namespace instrument
} // namespace fms

#ifdef _DEBUG

using namespace fms::fixed_income;

void test_fixed_income_interest_rate_leg()
{
	interest_rate_leg_fixed<> irlf;
}

#endif // _DEBUG
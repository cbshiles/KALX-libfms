// cash_deposit.h - cash deposit indicative data and cash flows
#pragma once
#include "../datetime/datetime.h"
#include "instrument.h"

namespace fms {
namespace fixed_income {

	//!!!dgtsx inherit from fixed_income::interest_rate_leg

	template<class T = double, class C = double>
	class cash_deposit : public fixed_income::leg<T, C> {
	public:
		
		// typical cash deposit conventions
		cash_deposit()
			:
			leg(1, fms::datetime::UNIT_DAYS, FREQ_SEMIANNUALLY, fms::datetime::DCB_ACTUAL_360, fms::datetime::ROLL_MODIFIED_FOLLOWING, fms::datetime::CALENDAR_NONE)
		{ }
		cash_deposit(
			int count, fms::datetime::time_unit unit,
			fms::datetime::day_count_basis dcb = DCB_30U_360,
			fms::datetime::roll_convention roll = ROLL_MODIFIED_FOLLOWING,
			fms::datetime::holiday_calendar cal = CALENDAR_NONE)
			:
			leg(count, unit, FREQ_SEMIANNUALLY, dcb, roll, cal)
		{ }

		cash_deposit(const cash_deposit&) = default;
		cash_deposit& operator=(const cash_deposit&) = default;
		~cash_deposit()
		{ }

		cash_deposit<T, C>& fix(const fms::datetime::date& set, const fms::datetime::date& eff, const C& rate)
		{
			datetime::date d0(eff);
			add(d0.diffyears(set), -1);

			datetime::date d1(d0);
			d1.incr(count_, unit_).adjust(roll_, cal_);
			add(d1.diffyears(set), 1 + rate*d1.diff_dcb(d0, dcb_));

			ensure(cash(1) > 0 || !"fms::fixed_income::cash_deposit: coupon not arbitrage free");

			return *this;
		}
		// settle using T + days
		cash_deposit<T, C>& fix(const fms::datetime::date& set, int days, const C& rate)
		{
			fms::datetime::date eff(set);

			eff.incr(days, fms::datetime::UNIT_DAYS).adjust(roll_, call_);

			return fix(set, eff, rate);
		}
	};

	/*
	template<class T = double, class C = double>
	class cash_deposit : public vector::instrument<T,C,fms::datetime::date> {
	public:
		// indicative data
		unsigned int count_; fms::datetime::time_unit unit_; // e.g., 2, UNIT_WEEKS
		fms::datetime::day_count_basis dcb_;
		fms::datetime::roll_convention roll_;
		fms::datetime::holiday_calendar cal_;

		// typical cash deposit conventions
		cash_deposit() 
		:
		  	count_(1), unit_(fms::datetime::UNIT_DAYS), 
			dcb_(fms::datetime::DCB_ACTUAL_360), 
			roll_(fms::datetime::ROLL_MODIFIED_FOLLOWING), 
			cal_(fms::datetime::CALENDAR_NONE)
		{ }
		cash_deposit(
			int count, fms::datetime::time_unit unit,
			fms::datetime::day_count_basis dcb = DCB_30U_360,
			fms::datetime::roll_convention roll = ROLL_MODIFIED_FOLLOWING,
			fms::datetime::holiday_calendar cal = CALENDAR_NONE)
		:
			count_(count), unit_(unit), dcb_(dcb), roll_(roll), cal_(cal)
		{ }

		cash_deposit(const cash_deposit&) = default;
		cash_deposit& operator=(const cash_deposit&) = default;
		~cash_deposit()
		{ }

		cash_deposit<T,C>& fix(const fms::datetime::date& set, const fms::datetime::date& eff, const C& rate)
		{
			datetime::date d0(eff);
			add(d0.diffyears(set), -1);

			datetime::date d1(d0);
			d1.incr(count_, unit_).adjust(roll_, cal_);
			add(d1.diffyears(set), 1 + rate*d1.diff_dcb(d0, dcb_));

			ensure (cash(1) > 0 || !"fms::fixed_income::cash_deposit: coupon not arbitrage free");

			return *this;
		}
		// settle using T + days
		cash_deposit<T,C>& fix(const fms::datetime::date& set, int days, const C& rate)
		{
			fms::datetime::date eff(set);

			eff.incr(days, fms::datetime::UNIT_DAYS).adjust(roll_, call_);

			return fix(set, eff, rate);
		}
	};
	*/

} // namespace fixed_income
} // namespace fms

#ifdef _DEBUG

using namespace fms::datetime;
using namespace fms::fixed_income;

void test_fixed_income_cash_deposit()
{
	cash_deposit<> cd;
	ensure (cd.size() == 0); //

	date d(2014,1,1);
	cd.fix(d, d.incr(2,UNIT_DAYS).adjust(cd.roll_), 0.01);
	ensure (cd.size() == 2);

	//!!!Giorgio add better tests
	date d1;
	d = d.addyears(cd.time(0));
	int ymd;
	ymd = d.ymd();
	d = d.addyears(cd.time(1));
	ymd = d.ymd();
	double r;
	r = cd.cash(0);
	r = cd.cash(1);

}

#endif // _DEBUG
// cash_deposit.h - cash deposit indicative data and cash flows
#pragma once
#include "../datetime/datetime.h"
#include "instrument.h"

namespace fms {
namespace fixed_income {

	template<class T = double, class C = double>
	class cash_deposit : public instrument<T,C,fms::datetime::date> {
		T t_[2];
		C c_[2];
	public:
		// indicative data
		unsigned int set_; // number of days until settlement
		unsigned int count_; fms::datetime::time_unit unit_; // e.g., 2, UNIT_WEEKS
		fms::datetime::day_count_basis dcb_;
		fms::datetime::roll_convention roll_;
		fms::datetime::holiday_calendar cal_;

		// typical cash deposit conventions
		cash_deposit() 
		:
			set_(2), // T+2
		  	count_(1), unit_(fms::datetime::UNIT_DAYS), 
			dcb_(fms::datetime::DCB_ACTUAL_360), 
			roll_(fms::datetime::ROLL_MODIFIED_FOLLOWING), 
			cal_(fms::datetime::CALENDAR_NONE)
		{ }
		cash_deposit(
			int eff,
			int count, fms::datetime::time_unit unit,
			fms::datetime::day_count_basis dcb = DCB_30U_360,
			fms::datetime::roll_convention roll = ROLL_MODIFIED_FOLLOWING,
			fms::datetime::holiday_calendar cal = CALENDAR_NONE)
		:
			set_(eff), count_(count), unit_(unit),
		    dcb_(dcb), roll_(roll), cal_(cal)
		{
		}

		cash_deposit(const cash_deposit&) = default;
		cash_deposit& operator=(const cash_deposit&) = default;
		~cash_deposit()
		{ }

		// create cash flows given valuation and rate
		cash_deposit& fix(const fms::datetime::date& val, const C& rate) override
		{
			ensure (effective());

			datetime::date d0(val);
			d0.incr(set_, fms::datetime::UNIT_DAYS).adjust(roll_, cal_);
			t_[0] = d0.diffyears(val);
			c_[0] = -1;

			datetime::date d1(d0);
			d1.incr(count_, unit_).adjust(roll_, cal_);
			t_[1] = d1.diffyears(val);
			c_[1] = 1 + rate*d1.diff_dcb(d0, dcb_);

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

} // namespace fixed_income
} // namespace fms

#ifdef _DEBUG

using namespace fms::datetime;
using namespace fms::fixed_income;

void test_fixed_income_cash_deposit()
{
	cash_deposit<> cd;
	ensure (cd.size() == 0); // must call fix()

	instrument<double,double,date>& i{cd};
	date d(2014,1,1);
	i.effective(d).fix(d, 0.01);
	ensure (i.size() == 2);

	date d1;
	d = d.addyears(i.time(0));
	int ymd;
	ymd = d.ymd();
	d = d.addyears(i.time(1));
	ymd = d.ymd();
	double r;
	r = i.cash(0);
	r = i.cash(1);
}

#endif // _DEBUG
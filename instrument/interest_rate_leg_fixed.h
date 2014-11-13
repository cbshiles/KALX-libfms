#pragma once
#include "../datetime/datetime.h"
#include "instrument.h"

//!!!bolenpeng move to interest_rate_leg_fixed.h
// fixed payments
namespace fms {
	namespace fixed {
		template<class T = double, class C = double>
		class leg : public fixed_income::leg<T, C> {
		public:
			leg() //!!! use base constructor!!!
			{ }
			~leg_fixed()
			{ }

			// create cash flows given settlement date and fixed coupon
			const fixed<T, C>& fix(const date& set, const date& eff, const C& coupon)
			{
				date mat(eff);
				mat.incr(count_, unit_);
				mat.adjust(roll_, cal_);

				date d0(eff);
				for (int i = 1; d0 <= mat; ++i) {
					date d1(eff);
					d1.incr(12 * i / freq_, fms::datetime::UNIT_MONTHS).adjust(roll_, cal_);
					add(d1, coupon*d1.diff_dcb(d0, dcb_));
					d0 = d1;
				}

				return *this;
			}
		};
	} // namespace instrument
} // namespace fms

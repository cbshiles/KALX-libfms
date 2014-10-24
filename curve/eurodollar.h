// eurodollar.h - Eurodollar related functions.
// See http://cmegroup.com/
#pragma once
#include "../datetime/datetime.h"

namespace fms {
namespace eurodollar {

	// index of closest contract past given days
	inline int 
	first_contract(const fms::datetime::date& d, int days)
	{
		ensure (days >= 0);
		int ordinal = 1;

		fms::datetime::date d_(d);
		d_ = fms::datetime::date(d_.year(), 3*(1 + (d_.month() - 1)/3), 15);
		d_.imm(3, fms::datetime::DAY_WED);
		if (d_.diffdays(d) < 0) {
			d_.incr(3, fms::datetime::UNIT_MONTH);
			d_.imm(3, fms::datetime::DAY_WED);
		}

		ensure (d_.diffdays(d) > 0);
	
		while (d_.diffdays(d) < days) {
			d_.incr(3, fms::datetime::UNIT_MONTH);
			d_.imm(3, fms::datetime::DAY_WED);
			if (d_.month() % 3 == 0)
				++ordinal;
		}

		return ordinal;
	}

} // namespace eurodollar
} // namespace fms
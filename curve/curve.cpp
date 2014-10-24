// curve.cpp - test curve routines
#include <iostream>
#include "pwflat.h"
#include "instrument.h"
#include "cash_deposit.h"
#include "forward_rate_agreement.h"
#include "interest_rate_swap.h"

using namespace fms;

int main()
{
	try {
		test_pwflat_value();
		test_pwflat_integral();
		test_pwflat_spot();
		test_pwflat_present_value();
		test_pwflat_duration();
		test_pwflat_curve();
		test_pwflat_pointer_curve();
		test_pwflat_vector_curve();
//		test_pwflat_bootstrap();
		test_fixed_income_instrument();
		test_fixed_income_cash_deposit();
		test_fixed_income_forward_rate_agreement();
		test_fixed_income_interest_rate_swap();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
// curve.cpp - test curve routines
#include <iostream>
#include "pwflat.h"

using namespace fms;

int main()
{
	try {
		test_pwflat_value();
		test_pwflat_integral();
		test_pwflat_curve();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
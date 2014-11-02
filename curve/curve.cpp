// curve.cpp - test curve routines
#include <iostream>
#include "pwflat.h" // includes pwflat_function.h
#include "bootstrap_functions.h"

using namespace fms;

int main()
{
	try {
		test_pwflat_function();
		test_pwflat();

		
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
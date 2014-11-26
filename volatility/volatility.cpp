// volatility.cpp
#include <iostream>
#include "curve.h"

int main()
{
	try {
		test_volatility_curve();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
// volatility.cpp
#include <iostream>
#include "curve.h"

int main()
{
	try {
#ifdef _DEBUG
		test_volatility_curve();
#endif
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
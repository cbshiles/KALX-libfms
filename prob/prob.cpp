// prob.cpp - test prob module
#include <iostream>
#include "normal.h"

int main()
{
	try {
		test_prob_normal();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}

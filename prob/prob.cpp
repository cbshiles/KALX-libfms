// prob.cpp - test prob module
#include <iostream>
#include "logistic.h"
#include "normal.h"

int main()
{
	try {
#ifdef _DEBUG
		test_prob_logistic();
		test_prob_normal();
#endif
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}

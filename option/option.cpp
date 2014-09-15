// option.cpp - test option module
#include <iostream>
#include "black.h"

int main()
{
	try {
		test_option_black();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
// option.cpp - test option module
#include <iostream>
#include "black.h"

int main()
{
	try {
#ifdef _DEBUG
		test_option_black();
#endif
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
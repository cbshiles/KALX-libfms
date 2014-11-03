// datetime.cpp - datetime tests
#include <iostream>
#include "datetime.h"

int
main(void)
{
	try {
		test_datetime();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
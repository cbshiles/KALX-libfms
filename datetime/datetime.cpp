// datetime.cpp - datetime tests
#include <iostream>
#include "datetime.h"

int
main(void)
{
	try {
#ifdef _DEBUG
		test_datetime();
#endif
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
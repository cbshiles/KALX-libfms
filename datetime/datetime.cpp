// main.cpp - driver for datetime tests
#include <iostream>

void fms_test_datetime(void);

int
main(void)
{
	try {
		fms_test_datetime();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
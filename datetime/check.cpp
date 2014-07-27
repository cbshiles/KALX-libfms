// check.cpp - check datetime routines
#include <iostream>
#include "dt.h"
#include "datetime.h"
#ifdef _WIN32
#include "excel_clock.h"
#endif

int main()
{
	try {
#ifdef _WIN32
		check_high_performance_clock();
#endif
		check_dt();
		check_datetime();
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;

		return -1;
	}

	return 0;
}

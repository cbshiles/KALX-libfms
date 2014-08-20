// check.cpp - check datetime routines
#include <iostream>
//#include "dt.h"
//#include "datetime.h"
#ifdef _WIN32
#include "high_resolution_clock.h"
#endif
#include "chrono_util.h"

int main()
{
	try {
#ifdef _WIN32
		check_high_resolution_clock();
#endif
		check_chrono_util();
//		check_dt();
//		check_datetime();
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;

		return -1;
	}

	return 0;
}


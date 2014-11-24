// root.cpp - root finding
#include <iostream>
#include "root1d.h"

int main()
{
	try {
#ifdef _DEBUG
		test_root1d();
#endif
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
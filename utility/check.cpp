#include <iostream>
#include "enumerator.h"

int main()
{
	try {
		check_enumerator();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
// instrument.cpp - test instruments
#include <iostream>
#include <stdexcept>

int main()
{
	try {
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
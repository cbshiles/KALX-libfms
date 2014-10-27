#include <iostream>
#include "jacobi.h"
#include "trnlsp.h"

int main()
{
	try {
		test_mkl_jacobi();
		test_mkl_trnlsp();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
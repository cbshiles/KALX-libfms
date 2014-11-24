#include <iostream>
#include "fmsmkl.h"
#include "jacobi.h"
#include "trnlsp.h"

int main()
{
	try {
#ifdef _DEBUG
		test_mkl_jacobi();
		test_mkl_trnlsp();
#endif
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
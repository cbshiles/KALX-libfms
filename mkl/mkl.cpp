#include <iostream>
#include "jacobi.h"
#include "trnlsp.h"
#include "trnlspbc.h"

int main()
{
	try {
#ifdef _DEBUG
		test_mkl_jacobi();
		test_mkl_trnlsp();
		test_mkl_trnlspbc();
#endif
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
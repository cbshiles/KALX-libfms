#include <iostream>
#include "trnlsp.h"

int main()
{
	try {
		// F(x) = x, dF(x) = I
		std::vector<double> x{1,1}, eps{1e-10, 1e-10, 1e-10, 1e-10, 1e-10, 1e-10};

		mkl::trnlsp problem(2, 2, &x[0], &eps[0]);
		problem.function([](const double* x) { return std::vector<double>(x, x + 2); });
		problem.jacobian([](const double* ) { return std::vector<double>({1, 0, 0, 1}); });

		int ret;
		ret = problem.step();
		ret = problem.step();
		ret = problem.step();

	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}
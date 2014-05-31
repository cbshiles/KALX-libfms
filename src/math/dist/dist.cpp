// prob.cpp - test prob module
#include <iostream>

void test_normal_pdf(void);
void test_normal_cdf(void);
void test_normal_inv(void);

int main()
{
	try {
//		test_normal_pdf();
//		test_normal_cdf();
		test_normal_inv();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}

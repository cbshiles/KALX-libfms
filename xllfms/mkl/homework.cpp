// homework.cpp
#include "mkl/jacobi.h"
#include "xllmkl.h"

using namespace xll;
using namespace mkl;

// jacobian {x[0],x[1] -> {2*x[0], 0, 1; 0, 3*x[1]^2, 1}
static AddIn xai_test_function1(
	Function(XLL_LPOPER, "?xll_test_function1", "TEST.FUNCTION1")
	.Arg(XLL_LPOPER, "x", "is an optional array of two numbers")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Return handle to the function {x[0], x[1]} -> {x[0]^2, x[1]^3, x[0] + x[1]}")
	.Documentation("Documentation.")
	);
LPOPER WINAPI xll_test_function1(LPOPER px)
{
#pragma XLLEXPORT
	static OPER y;

	try {
		auto f = [](const vec<double>& x) {
			ensure (x.size() == 2);
			vec<double> y(3);

			y[0] = x[0]*x[0];
			y[1] = x[1]*x[1]*x[1];
			y[2] = x[0] + x[1];

			return y;
		};

		if (px->xltype == xltypeMissing) {
			handle<fun<double>> hf = new fun<double>(f);

			y.resize(1,1);
			y[0] = hf.get();
		}
		else {
			ensure (px->size() == 2);
			vec<double> x(2);
			x[0] = (*px)[0];
			x[1] = (*px)[1];

			auto y_ = f(x);

			y.resize(1,3);
			std::copy(y_.begin(), y_.end(), y.begin());
		}
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return &y;
}
/*
// http://www.mathworks.com/help/optim/ug/lsqnonlin.html
static AddIn xai_test_function2(
	Function(XLL_LPOPER, "?xll_test_function2", "TEST.FUNCTION2")
	.Arg(XLL_LPOPER, "Arg", "is an array of two numbers.")
	.Category(CATEGORY)
	.FunctionHelp("matlab example with range dimension 10")
	.Documentation("Documentation.")
	);
LPOPER WINAPI xll_test_function2(const LPOPER px)
{
#pragma XLLEXPORT
	static OPER o(10,1);

	try {
		const OPER& x{*px};

		for (xword k = 1; k <= 10; ++k)
			o[k-1] = 2 + 2*k - exp(k*x[0]) - exp(k*x[1]);
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		o = OPER(xlerr::Num);
	}

	return &o;
}

// curve fitting !!!jl2372
// x = {1, 0.2}, x* = {1.881831115804464 0.700242006994123}, minres = 0.053812720914713
static AddIn xai_test_function3(
	Function(XLL_LPOPER, "?xll_test_function3", "TEST.FUNCTION3")
	.Arg(XLL_LPOPER, "Arg", "is an array of two numbers.")
	.Category(CATEGORY)
	.FunctionHelp("matlab example with range dimension 10")
	.Documentation("Documentation.")
	);
LPOPER WINAPI xll_test_function3(const LPOPER px)
{
#pragma XLLEXPORT
	static OPER o(10,1);

	try {
		static std::vector<double> xdata { -2,-1.64,-1.33,-0.7,0,0.45,1.2,1.64,2.32,2.9 };
		static std::vector<double> ydata { 0.699369,0.700462,0.695354,1.03905,1.97389,2.41143,1.91091,0.919576,-0.730975,-1.42001 };

		const OPER& x{*px};

		for (xword k = 0; k < 10; ++k)
			o[k] = x[0]*cos(x[1]*xdata[k]) + x[1]*cos(x[0]*xdata[k]) - ydata[k];
			
	}
	catch(const std::exception& ex) {
		XLL_ERROR(ex.what());

		o = OPER(xlerr::Num);
	}

	return &o;
}
*/
//!!!lf343
//!!!sjm366
//!!!zoewanforest
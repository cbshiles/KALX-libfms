// xllmkl.h - common MKL routines
#pragma once
#include "../xll8/xll/xll.h"

#ifndef CATEGORY
#define CATEGORY _T("MKL")
#endif

typedef xll::traits<XLOPERX>::xchar xchar;
typedef xll::traits<XLOPERX>::xword xword;
typedef xll::traits<XLOPERX>::xfp xfp;

namespace xllmkl {

	// convert registerId for f:OPER -> OPER to f:vector<double> -> vector<double>
	inline std::function<std::vector<double>(const std::vector<double>&)> vectorize(xword m, xword n, double f)
	{
		return [m,n,f](const std::vector<double>& x) {
			ensure (x.size() == m);

			OPERX X(m,1);
			std::copy(x.begin(), x.end(), X.begin());
		
			OPER Y = xll::Excel<XLOPER>(xlUDF, OPERX(f), X);
			ensure (Y.size() == n);

			std::vector<double> y(n);
			std::copy(Y.begin(), Y.end(), y.begin());
			
			return y;
		};
	}

}
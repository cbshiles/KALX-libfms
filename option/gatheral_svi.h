// gatheral_svi.h - Jim Gatheral stochastic volatility inspired curve
#pragma once
#include <cmath>

namespace fms {

	// stochastic volatility inspired
	// a - level
	// b - scale
	// rho - slope
	// k - strike
	// m - monieness
	// sigma - 
	template<class X = double>
	inline X gatheral_svi(X a, X b, X sigma, X rho, X m, X k)
	{
		return a + b*(rho*(k - m) + sqrt((k - m)*(k - m) + sigma*sigma));
	}

} // fms
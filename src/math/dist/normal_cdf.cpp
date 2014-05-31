// normal_cdf.cpp - test normal::cdf
#include <limits>
#include "normal.h"

template<class X>
void normal_cdf(void)
{
	X y;
	X eps = std::numeric_limits<X>::epsilon();

	struct { X x, y; } normal_cdf_dat[] = {
#include "normal_cdf.dat"
	};
	for (auto xy : normal_cdf_dat) {
		y = math::dist::normal::cdf(xy.x);
		ensure (static_cast<X>(fabs(y - xy.y) < 8*eps));
		y = erfc(-xy.x/M_SQRT2)/2;
		ensure (static_cast<X>(fabs(y - xy.y) < 1*eps));
	}
}

void normal_cdf(void)
{
	normal_cdf<float>();
	normal_cdf<double>();
}

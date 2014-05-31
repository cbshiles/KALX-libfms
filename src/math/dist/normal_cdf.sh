#!/bin/sh

TARGET=normal_cdf

bc -l normal.bc > ${TARGET}.dat <<EoF
scale=55
for (x = -8; x < 8; x += 0.01) {
	y=phi(x)
	print "{", x, ", ", man(y), "E", exp(y), "},\n"
}
EoF

cat > ${TARGET}.cpp <<EoF
// ${TARGET}.cpp - test normal::cdf
#include <limits>
#include "normal.h"

template<class X>
void ${TARGET}(void)
{
	X y;
	X eps = std::numeric_limits<X>::epsilon();

	struct { X x, y; } ${TARGET}_dat[] = {
#include "${TARGET}.dat"
	};
	for (auto xy : ${TARGET}_dat) {
		y = math::dist::normal::cdf(xy.x);
		ensure (static_cast<X>(fabs(y - xy.y) < 8*eps));
		y = erfc(-xy.x/M_SQRT2)/2;
		ensure (static_cast<X>(fabs(y - xy.y) < 1*eps));
	}
}

void ${TARGET}(void)
{
	${TARGET}<float>();
	${TARGET}<double>();
}
EoF

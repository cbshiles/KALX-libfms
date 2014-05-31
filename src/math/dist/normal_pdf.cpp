// normal_pdf.cpp - test normal::pdf
#include <limits>
#include "normal.h"

template<class X>
void normal_pdf(void)
{
	X y;
	X eps = std::numeric_limits<X>::epsilon();

	struct { X x, y; } normal_pdf_dat[] = {
#include "normal_pdf.dat"
	};
	for (auto xy : normal_pdf_dat) {
		y = math::dist::normal::pdf(xy.x);
		ensure (static_cast<X>(fabs(y - xy.y) < eps));
	}
}

void normal_pdf(void)
{
	normal_pdf<float>();
	normal_pdf<double>();
}

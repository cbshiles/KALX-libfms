// alnmoment3.h - Match first three moments of affine lognormal.
#pragma once
#include <cmath>
#include <tuple>

namespace fms {

	template<class X>
	tuple<X,X,X> alnmoment3(X m1, X m2, X m3)
	{
		// central moments
		X mu2 = m2 - m1*m1;
		X mu3 = m3 - 3*m2*m1 + 2*m1*m1*m1;

		ensure (mu2 > 0);
		ensure (m3*m3 > m2*m2*m2);

		X d = mu3/pow(mu2, 1.5);
		X e = pow(1 + (d*d + d*sqrt(4 + d*d))/2, 1/3.);
		X g2 = e + 1/e - 1;

		X b = sqrt(mu2/(g2*(g2 - 1)));

		return std::make_tuple(m1 - b*sqrt(g2), b, sqrt(log(g2)));
	}

} // fms

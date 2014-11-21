
// pwflat_fun
//ctions.h - pure functions for pwflat curves
// Piecewise-flat forward curves are modeled by arrays t and f, and an extrapolated value _f;
// 
// 	       { f[0] : t <= t[0]
// 	f(t) = { f[i] : t[i-1] < t <= t[i], i = 1,...,n-1
// 	       { f_   : t > t[n-1]
// 
//    |                 f_
//    |  f0          o---------
// ---*------*  f1   
//    |      o-------*
//    |
// ___0______t0______t1________
// 
// Note f(t[i]) = f[i], unlike for order 0 basis splines, and f is left continuous.
#pragma once
#include <algorithm>
#include <vector>
#include "../include/ensure.h"
#include <iostream>
namespace fms {
namespace pwflat {

	// value at single point
	template<class T, class F>
	inline F value(const T& u, size_t n, const T* t, const F* f, const F& f_ = 0)
	{
		if (n == 0)
			return f_;

		size_t i = std::lower_bound(t, t + n, u) - t; // t[i-1] < u <= t[i]
	
		return i == n ? f_ : f[i];
	}

	// integral from 0 to u
	template<class T, class F>
	inline F integral(const T& u, size_t n, const T* t, const F* f, const F& f_ = 0)
	{
		if (n == 0)
			return f_*u;

		T t0{0};
		F I{0};

		for (; n && *t <= u; ++t, ++f, --n) {
			I += (*f)*(*t - t0);
			t0 = *t;
		}

		I += (n == 0 ? f_ : *f)*(u - t0);

		return I;
	}

	// continuously compounded spot rate
	template<class T, class F>
	inline F spot(const T& u, size_t n, const T* t, const F* f, const F& f_ = 0)
	{
		//return 1 == 1 + u ? value(0, n, t, f, f_) : integral(u, n, t, f, f_)/u;
		return 0;
	}

	// e^{-int_0^u f(s) ds}
	template<class T, class F>
	inline F discount(const T& u, size_t n, const T* t, const F* f, const F& f_ = 0)
	{
		return exp(-integral<T,F>(u, n, t, f, f_));
	}

	// sum_i c[i] D(t[i])
	template<class T, class F>
	inline F present_value(size_t m, const T* u, const F* c, size_t n, const T* t, const F* f, const F& f_ = 0)
	{
		F pv{0};

		//!!! use std::accumulate
		for (size_t i = 0; i < m; ++i) {
			pv += c[i]*discount<T,F>(u[i], n, t, f, f_);
		}

		return pv;
	}

	// d(pv)/df for parallel shift past t0
	// (d/df) sum c[i] D(u[i])*exp(-f*(u[i] - t0)) 1(u[i] > t0)
	// = sum_{u[i] > t0} (u[i] - t0) c[i] D(u[i])
	template<class T, class F>
	inline F duration(T t0, size_t m, const T* u, const F* c, size_t n, const T* t, const F* f, const F& f_ = 0)
	{
		F dur{0};

		// skip past t0
		while (m && *u <= t0) {
			--m;
			++u;
			++c;
		}
		while (m--) {
			dur -= (*u - t0)*(*c)*discount(*u, n, t, f, f_);
			++u;
			++c;
		}
			
		return dur;
	}
} // pwflat
} // fms

#ifdef _DEBUG

using namespace fms::pwflat;

void test_pwflat_value()
{
	int t[] = {0,1,2};
	double f[] = {.1,.2,.3};

	for (auto i : t) {
		ensure (f[i] == value(i, 3, t, f));
	}

	ensure (.1 == value(-1, 3, t, f));
	ensure (.1 == value(0, 3, t, f));
	ensure (.2 == value(1, 3, t, f));
	ensure (.3 == value(2, 3, t, f));
	ensure ( 0 == value(3, 3, t, f));
	ensure (.4 == value(3, 3, t, f, .4));

}

void test_pwflat_integral()
{
	double t[] = {1,2,3};
	double f[] = {.1,.2,.3};

	ensure (-.1 == integral(-1., 3, t, f));
	ensure (0 == integral(0., 3, t, f));
	ensure (.1 == integral(1., 3, t, f));
	ensure (.1 + .2 == integral(2., 3, t, f));
	ensure (.1 + .2 + .3 == integral(3., 3, t, f));
	ensure (.1 + .2 + .3 + .4 == integral(4., 3, t, f, .4));

	ensure (.1 + .2*(1.5 - 1) == integral(1.5, 3, t, f));
	ensure (.1 + .2 + .3*(2.5 - 2) == integral(2.5, 3, t, f));
	ensure (.1 + .2 + .3 == integral(3.5, 3, t, f));
	ensure (.1 + .2 + .3 + .4*(3.5 - 3) == integral(3.5, 3, t, f, .4));

}

inline void test_pwflat_spot()
{
}

inline void test_pwflat_present_value()
{
}

inline void test_pwflat_duration()
{
	// cxccxlcxc
	double n = 3;
	double t[] = {1, 2, 3};
	double f[] = {.1, .2, .3};
	double m = 3;
	double c[] = {.5, 1, 2};
	double u[] = {1, 2, 3};
	double t0 = 0;

// ********************************************************************
// **  dur = -sum_i[(u_i - t0) * c_i * discount(u_i) ] for t_i > t0  **
// ********************************************************************
// Note: All the following tests are based on the assumption that previous 
//	defined functions (value, integral, discount, spot) have passed unit test.
// --------------------------------------------------------------------
// TEST CASES:
// 0) Normal usage case test
	t0 = 1.5;
	ensure(-1 * (2 - 1.5)*discount(2., n, t, f) - 2 * (3 - 1.5) *discount(3., n, t, f) \
		== duration(t0, m, u, c, n, t, f));
// The following are boundary cases and extreme situations
// 1) t0 is larger than all u's.  No change to pv is parallel shift all rates after t0.  So dur = 0
	t0 = 4;
	ensure(.0 == duration(t0, m, u, c, n, t, f));
// 2) t0 is exactly at the last cash flow. The time difference (u_i - t0) is 0.
	t0 = 3;
	ensure(.0 == duration(t0, m, u, c, n, t, f));
// 3) t0 is chosen at a size that the last and only the last cash flow is effective.
//          By definition, duration is the pv weight term.
	t0 = 2.5;
	ensure( -c[2] * (u[2] - t0) * discount(u[2], n, t, f) == duration(t0, m, u, c, n, t, f));
// 4) t0 is 0.  All cash flow are effective.
	t0 = .0;
	ensure(-c[0] * (u[0] - t0) * discount(u[0], n, t, f) \
		- c[1] * (u[1] - t0) * discount(u[1], n, t, f) \
		- c[2] * (u[2] - t0) * discount(u[2], n, t, f) \
		== duration(t0, m, u, c, n, t, f));
// 5) All cash flows are 0.  Then the pv weighted term should be 0.
	double c5[] = { .0, .0, .0 };
	ensure(.0 + .0 + .0 == duration(t0, m, u, c5, n, t, f));
// 6) All cash flow are same and happens at same timestamp.  Then the duration should be three times the duration 
//	of that cash flow at that stamp
	t0 = 0;
	double u6_1[] = { 3., 3., 3. }; // all cash flow is the last cash flow of original c[] and happens at last u[]
	double m6_1 = 3;
	double c6_1[] = {*(c+2), *(c+2), *(c+2)};
	double *u6_2 = u + 2;
	double m6_2 = 1.;
	double *c6_2 = c+2;
	ensure(duration(t0, m6_1, u6_1, c6_1, n, t, f) == 3 * duration(t0, m6_2, u6_2, c6_2, n, t, f));
}

#endif // _DEBUG
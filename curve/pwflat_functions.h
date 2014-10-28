// pwflat_functions.h - pure functions for pwflat curves
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
#include "ensure.h"

namespace fms {
namespace pwflat {

	// move to pwflat_functions.h!!!

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
		return 1 == 1 + u ? value<T,F>(0, n, t, f, f_) : integral(u, n, t, f, f_)/u;
	}

	// e^{-int_0^u f(s) ds}
	template<class T, class F>
	inline F discount(const T& u, size_t n, const T* t, const F* f, const F& f_ = 0)
	{
		return exp(-integral(u, n, t, f, f_));
	}

	// sum_i c[i] D(t[i])
	template<class T, class F>
	inline F present_value(size_t m, const T* u, const F* c, size_t n, const T* t, const F* f, const F& f_ = 0)
	{
		F pv{0};

		for (size_t i = 0; i < m; ++i) {
			pv += c[i]*discount(u[i], n, t, f, f_);
		}

		return pv;
	}

	// d(pv)/df for parallel shift past t0
	// (d/df) sum c[i] D(u[i])*exp(-f*(u[i] - t0)) 1(u[i] > t0)
	template<class T, class F>
	inline F duration(T t0, size_t m, const T* u, const F* c, size_t n, const T* t, const F* f, const F& f_ = 0)
	{
		F dur{0};

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
	//airc1209 done by lf343
	double t[] = { 1, 2, 3 };
	double f[] = { .1, .2, .3 };

	ensure((-.1/(-1.)) == spot(-1., 3, t, f));
	ensure(0.1 == spot(0., 3, t, f));
	ensure(.1/1. == spot(1., 3, t, f));																																					
	ensure((.1 + .2)/2. == spot(2., 3, t, f));
	ensure((.1 + .2 + .3)/3. == spot(3., 3, t, f));
	ensure((.1 + .2 + .3 + .4)/4. == spot(4., 3, t, f, .4));

	ensure((.1 + .2*(1.5 - 1))/1.5 == spot(1.5, 3, t, f));
	ensure((.1 + .2 + .3*(2.5 - 2))/2.5 == spot(2.5, 3, t, f));
	ensure((.1 + .2 + .3)/3.5 == spot(3.5, 3, t, f));
	ensure((.1 + .2 + .3 + .4*(3.5 - 3))/3.5 == spot(3.5, 3, t, f, .4));

}

inline void test_pwflat_present_value()
{
	// bsf48 
}

inline void test_pwflat_duration()
{
	// cxccxlcxc 
}

#endif // _DEBUG
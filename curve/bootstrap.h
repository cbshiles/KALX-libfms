// bootstrap.h - bootstrap a piecewise-flat forward curve
// Copyright (c) [2013] KALX, LLC. All rights reserved.
#pragma once
#include "ensure.h"
#include "../root/root1d.h"
#include "pwflat.h"

namespace fms {
namespace pwflat {

	// move to bootstrap_functions.h!!!

	// cash deposit, c = 1 + rate usually
	// 1 = c D0 exp(-f(u - t0))
	template<class T, class F>
	inline F bootstrap1(T u, T c, size_t n, const T* t, const F* f)
	{
		ensure (u > 0);
		ensure (c > 0);

		T t0 = n ? t[n-1] : 0;
		F D0 = discount(t0, n, t, f);

		return log(c*D0)/(u - t0);
	}

	// forward rate agreement, c0 = -1, c1 = 1 + forward, usually
	// 0 = c0 D0 + c1 D1, where D1 = D0 exp(-f(u1 - t0)) ish
	template<class T, class F>
	inline F bootstrap2(T u0, T c0, T u1, T c1, size_t n, const T* t, const F* f)
	{
		F f_;
		T t0 = n ? t[n-1] : 0;
		F D0 = discount(t0, n, t, f);
		F d = -c1/c0; // works if c0 != -1

		if (u0 < t0) { // overlap or cash deposit
			F D1 = discount(u1, n, t, f);
			f_ = static_cast<T>(log(d*D0/D1)/(u1 - u0));
		}
		else { // underlap
			f_ = static_cast<T>(log(d)/(u1 - t0));
		}

		return f_;
	}

	// note pv is present value of cash flows, f_ is best guess at bootstrap value
	template<class T, class F>
	inline T bootstrap(size_t m, const T* u, const T* c, size_t n, const T* t, const F* f, F f_ = 0, F pv = 0)
	{
		ensure (m && (n == 0 || u[m-1] > t[n-1]));

		// cd
		if (m == 1 && pv == 1) {
			return bootstrap1<T,F>(u[0], c[0], n, t, f);
		}

		// fra
		if (m == 2 && pv == 0) {
			return bootstrap2<T,F>(u[0], c[0], u[1], c[1], n, t, f);
		}
		
		T t0 = n ? t[n-1] : 0;
		auto um = std::upper_bound(u, u + m, t0);
		ensure (um != u + m); // already checked above
		F p0 = present_value<T>(um - u, u, c, n, t, f);

		m -= um - u;
		c += um - u;
		u += um - u;

		auto F_ = [p,p0,m,u,c,n,t,f](T f_) 
		{ 
			return -p + p0 + present_value<T>(m, u, c, n, t, f, f_)); 
		};
		auto dF = [t0,m,u,c,n,t,f](T f_) 
		{ 
			return duration<T>(t0, m, u, c, n, t, f, f_);
		};

		// start from last forward rate if not specified
		if (n && f_ == 0)
			f_ = f[n-1];

		return fms::root1d::find::newton(f_, F_, dF);
	}

} // pwflat
} // fms

#ifdef _DEBUG

using namespace fms::pwflat;

inline void test_pwflat_bootstrap1()
{
	// lukeyy 
}

inline void test_pwflat_bootstrap2()
{
	// rc633  
}

inline void test_pwflat_bootstrap()
{
	// sjm366
}

#endif // _DEBUG
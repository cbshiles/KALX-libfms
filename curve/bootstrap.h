// bootstrap.h - bootstrap a piecewise-flat forward curve
// Copyright (c) [2013] KALX, LLC. All rights reserved.
#pragma once
#include "ensure.h"
//#include "fixed_income.h"
#include "../root/root1d.h"
#include "pwflat.h"

namespace fms {
namespace pwflat {

	// cash deposit
	template<class T, class F>
	inline T bootstrap1(T u, T c, size_t n, const T* t, const F* f)
	{
		ensure (u > 0);
		ensure (c > 0);

		T t0 = n ? t[n-1] : 0;
		F D0 = discount(t0, n, t, f);

		return log(c*D0)/(u - t0);
	}

	// forward rate agreement
	template<class T, class F>
	inline T bootstrap2(T u0, T c0, T u1, T c1, size_t n, const T* t, const F* f)
	{
		F _f;
		T t0 = n ? t[n-1] : 0;
		F D0 = discount(t0, n, t, f);
		F d = -c1/c0; // works if c0 != -1

		if (u0 < t0) { // overlap or cash deposit
			F Dm = discount(u1, n, t, f);
			_f = static_cast<T>(log(d*D0/Dm)/(u1 - u0));
		}
		else { // underlap
			_f = static_cast<T>(log(d)/(u1 - t0));
		}

		return _f;
	}

	template<class T, class F>
	inline T bootstrap(size_t m, const T* u, const T* c, size_t n, const T* t, const F* f, F _f = 0, F p = 0)
	{
		ensure (m && (n == 0 || u[m-1] > t[n-1]));

		// cd
		if (m == 1) {
			return bootstrap1<T,F>(u[0], c[0], n, t, f);
		}

		// fra
		if (m == 2 && p == 0) {
			return bootstrap2<T,F>(u[0], c[0], u[1], c[1], n, t, f);
		}
		
		T t0 = n ? t[n-1] : 0;
		const T* um = std::upper_bound(u, u + m, t0);
		ensure (um != u + m); // already checked above
		F p0 = present_value<T>(um - u, u, c, n, t, f);

		m -= um - u;
		c += um - u;
		u += um - u;

		auto F_ = [p,p0,m,u,c,n,t,f](T _f) 
		{ 
			return -p + p0 + present_value<T>(fixed_income::instrument<T>(m, u, c), forward_curve<T>(n, t, f, _f)); 
		};
		auto dF = [t0,m,u,c,n,t,f](T _f) 
		{ 
			return duration<T>(fixed_income::instrument<T>(m, u, c), forward_curve<T>(n, t, f, _f), t0);
		};

		if (_f == 0)
			_f = n ? f[n-1] : static_cast<T>(0.01);

		return root1d::newton(_f, F_, dF);
	}

} // pwflat
} // fms
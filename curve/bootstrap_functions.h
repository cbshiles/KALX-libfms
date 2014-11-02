// bootstrap_functions.h - bootstrap a piecewise-flat forward curve
// Copyright KALX, LLC. All rights reserved. No warranty made.
#pragma once
#include "include/ensure.h"
#include "root/root1d.h"
#include "pwflat_functions.h"

namespace fms {
namespace pwflat {

	// cash deposit, c = 1 + rate usually
	// 1 = c D0 exp(-f(u - t0))
	template<class T, class F>
	inline F bootstrap1(T u, F c, size_t n, const T* t, const F* f)
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
	inline F bootstrap2(T u0, F c0, T u1, F c1, size_t n, const T* t, const F* f)
	{
		F f_;
		T t0 = n ? t[n-1] : 0;
		F D0 = discount(t0, n, t, f);
		F d = -c1/c0; // works if c0 != -1

		if (u0 < t0) { // overlap or cash deposit
			F D1 = discount(u1, n, t, f);
			f_ = static_cast<F>(log(d*D0/D1)/(u1 - u0));
		}
		else { // underlap
			f_ = static_cast<F>(log(d)/(u1 - t0));
		}

		return f_;
	}

	// note pv is present value of cash flows, f_ is best guess at bootstrap value
	template<class T, class F>
	inline T bootstrap(size_t m, const T* u, const F* c, size_t n, const T* t, const F* f, F f_ = 0, F pv = 0)
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

		auto F_ = [pv,p0,m,u,c,n,t,f](T f_) 
		{ 
			return -pv + p0 + present_value<T>(m, u, c, n, t, f, f_); 
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
#include "pwflat.h"

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

template<class T, class U>
inline void test_pwflat_bootstrap_(void)
{
	T eps = std::numeric_limits<T>::epsilon();
	T t[] = {1, 2, 3, 4};
//	size_t n = sizeof(t)/sizeof(*t);

	std::vector<U> f;

	// present_value of (0, -1), (1, e), ..., (n, 1+e) is 0 for f(t) = f0.
	U f0 = (U)0.04;
	U e = exp(f0) - 1;

	// cd with empty forward curve
	vector::curve<> f;
	f.push_back(forward<T,U>().bootstrap1(1., 1 + e));
	ensure (fabs(f.back() - f0) < eps);

	// fra
	f.push_back(forward<T,U>(1, t, &f[0]).bootstrap2(1., -1., 2., 1 + e));
	ensure (fabs(f.back() - f0) < eps);

	// generic
	T u[]  = {0, 1, 2, 3, 4};
	T c3[] = {-1, e, e, 1 + e};
	// initial guess 0.02
	f.push_back(forward<T,U>(2, t, &f[0], (U)0.02).bootstrap(4, u, c3)); 
	ensure (fabs(f.back() - f0) < eps);

	T c4[] = {-1, e, e, e, 1 + e};
	f.push_back(forward<T>(3, t, &f[0], (U).02).bootstrap(5, u, c4)); 
	ensure (fabs(f.back() - f0) < eps);
}

void curves_bootstrap_test(void)
{
	test_pwflat_bootstrap_<double,double>();
}
#endif // _DEBUG
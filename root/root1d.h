// root1d.h - One dimensional root finding
#pragma once
#include "ensure.h"
#include <functional>
#include <limits>

namespace fms {
namespace root1d {

	// next guess
	namespace step {

		// midpoint of [x0, x1]
		template<class X>
		inline X bisect(X x0, X x1)
		{
			return (x0 + x1)/2;
		}

		// root of line through (x0, y0) having slope m
		template<class X, class Y>
		inline X newton(X x0, Y y0, decltype(y0/x0) m)
		{
			ensure (m != 0);

			return x0 - X(y0/m);
		}

		// root of line through (x0, y0) and (x1, y1)
		template<class X, class Y>
		inline X secant(X x0, Y y0, X x1, Y y1)
		{
			ensure (x0 != x1);

			return newton(x0, y0, (y1 - y0)/(x1 - x0));
		}

		// root of inverse quadratic determined by three points
		template<class X, class Y>
		inline X inverse_quadratic(X x0, Y y0, X x1, Y y1, X x2, Y y2)
		{
			X dy0 = y1 - y2;
			X dy1 = y2 - y0;
			X dy2 = y0 - y1;

			ensure (dy0 != 0);
			ensure (dy1 != 0);
			ensure (dy2 != 0);	

			return x0*y1*y2/(dy1*dy2) + x1*y2*y0/(dy2*dy0) + x2*y0*y1/(dy0*dy1);
		}

	} // step

	// termination criteria: x is current, x_ is previous
	namespace done {

		// agree to machine epsilon
		template<class X>
		inline bool epsilon(const X& x, const X& x_)
		{
			return 1 + (x > X(1) || x < X(-1) ? x_/x - 1 : x_ - x) == 1;
		}

		template<class X>
		inline bool absolute(const X& x, const X& x_, const X& abs)
		{
			return fabs(x - x_) < abs; 
		}

		template<class X>
		inline bool relative(const X& x, const X& x_, const X& rel)
		{
			return fabs(x - x_) < rel*fabs(x); 
		}

		template<class Y>
		inline bool residual(const Y& y, const Y& abs)
		{
			return fabs(y) < abs;
		}
		
	} // done

	namespace find {
		
		template<class X, class Y>
		inline X newton(X x, const std::function<Y(X)>& f, const std::function<Y(X)>& df)
		{
			X x_(x);

			DEBUG_(int i = 0;)
			do {
				DEBUG_(++i;)
				X _x = step::newton<X,Y>(x, f(x), df(x));
				if (_x == x_) // cycle
					return step::bisect<X>(x, x_);
				x_ = x;
				x = _x;
			} while (!done::epsilon<X>(x, x_));

			return x;
		}
		
		template<class X, class Y>
		inline X secant(X x, X x_, const std::function<Y(X)>& f)
		{
			DEBUG_(int i = 0;)
			do {
				DEBUG_(++i;)
				X _x = step::secant(x, f(x), x_, f(x_)); // !!! don't recompute y !!!
				if (_x == x_) // cycle
					return step::bisect(x, x_);
				x_ = x;
				x = _x;
			} while (!done::epsilon(x, x_));

			return x;
		}

	} // find

} // root1d
} // fms

#ifdef _DEBUG

using namespace fms::root1d;

template<class X, class Y>
inline void test_root1d_step()
{
	X x1(1), x2(2), x3(3);

	ensure (step::bisect(x1, x2) == (x1 + x2)/2);

	auto f = [](const X& x) { return 1 + 2*Y(x); };
	auto x_ = step::newton<X,Y>(x1, f(x1), 2);
	ensure (f(x_) == 0);

	x_ = step::secant(x1, f(x1), x2, f(x2));
	ensure (f(x_) == 0);

	auto g = [](const X& x) { return x*x; };
	x_ = step::inverse_quadratic(g(x1), x1, g(x2), x2, g(x3), x3);
	ensure (g(x_) == 0);
}

template<class X, class Y>
inline void test_root1d_done()
{
	ensure (done::epsilon<X>(1, 1 + std::numeric_limits<X>::epsilon()/2));
	ensure (!done::epsilon<X>(1, 1 + std::numeric_limits<X>::epsilon()));
}

template<class X, class Y>
inline void test_root1d_find(void)
{
	auto f = [](const X& x) { return Y(x*x - 2); };
	auto df = [](const X& x) { return Y(2*x);};

	auto x = find::newton<X,Y>(X(1), f, df);
	if (typeid(x) == typeid(double)) {
		ensure (!done::epsilon<X>(x, sqrt(X(2)))); // surprise!!!
		x = nextafter(x, X(2));
		auto y = sqrt(X(2));
		ensure (done::epsilon<X>(x, y));
		ensure (x == y);
	}
	else {
		ensure (done::epsilon<X>(x, sqrt(X(2))));
	}

	x = find::secant<X,Y>(X(1), X(2), f);
	if (typeid(x) == typeid(double)) {
		ensure (!done::epsilon<X>(x, sqrt(X(2)))); // surprise!!!
		x = nextafter(x, X(2));
		auto y = sqrt(X(2));
		ensure (done::epsilon<X>(x, y));
		ensure (x == y);
	}
	else {
		ensure (done::epsilon<X>(x, sqrt(X(2))));
	}
}

inline void test_root1d(void)
{
	test_root1d_step<double,double>();
	test_root1d_step<float,float>();
	test_root1d_step<float,double>();
	test_root1d_step<double,float>();

	test_root1d_done<double,double>();
	test_root1d_done<float,float>();
	test_root1d_done<float,double>();
	test_root1d_done<double,float>();

	test_root1d_find<double,double>();
	test_root1d_find<float,float>();
	test_root1d_find<float,double>();
	test_root1d_find<double,float>();
}

#endif // _DEBUG

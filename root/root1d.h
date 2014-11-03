// root1d.h - One dimensional root finding
#pragma once
#include "include/ensure.h"
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
			ensure (x0 != x1 && y0 != y1);

			return newton(x0, y0, (y1 - y0)/(x1 - x0));
		}

		// root of inverse quadratic determined by three points
		template<class X, class Y>
		inline X inverse_quadratic(X x0, Y y0, X x1, Y y1, X x2, Y y2)
		{
			X dy0 = X(y1 - y2);
			X dy1 = X(y2 - y0);
			X dy2 = X(y0 - y1);

			ensure (dy0 != 0);
			ensure (dy1 != 0);
			ensure (dy2 != 0);	

			return X(x0*y1*y2/(dy1*dy2) + x1*y2*y0/(dy2*dy0) + x2*y0*y1/(dy0*dy1));
		}

	} // step

	// termination criteria: x is current, x_ is previous
	namespace done {

		template<class X>
		inline bool absolute(const X& x, const X& x_, const X& abs = 2*std::numeric_limits<X>::epsilon())
		{
			return fabs(x - x_) <= abs; 
		}

		template<class X>
		inline bool relative(const X& x, const X& x_, const X& rel)
		{
			return fabs(x - x_) < rel*fabs(x);
		}

		template<class Y>
		inline bool residual(const Y& y, const Y& abs = std::numeric_limits<Y>::epsilon())
		{
			return fabs(y) < abs;
		}

		// x is in (min(a,b), max(a,b))
		template<class X>
		inline bool between(const X& x, const X& a, const X& b)
		{
			return (x - a)*(x - b) < 0;
		}

	} // done

	namespace find {

		// must have root bracketed
		template<class X, class Y>
		inline X bisect(X x, X x_, const std::function<Y(X)>& f, size_t iter = 20)
		{
			Y y = f(x), y_ = f(x_);

			do {
				ensure (iter--);
				ensure (y*y_ < 0);
				X _x = step::bisect(x, x_);
				Y _y = f(_x);

				if (_y*y_ < 0) {
					std::swap(x, x_);
					std::swap(y, y_);
				}

				x_ = x;
				x = _x;
				y_ = y;
				y = _y;
			} while (y != 0 && !done::absolute(x, x_));

			return x;
		}

		// deliberately small iteration count
		template<class X, class Y>
		inline X newton(X x, const std::function<Y(X)>& f, const std::function<Y(X)>& df, size_t iter = 20)
		{
			X x_(x);

			do {
				ensure (iter--);
				Y y = f(x), dy = df(x);
				
				ensure (dy != 0);

				X _x = step::newton<X,Y>(x, y, dy);
				if (_x == x_) // cycle
					return step::bisect<X>(x, x_); // _x = !!!
				x_ = x;
				x = _x;
			} while (!done::absolute<X>(x, x_));

			return x;
		}
		
		template<class X, class Y>
		inline X secant(X x, X x_, const std::function<Y(X)>& f, size_t iter = 10)
		{
			Y y = f(x), y_ = f(x_);

			do {
				ensure (iter--);

				ensure (y != y_);

				X _x = step::secant(x, y, x_, y_);
				if (_x == x_) // cycle
					return step::bisect(x, x_);
				x_ = x;
				x = _x;
				y_ = y;
				y = f(x);
			} while (!done::absolute(x, x_));

			return x;
		}
		
		// simplified Hewlett Packard SOLVE routine
		template<class X, class Y>
		inline X kahan(X x, X x_, const std::function<Y(X)>& f, size_t iter = 10)
		{
			// current and previous
			Y y = f(x), y_ = f(x_);

			do {
				X _x;
				ensure (iter--);

				if (y == y_) {
					_x = step::bisect(x, x_);
				}
				else {
					_x = step::secant(x, y, x_, y_);
				}

				if (y*y_ < 0 && !done::between(_x, x, x_)) {
					_x = step::bisect(x, x_);
				}
				Y _y = f(_x);

				x_ = x;
				x = _x;
				y_ = y;
				y = _y;
			} while (y != 0 && !done::absolute(x, x_));

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
	ensure (done::absolute<X>(X(1), X(1) + X(0.5)*std::numeric_limits<X>::epsilon()));
	ensure (!done::absolute<X>(X(1), X(1) + X(4)*std::numeric_limits<X>::epsilon()));
	ensure (done::between(2, 1, 3));
	ensure (done::between(2, 3, 1));
	ensure (!done::between(1, 2, 3));
	ensure (!done::between(1, 3, 2));
	ensure (!done::between(3, 1, 2));
	ensure (!done::between(3, 2, 1));

}

template<class X, class Y>
inline void test_root1d_find(void)
{
	auto f = [](X x) { return Y(x*x - 2); };
	auto df = [](const X& x) { return Y(2*x);};
	 
	auto x = find::newton<X,Y>(X(1), f, df);
	ensure (done::absolute<X>(x, sqrt(X(2))));

	x = find::bisect<X,Y>(X(1), X(2), f, 51);
	ensure (done::absolute<X>(x, sqrt(X(2))));

	x = find::secant<X,Y>(X(1), X(2), f);
	ensure (done::absolute<X>(x, sqrt(X(2))));

	x = find::kahan<X,Y>(X(1), X(2), f);
	ensure (done::absolute<X>(x, sqrt(X(2))));
	x = find::kahan<X,Y>(X(1), X(-1), f);
	ensure (done::absolute<X>(x, sqrt(X(2))));

	// SOLVEkey examples
	X c1,c2;
	std::function<Y(X)> c = [&c1,&c2](X x) { return Y(exp(x) - c1*x - c2); };

	// Kahan's Fig. 3 (a) example
	c1 = -1; c2 = 2;
	x = find::kahan<X,Y>(X(1.5),X(1), c, 20);
	ensure (fabs(x - .442854401) < sqrt(std::numeric_limits<X>::epsilon()));

	// Kahan's Fig. 3 (b) example
	c1 = 5; c2 = -3;
	x = find::kahan<X,Y>(X(0),X(1.5), c, 20);
	ensure (fabs(x - 1.468829255) < sqrt(std::numeric_limits<X>::epsilon()));
	x = find::kahan<X,Y>(X(2),X(4), c, 20);
	ensure (fabs(x - 1.74375199) < sqrt(std::numeric_limits<X>::epsilon()));

	// Kahan's Fig. 3 (c) example
	c1 = 4; c2 = X(4 - 4*log(4));
	x = find::kahan<X,Y>(X(0),X(2), c, 50);
	ensure (fabs(x - 1.3862943473365201) < sqrt(std::numeric_limits<X>::epsilon()));
	// Kahan's solution uses float, not double!
	ensure (fabs(c(X(1.3862943473365201))) <= fabs(c(X(1.386277368))));

	auto g = [](X x) { return 6*x - x*x*x*x; };
	X r[2];
	r[0] = find::kahan<X,Y>(X(0),X(.5), [&g](X x) { return Y(g(x) - 1); });
	r[1] = find::kahan<X,Y>(X(1.5),X(2), [&g](X x) { return Y(g(x) - 1); });

	x = find::kahan<X,Y>(X(0),X(.5), [&g](X x) { return Y(exp(g(x) - 1) - 1); });
	ensure (1 + (x - r[0]) == 1);
//	x = find::kahan<X,Y>(X(1.5),X(2), [&g](X x) { return Y(exp(g(x) - 1) - 1); });
//	ensure (x == r[1]);
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

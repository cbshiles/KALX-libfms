// root1d.h - One dimensional root finding
#pragma once
#include <functional>
#include <deque>

namespace fms {
namespace root1d {

	// next guess
	namespace step {

		template<class X>
		inline X bisect(X x0, X x1)
		{
			return (x0 + x1)/2;
		}

		// root of line through (x0, y0) having slope m
		template<class X, class Y, class M>
		inline X newton(X x0, X y0, M m)
		{
			ensure (m != 0);

			return x0 - y0/m;
		}

		// root of line through (x0, y0) and (x1, y1)
		template<class X, class Y>
		inline X secant(X x0, Y y0, X x1, Y y1)
		{
			ensure (x0 != x1);

			return newton(x0, y0, (y0 - y1)/(x0 - x1));
		}

		// root of quadratic determined by three points
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

		template<class X>
		inline bool absolute(X x, X x_, X abs)
		{
			return fabs(x - x_) < abs; 
		}

		template<class X>
		inline bool relative(X x, X x_, X rel)
		{
			return fabs(x - x_) < rel*fabs(x); 
		}

		template<class Y>
		inline bool residual(Y y, Y abs)
		{
			return fabs(y) < abs;
		}
		
	} // done

	template<class X, class Y>
	class find {
		std::deque<X> x_;
		std::deque<Y> y_;
		const std::function<Y(const X&)> f_, df_;
	public:
		find(const std::function<Y(X)>& f)
			: f_(f), df_(df)
		{ }
		find(const std::function<Y(X)>& f, const std::function<Y(X)>& df)
			: f_(f), df_(df)
		{ }
		find(const find&) = delete;
		find& operator=(const find&) = delete;
		~find()
		{ }
		size_t size() const
		{
			return x_.size();
		}
		std::pair<X,Y> operator[](size_t i) const
		{
			return std::make_pair(x_[i], y_[i]);
		}

		X newton(X x0, X rel, X abs = 0)
		{
			ensure (rel != 0 || abs != 0);

			auto done = [=abs,rel](const X& x0, const X& x1) {
				if (rel && abs)
					return done::relative(x0, x1, rel) && done::absolute(x0, x1, abs);
				else if (rel)
					return done::relative(x0, x1, rel);
				else {
					return done::absolute(x0, x1, abs);
				}
			};

			x_.push_front(x0);
			y_.push_front(f_(x0));

			do {
				x_.push_front(step::newton(x_[0], y_[0], df_(x_[0])));
				y_.push_front(f_(x_[0]));
			} while (!done(x_[0], x_[1]));

			return x_[0];
		}
	};

} // root1d
} // fms
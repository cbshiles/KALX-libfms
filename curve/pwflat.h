// pwflat.h - piecewise flat curves
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

	// value at single point
	template<class T, class F>
	inline F value(const T& t, size_t n, const T* pt, const F* pf, const F& f_ = 0)
	{
		if (n == 0)
			return f_;

		ptrdiff_t i = std::lower_bound(pt, pt + n, t) - pt; // t[i-1] < t <= t[i]
	
		return i == n ? f_ : pf[i];
	}

	// integral from 0 to t
	template<class T, class F>
	inline F integral(const T& t, size_t n, const T* pt, const F* pf, const F& f_ = 0)
	{
		if (n == 0)
			return f_*t;

		T t0{0};
		F I{0};

		for (; n && *pt <= t; ++pt, ++pf, --n) {
			I += (*pf)*(*pt - t0);
			t0 = *pt;
		}

		I += (n == 0 ? f_ : *pf)*(t - t0);

		return I;
	}

	// e^{-int_0^t f(s) ds}
	template<class T, class F>
	inline F discount(const T& t, size_t n, const T* pt, const F* pf, const F& f_ = 0)
	{
		return exp(-integral(t, n, pt, pf, f_));
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

	// piecewise flat curve base class
	template<class T = double, class F = double>
	class curve {
		F f_;
	public:
		// constant curve
		curve(const F& f = 0)
			: f_(f)
		{ }
		curve(const curve&) = default;
		curve& operator=(const curve&) = default;
		virtual ~curve()
		{ }

		// get extrapolation value
		F extrapolate(void) const
		{
			return f_;
		}
		// change extrapolation value
		curve& extrapolate(const F& f)
		{
			f_ = f;

			return *this;
		}

		// non-virtual interface
		size_t size() const
		{
			return _size();
		}
		const T* t(void) const
		{
			return _t();
		}
		const F* f(void) const
		{
			return _f();
		}

		F value(const T& u) const
		{
			return fms::pwflat::value(u, size(), t(), f(), f_);
		}
		F operator()(const T& t) const
		{
			return value(t);
		}
		F integral(const T& u) const
		{
			return fms::pwflat::integral(u, size(), t(), f(), f_);
		}
		F present_value(size_t m, const T* u, const F* c)
		{
			return fms::pwflat::present_value(m, u, c, size(), t(), f(), f_);
		}

		// convenience functions
		T t(size_t i) const
		{
			ensure (i < size());

			return t()[i];
		}
		F f(size_t i) const
		{
			ensure (i < size());

			return f()[i];
		}
		std::pair<T,F> operator[](size_t i) const
		{
			ensure (i < size());

			return std::make_pair(t(i), f(i));
		}

	private:
		// functions to override
		virtual size_t _size(void) const
		{
			return 0;
		}
		virtual const T* _t(void) const
		{
			return nullptr;
		}
		virtual const F* _f(void) const
		{
			return nullptr;
		}
	};

	// curve using preallocated arrays
	template<class T = double, class F = double>
	class pointer_curve : public curve<T,F> {
		size_t n_;
		const T* t_;
		const F* f_;
	public:
		pointer_curve(size_t n = 0, const T* t = nullptr, const F* f = nullptr, const F& f_ = 0)
			: curve(f_), n_(n), t_(t), f_(t)
		{ }
		// avoid pointer aliasing
		pointer_curve(const pointer_curve&) = delete;
		pointer_curve& operator=(const pointer_curve&) = delete;
		~pointer_curve()
		{ }

		size_t _size(void) const override
		{
			return n_;
		}
		const T* _t(void) const override
		{
			return t_;
		}
		const T* _f(void) const override
		{
			return f_;
		}
	};

	// curve using vectors for storage
	template<class T = double, class F = double>
	class vector_curve : public curve<T,F> {
		std::vector<T> t_;
		std::vector<F> f_;
	public:
		vector_curve(size_t n = 0, const T* t = nullptr, const F* f = nullptr, const F& f_ = 0)
			: curve(f_), t_(t, t + n), f_(f, f + n)
		{ }
		vector_curve(const curve& c)
			: vector_curve(c.size(), c.t(), c.f(), c.extrapolate()) // C++11 allows other constructors to be called
		{ }
		vector_curve(const vector_curve&) = default;
		vector_curve& operator=(const vector_curve&) = default;
		vector_curve(vector_curve&& c)
			: curve(c.extrapolate()), t_(std::move(c.t_)), f_(std::move(c.f_))
		{ }
		vector_curve& operator=(vector_curve&& c)
		{
			t_ = std::move(c.t_);
			f_ = std::move(c.f_);
			extrapolate(c.extrapolate());

			return *this;
		}
		~vector_curve()
		{ }

		size_t _size(void) const override
		{
			return t_.size();
		}
		const T* _t(void) const override
		{
			return t_.data();
		}
		const F* _f(void) const override
		{
			return f_.data();
		}

		// add knot at back of curve
		vector_curve& push_back(const T& t, const F& f)
		{
			ensure (size() == 0 || t > t_.back());

			t_.push_back(t);
			f_.push_back(f);

			return *this;
		}
		// insert new knot point
		vector_curve& insert(const T& t, const F& f)
		{
			auto ti = std::lower_bound(t_.begin(), t_.end(), t);

			ensure (*ti != t); // times must be strictly increasing

			// do this first since...
			f_.insert(f_.begin() + (ti - t_.begin()), f);
			// ...this invalidates ti
			t_.insert(ti, t);

			return *this;
		}
		// add constant spread
		vector_curve& operator+=(const F& s)
		{
			for (auto& f : f_) {
				f += s;
			}
			// f_ += s does not work since f_ is private
			extrapolate(extrapolate() + s);

			return *this;
		}
		// multiply constant factor
		vector_curve& operator*=(const F& s)
		{
			for (auto& f : f_) {
				f *= s;
			}
			extrapolate(extrapolate() * s);

			return *this;
		}
		// add a vector_curve
		vector_curve& operator+=(const vector_curve& s)
		{
			std::vector<T> t(t_);

			t.insert(t.end(), s.t_.begin(), s.t_.end());
			std::inplace_merge(t.begin(), t.begin() + size(), t.end());
			auto ti = std::unique(t.begin(), t.end());
			t.resize(ti - t.begin());

			std::vector<F> f(t.size());
			for (size_t i = 0; i < t.size(); ++i) {
				f[i] = value(t[i]) + s(t[i]); // correct but not efficient!!!
			}

			t_ = t;
			f_ = f;
			extrapolate(extrapolate() + s.extrapolate());

			return *this;
		}
	};
} // pwflat
} // fms

// define arithmetic functions in global namesapce
template<class T, class F>
inline fms::pwflat::vector_curve<T,F> operator+(fms::pwflat::vector_curve<T,F> a, const F& s)
{
	return a += s; // a is passed by value
}
template<class T, class F>
inline fms::pwflat::vector_curve<T,F> operator+(const F& s, fms::pwflat::vector_curve<T,F> a)
{
	return a += s; // a is passed by value
}
template<class T, class F>
inline fms::pwflat::vector_curve<T,F> operator+(fms::pwflat::vector_curve<T,F> a, const fms::pwflat::vector_curve<T,F>& b)
{
	return a += b; // a is passed by value
}

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

void test_pwflat_curve()
{
	vector_curve<> c;
	ensure (c.size() == 0);
	ensure (c(2) == 0);

	vector_curve<> c2(c);
	ensure (c2.size() == 0);
	ensure (c2(2) == 0);

	c2.push_back(1,2);
	ensure (c2.size() == 1);
	ensure (std::make_pair(1.,2.) == c2[0]);
	ensure (c2(0) ==2);
	ensure (c2(1) == 2);
	ensure (c2(2) == 0);

	c = c2;
	ensure (c.size() == 1);
	ensure (c(0) == 2);
	ensure (c(1) == 2);
	ensure (c(2) == 0);
	ensure (c.integral(0) == 0);
	ensure (c.integral(1) == 2);
	ensure (c.integral(2) == 2);

	c += 3;
	ensure (c.size() == 1);
	ensure (c(0) == 5);
	ensure (c(1) == 5);
	ensure (c(2) == 3);
	ensure (c.integral(0) == 0);
	ensure (c.integral(1) == 5);
	ensure (c.integral(2) == 5 + 3);

	c.insert(.5, 6);
	ensure (c.size() == 2);
	ensure (c(0) == 6);
	ensure (c(.5) == 6);
	ensure (c(.7) == 5);
	ensure (c(2) == 3);

	double t3[] = {1, 2, 3};
	double f3[] = {.2,.4,.6};
	double t4[] = {1.5, 2.5};
	double f4[] = {.3, .5};

	vector_curve<> c3(3,t3,f3), c4(2,t4,f4);
	vector_curve<> c5 = c3 + c4;
	ensure (c5.size() == 5);
	for (double t = 0.5; t <= 3.5; t += 0.5) {
		ensure (c3(t) + c4(t) == c5(t));
	}
}

#endif // _DEBUG

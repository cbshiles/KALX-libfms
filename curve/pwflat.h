// pwflat.h - piecewise flat curves
#pragma once
#include "pwflat_functions.h"

namespace fms {
namespace pwflat {

	// piecewise flat curve base class
	// can only be used as a constant curve
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

		// non-virtual interface
		// subclasses must implement _size(), _t(), and _f()+
		size_t size() const
		{
			return _size();
		}
		const T* t(void) const
		{
			return _t();
		}
		// long name
		const T* time(void) const
		{
			return _t();
		}
		const F* f(void) const
		{
			return _f();
		}
		// long name
		const F* rate(void) const
		{
			return _f();
		}

		bool operator==(const curve& c) const
		{
			return extrapolate() == c.extrapolate()
				&& size() == c.size() 
				&& std::equal(t(), t() + size(), c.t())
				&& std::equal(f(), f() + size(), c.f())
		}
		bool operator!=(const curve& c) const
		{
			return !operator==(c);
		}
		// value(t) < c(t) for all t
		bool operator<(const curve& c) const
		{
			// check at all knot points
			return extrapolate() < c.extrapolate()
				&& std::all_of(t(), t() + size(), [this,&c](const T& t) { return value(t) < c(t); })
				&& std::all_of(c.t(), c.t() + c.size(), [this,&c](const T& t) { return value(t) < c(t); });
		}

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
		// duration

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

	// curve using preallocated arrays, not a value type
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
		pointer_curve(const pointer_curve&) = delete; // avoid pointer aliasing
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

	// curve using vectors for storage, is a value type
	template<class T = double, class F = double>
	class vector_curve : public curve<T,F> {
		std::vector<T> t_;
		std::vector<F> f_;
	public:
		vector_curve(size_t n = 0, const T* t = nullptr, const F* f = nullptr, const F& f_ = 0)
			: curve(f_), t_(t, t + n), f_(f, f + n)
		{ }
		vector_curve(const curve& c)
			: vector_curve(c.size(), c.t(), c.f(), c.extrapolate()) // C++11 allows delegating constructors
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
		// add a curve
		vector_curve& operator+=(const curve& s)
		{
			std::vector<T> t(t_);

			t.insert(t.end(), s.t(), s.t() + s.size());
			std::inplace_merge(t.begin(), t.begin() + size(), t.end());
			auto ti = std::unique(t.begin(), t.end());
			t.resize(ti - t.begin());

			std::vector<F> f(t.size());
			std::transform(t.begin(), t.end(), f.begin(), [this,&s](const T& ti) { return value(ti) + s(ti); });
			/*
			for (size_t i = 0; i < t.size(); ++i) {
				f[i] = value(t[i]) + s(t[i]); // correct but not efficient!!!
			}
			*/

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
inline fms::pwflat::vector_curve<T,F> operator+(const fms::pwflat::vector_curve<T,F>& a, const fms::pwflat::vector_curve<T,F>& b)
{
	return fms::pwflat::vector_curve<T,F>(a) += b;
}

#ifdef _DEBUG

using namespace fms::pwflat;

inline void test_pwflat_curve()
{
	// dgtsx 
}

inline void test_pwflat_pointer_curve()
{
	// giorgiovitale 
}

inline void test_pwflat_vector_curve()
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

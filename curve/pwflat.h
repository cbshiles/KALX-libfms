// pwflat.h - piecewise flat curves
#pragma once
#include "pwflat_functions.h"

namespace fms {
namespace pwflat {

	// constant curve base class
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
		// subclasses must implement _size(), _t(), and _f()
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
			if (extrapolate() != c.extrapolate())
				return false;
			if (size() != c.size())
				return false;
			if (size() == 0)
				return true;

			return std::equal(t(), t() + size(), c.t())
					&& std::equal(f(), f() + size(), c.f());
		}
		bool operator!=(const curve& c) const
		{
			return !operator==(c);
		}
		// value(t) < c(t) for all t
		bool operator<(const curve& c) const
		{
			// check at all knot points
			if (extrapolate() >= c.extrapolate())
				return false;
			if (size() == 0)
				return true;

			ensure (extrapolate() < c.extrapolate());
			if (c.size() == 0)
				return *std::max_element(f(), f() + size()) < c.extrapolate();

			return  std::all_of(t(), t() + size(), [this,&c](const T& t) { return value(t) < c(t); })
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
		F present_value(size_t m, const T* u, const F* c) const
		{
			return fms::pwflat::present_value(m, u, c, size(), t(), f(), f_);
		}
		F duration(T t0, size_t m, const T* u, const F* c) const
		{
			return fms::pwflat::duration(t0, m, u, c, size(), t(), f(), f_);
		}

		std::pair<T,F> back() const
		{
			/*
			ensure (size() > 0);

			return std::make_pair(t(size() - 1), f(size() - 1));
			*/
			return operator[](size() - 1);
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
		// knot point pairs
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

	namespace pointer {
		// curve using preallocated arrays, not a value type
		template<class T = double, class F = double>
		class curve : public fms::pwflat::curve<T,F> {
			size_t n_;
			const T* t_;
			const F* f_;
		public:
			// constant curve
			curve(const F& _f = 0)
				: fms::pwflat::curve<T,F>(_f), n_(0), t_(nullptr), f_(nullptr)
			{ }
			// number of points, pointer to times, pointer to rates, extrapolation value
			curve(size_t n, const T* t, const F* f, const F& _f = 0)
				: fms::pwflat::curve<T,F>(_f), n_(n), t_(t), f_(f)
			{ }
			// avoid pointer aliasing
			curve(const curve&) = delete;
			curve& operator=(const curve&) = delete;
			~curve()
			{ }

			size_t _size(void) const override
			{
				return n_;
			}
			const T* _t(void) const override
			{
				return t_;
			}
			const F* _f(void) const override
			{
				return f_;
			}
		};
	}

	namespace vector {
		// curve using vectors for storage, is a value type
		template<class T = double, class F = double>
		class curve : public fms::pwflat::curve<T,F> {
			std::vector<T> t_;
			std::vector<F> f_;
		public:
			curve(size_t n = 0, const T* t = nullptr, const F* f = nullptr, const F& f_ = 0)
				: fms::pwflat::curve<T,F>(f_), t_(t, t + n), f_(f, f + n)
			{ }
			 // C++11 allows delegating constructors
			curve(const fms::pwflat::curve<T,F>& c)
				: curve(c.size(), c.t(), c.f(), c.extrapolate())
			{ }
//			curve(const curve& c)
//				: curve(c.size(), c.t(), c.f(), c.extrapolate())
//			{ }
			curve& operator=(const curve&) = default;
			curve(curve&& c)
				: curve(c.extrapolate()), t_(std::move(c.t_)), f_(std::move(c.f_))
			{ }
			curve& operator=(curve&& c)
			{
				t_ = std::move(c.t_);
				f_ = std::move(c.f_);
				extrapolate(c.extrapolate());

				return *this;
			}
			~curve()
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
/*???
			std::pair<T,F> back() const
			{
				return std::make_pair(t_.back(), f_.back());
			}
*/
			// add knot at back of curve
			curve& push_back(const T& t, const F& f)
			{
				ensure (size() == 0 || t > t_.back());

				t_.push_back(t);
				f_.push_back(f);

				return *this;
			}
			// insert new knot point
			curve& insert(const T& t, const F& f)
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
			curve& operator+=(const F& s)
			{
				for (auto& f : f_) {
					f += s;
				}
				// f_ += s does not work since f_ is private
				extrapolate(extrapolate() + s);

				return *this;
			}
			curve& operator-=(const F& s)
			{
				return operator+=(-s);
			}
			// multiply constant factor
			curve& operator*=(const F& s)
			{
				for (auto& f : f_) {
					f *= s;
				}
				extrapolate(extrapolate() * s);

				return *this;
			}
			curve& operator/=(const F& s)
			{
				return operator*=(1/s);
			}
			curve& operator+=(const fms::pwflat::curve<T,F>& c)
			{
				return op_eq(c, std::plus<F>());
			}
			curve& operator-=(const fms::pwflat::curve<T,F>& c)
			{
				return op_eq(c, std::minus<F>());
			}
			curve& operator*=(const fms::pwflat::curve<T,F>& c)
			{
				return op_eq(c, std::multiplies<F>());
			}
			curve& operator/=(const fms::pwflat::curve<T,F>& c)
			{
				return op_eq(c, std::divides<F>());
			}
		private:
			// curve binary operators
			template<class Op>
			curve& op_eq(const fms::pwflat::curve<T,F>& c, Op op)
			{
				std::vector<T> t(t_);

				t.insert(t.end(), c.t(), c.t() + c.size());
				std::inplace_merge(t.begin(), t.begin() + size(), t.end());
				auto ti = std::unique(t.begin(), t.end());
				t.resize(ti - t.begin());

				std::vector<F> f(t.size());
				std::transform(t.begin(), t.end(), f.begin(), [this,&c,&op](const T& ti) { return op(value(ti), c(ti)); });
				/* same effect as
				for (size_t i = 0; i < t.size(); ++i) {
					f[i] = value(t[i]) + c(t[i]); // correct but not efficient!!!
				}
				*/

				t_ = t;
				f_ = f;
				
				extrapolate(extrapolate() + c.extrapolate());

				return *this;
			}
		};
	}
} // pwflat
} // fms

// define arithmetic functions in global namesapce
template<class T, class F>
inline fms::pwflat::vector::curve<T,F> operator+(const fms::pwflat::curve<T,F>& a, const F& s)
{
	return fms::pwflat::vector::curve<T,F>(a) += s;
}
template<class T, class F>
inline fms::pwflat::vector::curve<T,F> operator+(const F& s, const::fms::pwflat::curve<T,F>& a)
{
	return fms::pwflat::vector::curve<T,F>(a) += s;
}
template<class T, class F>
inline fms::pwflat::vector::curve<T,F> operator+(const fms::pwflat::curve<T,F>& a, const fms::pwflat::curve<T,F>& b)
{
	return fms::pwflat::vector::curve<T,F>(a) += b;
}
template<class T, class F>
inline fms::pwflat::vector::curve<T,F> operator-(const fms::pwflat::curve<T,F>& a, const fms::pwflat::curve<T,F>& b)
{
	return fms::pwflat::vector::curve<T,F>(a) -= b;
}
template<class T, class F>
inline fms::pwflat::vector::curve<T,F> operator*(const fms::pwflat::curve<T,F>& a, const fms::pwflat::curve<T,F>& b)
{
	return fms::pwflat::vector::curve<T,F>(a) *= b;
}
template<class T, class F>
inline fms::pwflat::vector::curve<T,F> operator/(const fms::pwflat::curve<T,F>& a, const fms::pwflat::curve<T,F>& b)
{
	return fms::pwflat::vector::curve<T,F>(a) /= b;
}

#ifdef _DEBUG

#include <random>

using namespace fms::pwflat;

inline void test_pwflat_curve()
{
	//default
	curve<> c1;
	ensure(c1.size() == 0);
	ensure(c1.t() == nullptr);
	ensure(c1.f() == nullptr);
	ensure (c1(100) == 0);

	//copy
	curve<> c2 = c1;
	ensure(c2.size() == 0);
	ensure(c2.t() == nullptr);
	ensure(c2.f() == nullptr);
	ensure(c1 == c2);

	//copy assignment 
	curve<> c3(1);
	curve<> c4;
	c4 = c3;
	ensure(c3 == c4);
	ensure(c3 != c1);

	//extrapolation
	ensure(c3.extrapolate() == 1);
	c3.extrapolate(3);
	ensure(c3.extrapolate() == 3);

	//comparison
	ensure(c1 < c3);
	ensure(!(c1 == c3));

	ensure(c1.value(0) == 0);
	ensure(c1(0) == 0);
	ensure(c1.integral(0) == 0);
	ensure(c3.integral(1) == 3);
	ensure(c1.present_value(0, 0, 0) == 0);

}

//!!!Giorgio
inline void test_pwflat_pointer_curve()
{
	pointer::curve<> c1;
	ensure(c1.size() == 0);
	ensure(c1.t() == 0);
	ensure(c1.f() == 0);

	int t[] = {0,1,2};
	double f[] = {.1,.2,.3};
	pointer::curve<int,double> c(3, t, f);
	c.back();
	/*
	pointer::curve <> c2 = c1; //!!!disabled for pointer curves
	ensure(c2.t() == 0);
	ensure(c2.f() == 0);
	ensure(c1 == c2);

	pointer::curve <> c3(1);
	pointer::curve <> c4;
	c4 = c3;
	ensure(c3 == c4);
	ensure(c3 != c1);

	ensure(c3.extrapolate() == 1);
	c3.extrapolate(3);
	ensure(c3.extrapolate() == 3);

	ensure(c1 < c3);
	ensure(c1.value(0) == 0);
	ensure(c1(0) == 0);
	ensure(c1.integral(0) == 0);
	ensure(c3.integral(1) == 3);
	ensure(c1.present_value(0, 0, 0) == 0);

	ensure(c1.t(0) == 0);
	ensure(c1.f(0) == 0);
	ensure(std::make_pair(0., 0.) == c1[0]);
	*/
}


inline void test_pwflat_vector_curve()
{
	vector::curve<> c;
	ensure (c.size() == 0);
	ensure (c(2) == 0);

	vector::curve<> c2(c);
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

	vector::curve<> c3(3,t3,f3), c4(2,t4,f4);
	vector::curve<> c5 = c3 + c4;
	ensure (c5.size() == 5);
	for (double t = 0.5; t <= 3.5; t += 0.5) {
		ensure (c3(t) + c4(t) == c5(t));
	}
}

inline vector::curve<> random_curve()
{
	static std::default_random_engine e;
	static std::uniform_int_distribution<size_t> u(0,10);
	static std::exponential_distribution<double> ed(10);

	size_t n = u(e);
	std::vector<double> t, f;
	for (size_t i = 0; i < n; ++i) {
		t.push_back((i ? t.back() : 0) + ed(e));
		f.push_back(ed(e));
	}

	return vector::curve<>(n, &t[0], &f[0]);
}

inline void test_pwflat_vector_curve_ops()
{
	std::default_random_engine e;
	vector::curve<> c1, c2;
	c1 = random_curve();
	c2 = random_curve();

	vector::curve<> add = c1 + c2;
	double tn = add.back().first;
	
	size_t N = 100;
	for (size_t i = 0; i < N; ++i) {
	//!!!jl2372
	// test sub(-), mul(*), and div(/)
}		double t = std::uniform_real_distribution<>(0, tn)(e);
		ensure (add(t) == c1(t) + c2(t));
	}



inline void test_pwflat()
{
	test_pwflat_curve();
	test_pwflat_pointer_curve();
	test_pwflat_vector_curve();
	test_pwflat_vector_curve_ops();
}

#endif // _DEBUG



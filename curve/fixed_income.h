// fixed_income.h - fixed income routines
// Copyright (c) 2013 KALX, LLC. All rights reserved. No warranty made.
#pragma once
#include <algorithm>
#include <functional>
#include <vector>

namespace fms {
namespace fixed_income {

	// fixed cash flows
	template<class T = double, class C = double>
	class instrument {
		std::vector<T> u_;
		std::vector<C> c_;
	public:
		// no cash flow
		instrument()
			: u_(), c_()
		{ }
		// single cash flow
		instrument(const T& u, const C& c)
			: u_(1, u), c_(1, c)
		{ }
		// n cash flows
		instrument(size_t n, const T* u, const C* c)
			: u_(u, u + n), c_(c, c + n)
		{
			ensure (increasing(u, u + n)); // test before constructing???
		}
		instrument(const std::initializer_list<C>& u, const std::initializer_list<C>& c)
			: u_(u), c_(c)
		{
			ensure (increasing(u_.begin(), u_.end()));
		}

		instrument(const instrument&) = default;
		instrument(instrument&& i)
			: u_(std::move(i.u_)), c_(std::move(i.c_))
		{ }
		instrument& operator=(const instrument&) = default;
		instrument& operator=(instrument&& i)
		{
			u_ = std::move(i.u_);
			c_ = std::move(i.c_);

			return *this;
		}
		virtual ~instrument()
		{ }

		size_t size() const
		{
			return u_.size();
		}

		const T* time() const
		{
			return u_.data();
		}
		T time(size_t i) const
		{
			ensure (i < size());

			return u_[i];
		}

		const C* cash() const
		{
			return c_.data();
		}
		C cash(size_t i) const
		{
			ensure (i < size());

			return c_[i];
		}

		instrument& set(size_t n, const T* u, const C* c)
		{
			ensure (increasing(u, u + n));

			u_ = std::vector<T>(u, u + n);
			c_ = std::vector<C>(c, c + n);

			return *this;
		}

	private:
		// strictly increasing
		template<class I>
		bool increasing(I b, I e) const
		{
			typedef std::iterator_traits<I>::value_type T;

			return std::adjacent_find(b, e, std::greater_equal<T>()) == u_.end();
		}

	};

} // namespace fixed_income
} // namespace fms

#ifdef _DEBUG

using namespace fms::fixed_income;

inline void test_fixed_income_instrument()
{
	instrument<> i;
	ensure (i.size() == 0);

	instrument<int,int> i2(1,2);
	ensure (i2.size() == 1);
	ensure (i2.time(0) == 1);
	ensure (i2.cash(0) == 2);

	instrument<int,int> i3({1,2},{3,4});
	ensure (i3.size() == 2);
	ensure (i3.time(0) == 1);
	ensure (i3.time(1) == 2);
	ensure (i3.cash(0) == 3);
	ensure (i3.cash(1) == 4);
}

#endif // _DEBUG
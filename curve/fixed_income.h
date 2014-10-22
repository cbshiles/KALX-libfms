// fixed_income.h - fixed income routines
// Copyright (c) 2013 KALX, LLC. All rights reserved. No warranty made.
#pragma once
#include "../include/ensure.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

namespace fms {
namespace fixed_income {

	// fixed cash flows
	template<class T = double, class C = double, class D = double>
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
		instrument(const std::initializer_list<T>& u, const std::initializer_list<C>& c)
			: u_(u), c_(c)
		{
			ensure (increasing(u_.begin(), u_.end()));
		}
		instrument(const std::initializer_list<std::pair<T,C>>& i)
		{
			std::for_each(i.begin(), i.end(), [this](const std::pair<T,C>& p) { u_.push_back(p.first); });
			std::for_each(i.begin(), i.end(), [this](const std::pair<T,C>& p) { c_.push_back(p.second); });

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

		// provide date and rate/coupon to determine cash flows
		virtual instrument& fix(const D& d, const C& r)
		{
			c_ = std::vector<C>(size(), r);

			return *this;
		}

		instrument& set(size_t n, const T* u, const C* c)
		{
			ensure (increasing(u, u + n));

			u_ = std::vector<T>(u, u + n);
			c_ = std::vector<C>(c, c + n);

			return *this;
		}

		bool operator==(const instrument& i) const
		{
			return u_ == i.u_ && c_ == i.c_;
		}
		bool operator!=(const instrument& i) const
		{
			return !operator==(i);
		}
		// cumulative cash flows strictly less than
		bool operator<(const instrument& i) const
		{
			return std::all_of(u_.begin(), u_.end(), [this,&i](const T& t) { accumulate(t) < i.accumulate(t); })
				&& std::all_of(i.u_.begin(), i.u_.end(), [this,&i](const T& t) { accumulate(t) < i.accumulate(t); }); 
		}

		size_t size() const
		{
			return u_.size();
		}

		const T* time() const
		{
			return u_.data();
		}
		const T& time(size_t i) const
		{
			ensure (i < size());

			return u_[i];
		}

		const C* cash() const
		{
			return c_.data();
		}
		const C& cash(size_t i) const
		{
			ensure (i < size());

			return c_[i];
		}

		// sum of cash flows to time t
		C accumulate(const T& t) const
		{
			auto it = std::upper_bound(u_.begin(), u_.end(), t);

			return std::accumulate(c_.begin(), c_.begin() + (it - u_.begin()), 0);
		}

		// insert one cash flow
		instrument& add(const T& u, const C& c)
		{
			auto iu = std::lower_bound(u_.begin(), u_.end(), u);

			if (iu != u_.end() && *iu == u) {
				c_[iu - u_.begin()] += c;
			}
			else {
				c_.insert(c_.begin() + (iu - u_.begin()), c);
				u_.insert(iu, u);
			}

			return *this;
		}

		instrument& operator+=(const instrument& i)
		{
			for (size_t i = 0; i < i.size(); ++i)
				add(i.time(i), i.cash(i));

			return *this;
		}

	private:
		// strictly increasing
		template<class I>
		bool increasing(I b, I e) const
		{
			typedef std::iterator_traits<I>::value_type T;

			return std::adjacent_find(b, e, std::greater_equal<T>()) == e;
		}

	};

} // namespace fixed_income
} // namespace fms

#ifdef _DEBUG

using namespace fms::fixed_income;

inline void test_fixed_income_instrument_ops()
{
}

inline void test_fixed_income_instrument_adt()
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

	instrument<int,int> i4{i3};
	ensure (i4.size() == 2);
	ensure (i4.time(0) == 1);
	ensure (i4.time(1) == 2);
	ensure (i4.cash(0) == 3);
	ensure (i4.cash(1) == 4);

	instrument<int,int> i5;
	i5 = i4;
	ensure (i5.size() == 2);
	ensure (i5.time(0) == 1);
	ensure (i5.time(1) == 2);
	ensure (i5.cash(0) == 3);
	ensure (i5.cash(1) == 4);

	ensure (i5.accumulate(-1) == 0);
	ensure (i5.accumulate(0) == 0);
	ensure (i5.accumulate(1) == 3);
	ensure (i5.accumulate(2) == 7);
	ensure (i5.accumulate(3) == 7);

	instrument<int,int> i6{{1,3},{2,4}};
	ensure (i5 == i6);
}

inline void test_fixed_income_instrument()
{
	test_fixed_income_instrument_adt();
	test_fixed_income_instrument_ops();
}
#endif // _DEBUG
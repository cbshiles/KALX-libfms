// fixed_income.h - instruments with fixed cash flows
#pragma once
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include "include/ensure.h"

namespace fms {
namespace fixed_income {

	// Time, Cash flow, Date
	template<class T = double, class C = double, class D = void*>
	class instrument {
		D eff_; // initial calculation date
	public:
		typedef T time_type;
		typedef C cash_type;
		typedef D date_type;
		instrument()
		{ }
		instrument(const instrument&) = default;
		instrument& operator=(const instrument&) = default;
		virtual ~instrument()
		{ }

		// provide date and rate/coupon to determine cash flows
		virtual instrument& fix(const D& d, const C& r) = 0;
		virtual size_t size() const = 0;
		virtual const T* time() const = 0;
		virtual const C* cash() const = 0;

		// convenience functions
		T time(size_t i) const
		{
			ensure (i < size());

			return *(time() + i);
		}
		C cash(size_t i) const
		{
			ensure (i < size());

			return *(cash() + i);
		}
		std::pair<T,C> back() const
		{
			return std::make_pair(time(size() - 1), cash(size() - 1));
		}
		// std::iterator<std::pair<T,C>> begin() ...

		// date of first cash flow (calculation)
		const D& effective() const
		{
			return eff_;
		}
		instrument& effective(const D& eff)
		{
			eff_ = eff;

			return *this;
		}

		bool operator==(const instrument& i) const
		{
			return size() == i.size()
				&& std::equal(time(), time() + size(), i.time())
				&& std::equal(cash(), cash() + size(), i.cash());
		}
		bool operator!=(const instrument& i) const
		{
			return !operator==(i);
		}
		// cumulative cash flows strictly less than
		bool operator<(const instrument& i) const
		{
			return std::all_of(time(), time() + size(), [this,&i](const T& t) { accumulate(t) < i.accumulate(t); })
				&& std::all_of(i.time(), i.time() + i.size(), [this,&i](const T& t) { accumulate(t) < i.accumulate(t); }); 
		}

		// sum of cash flows to time t
		C accumulate(const T& t) const
		{
			auto it = std::upper_bound(time(), time() + size(), t);

			return std::accumulate(cash(), cash() + (it - time()), 0);
		}

	protected:
		// strictly increasing
		template<class I>
		bool increasing(I b, I e) const
		{
			typedef std::iterator_traits<I>::value_type T;

			return std::adjacent_find(b, e, std::greater_equal<T>()) == e;
		}
	};
/*
	// value type
	template<class T = double, class C = double, class D = void*>
	class instrument_vector : public instrument<T,C,D> {
		std::vector<T> u_;
		std::vector<C> c_;
	public:
		typedef T time_type;
		typedef C cash_type;
		typedef D date_type;
		// known number of cash flows
		instrument_vector(size_t n = 0)
			: u_(n), c_(n)
		{ }
		// single cash flow
		instrument_vector(const T& u, const C& c)
			: u_(1, u), c_(1, c)
		{ }
		// n cash flows
		instrument_vector(size_t n, const T* u, const C* c)
			: u_(u, u + n), c_(c, c + n)
		{
			ensure (increasing(u, u + n)); // test before constructing???
		}
		instrument_vector(const std::initializer_list<T>& u, const std::initializer_list<C>& c)
			: u_(u), c_(c)
		{
			ensure (increasing(u_.begin(), u_.end()));
		}
		instrument_vector(const std::initializer_list<std::pair<T,C>>& i)
		{
			std::for_each(i.begin(), i.end(), [this](const std::pair<T,C>& p) { u_.push_back(p.first); });
			std::for_each(i.begin(), i.end(), [this](const std::pair<T,C>& p) { c_.push_back(p.second); });

			ensure (increasing(u_.begin(), u_.end()));
		}

		instrument_vector(const instrument_vector&) = default;
		instrument_vector(instrument_vector&& i)
			: u_(std::move(i.u_)), c_(std::move(i.c_))
		{ }
		instrument_vector& operator=(const instrument_vector&) = default;
		instrument_vector& operator=(instrument_vector&& i)
		{
			u_ = std::move(i.u_);
			c_ = std::move(i.c_);

			return *this;
		}
		virtual ~instrument_vector()
		{ }

		// provide date and rate/coupon to determine cash flows
		instrument_vector& _fix(const D&, const C& r) override
		{
			c_.assign(c_.size(), r);

			return *this;
		}
		size_t _size() const override
		{
			return u_.size();
		}

		const T* _time() const override
		{
			return u_.data();
		}
		const C* _cash() const override
		{
			return c_.data();
		}


		instrument_vector& set(size_t n, const T* u, const C* c)
		{
			ensure (increasing(u, u + n));

			u_ = std::vector<T>(u, u + n);
			c_ = std::vector<C>(c, c + n);

			return *this;
		}
		instrument_vector& set(std::vector<T>&& u, std::vector<C>&& c)
		{
			ensure (u.size() == c.size());
			ensure (increasing(u.begin(), u.end()));

			u_ = std::move(u);
			c_ = std::move(c);

			return *this;
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
		// add all cash flows
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
*/
} // namespace fixed_income
} // namespace fms

#ifdef _DEBUG

using namespace fms::fixed_income;
/*
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

void test_fixed_income_instrument_add()
{
	// ???
	// add same time
	// add different time
}
*/
inline void test_fixed_income_instrument()
{
//	test_fixed_income_instrument_adt();
//	test_fixed_income_instrument_ops();
//	test_fixed_income_instrument_add();
}
#endif // _DEBUG
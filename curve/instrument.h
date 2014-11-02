// fixed_income.h - instruments with fixed cash flows
#pragma once
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include "include/ensure.h"

namespace fms {
namespace fixed_income {

	// abstract base class of Time, Cash flow stream
	template<class T = double, class C = double>
	class instrument {
	public:
		typedef T time_type;
		typedef C cash_type;
		instrument()
		{ }
		instrument(const instrument&) = default;
		instrument& operator=(const instrument&) = default;
		virtual ~instrument()
		{ }

		size_t size() const
		{
			return _size();
		}
		const T* time() const
		{
			return _time();
		}
		const C* cash() const
		{
			return _cash();
		}

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
		std::pair<T,C> front() const
		{
			return std::make_pair(time(0), cash(0));
		}
		std::pair<T,C> back() const
		{
			return std::make_pair(time(size() - 1), cash(size() - 1));
		}
		// std::iterator<std::pair<T,C>> begin() ...

		bool operator==(const instrument& i) const
		{
			if (size() != i.size())
				return false;

			if (size() == 0)
				return true;

			return std::equal(time(), time() + size(), i.time())
				&& std::equal(cash(), cash() + size(), i.cash());
		}
		bool operator!=(const instrument& i) const
		{
			return !operator==(i);
		}
		// cumulative cash flows strictly less than
		bool operator<(const instrument& i) const
		{
			if (size() == 0)
				return true;
			if (i.size() == 0)
				return false;

			return std::all_of(time(), time() + size(), [this,&i](const T& t) { return accumulate(t) < i.accumulate(t); })
				&& std::all_of(i.time(), i.time() + i.size(), [this,&i](const T& t) { return accumulate(t) < i.accumulate(t); }); 
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

	private:
		// overrides
		virtual size_t   _size() const = 0;
		virtual const T* _time() const = 0;
		virtual const C* _cash() const = 0;
	};

	namespace vector {
		// specialize intrument as value type
		// D is date class placeholder
		template<class T = double, class C = double, class D = void*>
		class instrument : public fms::fixed_income::instrument<T,C> {
			std::vector<T> u_;
			std::vector<C> c_;
		public:
			instrument()
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
			instrument(const std::initializer_list<std::pair<T,C>>& i)
			{
				std::for_each(i.begin(), i.end(), [this](const std::pair<T,C>& p) {
					u_.push_back(p.first);
					c_.push_back(p.second);
				});

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
			~instrument()
			{ }

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

			// fix cash flows given settlement, effective and coupon
			instrument& fix(const D& set, const D& eff, const C& c)
			{
				return *this; // no-op;
			}

			// add/insert one cash flow
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
			instrument& add(const std::pair<T,C>& p)
			{
				return add(p.first, p.second);
			}
			// add all cash flows
			instrument& operator+=(const fms::fixed_income::instrument<T,C>& i)
			{
				
				for (size_t i = 0; i < i.size(); ++i)
					add(i.time(i), i.cash(i));

				return *this;
			}
		private:
		};

	}

} // namespace fixed_income
} // namespace fms

#ifdef _DEBUG

using namespace fms;
using vinst = fixed_income::vector::instrument<int,int>;

// abstract data type
inline void test_fixed_income_vector_instrument()
{
	vinst i;
	ensure (i.size() == 0);

	vinst i2(1,2);
	ensure (i2.size() == 1);
	ensure (i2.time(0) == 1);
	ensure (i2.cash(0) == 2);

	vinst i3({{1,3},{2,4}});
	ensure (i3.size() == 2);
	ensure (i3.time(0) == 1);
	ensure (i3.time(1) == 2);
	ensure (i3.cash(0) == 3);
	ensure (i3.cash(1) == 4);

	vinst i4{i3};
	ensure (i4.size() == 2);
	ensure (i4.time(0) == 1);
	ensure (i4.time(1) == 2);
	ensure (i4.cash(0) == 3);
	ensure (i4.cash(1) == 4);

	vinst i5;
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

	vinst i6{{1,3},{2,4}};
	ensure (i5 == i6);
	ensure (!(i5 < i6));
}

inline void test_fixed_income_instrument_ops()
{
	vinst i1{{1,2},{3,4}}, i2{{2,5},{3,6}};

	i1.add(5,7);
	// !!!test add
//	i1 += i2;
	//!!! ensure ...
}


void test_fixed_income_instrument_add()
{
	// ???
	// add same time
	// add different time
}

inline void test_fixed_income_instrument()
{
	test_fixed_income_vector_instrument();
	test_fixed_income_instrument_ops();
	test_fixed_income_instrument_add();
}
#endif // _DEBUG
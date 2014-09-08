// input_iterator.h - routines for input iterators
#pragma once
#ifndef ensure
#include <cassert>
#define ensure(e) assert(e)
#endif
#include <functional>
#include <iterator>
#include <tuple>

namespace fms {
namespace input_iterator {

	template<class I, class U = typename std::iterator_traits<I>::value_type>
	class map : public std::iterator<
		std::input_iterator_tag,
		typename std::iterator_traits<I>::value_type>
	{
		typedef typename std::iterator_traits<I>::value_type T;
		std::function<U(T)> f_;
		I i_;
	public:
		map(const std::function<U(T)>& f, I i) 
			: f_(f), i_(i)
		{ }
//		map(const map&) = default;
//		map& operator=(const map&) = default;
		~map()
		{ }
		U operator*() const
		{
			return f_(*i_);
		}
		map<I,U>& operator++()
		{
			++i_;

			return *this;
		}
		map<I,U> operator++(int)
		{
			map<I,U> m(*this);
			
			++i_;

			return m;
		}
		bool operator==(const map& m) const
		{
			return f_ == m.f_ && i_ == m.i_;
		}
		bool operator!=(const map& m) const
		{
			return !operator==(m);
		}
	};
	template<class I, class U>
	map<I,U> make_map(std::function<U(typename std::iterator_traits<I>::value_type)> f, I i)
	{
		return map<I,U>(f, i);
	}

	template<typename I0, typename I1>
	class zip : public std::iterator<
		std::input_iterator_tag,
		typename std::tuple<typename std::iterator_traits<I0>::value_type, typename std::iterator_traits<I1>::value_type>>
	{
		typedef typename std::iterator_traits<I0>::value_type T0;
		typedef typename std::iterator_traits<I1>::value_type T1;
		I0 i0_;
		I1 i1_;
	public:
		zip(I0 i0, I1 i1)
			: i0_(i0), i1_(i1)
		{ }
		~zip()
		{ }
		std::tuple<T0,T1> operator*() const
		{
			return std::make_tuple(*i0_, *i1_);
		}
		zip& operator++()
		{
			++i0_;
			++i1_;

			return *this;
		}
		zip operator++(int)
		{
			zip z(i0_, i1_);

			++i0_;
			++i1_;

			return z;
		}
		bool operator==(const zip& z) const
		{
			return i0_ == z.i0_ && i1_ == z.i1_;
		}
		bool operator!=(const zip& z) const
		{
			return !operator(z);
		}
	};

}
}

#ifdef _DEBUG

using namespace std;
using namespace fms;

inline void check_input_iterator_map()
{
	int i[] = {1, 2, 3};

	auto it = input_iterator::map<int*,double>([](int i) { return 1.0*i*i; }, begin(i));
	auto it2(it);
	ensure (it2 == it);
	it = it2;
	ensure (it == it2);

	ensure (*it == 1);
	ensure (*++it == 4);
	it++;
	ensure (*it == 9);

	std::function<double(int)> p1 = [](int i) -> double { return i + 1.; };
	auto mit = input_iterator::make_map(p1, begin(i));
//	auto mit = input_iterator::make_map([](int i) -> double { return i + 1.; }, begin(i));

	ensure (*mit == 2.);
	mit++;
	ensure (*mit == 3.);
	ensure (*++mit == 4);

}

void check_input_iterator_zip()
{
	int i0[] = {1, 2, 3};
	int i1[] = {4, 5, 6};

	input_iterator::zip<int*,int*> z(begin(i0), begin(i1));
	ensure (*z == std::make_tuple(1, 4));
	z++;
	ensure (*z == std::make_tuple(2, 5));
	int j0, j1;
	std::tie(j0, j1) = *++z;
	ensure (j0 == 3&& j1 == 6);
}

void check_input_iterator()
{
	check_input_iterator_map();
	check_input_iterator_zip();
}


#endif // _DEBUG
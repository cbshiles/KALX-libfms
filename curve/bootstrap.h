// bootstrap.h - bootstrap a curve
#pragma once
#include "bootstrap_functions.h"
#include "pwflat.h"
#include "instrument.h"

namespace fms {
namespace pwflat {

	template<class T, class C, class F>
	inline F bootstrap(const fixed_income::instrument<T,C>& i, const curve<T,F>& c, F f_ = 0, C pv = 0)
	{
		return bootstrap(i.size(), i.time(), i.cash(), c.size(), c.time(), c.rate(), f_, pv); 
	}

	// bootstrap a curve from a container of instruments
	template<class I, class F>
	inline vector_curve<I::time_type, F> bootstrap(I bi, I ei)
	{
		vector_curve<I::time_type,F> c;

		for (; bi != ei; ++bi) {
			c.push_back(bi->back().first, bootstrap(*bi, c));
		}

		return c;
	}

} // pwflat
} // fms

#ifdef _DEBUG

inline void test_bootstrap()
{
	// ???
}


#endif // _DEBUG
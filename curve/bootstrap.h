// bootstrap.h - bootstrap a curve
#pragma once
#include "bootstrap_functions.h"
#include "fixed_income.h"

namespace fms {
namespace pwflat {

	template<class T, class F>
	inline F bootstrap(const fixed_income::instrument& i, const curve& c, F f_ = 0, F pv = 0)
	{
		return bootstrap(i.size(), i.time(), i.cash(), c.size(), c.time(), c.rate(), f_, pv); 
	}

} // pwflat
} // fms

#ifdef _DEBUG


#endif // _DEBUG
// fixed_income.h - fixed income routines
// Copyright (c) 2013 KALX, LLC. All rights reserved. No warranty made.
#pragma once

namespace fms {
namespace fixed_income {

	template<class T = double, class C = void*>
	struct instrument {
		size_t n;
		const T* t;
		const C* c;
		instrument(size_t n_ = 0, const T* t_ = 0, const C* c_ = 0)
			: n(n_), t(t_), c(c_)
		{ }
		instrument(const instrument&) = delete;
		instrument& operator=(const instrument&) = delete;
		virtual ~instrument()
		{ }
		const instrument& set(size_t n_, const T* t_, const C* c_)
		{
			n = n_;
			t = t_;
			c = c_;

			return *this;
		}
		// typically valuation date and coupon
		template<class D> 
		virtual const instrument& fix(const D&, C) const
		{
			return *this;
		}
	};
} // namespace fixed_income
} // namespace fms
// lmm.h - LIBOR Market Model
#pragma once
#include "../prob/normal.h"
#include <vector>

namespace fms {
namespace curve {

	template<class T = double, class F = double>
	class lmm {
		std::vector<T> t;
		std::vector<F> f, sigma, rho;
		size_t n, d, i_;
		std::vector<F> f_, D_; // forward, deflator at t[i]
	public:
		lmm(size_t n, const T* t, const F* f, const F* sigma, size_t d, const F* rho)
			: t(t, t + n),
			  f(f, f + n), sigma(sigma, sigma + n), rho(rho, rho + n*d - d*(d+1)/2), 
			  f_(f, f + n), D_(n),
			  n(n), d(d), i_(0)
		{
			D_[0] = exp(-f[0]*t[0]); // time starts at 0
		}
		lmm(const lmm&) = default;
		lmm& operator=(const lmm&) = default;
		~lmm()
		{ }

		size_t size() const
		{
			return n;
		}
		size_t dimension() const
		{
			return d;
		}
		lmm& reset()
		{
			i_ = 0;
			f_ = f;

			return *this;
		}

		const std::vector<F>& forward() const
		{
			return f_;
		}
		const std::vector<F>& deflator() const
		{
			return D_;
		}

		template<class R>
		lmm& next(R& r)
		{
			++i_;
			ensure (i_ < n);
			T dt = t[i_] - (i_ == 0 ? T(0) : t[i_ - 1]);
			std::vector<F> dB(n); // n_ - i_ ???

			fms::prob::normal::correlated(r, n, d, &rho[0], &dB[0]);

			for (size_t i = i_; i < n; ++i) {
				F srt = sigma[i]*sqrt(dt);
				f_[i] *= exp(-srt*srt/2 + srt*dB[i]);
			}

			D_[i_] = D_[i_ - 1]*exp(-f_[i_]*dt);

			return *this;
		}
		template<class R>
		lmm& to(R& r, size_t i)
		{
			if (i == 0)
				i = n;

			while (i_ < i)
				next(r);

			return *this;
		}
	};
}
}
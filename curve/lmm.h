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
		std::vector<F> f_, D_; // forward, deflator at t[i_]
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

		// number of periods for time, forward, ...
		size_t size() const
		{
			return n;
		}
		// number of factors to use in simulation
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

		// increment next time step
		template<class R>
		lmm& next(R& r)
		{
			++i_;
			ensure (i_ < n);
			T dt = t[i_] - (i_ == 0 ? T(0) : t[i_ - 1]);
 			std::vector<F> dZ(n); // n_ - i_ since first i_ not used ???

			fms::prob::normal::correlated(r, n, d, &rho[0], &dZ[0]);

			for (size_t i = i_; i < n; ++i) {
				F srt = sigma[i]*sqrt(dt);
				f_[i] *= exp(-srt*srt/2 + srt*dZ[i]);
			}

			D_[i_] = D_[i_ - 1]*exp(-f_[i_]*dt);

			return *this;
		}

		// generate futures at expiration and deflator
		template<class R>
		lmm& diag(R& r)
		{
			reset();
 			std::vector<F> Z(n);

			fms::prob::normal::correlated(r, n, d, &rho[0], &Z[0]);

			for (size_t i = 1; i < n; ++i) {
				F srt = sigma[i]*sqrt(t[i]);
				f_[i] = f[i]*exp(-srt*srt/2 + srt*B[i]);
				D_[i_] = D_[i_ - 1]*exp(-f_[i_]*(t[i] - t[i - 1]));
			}


			return *this;
		}
	};
}
}

#ifdef _DEBUG
#include <random>

using namespace fms::curve;

inline std::default_random_engine& r0() { static std::default_random_engine r; return r; }

inline void test_curve_lmm()
{
	double t[] = {1, 2};
	double f[] = {.01, .02};
	double sigma[] = {.3, .4};
	double rho[] = {.9}; // 2*2 - 2*3/2 = 4 - 3 = 1

	lmm<> m(2, t, f, sigma, 2, rho);
	m.next(r0());
	m.next(r0());
}

#endif
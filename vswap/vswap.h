// vswap.h - Variance swap pricing and utilities.
#pragma once
#include <regex>
#include <tuple>
#include <wchar.h>
#ifndef ensure
#include <cassert>
#define ensure(x) assert(x)
#endif

#ifndef DAYS_PER_YEAR
#define DAYS_PER_YEAR 365.25
#endif

namespace vswap {

	enum { INDEX, MONTH, DAY, YEAR, CP_FLAG, STRIKE };
	template<class C>
	inline std::tuple<std::basic_string<C>, int, int, int, C, int>
	parse_bbg_option(const C* ticker, size_t count = 0)
	{
		static std::basic_regex<C> re(_T("([^\\d]*) (\\d\\d)/(\\d\\d)/(\\d\\d) (.)(\\d+)"));

		std::basic_string<C> tic;
		if (count == 0)
			tic = std::basic_string<C>(ticker);
		else
			tic = std::basic_string<C>(ticker, count);

		std::match_results<const C*> mr;
		ensure (std::regex_search(tic.c_str(), mr, re));

		std::basic_string<C> index(mr[1].str());
		int month = _tstoi(mr[2].str().c_str());
		int day = _tstoi(mr[3].str().c_str());
		int year = _tstoi(mr[4].str().c_str());
		C cp = mr[5].str()[0];
		int strike = _tstoi(mr[6].str().c_str());

		return std::make_tuple(index, month, day, year, cp, strike);
	}

	// Return VIX style nearest strike and linearly interpolated forward
	template<class T>
	inline std::pair<T,T> forward(size_t n, const T* k, const T* c, const T* p, double R = 1)
	{
		size_t i(0);

		while (i < n) {
			if (p[i] > c[i])
				break;
			++i;
		}
		ensure (i != n);
		ensure (i != 0);

		T k0, dcp;
		if (c[i-1] - p[i-1] < p[i] - c[i]) {
			k0 = k[i-1];
			dcp = c[i-1] - p[i-1];
		}
		else {
			k0 = k[i];
			dcp = c[i] - p[i];
		}
		

		T dk = k[i] - k[i - 1];
		T mp = (p[i] - p[i - 1])/dk;
		T mc = (c[i] - c[i - 1])/dk;

		return std::make_pair(k0 + R*dcp, k[i] + (c[i] - p[i])/(mp - mc));
	}

	// 30-day VIX from near and next term options
	template<class T>
	inline T interpolate(T s1, T t1, T s2, T t2)
	{
		ensure (0 < t1 && t1 < t2);

		T sst = (s1*s1*t1*(t2 - 30/DAYS_PER_YEAR) + s2*s2*t2*(30/DAYS_PER_YEAR - t1))/(t2 - t1);
		ensure (sst > 0);

		return sqrt(sst*DAYS_PER_YEAR/30);
	}

	// fill mask with included options
	template<class T>
	inline void cboe_mask(int n, const T* callbid, const T* putbid, T* mask)
	{
		ensure (n >= 3);

		mask[n - 1] = 1;
		for (int i = n/2; i < n - 1; ++i) {
			if (callbid[i] == 0) {
				mask[i] = 0;
				if (callbid[i + 1] == 0) {
					while (++i < n)
						mask[i] = 0;
				}
			}
			else {
				mask[i] = 1;
			}
		}

		mask[0] = 1;
		for (int i = n/2; i > 0; --i) {
			if (putbid[i] == 0) {
				mask[i] = 0;
				if (putbid[i - 1] == 0) {
					while (--i >= 0)
						mask[i] = 0;
				}
			}
			else {
				mask[i] = 1;
			}
		}
	}

	// CBOE VIX whitepaper formula. Use mid for put and call prices. Assumes stripped strikes.
	template<class T>
	inline T cboe_vix(T rate, T time, size_t n, const T* strikes, const T* calls, const T* puts)
	{
		ensure (time > 0);
		ensure (n > 2);

		T forward(0);
		T s2(0); // sigma squared
		T k0(0);
		const T* k = strikes;
		const T* p = puts;
		const T* c = calls;

		if (forward == 0) // approximate forward
			forward = vswap::forward(n, k, c, p, exp(rate*time)).first;

		s2 = p[0]*(k[1] - k[0])/(k[0]*k[0]); // first put

		for (size_t i = 1; i < n - 1; ++i) {
			T dk = (k[i + 1] - k[i - 1])/2;
			ensure (dk > 0);

			if (k[i] <= forward) {
				s2 += p[i] * dk/(k[i]*k[i]);
			}
			else {
				if (k[i - 1] <= forward) {
					s2 += ((p[i] + c[i])/2) * dk/(k[i]*k[i]);
					k0 = k[i - 1]; // first strike less than forward
				}
				else { // k[i - 1] > forward
					s2 += c[i] * dk/(k[i]*k[i]);
				}
			}
		}

		s2 += c[n - 1]*(k[n - 1] - k[n - 2])/(k[n - 1]*k[n - 1]); // last call

		ensure (k0 != 0);

		T fk = forward/k0 - 1;
		s2 = (2*exp(rate*time)*s2 - fk*fk)/time;

		return s2;
	}

} // namespace vswap
// vswap.cpp - variance swap pricing and utilities
#include <valarray>
#include "xll/xll.h"
#include "vswap/vswap.h"

#ifndef CATEGORY
#define CATEGORY _T("FMS")
#endif

using namespace std;
using namespace vswap;
using namespace xll;

typedef traits<XLOPERX>::xfp xfp;
typedef traits<XLOPERX>::xcstr xcstr;
typedef traits<XLOPERX>::xchar xchar;
typedef traits<XLOPERX>::xword xword;
typedef traits<XLOPERX>::xstring xstring;

static AddInX xai_parse_bbg_option(
	FunctionX(XLL_LPOPERX, _T("?xll_parse_bbg_option"), _T("PARSE.BBG.OPTION"))
	.Arg(XLL_LPOPERX, _T("Ticker"), _T("is an array of Bloomberg option tickers."))
	.Arg(XLL_BOOLX, _T("_Headers"), _T("is an optional flag indicating headers should be returned. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return three column range of index, expiration date, and strike."))
	.Documentation(_T("Negative strikes indicate put options. "))
);
LPOPERX WINAPI xll_parse_bbg_option(LPOPERX pticker, BOOL header)
{
#pragma XLLEXPORT
	static OPERX ies;

	try {
		if (header) {
			ies.resize(1, 3);
			ies[0] = _T("Index");
			ies[1] = _T("Expiration");
			ies[2] = _T("Strike");
		}
		else {
			ies.resize(0,0);
		}

		const OPERX& ticker(*pticker);
		for (xword i = 0; i < ticker.size(); ++i) {
			OPERX row(1, 3);

			if (ticker[i].xltype != xltypeStr) {
				row[0] = row[1] = row[2] = OPERX(xlerr::NA);
			}
			else {
				//std::tuple<xstring, int, int, int, xchar, int>
				auto t(parse_bbg_option(ticker[i].val.str + 1, ticker[i].val.str[0]));

				row[0] = get<INDEX>(t).c_str();
				row[1] = XLL_XLF(Date, OPERX(2000 + get<YEAR>(t)),
									   OPERX(get<MONTH>(t)),
									   OPERX(get<DAY>(t)));
				row[2] = get<STRIKE>(t);
				if (::toupper(get<CP_FLAG>(t)) == 'P')
					row[2] = -row[2];
			}

			ies.push_back(row);
		}
	}
	catch (const exception& ex) {
		XLL_ERROR(ex.what());

		ies = OPERX(xlerr::NA);
	}

	return &ies;
}

static AddInX xai_vswap_forward(
	FunctionX(XLL_FPX, _T("?xll_vswap_forward"), _T("OPTIONS.FORWARD"))
	.Arg(XLL_FPX, _T("Strikes"), _T("is an array of all put and call strikes."))
	.Arg(XLL_FPX, _T("Calls"), _T("is an array of call mid prices corresponding the Strikes."))
	.Arg(XLL_FPX, _T("Puts"), _T("is an array of put mid prices corresponding the Strikes."))
	.Arg(XLL_DOUBLEX, _T("_Return"), _T("is the optional realized return to expiration. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return estimated forwards based on put and call prices."))
	.Documentation(
		_T("Returns nearest strike and linearly interpolated estimate. ")
	)
);
xfp* WINAPI
xll_vswap_forward(const xfp* k, const xfp* c, const xfp* p, double R)
{
#pragma XLLEXPORT
	static FPX f(2,1);

	try {
		ensure (size(*k) == size(*p));
		ensure (size(*k) == size(*c));

		if (R == 0)
			R = 1;

		auto f_ = forward(size(*k), k->array, c->array, p->array, R);

		f[0] = f_.first;
		f[1] = f_.second;
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		f[0] = std::numeric_limits<double>::quiet_NaN();
	}

	return f.get();
}

static AddInX xai_vix_iterpolate(
	FunctionX(XLL_DOUBLEX, _T("?xll_vix_iterpolate"), _T("VIX.INTERPOLATE"))
	.Arg(XLL_DOUBLEX, _T("Vol1"), _T("is the VIX par volatility to the nearest expiration."))
	.Arg(XLL_DOUBLEX, _T("Time1"), _T("is the time in years to the nearest expiration."))
	.Arg(XLL_DOUBLEX, _T("Vol2"), _T("is the VIX par volatility to the next expiration."))
	.Arg(XLL_DOUBLEX, _T("Time2"), _T("is the time in years to the next expiration."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Interpolate 30 day VIX volatility from near and next term par volatilities."))
	.Documentation(
		_T("Time weighted average of the VIX variance converted to volatility. ")
	)
);
double WINAPI
xll_vix_iterpolate(double s1, double t1, double s2, double t2)
{
#pragma XLLEXPORT
	double s(numeric_limits<double>::quiet_NaN());

	try {
		s = interpolate(s1, t1, s2, t2);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return s;
}

static AddInX xai_cboe_mask(
	FunctionX(XLL_FPX, _T("?xll_cboe_mask"), _T("CBOE.MASK"))
	.Arg(XLL_FPX, _T("CallBid"), _T("is an array of call bid prices."))
	.Arg(XLL_FPX, _T("PutBid"), _T("is an array of put bid prices. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a mask indicating what options to include."))
	.Documentation(_T("Remove zero bids and two consecutive zeros to end of range. "))
);
xfp* WINAPI
xll_cboe_mask(const xfp* cbid, const xfp* pbid)
{
#pragma XLLEXPORT
	static FPX m;

	try {
		ensure (size(*pbid) == size(*cbid));
		m.reshape(pbid->rows, pbid->columns);

		cboe_mask(m.size(), cbid->array, pbid->array, &m[0]);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return m.get();
}

static AddInX xai_cboe_vix(
	FunctionX(XLL_DOUBLEX, _T("?xll_cboe_vix"), _T("CBOE.VIX"))
	.Arg(XLL_DOUBLEX, _T("Rate"), _T("is the continuously compounded interest rate."))
	.Arg(XLL_DOUBLEX, _T("Time"), _T("is the time in years to expiration"))
	.Arg(XLL_FPX, _T("Strikes"), _T("is an array of all put and call strikes."))
	.Arg(XLL_FPX, _T("Calls"), _T("is an array of call mid prices corresponding the Strikes."))
	.Arg(XLL_FPX, _T("Puts"), _T("is an array of put mid prices corresponding the Strikes. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the VIX variance based on the CBOE white paper formula."))
	.Documentation(
		_T("Implementation of the VIX calculation described in the VIX white paper. ")
	)
);
double WINAPI
xll_cboe_vix(double r, double t, const xfp* k, const xfp* c, const xfp* p)
{
#pragma XLLEXPORT
	double s2(std::numeric_limits<double>::quiet_NaN());

	try {
		ensure (size(*k) == size(*p));
		ensure (size(*k) == size(*c));

		s2 = cboe_vix(r, t, size(*k), k->array, c->array, p->array);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return s2;
}

static AddInX xai_bbg_vix(
	FunctionX(XLL_DOUBLEX, _T("?xll_bbg_vix"), _T("BBG.VIX"))
	.Arg(XLL_DOUBLEX, _T("Rate"), _T("is the continuously compounded interest rate."))
	.Arg(XLL_DOUBLEX, _T("Time"), _T("is the time in years to expiration"))
	.Arg(XLL_LPOPERX, _T("Tickers"), _T("is an array of Bloomberg option chain tickers."))
	.Arg(XLL_LPOPERX, _T("Calls"), _T("is an array of call bid/ask prices corresponding to Tickers."))
	.Arg(XLL_LPOPERX, _T("Puts"), _T("is an array of put bid/ask prices corresponding to Tickers. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the CBOE VIX variance using Bloomberg data."))
	.Documentation(
		_T("If Puts and/or Calls is 1-dimensional it assumes mids are provided.")
	)
);
double WINAPI
xll_bbg_vix(double r, double t, const LPOPERX pk, const LPOPERX pc, const LPOPERX pp)
{
#pragma XLLEXPORT
	double s2(std::numeric_limits<double>::quiet_NaN());

	try {
		ensure (pk->rows() == pp->rows());
		ensure (pk->size() == pc->rows());
		ensure (pp->columns() == 2);
		ensure (pc->columns() == 2);

		std::valarray<double> k_(pk->rows()), pb(pp->rows()), cb(pc->rows());

		// get strike, put bids, call bids
		for (xword i = 0; i < k_.size(); ++i) {
			const OPERX& ki = (*pk)[i];
			ensure (ki.xltype == xltypeStr);

			auto pbo = vswap::parse_bbg_option(ki.val.str + 1, ki.val.str[0]);
			k_[i] = std::get<STRIKE>(pbo);

			if ((*pc)(i, 0).xltype != xltypeNum && (*pc)(i, 1).xltype != xltypeNum) {
				cb[i] = 0;
			}
			else {
				cb[i] = (*pc)(i, 0).val.num; // call bid
			}
			if ((*pp)(i, 0).xltype != xltypeNum && (*pp)(i, 1).xltype != xltypeNum) {
				pb[i] = 0;
			}
			else {
				pb[i] = (*pp)(i, 0).val.num; // put bid
			}
		}

		std::valarray<double> m(k_.size()); // mask
		vswap::cboe_mask(m.size(), &cb[0], &pb[0], &m[0]);

		std::vector<double> k, p, c;

		// valid mids
		for (xword i = 0; i < k_.size(); ++i) {
			if (m[i]) {
				k.push_back(k_[i]);
				c.push_back(((*pc)(i, 0) + (*pc)(i, 1))/2);
				p.push_back(((*pp)(i, 0) + (*pp)(i, 1))/2);
			}
		}

		s2 = cboe_vix<double>(r, t, k.size(), &k[0], &c[0], &p[0]);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return s2;
}


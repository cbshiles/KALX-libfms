# Instrument
## Dependencies: datetime

This project involves _fixed income instruments_: instruments having deterministic cash flows. The simplest example is a _zero coupon bond_ that pays 1 unit of the underlying currency at _maturity_. A _cash deposit_ is equivalent to a zero coupon bond: it pays 1 unit plus accrued interest at _termination_. A _forward rate agreement_ has two cash flows: -1 unit at its _start period_ and 1 plus accrued interest at its _end period_. An _interest rate swap_ is just a sequence of back-to-back forward rate agreements.

## Contracts
Fixed income instruments are specified by a contract often called a _term sheet_ or _confirm(ation)_. For dollar denominated instruments [ISDA](http://isda.com) provides standardized contracts for commonly traded instruments. This template for a [_market agreed coupon swap_](http://libfms.codeplex.com/SourceControl/latest#instrument/formofconfirmMAC.pdf) illustrates terms used to specify a contract.

**Notional** - multiplier for all payment amounts
**Trade Date** - date on which coupon is agree upon
**Effective Date** - first date relevant for payment calculations
**Termination Date** - last date relavent for payment calculations
**Payment Dates** - usually specified by a frequency, e.g., quarterly
**Fixed Rate** - is the coupon agreed to on the trade date

### Date Calculations
Since _tenors_ are often described as a _count_ and _unit_, e.g., 3 months, adding a tenor period to a date can result in a non-business day: a weekend or holiday. _Roll conventions_ are used to _adjust_ the date to a business day. For example, _next business_ means advance the date to the next valid business day. The trade date (or _valuation date_) is when counterparties agree on notional and coupon, but the trade is not _settled_ until some number of days later to allow for associated activities to be completed. Two days (T+2) is a common convention. This is the date from which all _calculation dates_ are computed. Calculation dates, including payment dates, are computed by adding a tenor to the settlement date and then applying the appropriate roll convention. 

### Day Count Fractions
A _day count basis_ is used to calculate _day count fractions_. The interest accrued over a period is the rate times the day count fraction. The day count fraction is approximately equal to the time in years of the period. For example, using Actual/360 day count over the period 2014/1/15 to 2014/7/15 is number of days divided by 360: 181/360 = 0.50277...

## `instrument.h`
This class defines `fixed_income::instrument`. It is an _abstract base class_ that has three private _pure virtual_ functions that must be overriddend in derived classes: `_size`, `_time`, and `_cash`. These get called by the public intervace functions `size`, `time`, and `cash` by clients of the base class. [!!!Add something about the NVI idiom!!!]
The derived class `fixed_income::pointer::instrument` implements an instrument for which the time and cash arrays have already been allocated. No memory is allocated, but the copy and assignement constructors have been deleted to avoid aliasing issues.
The derived class `fixed_income::vector::instrument` uses `std::vector` to hold the time and cash flows. It is a value type and has several utility member functions for managing cash flows.
This class does not depend on any data arithmetic.

## `fixed_income_leg.h` (currently `interest_rate_leg.h`)
The class defines `fixed_income::leg` which derives from `fixed_income::vector::instrument`. It specifies the typical contract indicative data and depends on `datetime`. It is used as a base class for the common fixed income instruments such as cash deposits, forward rate agreements, and swaps.

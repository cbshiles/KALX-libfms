# Instrument

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
Since _tenors_ are often described as a _count_ and _unit_, e.g., 3 months, adding a tenor period to a date can result in a non-business day: a weekend or holiday. _Roll conventions_ are used to _adjust_ the date to a business day. For example, _next business_ means advance the date to the next valid business day. The trade date (or _valuation date_) is when counterparties agree on notional and coupon, but the trade is not _settled_ until some number of days later to allow for associated activities to be completed. Two days (T+2) is a common convention. This is the date from which all _calculation dates_ are computed.


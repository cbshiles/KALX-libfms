# Instrument

This project involves _fixed income instruments_: instruments having deterministic cash flows. The simplest example is a _zero coupon bond_ that pays 1 unit of the underlying currency at _maturity_. A _cash deposit_ is equivalent to a zero coupon bond: it pays 1 unit plus accrued interest at _termination_. A _forward rate agreement_ has two cash flows: -1 unit at its _start period_ and 1 plus accrued interest at its _end period_. An _interest rate swap_ is just a sequence of back-to-back forward rate agreements.

## Contracts
Fixed income instruments are specified by a contract often called a _term sheet_ or _confirm(ation)_. For dollar denominated instruments [ISDA](http://isda.com) provides standardized contracts for commonly traded instruments. This template for a [_market agreed coupon swap_](http://libfms.codeplex.com/) shows term used to specify a contract. 
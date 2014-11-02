# Curve
Fixed income yield curves.
The problem this project solves is how to construct a discount curve that prices a set of fixed income instruments.

The _discount_, $D(t)$, is the price of one unit received at time $t$.
A fixed income instrument is a sequence of cash flows, $c_j$ at times $u_j$. The _present value_ of the cash flows is $\sum_j c_j D(u_j)$. A discount curve _prices_ an instrument if its present value equals the market price.

Define the _forward_ curve, $f$, by $D(t) = e^{-\int_0^t f(s)\,ds}$ and the _spot_ curve, $r$, by $D(t) = e^{-t r(t)}$. They should probably have adjectives like _instantainiously_ or _continuously_ to distinguish them from the various market conventions for compounding.

## Piecewise flat curves
In this project, forward curves don't curve: they are piecewise constant.
The file `pwflat_functions.h` defines stand-alone functions and `pwflat.h` defines the base class `fms::pwflat::curve` and derived classes. For preallocated arrays use `fms::pwflat::pointer::curve`. Copy construction and assignment is not allowed to prevent [pointer aliasing](http://en.wikipedia.org/wiki/Pointer_aliasing). The class `fms::pwflat::vector::curve` is a [value type](http://msdn.microsoft.com/en-us/library/hh438479.aspx).

## Bootstrap
Given a piecewise flat forward curve defined on $[0,t]$ and an instrument with cash flows occuring after $t$,
extend the forward curve by the (constant) value that reprices this instrument.
The file `bootstrap_functions.h` has functions for bootstrapping fixed income instruments. The file `bootstrap.h` creates a `pwflat::vector::curve` given a collection of instruments sorted by maturity using `pwflat::bootstrap`.

## Instruments
The `fixed_income::instrument` class is an abstact base class for cash flow streams. The interface is an array of times in years and an array of cash amounts. Converting dates to time in years requires date and time routines from the `datetime` project.

In the real world, fixed income instruments are specified by _indicative data_, or _terms and conditions_. 

http://isda.org/

E.g., a 3 month forward rate agreement having Actual/360 day count and New York back holidays using modified following adjustments. In order to determine the cash flows at time in years, must specify the _valuation date_ corresponding to time 0, the _effective date_ of the first cash flow (calculation), and the coupon. These are the arguments to `fixed_income::fix`. If the effective date is specified as an integer then it is assumed to mean the number of days after valuation.

The file `instrument.h` defines an interface class for fixed income instruments -- `fms::fixed_income::instrument`. 




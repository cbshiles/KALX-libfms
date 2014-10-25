# Curve
Fixed income yield curves.
The _discount_, $D(t)$, is the price of one unit received at time $t$.
A fixed income instrument is a sequence of cash flows, $c_j$ at times $u_j$.
A discount curve, $D(t)$, _prices_ an instrument if $p = \sum_j c_j D(u_j)$, where $p$ is the market price of the cash flow sequence.

The problem this project solves is how to construct a discount curve given a set of fixed income instruments and their prices.

Define the _forward_ curve, $f$, by $D(t) = e^{-\int_0^t f(s)\,ds}$ and the _spot_ curve, $r$, by $D(t) = e^{-t r(t)}$.

In this project, forward curves don't curve: they are piecewise constant.
The file `pwflat_functions.h` defines stand-alone functions and `pwflat.h` defines `fms::pwflat::curve` and related classes.
For preallocated arrays use `fms::pwflat::pointer_curve`. Copy construction and assignment is not allowed to prevent pointer aliasing.
The class `fms::pwflat::vector_curve` is a [value type](http://msdn.microsoft.com/en-us/library/hh438479.aspx).

## Bootstrap
Given a piecewise flat forward curve defined on $[0,t]$ and an instrument with cash flows occuring after $t$,
extend the forward curve by the (constant) value that reprices this instrument.
The file `bootstrap_functions.h` has functions for bootstrapping cash deposits, forward rate agreements, and generic fixed income instruments.

## Instruments
The `fixed_income::instrument` class is a value type for cash flow streams. It also contains a member for the _effective date_: the date on which the first cash flow occurs. The rational is that most instruments are specified by indicative data.
E.g., a 3 month forward rate agreement having Actual/360 day count and New York back holidays using modified following adjustments. In order to determine the cash flows at time in years, one must first specify the `effective` date. A market quote provides a rate for the fixed coupon on a given date. These are the arguments to `instrument::fix`. A runtime error is thrown if you try to fix cash flows before specifying the effective date.





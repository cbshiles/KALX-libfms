# Curve
## Dependencies: root (???)

Fixed income yield curves.
The problem this project solves is how to construct a discount curve that prices a set of fixed income instruments.

The _discount_, $D(t)$, is the price of one unit received at time $t$.
A fixed income instrument is a sequence of cash flows, $c_j$ at times $u_j$. The _present value_ of the cash flows is $\sum_j c_j D(u_j)$. A discount curve _prices_ an instrument if its present value equals the market price.

Define the _forward_ curve, $f$, by $D(t) = e^{-\int_0^t f(s)\,ds}$ and the _spot_ curve, $r$, by $D(t) = e^{-t r(t)}$. They should probably have adjectives like _instantaneously_ or _continuously_ to distinguish them from the various market conventions for compounding.

## Piece-wise flat curves
In this project, forward curves don't curve: they are piece-wise constant.
The file `pwflat_functions.h` defines stand-alone functions and `pwflat.h` defines the base class `fms::pwflat::curve` and derived classes. For preallocated arrays use `fms::pwflat::pointer::curve`. Copy construction and assignment is not allowed to prevent [pointer aliasing](http://en.wikipedia.org/wiki/Pointer_aliasing). The class `fms::pwflat::vector::curve` is a [value type](http://msdn.microsoft.com/en-us/library/hh438479.aspx).

## Bootstrap
Given a piece-wise flat forward curve defined on $[0,t]$ and an instrument with cash flows occurring after $t$,
extend the forward curve by the (constant) value that reprices this instrument.
The file `bootstrap_functions.h` has functions for bootstrapping fixed income instruments. The file `bootstrap.h` creates a `pwflat::vector::curve` given a collection of instruments sorted by maturity using `pwflat::bootstrap`.

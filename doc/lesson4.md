---
title: <a href="index.html">Implementation of Financial Models</a>
...

# Lesson 4

> <i>"The fundamental idea is simply to improve design and programming
through abstraction.  You want to hide details, you want to exploit any
commonality in a system, and you want to make this affordable."</i>

Reading: [Why C++is not just an Object-Oriented Programming Language](http://www.stroustrup.com/oopsla.pdf)

## Bootstrap

The _time value of money_ is called the _discount_. A _zero coupon bond_
indicates the price today of 1 unit of currency received in the future.
Let $D(t)$ denote of 1 unit received at time $t$. The _(continuously
compounded) spot rate_ is defined by $D(t) = \exp(-tr(t))$ and the
_(continuously compounded) forward rate_ by $D(t) = \exp(-\int_0^t f(s)\,ds)$.

A _fixed income instrument_
is determined by cash flows $c_j$ at times $t_j$.
Since it is a portfolio of zero
coupon bonds, its value is $\sum_j c_j D(t_j)$.
Given a collection of fixed income instruments $(c_j^k, t_j^k)$ having
prices $p_k$ we can find many discount curves such that
$$
    p_k = \sum_j c_j^k D(t_j^k)
$$
for all $k$. The _bootstrap_ method gives a canonical way of building
a discount curve. Let $u_k = \max_j t_j^k$ be the maturity of the
$k$-th instrument. We look for a forward curve that is piece-wise flat
with breakpoints a $u_k$. Assume the $u_k$ are increasing. Given
a discount curve out to $u_k$, we can extend the forward to $u_{k+1}$
in a way that reprices the $k+1$-st instrument.

### Instruments
Typical fixed income instruments are cash deposits, forward rate agreements,
futures, and swaps. These are real world instruments that have associated
indicative data. For example, a _cash deposit_ is determined by its
notional, tenor, rate, and day count basis. There are also various
settlement conventions to deal with dates that fall on weekends,
holidays, or the end of month.

The calculation dates associated with these instruments must be converted
to time in years since some epoch, usually the _settlement date_.

### Datetime
The `datetime` library helps convert between absolute dates and
time in years. We choose the convention that one year consists
of 365.25 days(`DAYS_PER_YEAR`). This is slightly arbitrary, but
as long as it is used consistently there is no problem in practice.


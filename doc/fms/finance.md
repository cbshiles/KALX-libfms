# Finance

I order to apply mathematics to finance we need to map financial
concepts to mathematical concepts. This involves making assumptions
to simplify messy reality.

## Assumptions

### Trading Times

It is customary in the literature to model time as a real number,
usually time in years since a given epoch. Unfortunately, this
leads to unrealistic models. E.g., the
[Doubling Paradox](../../papers/HarKre1979.pdf).
We assume trading times are discrete and correspond to dates.
The time increments can be arbitrarily small and there is
no upper bound on time.

### Single Currency

To simplfy exposition we will assume a single currency is used.
There is a standard procedure for incorporating multiple currencies.

### Perfect Liquidity

This means every instrument can be bought or sold in any quantity at
a single price. The previous two assumptions are innocuous, but this
assumption is a drastic deviation from how markets work.  Buying or
selling even the smallest quantity of an instrument involves a bid-ask
spread and buying large quantities typically increases the spread. There
is a finite amount of any instrument available at which point price
loses meaning. There are also instruments that cannot be shorted.

### No Arbitrage

This is the most ridiculous assumption, but also the most crucial.
The (potential) existence of arbitrage is a major driving force.
A significant number of market participants get paid to identify and
eliminate arbitrage. This is also a reason that makes this assumption
more plausible.

It has been empirically verified that giving traders models that are not
arbitrage free results in them selling undervalued and buying overvalued
instruments. Eventually the real world catches up
and the company takes a P&L hit.

The Fundamental Theorem of Asset Pricing shows assuming a model is
arbitrage free places constraints on price dynamics.

## Definitions

$(t_j)$ -- Trading Times

:    The set of all times at which trading can occur.

$(X_j)$ -- Prices

:    Each $X_j$ is a vector of market instrument prices at time $t_j$.

$(C_j)$ -- Cash Flows

:    Each $X_j$ is a vector of cash flows instrument holders receive at
     time $t_j$ if the instrument is held at time $t_{j-1}$.
     Most components of $C_j$ are zero.

$(\Gamma_j)$ -- Trades

:    Each $\Gamma_j$ is the amount traded in each instrument at time $t_j$.
     Most components of $\Gamma_j$ are zero.

$(\Delta_j)$ -- Position

:    Define $\Delta_j = \sum_{i\lt j} \Gamma_j$. This is the total
     amount of each instrument held at time $t_j$.

$(A_j)$ -- Account

:    Define $A_j = \Delta_{j-1}\cdot C_j - \Gamma_j\cdot X_j$.
     The amount of money reflected in the trade blotter at time $t_j$ is
	 the cash flows from the existing position less the cost of current
	 securities traded.
     Note that no cash flows accrue to current trades.

Arbitrage

:    A sequence of trades $(\Gamma_j)$ such that

    i)    $\sum_j \Gamma_j = 0$, i.e., the trading strategy is closed out
         at some point.
    ii)    $A_0 \gt 0$, you make a positive amount on the first trade.
    iii)   $A_j \ge 0$, $j\gt 0$, you never lose money thereafter.

### Remarks

Trading times correspond to dates, but are often modeled as floating
point numbers since some epoch. In the C++ `<chrono>` class they
are called `time_point`s.

Cash flows typically have some period between when the instrument is
purchased and when the cash flows are available. E.g., ex-dividend
period for stocks. The model is misspecified if $t_j - t_{j-1}$ is
smaller than this period.

The definition of arbitrage is not sufficient for traders. In
addition to knowing how much they make up front,
$A_0 = \Gamma_0\cdot X_0$, they also want to know how much capital
they will tie up to make that amount. A crude measure is to slap
absolute values around every number, $|\Gamma_0|\cdot|X_0|$.

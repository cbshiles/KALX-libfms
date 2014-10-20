# Finance

In order to apply mathematics to finance we need to map the complicated
reality of the financial world to concepts amenable to mathematical
analysis. This involves making assumptions, but it allows rigorous
methods to be applied that can extend a trader's intuition or mitigate a
risk manager's uncertainty.

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

To simplify exposition we will assume a single currency is used.
There is a standard procedure for incorporating multiple currencies.

### Perfect Liquidity

This means every instrument can be bought or sold in any quantity at
a single price. The previous two assumptions are innocuous, but this
assumption is a drastic deviation from how markets work.  Buying or
selling even the smallest quantity of an instrument involves a bid-ask
spread and buying large quantities typically increases the spread. There
is a finite amount of any instrument available and some instruments
cannot be sold short.

### No Arbitrage

This is the most ridiculous assumption, but also the most crucial.
The potential existence of arbitrage is a major driving force.
Market participants get paid to identify and eliminate arbitrage. This
is also a reason that makes this assumption more plausible.

It has been empirically verified that giving traders models that are not
arbitrage free results in them selling undervalued and buying overvalued
instruments. Eventually the real world catches up and the company takes
a P&L hit. 

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

:    Define $\Delta_j = \sum_{i < j} \Gamma_j$. This is the total
     amount of each instrument held at time $t_j$.

$(A_j)$ -- Account

:    Define $A_j = \Delta_{j-1}\cdot C_j - \Gamma_j\cdot X_j$.
     The amount of money reflected in the trade blotter at time $t_j$ is
	 the cash flows from the existing position less the cost of current
	 securities traded.
     Note that no cash flows accrue to current trades.

$\Delta_j\cdot X_j$ -- Value

:	The position time price gives the (marked-to-market)
	value of a position.
	It is the amount you would receive from liquidating the position.

# Unified Derivatives

The last formula is the skeleton key to derivatives. It can be used
to turn market traded instruments into any sequence of cash flows,
assuming you can find the appropriate trades $(\Gamma_j)$. The value
of the cash flows is the cost of setting up the initial trade:
$\Gamma_0\cdot X_0$.

Unfortunately, this never happens in the real world. No hedge is
perfect. Tragically, the Nobel prize winning Black-Scholes/Merton theory
has had a pernicious influence on the mathematical finance world:
continuous time trading and perfect replication are a mathematical
fiction.

The hard problem that is yet to be solved is how to manage risk under
uncertainty. We are still in early stages. What follows is an attempt
to map the complicated financial world more faithfully to mathematics
with an eye to efficient software implementation.

The starting point is a clear understanding of how arbitrage can
only be defined in terms of a model.

## Arbitrage

Arbitrage exists if there are trades $(\Gamma_j)$ such that
$\sum_j \Gamma_j = 0$, $A_0 > 0$, and $A_j \ge 0$, $j > 0$.

The trading strategy must be closed out at some point,
make a positive amount on the first trade,
and never lose money thereafter.

You can double down on losses to keep $A_j$ non-negative but eventually
you run out of capital.  Closing out Leeson's position caused the demise
of the UK's oldest investment bank.

In the literature you will see arbitrage defined as $A_0 = 0$,
$A_j\ge0$, and $A_j > 0$ with non-zero probability. This is
sufficient to prove a mathematical theorem, but not
what a trader would consider to be arbitrage without more
information on how positive the payoff is and how likely
it is to occur.

Even this stronger definition of arbitrage [@Gar1981] is not sufficient.
In addition to knowing how much they make up front, traders also want
to know how much capital they will tie up to make that amount. A crude
measure is to slap absolute values around every number and only consider
trading if $-\Gamma_0\cdot X_0/|\Gamma_0|\cdot|X_0|$ is sufficiently large.

Furthermore, the value of $|\Delta_{j-1}|\cdot |C_j| - |\Gamma_j|\cdot
|X_j|$ over the life of the trade relative to $A_j$ will be something
risk managers look at every day.

But wait, that's not all. If $A_j$ becomes significantly positive risk
managers will pressure traders to modify the trading strategy to capture
the value as quickly as possible.

In what follows we will ignore these considerations.

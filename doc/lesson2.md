---
title: <a href="index.html">Implementation of Financial Models</a>
...

# Lesson 2

> <i>"The manifest characteristic of (21) is the number of variables that it does not depend on"</i>

## The Mathematical Model

Reading: [Theory of rational option pricing](http://kalx.net/Mer1973.pdf),
[The Fundamental Theorem of Asset Pricing](http://kalx.net/ftapd.pdf)

This lesson provides a mathematical framework for valuing and
hedging every financial product. First we map the real world
to the mathematical model.

Trading Times
  ~ $t_0\lt t_1\lt \cdots$ -- when market instruments can be traded
Market Prices
  ~ $X_0, X_1, \dots$ -- in terms of a fixed base currency
Cash Flows
  ~ $C_0, C_1, \dots$ -- payments to holder associated with the insturment
Trades
  ~ $\Gamma_0, \Gamma_1, \dots$ -- amount traded in each instrument
Position
  ~ $\Delta_j = \sum_{i\le j} \Gamma_i$ -- amount held in each instrument
Account
  ~ $A_j = \Delta_{j-1}\cdot C_j - \Gamma_j\cdot X_j$

The last item is the amount you see on the account statement from your broker
or on your trade blotter. At time $t_j$ you receive cash flows associated
with the position that you already hold. This includes stock dividends,
bond coupons, etc. You trade $\Gamma_j$ at price $X_j$ so the product
is the dollar amount that will be deducted from your account.

Arbitrage
  ~ Trades $(\Gamma_j)$ with $\sum_j \Gamma_j = 0$, $A_0\gt0$, and $A_j\ge0$ for $j\gt0$

In words, arbitrage is a sequence of trades that are eventually closed
out that make a strictly positive amount up front and never lose money
thereafter. In the real world this definition is not strong enough. Traders
and risk managers will look at $|\Gamma_0|\cdot|X_0|$ too. This is
a measure of how much capital will be tied up to make a profit
of $A_0 = \Gamma_0\cdot X_0$. In the real real world (this actually happened
to me) even that is not sufficient. Traders also want to know the
__gamma profile__ of the trading strategy: under what conditions will
future $\Gamma_j$ become large? That is a pain point for them.

### The Fundamental Theorem of Asset Pricing

Market prices, cash flows, trades, etc. are vector-valued functions
on a set, $\Omega$, of possible outcomes. A simple one-period model
for a bond having realized return $R$, a stock with initial price $s$
and final price any positive value, and a call option with price $c$
and strike $k$ is $\Omega = \{\omega : 0\lt\omega\lt\infty\}$,
$X_0 = (1, s, c)$,
$X_1(\omega) = (R, \omega, 0)$, we always assume $C_0 = 0$, and
$C_1(\omega) = (0, 0, \max\{\omega - k,0\})$.

I prefer writing $R$ instead of $e^{rt}$. Fewer symbols.
Note that the option has price
0 at expiration. The option holder receives a cash flow at expiration. It
is important to distinguish between prices and cash flows.

One thing we also have to specify for a model is a __filtration__:
an increasing sequence of algebras. Prices, cash flows, etc. must
be __adapted__ to the filtration. 

_Theorem_ (The Fundamental Theorem of Asset Pricing)
A model is arbitrage free if and only if there exist positive
scalar measures, $\Pi_j$, on $\mathscr{A}_j$ such that
$$X_j\Pi_j = (C_{j+1} + X_{j+1})\Pi_{j+1}|_{\mathscr{A}_j}.$$

The positive scalar measures are called __deflators__.
One direction of the proof is easy, as we will soon show.
The difficult direction of the proof is that no arbitrage
implies the existence of deflators. Fortunately, we don't
care about that direction because it straighforward find
explict deflators that satisfy the no arbitrage condition.

_Lemma_ If a model is arbitrage free then
$$\Delta_j\cdot X_j\Pi_j = (A_{j+1} + \Delta_{j+1}\cdot X_{j+1})\Pi_{j+1}|_{\mathscr{A}_j}.$$

### Algebras/Partitions
Partial information is modeled by an
[algebra](http://en.wikipedia.org/wiki/Algebra_of_sets),
$\mathscr{A}$, on $\Omega$. 
An __atom__, $A$, is a set in the algebra such that if $B\subseteq A$
and $B$ is in the algebra, then either $B=\emptyset$ or $B=A$.

_Exercise._ Show that if an algebra is finite then the atoms form
a [partition](http://en.wikipedia.org/wiki/Partition_of_a_set) of $\Omega$.

A simple example of modeling partial information is knowing if the
roll of a single die is either even or odd. The possible outcomes
are $\{1,2,3,4,5,6\}$ and the partition is $\{\{1,3,5\},\{2,4,6\}\}$

The power set algeba, $P(\Omega) = \{A:A\subseteq\Omega\}$ represents
complete information. The atoms are singletons, $\{\omega\}$,
$\omega\in\Omega$. The trival algebra having $\Omega$
as the only atom represents having no information.

In general, partial information is modeled by knowing only which
atom an outcome belongs to, not the exact outcome.

[!!!measurable function???]

[!!!measures, restriction???]


# Pricing, Hedging, and Risk

There are Nobel prizes to be won by people who can advance the
theory Black, Scholes, and Merton developed that revolutionized
derivative securities. They showed how to use existing market
instruments to create synthetic instruments tailored to the
needs of companies that want to control the risk of uncertain
future cash flows.

Its major failing is the lack of some measure of risk on how well the
hedge can be expected to perform. Markets are not complete.  The gamma
profile is only a measure of how busy traders might become.  VaR does
not take into account the fact that positions are actively hedged.
The various Value Adjustments are a better measure, but they can
be improved.

The first step is to map what occurs in the financial world faithfully
to mathematics and give unambiguous names to relevant concepts.
It is important to avoid making implicit assumptions. Not everyone can
borrow at the same rate. Options aren't always exercised optimally.
_All_ transactions involved with trading must be accounted for.

## Transactions

_Transactions_ are the atoms of finance.
At a given time, a buyer exchanges some amount of an instrument with
some amount of another instrument the seller is offering.
Korg give Grok 2 bear skin for 10 hand ax at some point in the
late Pleistocene epoch. Every transaction
that has ever happened can be represented by
$$
\chi = (t;a,i,c;a',i',c')
$$
At time $t$ the buyer, $c$,
received amount $a$ of instrument $i$ and gave the seller, $c'$,
amount $a'$ of instrument $i'$.

Every transaction has a _buyer_ and a _seller_. The buyer decides the
amount of an instrument they wish to obtain in exchange for what is
offered by the seller. These nouns are distinct from the verbs _buy_
and _sell_ indicating the sign of the amount. If $a$ is positive the
buyer is buying, aka going _long_, $i$. If $a$ is negative the buyer is
selling, aka _shorting_, $i$.

Buyers are the active counterparty. Sellers present their wares to
buyers, but they can sell instruments that contain provisions for
transactions under their control. E.g., callable bonds.

### Accounting

Given a set of transactions, $\{\chi_j\}$, we can use something akin
to the Einstein summation convention to indicate various accounting
quantities:
$$
A_{i,c;i',c'}(t) = \sum\{a_j\colon i_j = i, c_j = c, i'_j = i', c'_j = c'\}
$$
is the _activity_: the total amount of instrument $i$ counterparty
$c$ has transacted for
instrument $i'$ with counterparty $c'$ at time $t$. Usually this sum has
only one term.
$$
B_{i,c;i',c'}(t) = \sum_{s\le t} A_{i,c;i',c'}(s)
$$
is the _balance_ the buyer has in these type of transactions.

Let $A_{i,c}(t) = \sum_{i',c'} A_{i,c;i',c'}(t)$ and similarly for
$B_{i,c}(t)$.  The later is the balance of instrument $i$ that
counterparty $c$ has with all instruments traded to all counterparties.

Likewise, let $A'(t)$ and $B'(t)$ represent the seller's activity and
balance by replacing $a$ with $a'$ in the sums.  In this case $B'(t)$
is called _inventory_.

The classical theory of mathematical finance usually does not make
a distinction between counterparties and assumes $i'$ is the buyer's
native currency.

## Models

> _In this sense, rational mechanics will be the science, expressed in exact propositions and demonstrations, of the motions that result from any forces whatever and of the forces that are required for any motions whatever._ 

> _But the errors are not in the art, but in the artificers._

> \ \ \ \ \ -Sir Issac Newton, _Principia_

We use mathematics to rigorously define financial terms.  Math is too
simple to capture the messy complexity of the real world, assumptions must
be made and kept in mind when interpreting the mathematical consequences,
but the ideal is to write down mathematical representations and then
use the machinery to derive useful results.

In the Newtonian spirit, we lay a mathematical foundation for describing
salient features of the financial world. The lack of arbitrage
implies restrictions on the dynamics of prices and cash flows of market
instruments. This can be used to create synthetic instruments by dynamic
trading of market instruments.

Classical mathematical finance fails to account for how well these
derivative instruments can be replicated and ignores important real-world
considerations. There are fees, collateral, and tax implications, among
other things, that must be accounted for in any complete theory.

<!--|
[Rational mechanics](https://people.maths.ox.ac.uk/ball/Miscelleaneous Articles/truesdell.pdf)
|-->

Non-mathematicians tend to be surprised that all possible outcomes are
modeled by a set.  This also surprises some mathematicians too until
they realize the set can be quite large.

It usually contains all possible future price trajectories of the
instruments being modeled. It can also contain historical facts: the text
of every book, newspaper, journal article, post-it note, and bathroom
graffiti ever written in the history of the world. Big Data is making
this not as ridiculous as it might seem at first blush.

Math allows you to think much larger than what can be practically
implemented on a computer.

## Mathematical Preliminaries

Let $\Omega$ be a set and $B(\Omega)$ be the set of all _bounded functions_
on this set. Its _vector space dual_ is $B(\Omega)^* = ba(\Omega)$, the
space of _finitely additive measures_ on $\Omega$.
We write the dual space pairing as any of $\langle X,\Pi\rangle =
\int_\Omega X\,d\Pi = \Pi(X)$ for $X\in B(\Omega)$ and $\Pi\in
ba(\Omega)$. The last is the usual function call notation since $\Pi$
is simply a linear function(al) from $B(\Omega)$ to $\mathbf{R}$. If
$\Pi$ is positive with mass 1, this is just the expected value of $X$
under the probability measure $\Pi$.

Multiplying a bounded function, $X$, by a measure, $\Pi$, gives a new
measure defined by $\langle Y,X\Pi\rangle = \langle YX,\Pi\rangle$
for any function $Y\in B(\Omega)$.

An _algebra_ of sets, $\mathscr{A}$, on $\Omega$ is a subset of the
power set of $\Omega$ that is closed under complements and unions. By
De Morgan's laws, it is also closed under intersection. We assume the
empty set, hence $\Omega$, belong to $\mathscr{A}$.

Subsets of $\Omega$ are called _events_. If you want to talk about
something not happening, or either of two events happening, then algebras
are the natural mathematical object for that.

If the cardinality of $\mathscr{A}$ is finite the _atoms_ form
a _partition_ of $\Omega$. A partition is the mathematical way
to describe partial information. Complete information is knowing
$\omega\in\Omega$. Partial information is knowing which atom in the
partition $\omega$ belongs to.

A function in $B(\Omega)$ is $\mathscr{A}$-_measurable_ if it is
constant on atoms of $\mathscr{A}$, i.e., it depends only on the partial
information available. Let $B(\Omega,\mathscr{A})$ be the bounded
$\mathscr{A}$-measurable functions on $\Omega$. Its dual is
$B(\Omega,\mathscr{A})^* = ba(\Omega,\mathscr{A})$, the space of
finitely additive measures on $\mathscr{A}$.

We can define a linear operator $E\colon ba(\Omega)\to
ba(\Omega,\mathscr{A})$ by $\Pi\mapsto \Pi|_{\mathscr{A}}$, the
restriction of $\Pi$ to the algebra $\mathscr{A}$. This is closely
related to _conditional expectation_ but we have no need for that
concept.

In fact, there is no need for the highly technical theory of countably
additive measures, probability theory, martingales, or Ito processes.
The above suffices for a complete theory of mathematical finance.

## Trading times

Let $T\subseteq\mathbf{R}$ be the set of times at which trades can
occur. The classical theory assumes $T = [0,\infty)$.  At each time $t\in
T$ we have an algebra $\mathscr{A}_t$ that represents the information
available at time $t$. Since information increase over time, we assume
$\mathscr{A}_t\subseteq\mathscr{A}_u$ whenever $t < u$.

## Prices
A model of _prices_ is a bounded function
$$
X\colon T\times (A\times I\times C)\times (I\times C)\times\Omega
\to\mathbf{R}^m
$$
such that $\omega\mapsto X(t,\dots,\omega)$ is $\mathscr{A}_t$-measurable,
i.e., $X$ is _adapted_. The value of $X$ at time $t$ depends only on
the information available at time $t$.
The transaction $\chi=(t;a,i,c;aX(t),i',c')$
is available to the buyer at time $t$, where $X(t)$ is a lazy way of
writing $X(t;a,i,c;i',c',\omega)$.
Making price depend on the amount allows for the incorporation of bid/ask
spread. It also allows for the fact that different counterparties can
have different prices for the same instruments.

## Cash Flows
Ownership of an instrument entails cash flows. Stocks pay dividends,
bonds pay coupons, futures have daily margin adjustments.

A model also specifies _cash flows_
$$
C\colon T\times (I\times C)\times (I\times C)\times\Omega\to\mathbf{R}^m
$$
that are bounded and adapted.
Buyers receive cash flows proportional to their positions.
Note that cash flows can depend on counterparties. Interest rate
swaps usually have contractually obligated collateral postings.
Something current mathematical finance theory treats ad hoc.

### Convention

If we assume perfect liquidity, counterparties don't matter, and
that the buyer always trades home currency, then we can write the above
as
$$
X,C\colon T\times\Omega\to\mathrm{R}^I
$$
where we curry ($A\times B\to C\cong A\to C^B$) the instrument argument.
This is the usual formulation of models as vector-valued stochastic
processes.

We use the notation $X_t(\omega) = X(t,\omega)$ when emphasizing
time dependence.

## Trades

The buyer can specify a bounded, adapted function
$$
\Gamma\colon T\times\Omega\to\mathrm{R}^I.
$$
We assume this function is 0 for all but a finite number
of _trading times_ $t\in T$ because in the real world it is.
Trades accumulate into a _position_
$\Delta_t = \sum_{s\le t}\Gamma_s$.

Let $t_0 < t_1 < \cdots t_n$ be the times at which $\Gamma$ is
non-zero and $\Gamma_j = \Gamma_{t_j}$.

## Account

The values that show up in the buyer's trading account/blotter at time
$t_j$ are $A_j = \Delta_{j-1}\cdot C_j - \Gamma_j\cdot X_j$.  The buyer
receives cash flows from the existing position and has to pay for the
trades executed based on market prices.  Note that cash flows for trades
at $t_j$ do not accrue to the account.

The _value_ of a position at time $t$ is $V_t = \Delta_t\cdot X_t$.
This is the _marked-to-market_ "price" assuming the position could be
completely unwound at the quoted market prices. Another unrealistic
assumption.

## Arbitrage

A model is _arbitrage free_ if there do not exist trades $(\Gamma_j)$
with $\sum_j\Gamma_j = 0$, $A_0 > 0$, and $A_j\ge0$ for $j>0$.
In words: there is no _closed-out_ trading strategy that makes
money up front and never loses money thereafter.

Assuming the model contains a bond, it is easy to make $A_j>0$ for
all $j$. The trick is finding a trading strategy that closes out.

## FTAP
The _Fundamental Theorem of Asset Pricing_ states that a model
is arbitrage free if and only if there exist _deflators_,
$(\Pi_t)_{t\in T}$, that are positive scalar measures
such that
$$
X_j\Pi_j = (C_{j+1} + X_{j+1})\Pi_{j+1}|_{\mathscr{A}_j}\tag{1}
$$
An immediate consequence is
$$
V_j\Pi_j = (A_{j+1} + V_{j+1})\Pi_{j+1}|_{\mathscr{A}_j}\tag{2}
$$
since
$$
\begin{align*}
V_j\Pi_j &= \Delta_j\cdot X_j\Pi_j\\
&= \Delta_j\cdot (C_{j+1} + X_{j+1})\Pi_{j+1}|_{\mathscr{A}_j}\\
&= (A_{j+1} + \Gamma_{j+1}\cdot X_{j+1} + \Delta_j\cdot X_{j+1})\Pi_{j+1}|_{\mathscr{A}_j}\\
&= (A_{j+1} + \Delta_{j+1}\cdot X_{j+1})\Pi_{j+1}|_{\mathscr{A}_j}\\
&= (A_{j+1} + V_{j+1})\Pi_{j+1}|_{\mathscr{A}_j}\\
\end{align*}
$$
Equation $(2)$ is the skeleton key to derivative securities.
Note how the value $V$ plays the roll of price $X$ and
the account $A$ corresponds to cash flows $C$ of market instruments.

A _derivative security_ is a contract between two counterparties for the
exchange of cash flows. In terms of the model, the contract specifies the
$(A_j)$. The job of a quant is to find trades $(\Gamma_j)$ to replicate
these. The pernicious influence of using Brownian motion to model prices
and the fiction of continuous time trading have led to myopia when it
comes to measuring risk. Markets are never complete. The job of a quant
should also include providing quantitative information on how well a
hedge can be expected to perform.

One direction of the FTAP is easy. By induction, equation $(2)$ implies
$$
V_j\Pi_j = (\sum_{j<i\le k} A_i\Pi_i + V_k\Pi_k)|_{\mathscr{A_j}}
$$
If we assume $\mathscr{A}_0$ is $\{\emptyset,\Omega\}$ then we can
assume $\Pi_0(\Omega) = 1$. In this case $V_0 = -A_0 = \sum_{i>0}
A_i\Pi_i(\Omega)$ for a closed-out strategy so $A_j\ge 0$ for $j > 0$
implies $A_0\le 0$, hence the model is arbitrage free.

The other direction is difficult. Ross generalized the
Black-Scholes/Merton model from a bond, stock, and option to an arbitrary
collection of instruments and made the brilliant observation that the
Hanh-Banach theorem could be used to prove this result.  Filling in the
mathematical gaps of his proof led to a small cottage industry as outlined
[here](http://kalx.net/ftapd.pdf).

The good news is that there is no need to prove the difficult direction.
It is easy to simply write down deflators, there is no need for the
Hahn-Banach theorem to prove they exist. As far as I know, nobody has
ever used the Hahn-Banach theorem to do that. It does come in handy for
finding arbitrages when they exist, as illustrated in the above link.

### Pricing is Hedging

Given a derivative, i.e., a contract specifying cash flows $(A_j)$,
if we can find a closed-out trading strategy $(\Gamma_j)$ that
replicates the cash flows, the value of the security is simply
the cost of setting up the initial hedge.
Somewhat miraculously, we do not need to know
what the trading strategy is to compute this
\[
V_0 = \sum_{j>0} A_j\Pi_j(\Omega)
\]
Rather miraculous is that we can use this to compute the initial hedge
$\Gamma_0 = \partial V_0/\partial X_0$ since $V_0 = \Gamma_0\cdot X_0$. In
fact, we can compute the entire hedge using $\Delta_j = \partial
V_j/\partial X_j$ and $V_j\Pi_j = sum{i>j}A_i\Pi_i|_{\mathscr{A}_j}$.
Taking differences yields the $\Gamma_j$.

Now you understand the choice of notation for the position and trades.

This miracle seems to have blinded everyone to the reality that no hedge
is perfect. Our job is not over, it is just starting.

### Risk

In any realistic model, it is never the case that the derivative cash
flows are perfectly hedged. We can however come up with a rough measure
of how good the hedge is using the tools at hand. Given the
positions computed by this method,
$\Pi(\Delta_j\cdot C_{j+1} - \Gamma_{j+1}\cdot X_{j+1} - A_{j+1})^2$



## Examples

[Cost of carry](coc.html)

[Put-Call parity](pcp.html)

[Canonical price deflator](cpd.html)

[Stock with dividends](swd.html)

## CVA

Credit Value Adjustment accounts for the risk of a counterparty
defaulting. 

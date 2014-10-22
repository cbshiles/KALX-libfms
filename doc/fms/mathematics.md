# Mathematics

Contrary to popular belief, stochastic processes are not needed
for financial modeling. All you need to know about are algebras and
measures. Positive measures with mass one show up, but they
are not the probability of anything.

## Outcomes

The set of everything that can happen, all possible _outcomes_, is
denoted by $\Omega$.  It is usually a collection of possible instrument
price trajectories but it could also include current and future news,
social media data, etc. No, really. It can be the set of EVERYTHING that
can happen. It may not be practical to implement, but math allows us to
think big.

## Algebras

A subset of outcomes is an _event_. The outcome of rolling a die is
represented by a set: $\{1,2,3,4,5,6\}$. The event of rolling an even
number is the subset $\{2,4,6\}$.  An _algebra_ is a collection of sets
closed under complement and union. By
[De Morgan's laws](http://en.wikipedia.org/wiki/De_Morgans_laws),
algebras are also closed under intersection. These are natural axioms when
talking about an event not happening, or either of two events occurring.

A [_partition_](http://en.wikipedia.org/wiki/Partition_of_a_set)
is a collection of events, $(A_j)_j$,
such that $\Omega = \cup_j A_j$ where $A_i\cap A_j =
\emptyset$ if $i\not= j$. For an algebra, $\mathcal{F}$,
$A\in\mathcal{F}$ is an _atom_ if $B\subseteq A$,
$B\in\mathcal{F}$ imply $B=A$ or $B=\emptyset$.
If an algebra $\mathcal{F}$ is finite the atoms form a partition.
(Exercise: prove this.)

The algebra $\{\emptyset,\Omega\}$ represents no
information.
The _power set_ $\mathcal{P}(\Omega) =
\{A:A\subseteq\Omega\}$ represents complete information.
Knowing which atom $\omega\in\Omega$ belongs to represents
_partial information_.
E.g., the partition $\{\{1,3,5\},\{2,4,6\}\}$ represents knowing whether
a die roll is even or odd.

## Measures

A _(finitely additive) measure_ is a function
$\Pi\colon\mathcal{F}\to\mathbb{R}$ such that
$\Pi(A\cup B) = \Pi(A) + \Pi(B)$ if $A\cap B = \emptyset$.
The set of finitely additive measures is denoted $ba(\Omega,\mathcal{F})$.

A function $X\colon\Omega\to\mathbb{R}$ is _measurable_ if
$\{\omega\in\Omega: X(\omega) \le x\}\in\mathcal{F}$ for all
$x\in\mathbb{R}$. If $\mathcal{F}$ is finite, measurable is the same as
being constant on atoms. The set of bounded measurable functions
is denoted $B(\Omega, \mathcal{F})$.

Finitely additive measures are the
[vector space dual](http://en.wikipedia.org/wiki/Dual_space)
of bounded measurable functions.
The dual pairing is $\langle X,\Pi\rangle = \int_\Omega X\,d\Pi$.
If $\mathcal{F}$ is finite the integral is just the sum over
atoms.

For $X\in B(\Omega,\mathcal{F})$ and $\Pi\in ba(\Omega,\mathcal{F})$
define $X\Pi\in ba(\Omega,\mathcal{F})$ by $\langle Y,X\Pi\rangle =
\langle YX,\Pi\rangle$ for all $Y\in B(\Omega,\mathcal{F})$.

Let $\Pi|_\mathcal{G}$ be the measure $\Pi$ _restricted_ to
the algebra $\mathcal{G}$.
If $\Pi$ is a probability measure, the _conditional expectation_,
$E[X|\mathcal{G}]$, is defined by $\langle E[X|\mathcal{G}],\Pi\rangle
= \langle X,\Pi|_\mathcal{G}\rangle$, i.e, the
adjoint of conditional expectation is restriction.

If you know something about the classical theory, you can forget about
using conditional expectation. Using the much simpler (but equivalent)
notion of restriction of measure is all you need.

## Filtrations

A _filtration_ is an increasing collection of algebras
$(\mathcal{F}_t)_{t\in T}$, i.e., $\mathcal{F}_t\subseteq\mathcal{F}_u$
if $t < u$.  A filtration represents information available over time.

Consider flipping a coin: $T$,$H$,$H$,$\dots$ can be modeled by
the base 2 representation of $\omega\in[0,1)$, $\omega = .011\dots_2$,
where $T$ is 0 and $H$ is 1.
Any sequence of flips, $\omega_1$, $\omega_2$, $\omega_3, \dots$
can be encoded by a single $\omega\in[0,1)$:
$\omega = \sum_{j > 0} \omega_j 2^{-j}$, $\omega_j \in\{0,1\}$. 
The algebra $\mathcal{F}_j = \{[\frac{i}{2^j},\frac{i+1}{2^j}) : 0\le
i < 2^j\}$ represents knowing the first $j$ digits

## The Fundamental Theorem of Asset Pricing

Given a filtration $(\mathcal{F}_j)$ and adapted vector valued functions
$X_j,C_j\colon \Omega\to\mathbf{R}^m$, 
there is no arbitrage if and only if there exist positive scalar measures
$\Pi_j\in ba(\Omega,\mathcal{F}_j)$ with
$$
X_j\Pi_j = (C_{j+1} + X_{j+1})\Pi_{j+1}|_{\mathcal{F}_j}
$$

By induction
$$
X_j\Pi_j = (\sum_{j < i\le k}C_i\Pi_i + X_k\Pi_k)|_{\mathcal{F}_j} \label{ftap}
$$

We can multiply the $(\Pi_j)$ by any positive $\mathcal{F}_0$-measurable
function so replacing
$\Pi_j$ by $\Pi_j \Pi_0^{-1}$ allows us to assume $\Pi_0 = 1$.

The deflators are unique if the market is complete
(the so called Second fundamental theorem) but this is never true for
realistic models. We will see later that there is a canonical way
of choosing deflators for most models. In the case of non-stochastic
interest rates $\Pi_j = D(j)P$ where $D(j)$ is the discount to time $t_j$ and
$P$ is some probability measure.

### FTAP (easy direction)

Suppose there exist price deflators with
$X_j\Pi_j = (C_{j+1} + X_{j+1})\Pi_{j+1}|_{\mathcal{F}_j}$.
Using $A_{j+1} = \Delta_{j}\cdot C_{j+1} - \Gamma_{j+1}\cdot X_{j+1}$
$$
\begin{align*}
\Delta_j\cdot X_j\Pi_j
&= \underline{\Delta_j}\cdot(\underline{C_{j+1}} +
    X_{j+1})\Pi_{j+1}|_{\mathcal{F}_j}\\
&= (\mathbf{A_{j+1} + \underline{\Gamma_{j+1}}\cdot X_{j+1}} +
    \underline{\Delta_j}\cdot X_{j+1})\Pi_{j+1}|_{\mathcal{F}_j}\\
&= (A_{j+1} + \mathbf{\Delta_{j+1}}\cdot X_{j+1})\Pi_{j+1}|_{\mathcal{F}_j}\\
\end{align*}
$$
By induction $\Delta_j\cdot X_j\Pi_j = (\sum_{j < i\le k} A_i\Pi_i +
\Delta_k\cdot X_k\Pi_k)|_{\mathcal{F}_j}$.
Note if $\sum_j\Gamma_j = 0$
and $A_i\ge0$, $i>0$ then $A_0\le0$ since
$-A_0 = \Delta_0\cdot X_0 = \sum_{j>0} A_j\Pi_j|_{\mathcal{F}_0}\ge0$.

## The Money Shot of Derivatives
Note the similarity between
$$
\underline{X_j}\Pi_j = (\mathbf{C_{j+1}}
+ \underline{X_{j+1}})\Pi_{j+1}|_{\mathcal{F}_j}
$$
and
$$
\underline{\Delta_j\cdot X_j}\Pi_j = (\mathbf{A_{j+1}}
+ \underline{\Delta_{j+1}\cdot X_{j+1}})\Pi_{j+1}
|_{\mathcal{F}_j}
$$
This is the foundation of a unified approach to derivative securities.
A derivative is an exchange of cash flows. _If_ we can find trades
$(\Gamma_j)$ such that the account $(A_j)$ replicates those
cash flows then the value $\Delta_j\cdot X_j$ plays the analog of
the price of a market instrument. Dynamically trading market instruments
allows us to synthetically create (approximations to) new market-like
instruments.

Reread the above paragraph.

The '_If_' is a big if. This can never be achieved in practice, but
the classical theory of mathematical finance tends to ignore this reality. 
It is fun to ignore because then the theory tells us how to find the
trades that 'replicate' the cash flows.

Since $-A_0 = \Gamma_0\cdot X_0 = \sum_{j>0} A_j\Pi_j|_{\mathcal{F}_0}$
we can find the initial trade by taking a derivative with respect to
price at time $t_0$: $\Gamma_0 = (d/dX_0)\sum_{j>0} A_j\Pi_j(\Omega)$.
Note $\Gamma_0 = \Delta_0$ and this is our initial delta hedge in the
classical theory.

In fact, $\Delta_j = (d/dX_j)\sum_{k>j} A_k \Pi_k/\Pi_j|_{\mathcal{F}_j}$
can be given rigorous mathematical meaning to allow us to calculate
all the delta's over the life of the trade.

### FTAP (hard direction)

Stephen Ross [@Ros1978] gave the first proof of the FTAP using
the Hahn-Banach theorem. His primary contribution was to extend the
Black-Scholes/Merton result from a bond, stock, and option to an
arbitrary collection of instruments and show the FTAP is essentially
a geometric fact. It has nothing to to with the probability of
anything. Positive measures with mass one just happen to make a showing.

Fischer Black and Myron Scholes gave a mathematically incorrect derivation
of their eponymous partial differential equation that was immediately
corrected by Robert Merton who understood the Ito calculus better than
they did.

Unfortunately, Brownian motion is just a binomial model in
continuous time wolf's clothing.
Using that as a model of stock prices leads to mathematical nonsense.
Among other defects, it exhibits infinite oscillatory behavior. The
price of a barrier option that knocks in (or out) the 1 millionth
time it hits a barrier has the same value, as a one touch barrier option.

Ross's proof neglected to establish an essential condition of an interior
point required for the application of the Hahn-Banach theorem and this led
to a sequence of papers addressing the matter. The current state of
the art is [@DelSch1994] that contains a 61 page proof of the current
formulation comprehensible only to a handful of experts.

__But who cares__?
No arbitrage implies deflators exist, but we can find plenty without
the help of Messrs. Hahn and Banach.

Using the fact that $e^{-\sigma^2t/2 + \sigma B_t}$ is a martingale, where
$(B_t)$ is [Brownian motion](http://en.wikipedia.org/wiki/Brownian_motion),
it follows $X_t = (e^{rt}, se^{(r - \sigma^2/2)t + \sigma B_t})$, $\Pi_t =
e^{-rt}P$, where $P$ is Wiener measure, is an arbitrage free model.  This is
the Black-Scholes/Merton model for a bond and non-dividend paying stock,
only without the unnecessary detour through assuming a 'real-world' drift,
self-financing conditions, change of measure,
and the assorted machinery of the Ito calculus.

Finding arbitrage free models is not difficult.  Finding models that
reflect market dynamics with parameters that can be fit to market
data is the holy grail.

## Examples

Let's define some models and start putting them to use.

### Put-Call Parity

Let $T = \{0,1\}$, $\Omega = [0,\infty)$, $\mathcal{F}_0
= \{\Omega\}$, $\mathcal{F}_1 = \mathcal{P}(\Omega)$,
$X_0 = (1,s,c,p)$, $X_1(\omega) = (R,\omega,0,0)$, and
$C_1(\omega) = (0,0,\max\{\omega - k,0\},\max\{k -
\omega,0\})$.

This is a one period model of a bond with realized return $R$,
a stock that can have any non-negative value,
and a call and put both struck at $k$. Note the call and put
have zero price at expiration. They are derivatives hence
specified by their cash flows.

No arbitrage implies there is a deflator, $\Pi$, such that
$$
(1,s,c,p)
= \langle (R,\omega,\max\{\omega - k,0\},\max\{k - \omega,0\}), \Pi\rangle.
$$
Taking $\Gamma_0 = (k/R, -1, 1, -1)$ and computing $\Gamma_0\cdot X_0$ gives
$k/R - s + c - p
= \langle k - \omega + \max\{\omega - k,0\} - \max\{k - \omega,0\}),\Pi\rangle
= 0$.
_Put-call parity_ is $c - p = s - k/R$.  We don't really need a model
for this, but it illustrates how to use the mathematical framework.

Note that $\Pi$ is not unique but no matter which $\Pi$ we use we
come to the same conclusion. The first thing a trader will check with
any new model is put-call parity. If that does not hold, the model
must be wrong.

### Cost of Carry

Let $T = \{0,1\}$, $\Omega = [0,\infty)$, $\mathcal{F}_0
= \{\Omega\}$, $\mathcal{F}_1 = \mathcal{P}(\Omega)$,
$X_0 = (1,s,0)$, $X_1(\omega) = (R,\omega,0)$, and
$C_1(\omega) = (0, 0, \omega - f)$

This models a bond with realized return $R$, a stock that can have
any non-negative value, and an at-the-money forward.
Forwards have price zero at expiration
No arbitrage implies $(1,s,0) = \langle
(R,\omega,\omega-f),\Pi\rangle$.
Taking $\Gamma_0 = (f/R, -1, 1)$ and computing $\Gamma_0\cdot X_0$ gives
$f/R - s = \langle f - \omega + \omega - f,\Pi\rangle = 0$.
The _cost-of-carry_ is $f = Rs$.
We also don't really need a model for this.

### One Period Binomial Model

Let $T = \{0,1\}$, $\Omega = \{S^-,S^+\}$, $X_0 = (1,s)$,
$X_1(\omega) = (R,\omega)$, and $C_j = 0$.
This models a bond with realized return $R$
and a stock that goes from $s$ to either $S^-$ or $S^+$.
We can find $\pi^-$ and $\pi^+$ such that
$(1,s) = (R,S^-)\pi^- + (R,S^+)\pi^+$:
$\pi^- = (S^+/R - s)/(S^+ - S^-)$,
$\pi^+ = (s - S^-/R)/(S^+ - S^-)$.
Define the measure $\Pi$ on $\Omega$ by
$\Pi(S^-) = \pi^-$ and $\Pi(S^+) = \pi^+$.

Suppose a derivative pays $V(\omega)$ at time 1.
There exists $\Gamma_0 = (m,n)$ such that $\Gamma_0\cdot X_1 = V$
on $\Omega$.
Solving $mR + nS^- = V(S_-)$, $mR + nS^+ = V(S_+)$ for $m,n$
yields $n = (V(S_+)-V(S_-))/(S_+-S_-)$, and
$$
v = \Gamma_0\cdot X_0 = m + ns =
    \frac{1}{R}
    	\left(\frac{S_+-Rs}{S_+-S_-}V(S_-)
	    	+\frac{Rs - S_-}{S_+-S_-}V(S_+)
		\right)
$$

The deflator is unique in the one period binomial model, and this
makes it a poor model. Since there are only two possible outcomes
every payoff is (equivalent to) a linear payoff. And that is just wrong.

Note that the stock hedge $n = \partial v/\partial s$ is the
derivative of option value with respect to underlying.

#### Alternate Parameterization

The above model is not the usual way of paramterizing the OPB model
as taught in MBA programs.

Let $\Omega = \{d,u\}$, $X_0 = (1,s)$, and $X_1(\omega) = (R,s\omega)$.
This models a bond with realized return $R$
and a stock that goes from $s$ to either $sd$ or $su$.
There exists $\Gamma_0 = (m,n)$ such that $\Gamma_0\cdot X_1 = V$.
Solving $mR + nsd = V(sd)$, $mR + nsu = V(su)$ for $m,n$
gives $n = (V(su)-V(sd))/(su - sd)$, and
$$
v = \Gamma_0\cdot X_0 = m + ns = \frac{1}{R}\left(\frac{u-R}{u-d}V(sd) + \frac{R-d}{u-d}V(su)\right)
$$
Note that the stock hedge $n \not= dv/ds$ in general.
E.g., for a butterfly spread with support inside the interval $(sd,su)$
we have $dv/ds = 0$ since $V'(sd) = V'(su) = 0$.

Parameterization is important.

## Delta Hedging

Suppose an option pays $V(\omega)$ in a general one period model.
For a one period model, $X_1 = 0$.
If we can find $\Gamma_0$ such
that $\Gamma_0\cdot C_1 = V$ then using the existence of
a deflator, $\Pi_1 = \Pi$, we have
$v = \Gamma_0\cdot X_0 = \langle \Gamma_0\cdot C_1,\Pi\rangle$
is the value of the option. We can find the _delta hedge_ by
$\Gamma_0 = dv/dX_0$.

If the market is not complete we aren't guaranteed that we can find
a hedge that replicates the option payoff. If we fix a deflator then
we can minimize the mean square error:
$$
	\min_{\Gamma_0} \langle (\Gamma_0\cdot C_1 - V)^2,\Pi\rangle.
$$
Of course this depends on the deflator but, as we will see, there are
usually canonical deflators available for a model. The solution to
this problem is $\Gamma_0 = \langle C_1C_1^T,\Pi\rangle^{-1}
\langle VC_1,\Pi\rangle$.

We can use this minimum as a measure of the quality of the hedge.

<!--|
Derivatives
-----------

-   Prices and cash flows satisfy $\color{blue}X_j\Pi_j =
    \sum_{j < i\le k}\color{red}C_i\Pi_i +
    \color{blue}X_k\Pi_k|_{\mathcal{F}_j}$
-   For any trades $(\Gamma_j)$, $\color{blue}\Delta_j\cdot
    \color{blue}X_j\Pi_j = \sum_{j < i\le k}
    \color{red}A_i\Pi_i + \color{blue}\Delta_k\cdot
    \color{blue}X_k\Pi_k|_{\mathcal{F}_j}$
-   The position determines the value $\color{blue}\Delta_j\cdot
    \color{blue}X_j$...
-   ...and the account determines the cash flows $\color{red}A_j$
    for a derivative instrument
-   This is how to create synthetic instruments

Delta Hedging
-------------

-   Assuming $\Pi_0 = 1$ and $\Delta_j$ is eventually zero
    $$ \Delta_0\cdot X_0 = \sum_{0 <
    i}A_i\Pi_i|_{\mathcal{F}_0} $$
-   "The value of a derivative is the expected value of discounted cash
    flows"
-   _If_ a hedge exists the initial hedge is given by $$\Gamma_0 =
    \Delta_0 = \frac{\partial(\Delta_0\cdot X_0)}{\partial
    X_0} = \frac{\partial}{\partial X_0}E[\sum_{0 <
    i}A_i\Pi_i]$$
-   For a one period model with $C_j = 0$ we could solve
    $\min_{\Gamma_0}||\Gamma_0\cdot X_1 - A_1||^2$ and get a
    measure of the hedging error

A Multiperiod Model
-------------------

-   $\Omega = [0,\infty)^n$
-   $X_0 = (1,s,0)$, $X_j = (R_j, \omega_j,
    \phi_j(\omega_j))$, $X_n = (R_n, \omega_n, 0)$
-   $C_j = 0$, $0\le j < n$, $C_n = (0, 0, \omega_n -
    f)$
-   Multiperiod stock and forward contract
-   The $\phi_j$ are determined by the no arbitrage condition
-   $\langle R_j,\Pi_j\rangle = \langle R_n, \Pi_n\rangle$
-   $\langle \omega_j, \Pi_j\rangle = \langle \omega_n,
    \Pi_n\rangle$
-   $\langle \phi_j(\omega_j), \Pi_j\rangle = \langle
    \omega_n - f, \Pi_n\rangle = \langle \omega_j -
    fR_n/R_j,\Pi_j\rangle$,
-   so $\phi_j(\omega_j) = \omega_j - fR_n/R_j$

Fixed Dividends
---------------

-   $\Omega = [0,\infty)^n$
-   $X_0 = (1,s,0)$, $X_j = (R_j, \omega_j,
    \phi_j(\omega_j))$, $X_n = (R_n, \omega_n, 0)$
-   $C_0 = 0$, $C_j = (0,d_j,0)$, $0 < j < n$,
    $C_n = (0, d_n, \omega_n - f)$
-   Multiperiod stock paying dividends and forward contract
-   The $\phi_j$ are determined by the no arbitrage condition
-   $\langle R_j,\Pi_j\rangle = \langle R_n, \Pi_n\rangle$
-   $\langle \omega_j, \Pi_j\rangle = \sum_{j < k <
    n}\langle d_k, \Pi_k\rangle + \langle \omega_n + d_n,
    \Pi_n\rangle$
-   $\langle \phi_j(\omega_j), \Pi_j\rangle = \langle
    \omega_n - f, \Pi_n\rangle = \langle \omega_j -
    \sum_{j < k\le n}d_kR_n/R_k - fR_n/R_j,\Pi_j\rangle$,
-   so $\phi_j(\omega_j) = \omega_j - R_N(f/R_j +
    \sum_{j < k\le n}d_k/R_k)$

General Models
--------------

-   Specify a probability measure $P$ on $\Omega$
-   Choose $\pi_j\in B(\Omega,\mathcal{F}_j)$ and let
    $\Pi_j = \pi_jP|_{\mathcal{F}_j}$
-   Arbitrage free if $X_j\Pi_j = (C_{j+1} +
    X_{j+1})\Pi_{j+1}|_{\mathcal{F}_j}$
-   Customary to assume $\mathcal{F}_0 = \{\emptyset,\Omega\}$
    and $\pi_0 = 1$
-   The cash flows are usually specified by the market
-   The difficult part is specifying the prices and deflators
|-->

## Canonical Price Deflator

If $X_t$ is deterministic and $C_t = 0$ then
$\Pi_t = X(t)^{-1}P|_{\mathcal{F}_t}$, for any probability
measure $P$, is a deflator.

Assume for each time there is an instrument with $X_j = 1$,
$C_{j+1} = R_j$, and $X_k = 0$ for $k > j$.
$R_j$ is the _short realized return_ over the interval $t_j$ to
$t_{j+1}$.
Define _canonical price deflators_
$$
	\Pi_j = (R_0\cdots R_{j-1})^{-1}P|_{\mathcal{F}_j}
$$
It is easy to see $\Pi_j = R_j\Pi_{j+1}|_{\mathcal{F}_j}$.
Note $\Pi_j$ is $\mathcal{F}_{j-1}$ measurable (aka _predictable_).
There are many possible deflators, but this is canonical given
a short rate process.

One interesting fact about the fixed income world is that the
price deflator determines the price of every instrument.

### Zero Coupon Bonds

A zero coupon bond maturing at $u$ has $X_0 = D(u)$ and
$C_u = 1$.
$D(u)\Pi_0 = \Pi_u|_{\mathcal{F}_0}$ so $D(u) = \Pi_u(\Omega)$.
Let $D_t(u)$ be the price at time $t$, then
$D_t(u)\Pi_t = \Pi_u|_{\mathcal{F}_t}$ so
$$
D_t(u) = \Pi_u/\Pi_t|_{\mathcal{F}_t}
= \Pi_{t\le s < u}R_s^{-1}P|_{\mathcal{F}_t}
$$

### Forward Rate Agreements

FRA's have price $X_0 = 0$ and two cash flows
$C_u = -1$ and $C_v = 1 + F(u,v)\delta_{u,v}$, where
$\delta_{u,v}$ is the _day count fraction_ that is
approximately $v - u$ in years depending on the
[day count convention](http://en.wikipedia.org/wiki/Day_count_convention)
Since $0 = -D(u) + (1 + F(u,v)\delta_{u,v})D(v)$ we have
$$
    F(u,v) = \frac{1}{\delta_{u,v}}\left(\frac{D(u)}{D(v)} - 1\right)
    = \frac{1}{\delta_{u,v}}\left(\frac{\Pi_u}{\Pi_v}\bigr|_{\mathcal{F}_0}
    - 1\right)
$$
Let $F_t(u,v)$ be the forward at time $t$ over $[u,v]$
Since $X_t = 0 = -D_t(u) + (1 + F_t(u,v)\delta_{u,v})D_t(v)$
we have
$$
F_t(u,v) = \frac{1}{\delta_{u,v}}\left(\frac{D_t(u)}{D_t(v)} - 1\right)
    = \frac{1}{\delta_{u,v}}\left(\frac{\Pi_u}{\Pi_v}\bigr|_{\mathcal{F}_t}
    - 1\right)
$$

### Forward Rate Agreements w/o Notional

FRA's can also be specified as a single cash flow
having price $X_0 = 0$ and forward $f(u,v)$ with
$C_v = (F_u(u,v) - f(u,v))\delta_{u,v}$, i.e, 
the prevailing forward rate at start of period versus fixed.
Note $0 = (F_u(u,v) - f(u,v))\delta_{u,v}\Pi_v|_{\mathcal{F}_0}
= (\Pi_u - \Pi_v - f(u,v)\delta_{u,v})|_{\mathcal{F}_0}$
and $F_0(u,v)\delta_{u,v}\Pi_v|_{\mathcal{F}_0}
= (\Pi_u - \Pi_v)|_{\mathcal{F}_0}$
so $f(u,v) = F_0(u,v)$.

However, These two contracts have very different risk profiles
In the first contract the counterparty holds a large notional
amount and if they default a significant loss will occur.
In the second contract no money is exchanged up front. If the
counterparty defaults and the contract is nullified there will
be no material loss. But that won't stop lawyers from trying
to recover something if the market has gone in favor of either
of the counterparties in the meantime.

### Swaps
A _fixed versus floating rate swap_ is defined by specifying
a tenor (the lifetime of the trade) and the _fixed_ and _floating
rate legs_. The fixed leg pays a fixed _coupon_ at some
_frequency_ (monthly, quarterly, semiannually, etc) calculated
with a given daycount basis. The floating leg pay the then
current floating rates at a possibly different frequency.
The tenor determines the _termination date_ of the swap.

Using the notation above, if the calculation dates are $(u_j)$ then
the fixed leg pays $C_j = c\delta_{u_{j-1},u_j}$ at $u_j$ and
the float leg receives $F_{u_{j-1}}(u_{j-1},u_j)\delta_{u_{j-1},u_j}$ at $u_j$.
In practice, each leg could have different calculation dates and
daycount basis.

A fundamental fact about floating rate legs is that they can be modeled
by a portfolio of two zero coupon bonds.
$$
\sum_{j=1}^n F_{u_{j-1}}(u_{j-1},u_j)\delta_{u_{j-1},u_j}\Pi_{u_j}|_{\mathcal{F}_0}
= 1 - \Pi_n|_{\mathcal{F}_0}
$$
The intuition is that the floating leg can be replicated by investing
unit notional at the prevailing floating rate, harvesting the interest
payments, and reinvesting the notional. Repeat until termination.

The _swap par coupon_ is the fixed rate that makes the value of the
two legs equal. We use the notation $F_t(u_0, \dots, u_n)$ for this
$$
F_t(u_0, \dots, u_n) = \frac{D_t(u_0) - D_t(u_n)}
{\sum_{j=1}^n D_t(u_j)\delta_{u_{j-1},u_j}}.
$$
For the case $n = 1$ this reduces to the forward rate of an FRA.

<!--|
Counterparty Risk
-----------------

-   Assume default time $T$ and recovery $R$ on remaining cash
    flows
-   $R$ assumed to be a constant, $T$ is a random variable
-   Assume $T$ is independent of the deflators
-   Augment sample space to $\Omega' = \Omega\times [0,\infty)$
-   Augment filtration to $\mathcal{F}_t' = \mathcal{F}_t \times
    \mathcal{B}_t$,
-   Where $B_t$ contains the set $(t,\infty)$ and any
    $B\subset [0,t]$
-   At time $t$ we either know the default time exactly or only that
    it has some value greater than $t$
|-->

# Mathematics

Contrary to popular belief, stochastic processes are not needed
for financial modeling. All you need to know about are algebras and
measureable functions. Positive measures with mass one show up, but they
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
[De Morgan's laws](http://en.wikipedia.org/wiki/De_Morgan's_laws),
algebras are also closed under intersection. These are natual axioms when
talking about an event not happening, or either of two events occuring.

A _partition_ is a disjoint union of subsets, $(A_j)_j$,
such that $\Omega = \cup_j A_j$ where $A_i\cap A_j =
\emptyset$ if $i\not= j$. For an algebra, $\mathcal{F}$,
$A\in\mathcal{F}$ is an _atom_ if $B\subseteq A$,
$B\in\mathcal{A}$ imply $B=A$ or $B=\emptyset$.

If an algebra $\mathcal{F}$ is finite the atoms form a partition.
The algebra $\{\emptyset,\Omega\}$ represents complete lack
of information.
The _power set_ $\mathcal{P}(\Omega) =
\{A:A\subseteq\Omega\}$ represents complete information.
Knowing which atom $\omega\in\Omega$ belongs to represents
_partial information_.
E.g., the partition $\{\{1,3,5\},\{2,4,6\}\}$ represents knowing whether
a die roll is even or odd.

## Measurable Functions

A function $X\colon\Omega\to\mathbb{R}$ is _measurable_ if
$\{\omega\in\Omega: X(\omega) \le x\}\in\mathcal{F}$ for all
$x\in\mathbb{R}$ If $\mathcal{F}$ is finite, measurable is the same as
being constant on atoms. The set of bounded measurable functions
is denoted $B(\Omega, \mathcal{F})$.

## Measures

A _(finitely additive) measure_ is a function
$\Pi\colon\mathcal{F}\to\mathbb{R}$ such that
$\Pi(A\cup B) = \Pi(A) + \Pi(B)$ if $A\cap B = \emptyset$

Finitely additive measures are the
[vector space dual](http://en.wikipedia.org/wiki/Dual_space)
of bounded measurable functions.
The dual pairing is $\langle X,\Pi\rangle = \int_\Omega X\,d\Pi$.
If $\mathcal{F}$ is finite the integral is just the sum over
atoms.

For $X\in B(\Omega,\mathcal{F})$ and $\Pi\in ba(\Omega,\mathcal{F})$
define $X\Pi\in ba(\Omega,\mathcal{F})$ by $\langle Y,X\Pi\rangle =
\langle YX,\Pi\rangle$.

Let $\Pi|_\mathcal{G}$ be the measure $\Pi$ restricted to
the algebra $\mathcal{G}$.
If $\Pi$ is a probability measure _conditional expectation_,
$E[X|\mathcal{G}]$, is defined by $\langle E[X|\mathcal{G}],\Pi\rangle
= \langle X,\Pi|_\mathcal{G}\rangle$, $\Pi\in ba(\Omega)$. The
[adjoint/dual/transpose](http://en.wikipedia.org/wiki/Dual_space) of
conditional expectation is restriction.

## Filtrations

A _filtration_ is an increasing collection of algebras
$(\mathcal{F}_t)_{t\in T}$, i.e., $\mathcal{F}_t\subseteq\mathcal{F}_u$
if $t < u$.  A filtration represents information available over time.

Consider flipping a coin: $T$,$H$,$H$,$\dots$.  This can be modeled by
the base 2 representation of $\omega\in[0,1)$, $\omega = .011\dots_2
= \sum_{j > 0} \omega_j 2^{-j}$, $\omega_j \in\{0,1\}$. 
The algebra $\mathcal{F}_j = \{[\frac{i}{2^j},\frac{i+1}{2^j}) : 0\le
i < 2^j\}$ represents knowing the first $j$ digits

## The Fundamental Theorem of Asset Pricing

There is no arbitrage iff there exist positive scalar measures
$(\Pi_j)$ with
$$
X_j\Pi_j = (C_{j+1} + X_{j+1})\Pi_{j+1}|_{\mathcal{A}_j}
$$

By induction
$$
X_j\Pi_j = (\sum_{j < i\le k}C_i\Pi_i + X_k\Pi_k)|_{\mathcal{A}_j} \label{ftap}
$$

We can multiply the $(\Pi_j)$ by any positive function so replacing
$\Pi_j$ by $\Pi_j \Pi_0^{-1}$ allows us to assume $\Pi_0 = 1$.

Under this assumption the deflators are unique if the market is complete
(the so called Second fundamental theorem) but this is never true for
realistic models

### FTAP (easy direction)

Suppose there exist price deflators with
$X_j\Pi_j = (C_{j+1} + X_{j+1})\Pi_{j+1}|_{\mathcal{A}_j}$.
Using $A_{j+1} = \Delta_{j}\cdot C_{j+1} - \Gamma_{j+1}\cdot X_{j+1}$



\begin{align*}
\Delta_j\cdot X_j\Pi_j
&= \underline{\Delta_j}\cdot(\underline{C_{j+1}} +
    X_{j+1})\Pi_{j+1}|_{\mathcal{A}_j}\\
&= (\mathbf{A_{j+1} + \underline{\Gamma_{j+1}}\cdot X_{j+1}} +
    \underline{\Delta_j}\cdot X_{j+1})\Pi_{j+1}|_{\mathcal{A}_j}\\
&= (A_{j+1} + \mathbf{\Delta_{j+1}}\cdot X_{j+1})\Pi_{j+1}|_{\mathcal{A}_j}\\
\end{align*}


By induction $\Delta_j\cdot X_j\Pi_j = (\sum_{j < i\le k} A_i\Pi_i +
\Delta_k\cdot X_k\Pi_k)|_{\mathcal{A}_j}$.
Note if $\sum_j\Gamma_j = 0$
and $A_i\ge0$, $i>0$ then $A_0\le0$ since
$-A_0 = \Delta_0\cdot X_0 = \sum_j A_j\Pi_j|_{\mathcal{A}_0}\ge0$.

### FTAP (hard direction)

<!--|
Stephen Ross [@Ros1978] gave the first proof of the FTAP using
the Hahn-Banach theorem. His primary contribution was to extend the
Black-Scholes/Merton result from a bond, stock, and option to an
arbitrary collection of instruments and show it was essentially
a geometric fact. 

Fischer Black and Myron Scholes gave a mathematically incorrect derivation
of their eponymous partial differential equation that was immediately
corrected by Robert Merton who understood the Ito calculus better than
they did. Ross's proof neglected to establish an essential condition
required for the application of the Hahn-Banach theorem and this led
to a sequence of papers addressing the matter. The current state of
the art is [@DelSch1994] that contains a 61 page proof of the current
formulation. 
|-->

Who cares?  No arbitrage implies deflators exist, but we can find plenty.

E.g., $X_t = (e^{rt}, se^{(r - \sigma^2/2)t + \sigma B_t})$,
$\Pi_t = e^{-rt}P$, where $(B_t)$ is
[Brownian motion](http://en.wikipedia.org/wiki/Brownian_motion) and $P$ is
Weiner measure models a bond and non-dividend paying stock.

Finding arbitrage free models is not difficult.  Finding models that
reflect market dynamics with parameters that can be fitted to market
data is the holy grail.

## Models

Let's define some models and start putting them to use.

### Put-Call Parity

Let $T = \{0,1\}$, $\Omega = [0,\infty)$, $\mathcal{A}_0
= \{\Omega\}$, $\mathcal{A}_1 = \mathcal{P}(\Omega)$,
$X_0 = (1,s,c,p)$, $X_1(\omega) = (R,\omega,0,0)$, and
$C_1(\omega) = (0,0,\max\{\omega - k,0\},\max\{k -
\omega,0\})$.

This is a one period model of a bond with realized return $R$,
a stock that can have any non-negative value,
and a call and put both struck at $k$. Note the call and put
have zero price at expiration. They are derivatives hence
specified by their cash flows.

No arbitarge implies
$$
(1,s,c,p)
= \langle (R,\omega,\max\{\omega - k,0\},\max\{k - \omega,0\}), \Pi\rangle.
$$
Taking $\Gamma_0 = (k/R, -1, 1, -1)$ yields $k/R - s + c - p
= \langle k - \omega + \max\{\omega - k,0\} - \max\{k - \omega,0\}),\Pi\rangle = 0$
_Put-call parity_ is $c - p = s - k/R$.  We don't really need a model
for this, but it illustrates how to use the mathematical framework.

Note that $\Pi$ is not unique but no matter which $\Pi$ we use we
come to the same conclusion. The first thing a trader will check with
any new model is put-call parity. If that does not hold, the model
must be wrong.

### Cost of Carry

Let $T = \{0,1\}$, $\Omega = [0,\infty)$, $\mathcal{A}_0
= \{\Omega\}$, $\mathcal{A}_1 = \mathcal{P}(\Omega)$,
$X_0 = (1,s,0)$, $X_1(\omega) = (R,\omega,0)$
$C_1(\omega) = (0, 0, \omega - f)$

This models a bond with realized return $R$, a stock that can have
any non-negative value, and an at-the-money forward.
Forwards have price zero at expiration
No arbitarge implies $(1,s,0) = \langle
(R,\omega,\omega-f),\Pi\rangle$ so $1 = \langle
R,\Pi\rangle$, $s = \langle \omega,\Pi\rangle$, and $0
= s - f/R$.
The _cost-of-carry_ is $f = Rs$
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

Suppose a derivative pays $v(\omega)$ at time 1 for some function $v$.
There exists $\Gamma_0 = (m,n)$ such that $\Gamma_0\cdot X_1 = v$
on $\Omega$.
Solve $mR + nS^- = V(S_-)$, $mR + nS^+ = V(S_+)$ for $m,n$
yields $n = (V(S_+)-V(S_-))/(S_+-S_-)$, and
$$
v = m + ns =
    \frac{1}{R}\left(\frac{S_+-Rs}{S_+-S_-}V(S_-)+\frac{Rs -
    S_-}{S_+-S_-}V(S_+)\right)
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
There exists $\Gamma_0 = (m,n)$ such that $\Gamma_0\cdot X_1 = v$.
Solving $mR + nsd = V(sd)$, $mR + nsu = V(su)$ for $m,n$
gives $n = (V(su)-V(sd))/(su - sd)$, and
$$
v = \Gamma_0\cdot X_0 = m + ns = \frac{1}{R}\left(\frac{u-R}{u-d}V(sd) + \frac{R-d}{u-d}V(su)\right)
$$
However $n \not= dv/ds$ in general.
E.g., for a butterfly spread with support inside of $[sd,su]$ we have
$dv/ds = 0$ since $V'(sd) = V'(su) = 0$.

## Delta Hedging

<!--|
Derivatives
-----------

-   Prices and cash flows satisfy $\color{blue}X_j\Pi_j =
    \sum_{j < i\le k}\color{red}C_i\Pi_i +
    \color{blue}X_k\Pi_k|_{\mathcal{A}_j}$
-   For any trades $(\Gamma_j)$, $\color{blue}\Delta_j\cdot
    \color{blue}X_j\Pi_j = \sum_{j < i\le k}
    \color{red}A_i\Pi_i + \color{blue}\Delta_k\cdot
    \color{blue}X_k\Pi_k|_{\mathcal{A}_j}$
-   The position determines the value $\color{blue}\Delta_j\cdot
    \color{blue}X_j$...
-   ...and the account determines the cash flows $\color{red}A_j$
    for a derivative instrument
-   This is how to create synthetic instruments

Delta Hedging
-------------

-   Assuming $\Pi_0 = 1$ and $\Delta_j$ is eventually zero
    $$ \Delta_0\cdot X_0 = \sum_{0 <
    i}A_i\Pi_i|_{\mathcal{A}_0} $$
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
-   Multiperiod stock and foward contract
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
-   Multiperiod stock paying dividends and foward contract
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
-   Choose $\pi_j\in B(\Omega,\mathcal{A}_j)$ and let
    $\Pi_j = \pi_jP|_{\mathcal{A}_j}$
-   Arbitrage free if $X_j\Pi_j = (C_{j+1} +
    X_{j+1})\Pi_{j+1}|_{\mathcal{A}_j}$
-   Customary to assume $\mathcal{A}_0 = \{\emptyset,\Omega\}$
    and $\pi_0 = 1$
-   The cash flows are usually specified by the market
-   The difficult part is specifying the prices and deflators

Canonical Price Deflator
------------------------

-   If $X_t = R(t)$ is deterministic and $C_t = 0$ then
    $\Pi_t = R(t)^{-1}P|_{\mathcal{A}_t}$ for any probability
    measure $P$ is a deflator for that single instrument
-   Assume for each time there is an instrument with $X_j = 1$ and
    $C_{j+1} = R_j$
-   $R_j$ is the _short realized return_ over $t_j$ to
    $t_{j+1}$
-   Define _canonical price deflators_ $$\Pi_j = (R_0\cdots
    R_{j-1})^{-1}P|_{\mathcal{A}_j}$$
-   Easy to show $\Pi_j = R_j\Pi_{j+1}|_{\mathcal{A}_j}$
-   Note $\Pi_j$ is $\mathcal{A}_{j-1}$ measurable (aka
    _predictable_)
-   There are many possible deflators, but this is canonnical

Zero Coupon Bonds
-----------------

-   A zero coupon bond maturing at $u$ has $X_0 = D(u)$ and
    $C_u = 1$
-   $D(u)\Pi_0 = \Pi_u|_{\mathcal{A}_0}$ so $D(u) =
    \Pi_u(\Omega)$
-   Let $D_t(u)$ be the price at time $t$
-   $D_t(u)\Pi_t = \Pi_u|_{\mathcal{A}_t}$ so $$ D_t(u) =
    \Pi_u/\Pi_t|_{\mathcal{A}_t} = \Pi_{t\le s <
    u}R_s^{-1}P|_{\mathcal{A}_t} $$

Forward Rate Agreements
-----------------------

-   have price $X_0 = 0$ and two cash flows
    -   $C_u = -1$, $C_v = 1 + F(u,v)\delta_{u,v}$
-   $\delta_{u,v}$ is the _day count fraction_ that is
    approximately $v - u$ in years depending on the [day count
    convention](http://en.wikipedia.org/wiki/Day_count_convention)
-   Since $0 = -D(u) + (1 + F(u,v)\delta_{u,v})D(v)$ we have $$
    F(u,v) = \frac{1}{\delta_{u,v}}\left(\frac{D(u)}{D(v)} -
    1\right) =
    \frac{1}{\delta_{u,v}}\left(\frac{\Pi_u}{\Pi_v}\bigr|_{\mathcal{A}_0}
    - 1\right) $$
-   Let $F_t(u,v)$ be the forward at time $t$ over $[u,v]$
-   Since $X_t = 0 = -D_t(u) + (1 +
    F_t(u,v)\delta_{u,v})D_t(v)$ we have $$ F_t(u,v) =
    \frac{1}{\delta_{u,v}}\left(\frac{D_t(u)}{D_t(v)} - 1\right)
    =
    \frac{1}{\delta_{u,v}}\left(\frac{\Pi_u}{\Pi_v}\bigr|_{\mathcal{A}_t}
    - 1\right) $$

Forward Rate Agreements w/o Notional
------------------------------------

-   Can also be specified as a single cash flow
-   price $X_0 = 0$ and forward $f(u,v)$ with
    -   $C_v = (F_u(u,v) - f(u,v))\delta_{u,v}$
-   Prevailing forward rate at start of period versus fixed
-   Note $0 = (F_u(u,v) -
    f(u,v))\delta_{u,v}\Pi_v|_{\mathcal{A}_0} = (\Pi_u -
    \Pi_v - f(u,v)\delta{u,v})|_{\mathcal{A}_0}$
-   and $F_0(u,v)\delta_{u,v}\Pi_v|_{\mathcal{A}_0} = (\Pi_u
    - \Pi_v)|_{\mathcal{A}_0}$
-   so $f(u,v) = F_0(u,v)$
-   These two contracts have very different risk profiles

Counterparty Risk
-----------------

-   Assume default time $T$ and recovery $R$ on remaining cash
    flows
-   $R$ assumed to be a constant, $T$ is a random variable
-   Assume $T$ is independent of the deflators
-   Augment sample space to $\Omega' = \Omega\times [0,\infty)$
-   Augment filtration to $\mathcal{A}_t' = \mathcal{A}_t \times
    \mathcal{B}_t$,
-   Where $B_t$ contains the set $(t,\infty)$ and any
    $B\subset [0,t]$
-   At time $t$ we either know the default time exactly or only that
    it has some value greater than $t$

|-->

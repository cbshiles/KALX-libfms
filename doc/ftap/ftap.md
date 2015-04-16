% The Fundamental Theorem of Asset Pricing
% Keith A. Lewis
% <a href="http://kalx.net">KALX, LLC</a>

## State of the Art

-  _There should be no sequence of final payoffs of admissible
    integrands,_ $f_n = (H_n\cdot S)_{\infty}$_, such that the
    negative parts_ $f_n$ _tend to zero uniformly and such that_
    $f_n$ _tends almost surely to a_ $[0,\infty)$_-valued
    function_ $f_0$ _satisfying_ $P[f_0 \gt 0] > 0$

-   Freddy Delbaen and Walter Schachermayer. _A general version of the
    fundamental theorem of asset pricing_. Mathematische Annalen,
    300:463--520, 1994.

-   How many people have read (and understood) the 61 page proof?

----------------------------

## 1-2-3 Example

- One period model of bond, stock, and option
- Bond: $1\to 2$ with probability $1$.
- Stock: $1\to \omega$ with $P(\omega = 1) = 0.1$, $P(\omega = 3) = 0.9$
- Option: call with strike $2$ so $v\to 0$ or $v\to 1$
- $v \not= (1/2)(0\times 0.1 + 1\times 0.9) = 0.45$.
- We can find $m$, $n$ such that $(\omega - 2)^+ = 2m + \omega n$
- In a binomial model all payoffs are linear
- This determines $v = 0.25$
- "Real world" probabilities don't matter in theory
- But they do in the real world

----------------------------

## Old Baggage

-   The classical definition of arbitrage is unrealistic
    -   Traders want to make money on the initial position
    -   and minimize the capital required to do that
-   Specifying a "real-world" measure is irrelevant
    -   It gets immediately discarded anyway
    -   Measuring risk is the important problem
-   Discounted prices are martingales
    -   but only if cash flows are ignored
-   Conditional expectation is unnecessary
    -   it can be replaced by a simpler concept

----------------------------

## A Simpler Approach

-   Map the finance to mathematics as directly as possible...
    -   ...and clearly identify the misspecification
-   The mathematics has to be implemented in software to be useful...
    -   ...by people who don't understand complicated mathematics
-	The FTAP is a geometric result, not probabilistic...
	-	...positive measure show up and can have weight 1

----------------------------

## One Period Model

- $\Omega$ is the set of all outcomes over the period
- $x\in\mathbf{R}^m$ initial prices of $m$ instruments
- $X\colon\Omega\to\mathbf{R}^m$ final prices
- Arbitrage: $\gamma\in\mathbf{R}^m$, $-\gamma\cdot x > 0$, $\gamma\cdot X\ge0$
- FTAP: No arbitrage iff $x$ belongs to the smallest cone containing the range of $X$.
- $x = \int_\Omega X\,d\Pi = \langle X, \Pi\rangle$ for some positive measure $\Pi$
- See <a href="http://kalx.net/ftapd.pdf" target=_blank>ftapd.pdf</a> Lemma 3.2
- $\gamma\cdot x = 0$, $\gamma\cdot X\ge0$, and $E[\gamma\cdot X] > 0$ doesn't fly.

----------------------------

## 1-2-3 Example Again

- $\Omega = \{1,3\}$, possible terminal stock prices
- $x = (1, 1, v)$, bond, stock, call with strike $2$
- $X(\omega) = (2, \omega, (\omega - 2)^+)$
- $\mathrm{cone}\ X(\Omega) = \{(2,1,0)\pi_1 + (2,3,1)\pi_3:\pi_j\ge0\}$
- $(1,1,v) = (2,1,0)\pi_1 + (2,3,1)\pi_3$ 
- so $\pi_1 = \pi_3 = 1/4$ and $v = 0.25$

-----------------------------

## 9-10-11 Example

- $\Omega = \{9,10,11\}$, possible terminal stock prices
- $x = (1, 10, v)$, bond, stock, call with strike $10$
- $X(\omega) = (1, \omega, (\omega - 10)^+)$ so zero interest rate
- $(1, 10, v) = (1,9,0) \pi_{9} + (1,10,0) \pi_{10} + (1,11,1) \pi_{11}$
- so $\pi_{9} + \pi_{10} + \pi_{11} = 1$ and $-\pi_{9} + \pi_{11} = 0$
- $\pi_{10} = 1 - 2\pi_{11} \ge 0$ implies $v = \pi_{11}\le 1/2$
- _Exercise_. What if the bond is removed?
- __Answer__. $0\le v\le 10/11$

----------------------

## Cost of Carry

-   $\Omega = [0,\infty)$
-   $x = (1,s,0)$
-	$X(\omega) = (R, \omega, \omega - f)$
-   A bond with realized return $R$, a stock that can have
    any non-negative value, and an at-the-money forward
-   No arbitrage implies $(1,s,0) = \langle
    (R,\omega,\omega-f),\Pi\rangle$
-	Taking $\gamma = (f/R, -1, 1)$ yields
	$$f/R - s = \langle f - \omega + \omega - f,\Pi\rangle = 0$$
-   Cost-of-carry:$f = Rs$
-   Don't really need a model for this, but it illustrates how to use
    the framework

------------------------

## Put-Call Parity

-   $\Omega = [0,\infty)$
-   $x = (1,s,c,p)$
-	$X(\omega) = (R,\omega,(\omega - k)^+,(k - \omega)^+)$
-   A bond with realized return $R$, a stock that can have
    any non-negative value, and a call and put both struck at $k$.
-   No arbitrage implies
	$$(1,s,c,p) = \langle (R,\omega,(\omega - k)^+,(k - \omega)^+),\Pi\rangle$$
-   Taking $\gamma = (k/R, -1, 1, -1)$ yields $k/R - s + c - p
    = \langle k - \omega + (\omega - k)^+ - (k - \omega)^+),\Pi\rangle = 0$
-   Put-call parity: $c - p = s - k/R$
-   Also don't really need a model for this

-----------------------------

## Multi Period Model

- Times: increasing $(t_j)$
	- Times at which trading can occur
- Prices: $\mathbf{R}^m$-valued $(X_j)$
	- Perfectly liquid market instrument prices
- Cash flows: $\mathbf{R}^m$-valued $(C_j)$
	- Associated with owning an instrument
- Trades: $\mathbf{R}^m$-valued $(\Gamma_j)$
	- Number of shares transacted by buyer

-----------------------------

## Accounting

-   Position: $\Delta_j = \sum_{i\le j}\Gamma_i$
    -   shares held at time $t_j$
-   Value: $V_j = \Delta_j\cdot X_j$
    -   Marked-to-market value of the position
-   Account: $A_j = \Delta_{j-1}\cdot C_j - \Gamma_j\cdot X_j$
    -   Cash flows from existing position less cost of current
        securities traded

-----------------------------

## Mathematics

- Filtration: increasing algebras $(\mathcal{F}_j)$ on $\Omega$
	- Information available at time $t_j$
- All functions are assumed to be adapted and bounded
	- `#define DBL_MAX 1.7976931348623157E+308`
- $B(\Omega, \mathcal{F})$ denotes bounded $\mathcal{F}$-measurable functions
- $B(\Omega, \mathcal{F})^* = ba(\Omega, \mathcal{F})$, finitely additive measures
- The atoms of a finite algebra form a partition
- Measurable functions are constant on atoms

-----------------------------

## Arbitrage

-   Trades $(\Gamma_j)$ such that
    $A_0\gt 0$, $A_j\ge0$ and $\sum_j \Gamma_j = 0$.
-	Make money on the initial trade, never lose thereafter,
    and close out the position at some point.
-   Note no prior 'real world' measure is assumed
-   This definition is not sufficient for traders
	- Risk managers will slap absolute value signs around every number.
	- If $|\Gamma_0|\cdot|X_0|$ is too large they can't do the trade.
-	It is also not good enough for risk managers
	- If $A_j$ gets large they will pressure traders to unwind

------------------------------------

## Fundamental Theorem of Asset Pricing

-   There is no arbitrage iff there exist positive scalar measures
    $(\Pi_j)\in ba(\Omega, \mathcal{F}_j)$ with 
	$$X_j\Pi_j = (C_{j+1} + X_{j+1})\Pi_{j+1}|_{\mathcal{F}_j}$$
-   By induction $$X_j\Pi_j = (\sum_{j\lt i\le
    k}C_i\Pi_i + X_k\Pi_k)|_{\mathcal{F}_j} \label{ftap}
    $$
-   $(\Pi_j)$ are unique if the market is complete
	(Second fundamental theorem)
-   If markets were complete, derivatives would not exist

------------------------------------

## Fundamental Formula of Derivative Pricing

-   Suppose there exist price deflators with
	$$X_j\Pi_j = (C_{j+1}
    + X_{j+1})\Pi_{j+1}|_{\mathcal{F}_j}$$
-   $\Delta_j\cdot X_j\Pi_j =
    \underline{\Delta_j}\cdot(\underline{C_{j+1}} +
    X_{j+1})\Pi_{j+1}|_{\mathcal{F}_j}$
-   Using $A_{j+1} = \Delta_{j}\cdot C_{j+1} -
    \Gamma_{j+1}\cdot X_{j+1}$
-   $\Delta_j\cdot X_j\Pi_j = (\mathbf{A_{j+1} +
    \underline{\Gamma_{j+1}}\cdot X_{j+1}})\Pi_{j+1} +
    \underline{\Delta_j}\cdot
    X_{j+1}\Pi_{j+1}|_{\mathcal{F}_j}$
-	Since $\Gamma_{j+1} + \Delta_j = \Delta_{j+1}$ 
	$$V_j\Pi_j = (A_{j+1} + V_{j+1})\Pi_{j+1}|_{\mathcal{F}_j}$$
-   Value acts like price, account acts like cash flow

--------------------------

## FTAP Easy Direction

-   By induction $V_j\Pi_j
	= (\sum_{j\lt i\le k} A_i\Pi_i + V_k\Pi_k)|_{\mathcal{F}_j}$
-   $\Delta_0\cdot X_0\Pi_0(\Omega) = (\sum_{0<i\le n} A_i\Pi_i)(\Omega)
	+ \Delta_n\cdot X_n\Pi_n(\Omega)$
-   If $\sum_{j=0}^n\Gamma_j = 0$ and $A_i\ge0$, $i\gt0$ then
    $$-A_0\Pi_0(\Omega) = \Delta_0\cdot X_0\Pi_0(\Omega) \ge 0$$
-	Since $\Pi_0(\Omega) > 0$ we must have $A_0 \le 0$

-------------------

## FTAP Hard Direction

-   Who cares?
-   No arbitrage implies deflators exist, but we can find plenty
	without using the Hahn-Banach theorem
    -   E.g., $X_t = (e^{rt}, se^{(r - \sigma^2/2)t + \sigma
        B_t})$, $\Pi_t = e^{-rt}P$,
    -   where $(B_t)$ is Brownian motion and $P$ is Weiner
        measure
    -   models a bond and non-dividend paying stock
-   The hard part is finding models that reflect market dynamics with
    parameters that can fit market data

-------------

## Delta Hedging

-   Assuming $\Pi_0(\Omega) = 1$, $\mathcal{F}_0 = \{\Omega\}$,
	and $\Delta_n = 0$
    $$ \Delta_0\cdot X_0 = \sum_{0\lt i}A_i\Pi_i(\Omega) $$
-   "The value of a derivative is the expected value of discounted cash
    flows"
-   _If_ a hedge exists the initial hedge is given by $$\Gamma_0 =
    \Delta_0 = \frac{\partial(\Delta_0\cdot X_0)}{\partial
    X_0} = \frac{\partial}{\partial X_0}E[\sum_{0\lt
    i}A_i\Pi_i]$$
-	A perfect hedge never exists, so the question is how bad
	is the hedge?

----------------

## Measuring Risk

-   Traders look at the _gamma profile_: gamma versus time and underlying
-   For a one period model $\langle (\gamma\cdot X - V)^2,\Pi\rangle$
	is one measure
-   We could solve
    $$\min_{\gamma}\langle (\gamma\cdot X - V)^2, \Pi\rangle$$
	and get another measure of the hedging error
-	The solution is
	$\gamma = \langle XX^T,\Pi\rangle^{-1}\langle XV,\Pi\rangle$
-	_Exercise_. Calculate this for $x = (1,s,v)$, $X = (R, S, V(S))$.
-	Both generalize to multi-period models

-------------------

## Multiperiod Stock Model

-   $\Omega = [0,\infty)^n$
-   $X_0 = (1,s,0)$, $X_j = (R_j, \omega_j,
    \phi_j(\omega_j))$, $X_n = (R_n, \omega_n, 0)$
-   $C_j = 0$, $0\le j\lt n$, $C_n = (0, 0, \omega_n -
    f)$
-   Multiperiod stock and foward contract
-   The $\phi_j$ are determined by the no arbitrage condition
-   $(R_j, \omega_j, 0)\Pi_j = (R_n, \omega_n,\omega_n - f)\Pi_n$
	on $\mathcal{F}_j$
-   so $\phi_j(\omega_j) = \omega_j - fR_n/R_j$
-	_Exercise_. Add fixed dividends to the model

--------------

## General Models

-   Specify a probability measure $P$ on $\Omega$
-   Choose $\pi_j\in B(\Omega,\mathcal{F}_j)$ and let
    $\Pi_j = \pi_jP|_{\mathcal{F}_j}$
-   Arbitrage free if $X_j\Pi_j = (C_{j+1} +
    X_{j+1})\Pi_{j+1}|_{\mathcal{F}_j}$
-   Customary to assume $\mathcal{F}_0 = \{\emptyset,\Omega\}$
    and $\pi_0 = 1$
-   The cash flows are usually specified by the market
-   The difficult part is specifying the prices and deflators

------------------------

## Canonical Price Deflator

-   Assume for each time there is an instrument with
	$$X_j = 1, C_{j+1} = R_j$$
-   $R_j$ is the _short realized return_ over $t_j$ to
    $t_{j+1}$
-   Define _canonical price deflators_ $$\Pi_j = (R_0\cdots
    R_{j-1})^{-1}P|_{\mathcal{F}_j}$$
-   Easy to show $\Pi_j = R_j\Pi_{j+1}|_{\mathcal{F}_j}$
-   Note $\Pi_j$ is $\mathcal{F}_{j-1}$ measurable (aka
    _predictable_)
-   There are many possible deflators, but this is canonical
-	Find $R_j$ that reprice cash deposits, FRA, swaps, etc.

--------------

## Forwards/Futures

-	A forward expiring at $t_n$ with strike $f_n$ has a single
	cash flow $C_n = \omega_n - f_n$.
-	Let $(\Phi_j)$ be the futures _quotes_
-	A futures expiring at $t_n$ is determined by $\Phi_n = \omega_n$,
	cash flows $C_j = \Phi_{j} - \Phi_{j-1}$ and prices $X_j = 0$
-	Since $0 = (\Phi_{j+1} - \Phi_{j})\Pi_{j}|_{\mathcal{F}_j}$
	we have $\Phi_{j+1}P|_{\mathcal{F}_j} = \Phi_jP$ for canonical deflators

-----------------

## Counterparty Risk

-   Assume default time $T$ and recovery $R$ on remaining cash
    flows
-	$V_0 = \sum_{t_i\le T} A_i\Pi_i + R(\sum_{t_i>T}A_i\Pi_i)$
-   $R$ assumed to be a constant, $T$ is a stopping time
-   Augment sample space to $\Omega' = \Omega\times [0,\infty)$
-   Augment filtration to $\mathcal{F}_j' = \mathscr{F}_j \times
    \mathcal{G}_j$,
-   Where $\mathcal{G_j} = \{\{t_0\},...,\{t_j\},\{t_{j+1},...\}\}$
-   At time $t_j$ we either know the default time exactly or only that
    it has some value greater than $t_j$

------------------

## American Options

-	Discrete time, so really Bermudan
-	Buyer specifies a stopping time $T_b$
-	Buyer filtration might be a subset of $(\mathcal{F}_j)$
-	$V_0 = \sum_{t_i\le T_b} A_i\Pi_i(\Omega)$
-	Models should provide knobs, not prescribe optimal behavior
-	E.g., Clean model for prepayments

-------------------

## Callable and Putable Bonds

-	Both buyer and issuer (seller) have stopping times
-	Each might have their own subfiltration
-	$V_0 = \sum_{t_i\le \min\{T_b,T_s\}} A_i\Pi_i(\Omega)$

-------------------

## Implementation

-	$V_j(A) = sum_{B\subset A} V_{j+1}\Pi_{j+1}(B)$
-	Binomial model: $\Omega = \{-1,1\}^n$, $P(\{\omega\}) = 1/2^n$
-	Random walk: $W_j(\omega) = \omega_1 + \cdots + \omega_n$
-	$\Pi_j = \pi_j(W_j)P$
-	Naive implementation of $\pi_jP(A)$ requires
	$2^j$ calculations
-	$A = A\cap(\{W_j = -j\}\cup\{W_j = -j + 2\}\cup\cdots\cup\{W_j = j\})$
	reduces this to order $j$

-------------------

## The Future?

-	Monte Carlo and compute power
	- Simple models and multicore machines
-	Multicore is major advance from von Neumann architecture
	- People are still learning how to write for this
-	Interesting things are happening with C++
	- <a href="http://isocpp.org/blog/2014/12/myths-1">Popular Myths about C++</a>
-	Probably not GPUs
	- Except for problems shaped like rendering pixels

-------------------

## Links

<a href="http://kalx.net">KALX</a>

<a href="http://kalx.net/fms/rough/pp.html">Probability Preliminaries</a>

<a href="https://xll.codeplex.com">Excel Add-in Library</a>

<a href="https://libfms.codeplex.com">A Software Library for Financial Mathematics</a>

<a href="https://cuda.codeplex.com">CUDA Driver API</a>

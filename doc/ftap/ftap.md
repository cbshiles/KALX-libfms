% The Fundamental Theorem of Asset Pricing
% Keith A. Lewis
% <a href="http://kalx.net">KALX, LLC</a>

# State of the Art

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

# One Period Model

- $\Omega$ is the set of all outcomes over the period
- $x\in\mathbf{R}^m$ initial prices of $m$ instruments
- $X\colon\Omega\to\mathbf{R}^m$ final prices
- Arbitrage: $\gamma\in\mathbf{R}^m$, $-\gamma\cdot x > 0$, $\gamma\cdot X\ge0$
- FTAP: No arbitrage iff $x$ belongs to the smallest cone containing the range of $X$.
- See <a href="http://kalx.net/ftapd.pdf" target=_blank>ftapd.pdf</a> Lemma 3.2
- $\gamma\cdot x = 0$, $\gamma\cdot X\ge0$, and $E[\gamma\cdot X] > 0$ doesn't fly.

----------------------------

# Old Baggage

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

<!--|
----------------------------

# A Simpler Approach

-   Map the finance to mathematics as directly as possible...
    -   ...and clearly identify the misspecifications
-   The mathematics has to be implemented in software to be useful...
    -   ...by people who don't understand complicated math,
-   And make sense to the business side
    -   They write the checks
|-->
----------------------------

# 1-2-3 Example

- One period model of bond, stock, and option
- Bond: $1\to 2$ with probability $1$.
- Stock: $1\to \omega$ with $P(\omega = 1) = 0.1$, $P(\omega = 3) = 0.9$
- Option: call with strike $2$ so $v\to 0$ or $v\to 1$
- $v \not= (1/2)(0\times 0.1 + 1\times 0.9) = 0.45$.
- $\mathrm{cone}\ X(\Omega) = \{(2,1,0)\pi_1 + (2,3,1)\pi_3:\pi_j\ge0\}$
- $(1,1,v) = (2,1,0)\pi_1 + (2,3,1)\pi_3$ implies $\pi_1 = \pi_3 = 1/4$ so $v = 0.25$
- "Real world" probabilities don't matter in theory.
- But they do in the real world.

-----------------------------

# 9-10-11 Example

- $\Omega = \{9,10,11\}$, possible terminal stock prices
- $x = (1, 10, v)$, bond, stock, call with strike $10$
- $X(\omega) = (1, \omega, (\omega - 10)^+)$ so zero interest rate
- $(1, 10, v) = (1,9,0) \pi_{9} + (1,10,0) \pi_{10} + (1,11,1) \pi_{11}$
- so $\pi_{9} + \pi_{10} + \pi_{11} = 1$ and $-\pi_{9} + \pi_{11} = 0$
- $\pi_{10} = 1 - 2\pi_{11} \ge 0$ implies $v = \pi_{11}\le 1/2$
- _Exercise_. What if the bond is removed?
- __Answer__. $0\le v\le 10/11$

-----------------------------

# Multi Period Model

- Times: increasing $(t_j)$
	- Times at which trading can occur
- Prices: $\mathbf{R}^m$-valued $(X_j)$
	- Perfectly liquid market instrument prices
- Cash flows: $\mathbf{R}^m$-valued $(C_j)$
	- Associated with owning an instrument
- Trades: $\mathbf{R}^m$-valued $(\Gamma_j)$
	- Number of shares transacted by buyer

-----------------------------

# Accounting

-   Position: $\Delta_j = \sum_{i\le j}\Gamma_i$
    -   shares held at time $t_j$
-   Value: $\Delta_j\cdot X_j$
    -   Marked-to-market value of the position
-   Account: $A_j = \Delta_{j-1}\cdot C_j - \Gamma_j\cdot
    X_j$
    -   Cash flows from existing position less cost of current
        securities traded

-----------------------------

# Mathematics

- Filtration: increasing algebras $(\mathcal{F}_j)$ on $\Omega$
	- Information available at time $t_j$
- All functions are assumed to be adapted and bounded
	- By `#define DBL_MAX    1.7976931348623157E+308`
- The dual of $B(\Omega, \mathcal{F})$ is $ba(\Omega, \mathcal{F})$
	- The space of finitely additive measures
- The atoms of a finite algebra form a partition
- Measurable functions are constant on atoms

-----------------------------

# Arbitrage

-   Trades $(\Gamma_j)$ such that
    $A_0\gt 0$, $A_j\ge0$ and $\sum_j \Gamma_j = 0$.
-	Make money on the initial trade, never lose thereafter,
    and close out the position at some point.
-   Note: no prior 'real world' measure is assumed
-   This definition is not sufficient for traders
	- Risk managers will slap absolute value signs around every number.
	- If $|\Gamma_0|\cdot|X_0|$ is too large they can't do the trade.


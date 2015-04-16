# Cost of Carry

Consider a bond having realized return $R$ over a single period,
a stock having initial price $s$ and any non-negative value at
the end of the period, and an at-the-money forward having strike $f$.
The _cost-of-carry_ formula is $f = Rs$.

An ATM forward has initial price 0 and a cash flow of $S - f$
at expiration, where $S$ is the price of the
stock at expiration and $f$ is the ATM forward.

This is modeled as $T = \{t_0,t_1\}$, $\Omega =
[0,\infty)$, $X(t_0,\omega)
= \begin{bmatrix}1\\ s\\ 0\end{bmatrix}$,
$X(t_1,\omega) = \begin{bmatrix}R\\ S\\ 0\end{bmatrix}$
and $C(t_1,\omega) = \begin{bmatrix}0\\ 0\\ S - f\end{bmatrix}$,
where $S = S(\omega) = \omega$.

Let $\Pi_1 = \Pi$ be any deflator. Since
$\begin{bmatrix}1&s&0\end{bmatrix}' =
\Pi(\begin{bmatrix}R&S&S-f\end{bmatrix}')$
we have $1 = \Pi(R) = R||\Pi||$, $s = \Pi(S)$,
and $0 = \Pi(S - f) = s - f||\Pi||$, hence $s = f/R$.

Of course there is no need for elaborate theory to prove this result.
It is just a simple example of specifying a model, using the FTAP,
and cranking the mathematical handle to produce a result.
Something we endeavor to do for all and every derivative instrument.

Note we could also use $\Omega = (-\infty,\infty)$, or indeed any subset
of $\mathbb{R}$, and the same result holds. One benefit of using a solid
mathematical foundation is that it allows us to generalize results that
might not be obvious using ad hoc methods.

### Dividends
If the stock pays a dividend, $d$, at the end of the period, then
$C(t_1,\omega) = \begin{bmatrix}0& d& S - f\end{bmatrix}'$.
The same analysis shows $f = Rs - d$.

### Remark
We will not address the philosophical question of whether all prices
should be 0 at the end of a one-period model.

[Back](xva.html#examples)

# Put-Call Parity

Consider a bond having realized return $R$ over a single period,
a stock having initial price $s$ and any non-negative value at
the end of the period, and a call and put having the same strike $k$.
The _put-call parity_ formula is $c - p = s - k/R$, where $p$ is
the put price and $c$ is the call price.

This is modeled as $T = \{t_0,t_1\}$, $\Omega =
[0,\infty)$, $X(t_0,\omega)
= \begin{bmatrix}1&s&c&p\end{bmatrix}'$, $X(t_1,\omega)
= \begin{bmatrix}R&S&0&0\end{bmatrix}'$ and $C(t_1,\omega)
= \begin{bmatrix}0&0&\max\{S-k,0\}&\max\{k-S,0\}\end{bmatrix}'$,
where $S = S(\omega) = \omega$.

Let $\Pi_1 = \Pi$ be any deflator. Since
$\begin{bmatrix}1&s&c&p\end{bmatrix}' =
\Pi(\begin{bmatrix}R&S&(S-k)^+&(k-S)^+\end{bmatrix}')$
we have $1 = \Pi(R) = R||\Pi||$, $s = \Pi(S)$,
$c = \Pi(S-k)^+$, and $p = \Pi(k-S)^+$. Since
$(S-k)^+ - (k - S)^+ = S - k$ we have
$c - p = \Pi(S - k) = s - k||\Pi|| = s - k/R$.

Again, no need for elaborate theory. Also, the result holds for
arbitrary $\Omega\subseteq\mathbb{R}$.

[Back](xva.html#examples)

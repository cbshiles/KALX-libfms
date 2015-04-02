# Fixed Income Theory

Price deflators determine the prices of all fixed income products,
assuming no default.

## Zero Coupon Bonds

A _zero coupon bond_ maturing at $u$ has price
$X_0^{D(u)} = D(u)$ at time $0$ and a single non-zero cash flow
$C_u^{D(u)} = 1$ at time $u$. By the FTAP,
$X_t^{D(u)}\Pi_t = \Pi_u|_{\mathscr{A}_t}$.
We use $D_t(u)$ to denote $X_t^{D(u)}$, the price at time $t$
of a zero coupon bond maturing at time $u$.

Assuming discrete trading times and short returns are market instruments,
we have
$$
	D_t(u)P|_{\mathscr{A}_t} = \prod_{t \le s < u} R_s^{-1}P|_{\mathscr{A}_t}
$$
Note that in general zero coupons bonds cannot be replicated
from short returns.

## Fixed Income Instruments

A _fixed income instrument_ has a fixed sequence of cash flows
$(c_j)$ at $(t_j)$. It is just a portfolio of zero coupon bonds
and has value
$$
    P_t = \sum_{t_j > t} c_j D_t(t_j)
$$

## Forward Rate Agreements

A _forward rate agreement_ over the interval $[u,v]$ with
_day count convention_ $\delta$ has price $X_0^{F^\delta(u,v)} = 0$
at time $0$ and two cash flows, $C_u^{F^\delta(u,v)} = -1$ at time
$u$ and $C_v^{F^\delta(u,v)} = 1 + \delta(u,v)F^\delta(u,v)$ at time $v$.
The forward rate at time $t$ is the quote that value of the two cash
flows zero:
$$
	F_t^\delta(u,v) = \frac{1}{\delta(u,v)}(D_t(u)/D_t(v) - 1)
$$

There are also FRAs, denoted $\tilde{F}^\delta(u,v),
having only a single cash flow.
The price is zero at time $0$ 
and has cash flow $C^{\tilde{F}^\delta(u,v)}(v)
= \delta(u,v)(\tilde{F}^\delta(u,v) - F_u^\delta(u,v))$
at time $v$.

[Back](xva.html#examples)

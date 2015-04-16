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
The short realized returns determine the dynamics of zero coupon bonds.

Note that in general zero coupons bonds cannot be replicated from short
returns.

## Fixed Income Instruments

A _fixed income instrument_ has a fixed sequence of cash flows
$(c_j)$ at $(t_j)$. It is just a portfolio of zero coupon bonds
and has value
$$
    V_t = \sum_{t_j > t} c_j D_t(t_j)
$$

## Forward Rate Agreements

A _forward rate agreement_ over the interval $[u,v]$ with
_day count convention_ $\delta$ has price $X_0^{F^\delta(u,v)} = 0$
at time $0$ and two cash flows, $C_u^{F^\delta(u,v)} = -1$ at time
$u$ and $C_v^{F^\delta(u,v)} = 1 + \delta(u,v)F^\delta(u,v)$ at time $v$.

The forward rate at time $t$, $F_t^\delta(u,v)$, is defined to be the
rate at which these two cash flows have 0 value at time $t$:
$V_t = 0 = -D_t(u) + (1 + F_t^\delta(u,v))D_t(v)$ hence
$$
	F_t^\delta(u,v) = \frac{1}{\delta(u,v)}(D_t(u)/D_t(v) - 1)
$$

Note $\delta(u,v) F_u^\delta(u,v)\Pi_v|_{\mathscr{A}_u} = (1 - D_u(v))\Pi_u$
since $\delta F_u^\delta = (1/D_u(v) - 1)$ and
$\Pi_v|_{\mathscr{A}_u}$ = $D_u(v)\Pi_u$.

There are also FRAs, denoted $\tilde{F}^\tilde{\delta}(u,v)$,
having only a single cash flow.
The price is zero at time $t$ 
and has cash flow $C^{\tilde{F}^\tilde{\delta}(u,v)}(v)
= \tilde{\delta}(u,v)\tilde{F}_t^\tilde{\delta}(u,v)
- \delta(u,v)F_u^\delta(u,v)$
at time $v$. Using the formula in the previous paragraph
$$
\begin{align*}
(\tilde{\delta}\tilde{F}_t - \delta F_u)\Pi_v|_{\mathscr{A}_t}
&= 
\tilde{\delta}\tilde{F}_t\Pi_v|_{\mathscr{A}_t} 
- \delta F_u\Pi_v|_{\mathscr{A}_u}|_{\mathscr{A}_t}\\
&= 
\tilde{\delta}\tilde{F}_t\Pi_v|_{\mathscr{A}_t} 
- (1 - D_u(v))\Pi_u|_{\mathscr{A}_t}\\
\end{align*}
$$
[Back](xva.html#examples)

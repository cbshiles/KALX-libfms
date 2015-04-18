# Black-Scholes/Merton

Let $(P, C[0, \infty), (\mathscr{F}_t)_{t\ge0})$ be Wiener measure
with the usual filtration and let $(B_t)_{t\ge0}$ be standard
Brownian motion.
The Black-Scholes/Merton model is
$$
X_t = (e^{rt},se^{(r - \sigma^2/2)t + \sigma B_t}),\ C_t = (0,0).
$$
The following lemma shows the deflators $\Pi_t = e^{-rt}P|_{\mathscr{F}_t}$
imply the model is arbitrage free.

__Lemma__. _The process $(M_t)$ is a martingale if and only if
$M_tP|_{\mathscr{F}_t} = M_uP|_{\mathscr{F}_t}$ for $t < u$._

Recall the definition of conditional expectation $E[X|\mathscr{F}] = Y$
if $Y$ is $\mathscr{F}$ measurable and $E[1_AX] = E[1_AY]$ for
all $A\in\mathscr{F}$. This is equivalent to
$XP(A) = YP(A)$ for all $A\in\mathscr{F}$.

The price of an European option is the discounted expected payoff
and the hedge is the standard Black-Scholes delta hedge,
but there is no need for the Ito formula, partial differential
equations, self-financing conditions, or change of measure.
Just write down an arbitrage free model and start pricing.

Another benefit of this approach is that it forces you to realize
continuous time hedging is an insidious myth. After the initial delta
hedge, when do you do your next trade? Classical theory has nothing
to say about this.

[Back](xva.html#examples)

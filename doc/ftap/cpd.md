# Canonical Price Deflators

Consider a multi-period model with trading times
$t_0<t_1<\cdots<t_n$. Assume at each $t_j$, $j<n$, there is
an instrument that pays _short realized return_ $R_j$ over the
interval $[t_j,t_{j+1}]$, where $R_j$ depends only on the
information available at time $t_j$.

The model is $X^{R_j}(t_j,\omega) = 1$ and
$C^{R_j}(t_{j+1},\omega) = R_j(\omega)$.
We make $R_j$ do double duty as a symbol for the instrument and as
a function specifying the cash flow.

Pick an $\Omega$, any $\Omega$, and a probability measure $P$, any $P$,
specify any increasing algebras $(\mathscr{A}_j)$ and define
$\Pi_j = R_0^{-1}\dots R_{j-1}^{-1}P|_{\mathscr{A}_j}$.
Clearly $\Pi_j = R_j\Pi_{j+1}|_{\mathscr{A}_j}$ so the model is
arbitrage free. We call such deflators _canonical_.

I told you it was easy to come up with deflators.

[Back](xva.html#examples)

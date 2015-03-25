# One Period Model

A model specifies how instrument prices can evolve over time. Classical
theory uses the mathematical machinery of probability theory, conditional
expectation, and martingales. Simpler mathematical machinery can do the
same job. In the case of one period models all you need are positive
measures.

## Model

Let $\Omega$ be the set of all possible outcomes over a period,
$x\in\mathbf{R}^m$ the prices of $m$ instruments at the beginning of the
period, and $X\colon\Omega\to\mathbf{R}^m$ the prices at the end of the
period given the outcome $\omega\in\Omega$ occurred.

## Arbitrage

_Arbitrage_ exists if we can find $\gamma\in\mathbf{R}^m$ with
$\gamma\cdot x < 0$ and $\gamma\cdot X\ge0$: you make money putting on
the position at the beginning of the period and do not lose money taking
it off at the end of the period.

The model is arbitrage free if there exists a positive measure $\Pi$
on $\Omega$ with $x = \int_\Omega X\,d\Pi = \langle X,\Pi\rangle$
since $\gamma\cdot X\ge0$ implies $\gamma\cdot x = \langle\gamma\cdot
X,\Pi\rangle\ge0$.  We call such $\Pi$ a _pricing measure_.

## Mathematics

To be precise, let $B(\Omega)$ be the space of _bounded functions_
on $\Omega$. It is a _normed linear space_ with norm
$\|X\| = \sup_\Omega|X|$.
Its [dual space](http://en.wikipedia.org/wiki/Dual_space)
is $B(\Omega)^* = ba(\Omega)$, the space
of _bounded finitely additive measures_. We can also write $\Pi(X) =
\langle X,\Pi\rangle$ since $\Pi\colon B(\Omega)\to\mathbf{R}$ is simply
a linear functional.

## Probability

If $\Pi$ is positive then $E[X] = \Pi(X)/\|\Pi\|$ is the _expected value_
of $X$ under the probability measure $P = \Pi/\|\Pi\|$.

If a bond exists with deterministic _realized return_ $R$ and $\Pi$
is a pricing measure then $1 = \Pi(R) = R\|\Pi\|$ so $\|\Pi\| = 1/R$.
In this case $x = \Pi(X) = E[X]/R$: price is discounted expected value.
A less misleading way of saying this is that the forward price $Rx$
is in the convex hull of the range of $X$.

The FTAP is a theorem about geometry, not probability.

## Pricing
Suppose a derivative security has an initial price $v$ and pays
$V\colon\Omega\to\mathbf{R}$ at the end of the period. The possible
arbitrage free prices are
$$
	v\in\{\langle V,\Pi\rangle : x = \langle X,\Pi\rangle,\,\Pi\ge0\}.
$$
The intersection of a plane and a cone is convex so this set is an
interval contained in $[\inf_\Omega V\|\Pi\|,\sup_\Omega V\|\Pi\|]$.

### Replication and Uniqueness

The derivative can be _replicated_ if there exists
$\gamma\in\mathbf{R}^m$ with $\gamma\cdot X = V$.
For any pricing measure we have $v
= \langle V,\Pi\rangle
= \langle \gamma\cdot X,\Pi\rangle
= \gamma\cdot x$.
In this case $\gamma = \partial\Pi(V)/\partial x$.

If $\Pi$ is unique then $V$ can be replicated.  The linear transformation
$X\colon ba(\Omega)\to\mathbf{R}^m$ given by $\Pi\mapsto\langle X,
\Pi\rangle$ is one-to-one.  This implies $\mathrm{dim}\,ba(\Omega)\le
m$ and the cardinality of $\Omega$ is not greater than $m$. The
linear transformation $\mathbf{R}^m\to B(\Omega)$ given by
$\gamma\mapsto\gamma\cdot X$ is therefore onto, in general.

### Incompleteness

Only toy models are complete. Given any positive measure, $\Pi$,
we can a find $\gamma\in\mathbf{R}^m$ that minimizes
$\Pi (\gamma\cdot X - V)^2$. 

__Exercise__. _Show the solution is $\gamma = \Pi(XX^T)^{-1}\Pi(XV)$_.

<!--|
$$
\partial}\Pi (\gamma\cdot X - V)^2/{\partial\gamma}
= 2\Pi(\gamma\cdot X - V)X = 0
$$
|-->

__Exercise__. _For the two instrument case $x = (1,s)$, $X = (R,S)$
where $R$ is the deterministic realized return show
$\gamma\cdot x = \Pi(V) + \mathrm{Cov}(S,V)/\mathrm{Var}(S)(s - \Pi(S))$_.

This shows that if $\Pi$ is a pricing measure then the least squares
best hedge agrees with the arbitrage free price.

Note that in general it is not the case
$\Pi(X)^T\Pi(XX^T)^{-1}\Pi(XV) = \Pi(V)$.
There are easy counter examples in the $m = 1$ case.

If $X\ge0$ then the least squares deflator gives an arbitrage free price.
This follows from $\Pi(X)^T\Pi(XX^T)^{-1}X\Pi\ge0$.

<!--|
$$\begin{align}
\gamma &=
\begin{bmatrix}
R^2 & R\Pi(S)\\
R\Pi(S) & \Pi(S^2)\\
\end{bmatrix}^{-1}
\begin{bmatrix}
R\Pi(V)\\
\Pi(SV)\\
\end{bmatrix}\\
&= \frac{1}{R^2(\Pi(S^2) - \Pi(S)^2)}
\begin{bmatrix}
\Pi(S^2) & -R\Pi(S)\\
-R\Pi(S) & R^2\\
\end{bmatrix}
\begin{bmatrix}
R\Pi(V)\\
\Pi(SV)\\
\end{bmatrix}\\
&= \frac{1}{R^2(\Pi(S^2) - \Pi(S)^2)}
\begin{bmatrix}
\Pi(S^2) R\Pi(V) - R\Pi(S)\Pi(SV)\\
-R\Pi(S) R\Pi(V) + R^2\Pi(SV)\\
\end{bmatrix}\\
&= \frac{1}{\Pi(S^2) - \Pi(S)^2}
\begin{bmatrix}
(\Pi(S^2) \Pi(V) - \Pi(S)\Pi(SV))/R\\
\Pi(SV) - \Pi(S) \Pi(V)\\
\end{bmatrix}\\
\end{align}$$

Note
$$\begin{align}
\Pi(S^2)\Pi(V) - \Pi(S)\Pi(SV)
&=(\Pi(S)^2 + \mathrm{Var}(S))\Pi(V) - \Pi(S)(\Pi(S)\Pi(V) + \mathrm{Cov}(S,V))\\
&= \mathrm{Var}(S)\Pi(V) - \Pi(S)\mathrm{Cov}(S,V)\\
\end{align}$$
|-->

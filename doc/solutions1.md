_Exercise 1_. The error function is $\mathrm{erf}(x) = c\int_0^x e^{-t^2}\,dt$
with $c$ chosen so that $\lim_{x\to\infty}\mathrm{erf}(x) = 1$.
Use $\int_{-\infty}^\infty e^{-\pi t^2}\,dt = 1$ to find $c$.

_Exercise 2_. The standard normal cumulative distribution is
$N(x)=\int_{-\infty}^x e^{-t^2/2}\,dt/\sqrt{2\pi}$. Express this
in terms of the complementary error function
$\mathrm{erfc}(x) = 1 - \mathrm{erf}(x)$.

_Exercise 3_. If $N$ is a normally distributed random variable
show $Ee^N = e^{E\,N + \mathrm{Var}(N)/2}$.

_Exercise 4_. If $N$ is a normally distributed random variable
show $Ee^N f(N) = Ee^N E f(N + \mathrm{Var}(N))$.

More generally, $Ee^N f(N_1,\dots) = Ee^N E f(N + \mathrm{Cov}(N,N_1),\dots)$
if $N$, $N_1$, \dots are jointly normal.

_Exercise_ 5. If $N$ and $N_1$ are jointly normal
show $EN f(N_1) = EN Ef(N_1) + E f'(N_1)$.
(_Hint_: Take the derivative of $Ee^{aN} f(N_1)$ with respect to $a$.)

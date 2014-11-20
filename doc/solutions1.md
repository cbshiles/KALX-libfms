## Lesson 1 Solutions

_Exercise 1._ The error function is $\mathrm{erf}(x) = c\int_0^x e^{-t^2}\,dt$
 with $c$ chosen so that $\lim_{x\to\infty}\mathrm{erf}(x) = 1$.
 Use $\int_{-\infty}^\infty e^{-\pi t^2}\,dt = 1$ to find $c$.

_Solution 1._ We want $t^2 = \pi u^2$, so $t = u\sqrt{\pi}$ and
 $\int_0^\infty e^{-t^2}\,dt = \int_0^\infty e^{-\pi u^2}\,du\sqrt{\pi}/2$.
 Hence $c = 2/\sqrt{\pi}$.

_Exercise 2._ The standard normal cumulative distribution is
 $N(x)=\int_{-\infty}^x e^{-t^2/2}\,dt/\sqrt{2\pi}$. Express this
 in terms of the complementary error function
 $\mathrm{erfc}(x) = 1 - \mathrm{erf}(x)$.

_Solution 2._ Using $t^2/2 = u^2$, so $t = u\sqrt{2}$ gives

 $$\begin{align}
 N(x) &= 1/2 + \int_0^x e^{-t^2/2}\,dt/\sqrt{2\pi}\
 &= 1/2 + \int_0^{x/\sqrt{2}} e^{-u^2}\,du\sqrt{2}/\sqrt{2\pi}\
 &= 1/2 + \mathrm{erf}(x/\sqrt{2})/2.
 \end{align}$$

 Since $\mathrm{erf(-x)} = -\mathrm{erf(x)}$ we have
 $\mathrm{erfc(-x)} = 1 - \mathrm{erf}(-x) = 1 + \mathrm{erf(x)}$
 so $N(x) = \mathrm{erfc}(-x/\sqrt{2})/2$.

_Exercise 3._ If $N$ is a normally distributed random variable
 show $Ee^N = e^{E\,N + \mathrm{Var}(N)/2}$.

_Solution 3._ We can write $N = \mu + \sigma X$ where $X$ is
 standard normal, $\mu = EX$, $\sigma^2 = \mathrm{Var}(X)$.

 $$\begin{align*}
 Ee^N &= \int_{-\infty}^\infty e^{\mu + \sigma x}e^{-x^2/2}\,dx/\sqrt{2\pi}\
 &= e^\mu \int_{-\infty}^\infty e^{\sigma^2/2}
e^{-(x - \sigma)^2/2}\,dx/\sqrt{2\pi}\\
&= e^\mu e^{\sigma^2/2}\int_{-\infty}^\infty
e^{-x^2/2}\,dx/\sqrt{2\pi}\\
&= e^{\mu + \sigma^2/2}\
 \end{align*}$$

_Exercise 4._ If $N$ is a normally distributed random variable
 show $Ee^N f(N) = Ee^N E f(N + \mathrm{Var}(N))$.

_Solution 4._ Similar to solution 3,

 $$\begin{align}
 Ee^N f(N) &= \int_{-\infty}^\infty e^{\mu + \sigma x}
 f(\mu + \sigma x) e^{-x^2/2} \,dx/\sqrt{2\pi}\
 &= e^\mu e^{\sigma^2/2} \int_{-\infty}^\infty
 f(\mu + \sigma x) e^{-(x - \sigma)^2/2}\,dx/\sqrt{2\pi}\
 &= e^\mu e^{\sigma^2/2} \int_{-\infty}^\infty
 f(\mu + \sigma(x + \sigma) e^{-x^2/2}\,dx/\sqrt{2\pi}\
 &= Ee^N Ef(X + \sigma^2)\
 \end{align}$$

 More generally, $Ee^N f(N_1,\dots) = Ee^N E f(N_1 + \mathrm{Cov}(N,N_1),\dots)$
 if $N$, $N_1$, \dots are jointly normal.

_Exercise 5._ If $N$ and $N_1$ are jointly normal
 show $EN f(N_1) = EN Ef(N_1) + \mathrm{Cov}(N,N_1)E f'(N_1)$.
 (Hint: Take the derivative of $Ee^{aN} f(N_1)$ with respect to $a$.)

_Solution 5._ Since $Ee^{aN} f(N_1) = Ee^{aN} Ef(N_1 + a\mathrm{Cov}(N,N_1))$
 taking a derivative with respect to $a$ gives
 $$
 ENe^{aN}f(N_1) = ENe^{aN} Ef(N_1 + a\mathrm{Cov}(N,N_1))
 Ee^{aN} Ef'(N_1 + a\mathrm{Cov}(N,N_1))\mathrm{Cov(N,N_1)}.
 $$
 Setting $a = 0$ gives the result. 


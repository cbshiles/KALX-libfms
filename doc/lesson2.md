---
title: <a href="index.html">Implementation of Financial Models</a>
...

# Lesson 2

> <i>"The manifest characteristic of (21) is the number of variables that it does not depend on"</i>

Reading: [The Pricing of Options and Corporate Liabilities](http://kalx.net/BlaSch1973.pdf),
[Theory of rational option pricing](http://kalx.net/Mer1973.pdf),
[Black-Scholes/Merton](http://kalx.net/bms.pdf).

## Black-Scholes/Merton

The value of an European put option is $v = e^{-rt}E\max\{k - S_t,0\}$,
where $S_t = se^{rt - \sigma^2t/2 + \sigma B_t}$.
Here, $r$ is the continuously compounded risk-free rate,
$t$ is the time in years to option expiration,
$k$ is the strike of the option,
$s$ is the current stock price,
$\sigma$ is the volatility, 
and $B_t$ is standard Brownian motion.

It is more convenient to work with the Black formula for the forward
value of the option $E\max\{k - F_t,0\}$, where
$F_t = fe^{-\sigma^2t/2 + \sigma B_t}$ and $f = se^{rt}$ is the forward value
of the stock at time $t$.

If $F$ is lognormal, i.e., $F = e^N$ for some normally distributed
random variable $N$, $EF \phi(F) = EF E\phi(Fe^{\mathrm{Var}(\log F)})$,
hence

$$\begin{align*}
E\max\{k - F,0\} &= E(k - F)1(F\le k)\\
 &= kE1(F\le k) - EF E1(Fe^{\sigma^2t}\le k)\\
 &= kP(F\le k) - fP(Fe^{\sigma^2t}\le k).\\
\end{align*}$$

_Exercise 1_. (20 points) Show $F\le k$ if and only if
$B_t/\sqrt{t}\le (\log k/f)/\sigma\sqrt{t} + \sigma\sqrt{t}/2$ and
$Fe^{\sigma^2t}\le k$ if and only if
$B_t/\sqrt{t}\le (\log k/f)/\sigma\sqrt{t} - \sigma\sqrt{t}/2$.

If $F$ is lognormal then $dE\phi(F)/df
= E\phi'(F)e^{-\sigma^2t/2+\sigma B_t}
= E\phi'(Fe^{\sigma^2t})$. Since $d\max\{k - x,0\}/dx = -1(x\le k)$
we have delta is $dE(k - F)^+/df = -P(F^{\sigma^2t}\le k)
= -N((\log k/f)/\sigma\sqrt{t} - \sigma\sqrt{t}/2)$.

From this we get gamma, $d^2E(k - F)^+/df^2
= N'((\log k/f)/\sigma\sqrt{t} - \sigma\sqrt{t}/2)/f\sigma\sqrt{t}$.

_Exercise 2_. (20 points) Show vega
$dE(k-F)^+/d\sigma = ...$.
(Hint: ...)

_Exercise 3_. (20 points) Show theta
$dE(k - F)^+/dt = ...$.

_Exercise 4_. (40 points) Implement the Black greeks i
[black.h]()
and add-ins [xllblack.cpp]()

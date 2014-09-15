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
random variable $N$, $EF \phi(F) = EF E\phi(Fe^{\mathrm{Var}(\log F)})$.

_Exercise 1_. Use this to show
$E\max\{k - F,0\} = kP(F\le k) - fP(Fe^{\sigma^2t}\le k)$.

_Exercise 2_. Show $F\le k$ if and only if
$B_t/\sqrt{t}\le (\log k/f)/\sigma\sqrt{t} + \sigma\sqrt{t}/2$ and
$Fe^{\sigma^2t}\le k$ if and only if
$B_t/\sqrt{t}\le (\log k/f)/sigma\sqrt{t} - \sigma\sqrt{t}/2$.

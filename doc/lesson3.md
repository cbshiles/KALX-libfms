---
title: <a href="index.html">Implementation of Financial Models</a>
...

# Lesson 3

> <i>"I think that object orientedness is almost as much of a hoax as Artificial Intelligence. I have yet to see an interesting piece of code that comes from these OO people."</i>

## Functions

Reading: [An Interview with A. Stepanov](http://www.stepanovpapers.com/LoRusso_Interview.htm)

Complexity is the bane of software engineering and it is best to keep
things simple from the start.  If you can write something as a global
function, do it. If it more than a few lines of code, split it into
two or more global functions. Use simple, descriptive names and C++
namespaces to avoid collisions.

In this lesson we will implement a Black-Scholes/Merton option pricer.
The model is $X_t = (R_t, S_t) = (e^{rt}, se^{(r - \sigma^2/2)t + \sigma B_t})$
where $B_t$ is standard Brownian motion. The deflator is $e^{-rt}P$
where $P$ is Weiner measure. Since $e^{(r - \sigma^2/2)t + \sigma B_t}$
is a martingale, this model is arbitrage free.

A call option with strike $k$ and expiration $t$ has a single cash flow
of $\max\{S_t - k, 0\}$ so the option value is
$E \max\{S_t - k, 0\}e^{-rt}$.

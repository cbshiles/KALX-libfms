# Volatility

The Black-Scholes/Merton model for stock prices is wrong. The data for option prices show the underlying is not constant volatility geometric Brownian motion. Fixing option expiration, the Black-Scholes implied volatility is not flat as a function of strike. Usually it is concave up (_a smile_) and often skewed (_a smirk_). The holy grail of volatility curve building is to find a paramterization such that when fit to a few option prices it automatically fits the remaining option strikes.

## Curve Fitting
Assume a fixed time to expriration, $t$. Given Black-Scholes implied volatilities $\sigma_j$ at strikes $k_j$, find a curve $\sigma_{BS}(k)$ such that $\sigma(k_j) = \sigma_j$. Experience has shown that the _total implied variance_  $w(t) = \sigma_{BS}^2(t)t$ is easier to parameterize and that _moneyness_, $z = \log k/f$, where $f$ is the forward is preferred to working directly with the strike.

## Gatheral Stochastic Volatility Inspired
[Jim Gatheral](http://mfe.baruch.cuny.edu/jgatheral/) has proposed various parameterizations for the Black-Scholes implied volatility smile at a given maturity.  See [Arbitrage-free SVI volatility surfaces](http://papers.ssrn.com/sol3/papers.cfm?abstract_id=2033323) for the latest results.

We propose the parameterization for the total implied variance $w(z) = \sigma^2 + mz + n(\sqrt{z^2 + d^2} - d)$, where $z = \log k/f$ is the moneyness and $\sigma$, $m$, $n$, and $d$ are parameters.

Note $w'(z) = m + nz/\sqrt{z^2 + d^2}$, $w''(z) = nd^2/(z^2 + d^2)^{3/2}$, so $w(0) = sigma^2$, $w'(0) = m$, and $w''(0) = n/d$. Also $w(z) \tilde \sigma^2 + (m + n)z$ as $z\to\infty$ and $w(z) \tilde \sigma^2 + (m - n)z$ as $z\to\infty$. We can use this to find an initial guess for the parameters from the data.


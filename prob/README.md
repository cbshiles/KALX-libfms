# Prob
Probability related functions.
A _random variable_, $X$, is completely determined by its _cumulative distribution function_, $F(x) = P(X\le x)$.
Just like variables we all learned about in high school algebra, a random variable takes the place of a number in equations.
In addition we know the probability of the values it can take. The probability it is in the interval $(a,b]$ is $F(b) - F(a)$.
Every set can be approximated by a disjoint union of intervals, so the distribution function determines that. 
For any (measurable) set $A$, $P(X\in A) = \int_A x\,dF(x)$ using Riemann-Stieltjes integrals.

If $dF(x) = f(x)\,dx$ for some function $f$, then $f$ is the _probability density function_ of $X$.
If $P(X = x) \not= 0$ for some $x$, then it does not have a probability density function.
You might think the converse is true, but you would be [wrong](http://en.wikipedia.org/wiki/Cantor_function). 

In financial mathematics we need the normal distribution. The file `normal.h` implements the `pdf`, `cdf`, and `inv`erse of the cdf.
We use the logistic distribution from `logistic.h` to give an initial guess to the root finding routine for the inverse.
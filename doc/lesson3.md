---
title: <a href="index.html">Implementation of Financial Models</a>
...

# Lesson 3

> <i>"I think that object orientedness is almost as much of a hoax as Artificial Intelligence. I have yet to see an interesting piece of code that comes from these OO people."</i>


Reading: [An Interview with A. Stepanov](http://www.stepanovpapers.com/LoRusso_Interview.htm)

Complexity is the bane of software engineering and it is best to keep
things simple from the start.  If you can write something as a global
function, do it. If it more than a few lines of code, split it into
two or more global functions. Use simple, descriptive names and C++
namespaces to avoid collisions.

## Root Finding

Given a function $f\colon\mathbf{R}\to\mathbf{R}$, a _root_ is a number
$x$ such that $f(x) = 0$. The process of finding a root consists of
starting with an initial guess, improving the guess, then deciding
when the floating point approximation is good enough.

Finding a good initial guess is half the battle. There is no substitute
for knowing things the program doesn't about the function. The first
step is to look at the graph of the function to identify problematic
areas.

If the function can be approximated by a function with a simple inverse,
that can be used to find a first guess. This is the method used for
finding the inverse of the standard normal cumulative distribution,
[fms::prob::normal::inv](http://libfms.codeplex.com/SourceControl/latest#prob/normal.h)

### [root1d.h](http://libfms.codeplex.com/SourceControl/latest#root/root1d.h)

The `fms::root1d` namespace has three sub-namespaces: `step`, `done`, and
`find`. The `step` namespace provides various functions for going from
current guess(es) for roots to a new guess. If you are wondering why
there is an `inverse_quadratic` instead of `quadratic` it is because
the inverse of a quadratic always has a root.

The `done` namespace has various tests for convergence. If you can use
the `done::absolute` criterion, that is preferred. It means you are
within machine precision of the best root estimate. The problem with
using the (seeming) more natural `done::residual` on the value of the
function is that if the slope of the function near the root is
close to zero then you may be quite far from the actual root.

The `find` namespace uses the `step` and `done` functions to iterate
to a solution. Most commercial libraries have general functions with
many parameters that can be used to specify various convergence criteria.
We take the simple and pragmatic approach that always attempts to find
the best solution to machine precision. The routines `find::newton`
and `find::secant` call the corresponding `step` routines. The former
typically converges in 4--5 iterations and the latter in 5--6.
The secant version can be faster because it makes fewer function calls.

# Homework

Due September 29 at 5pm. Late homework will not be accepted.

Pull a fresh copy of [libfms](https://git01.codeplex.com/libfms).

_Exercise 1_. (25 points)
Rewrite the function `OPTION.BLACK.VALUE` in `xllblack.cpp` to
return a one row array of option value, delta, gamma, vega, and theta.
(_Hint_: See the documentation for the
[`FP`](http://xll.codeplex.com/wikipage?title=FP&referringTitle=Documentation)
data type.)

_Exercise 2_. (25 points)
Create a spread sheet that calculates difference quotients to test the
output of the routine in Exercise 1. You should parameterize by the
bump size. Is there an optimal choice for that?

_Exercise 3_. (25 points)
Write the function `fms::option::black::implied_volatility` in `black.h`
to compute the implied volatility. Provide tests to show your
implementation is correct.

_Exercise 4_. (25 points)
Implement `OPTION.BLACK.IMPLIED.VOLATILITY` in `xllblack.cpp`.

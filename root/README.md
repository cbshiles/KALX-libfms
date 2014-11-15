# Root
## Dependencies: none
Root finding.
There is no general routine for finding roots. Knowledge of the function and a good initial guess is essential.

## One Dimensional Root Finding
The file `root1d.h` contains tools for finding roots of a function of one variable.

The namespace `step` contains functions for (hopefully) improving successive estimations.

The namespace `done` provides criteria for terminating a search. The preferred method is `done::absolute` since, ideally, one wants to find the closest representable floating point root. See `xllfms/float` for floating point related functions that can help you understand the difference between the mathematical concept of a real number and the bits used on a computer to represent [them](http://www.cs.berkeley.edu/~wkahan/MathSand.pdf).

The namespace `find` provides three methods of solving for roots: `newton`, `secant`, and `kahan`.
The `newton` method requires the derivative of the function and an initial guess.
The `secant` method does not require the derivative, but it does require two initial guesses.
The `kahan` method is based on the HP solve routine described in [`SOLVEkey.pdf`](https://libfms.codeplex.com/SourceControl/latest#root/SOLVEkey.pdf). It uses the secant method unless the root is bracketed and the next guess would be outside the bracket, in which case it uses bisection.

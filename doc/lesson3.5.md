---
title: <a href="index.html">Implementation of Financial Models</a>
...

# Lesson 3.5

Reading: [C++ is C++](http://xllblog.wordpress.com/2014/10/01/c-is-c/),
[Numerical Derivatives in Scilab](http://forge.scilab.org/index.php/p/docnumder/downloads/get/numericalderivatives-v0.2.pdf)

By Taylor's Theorem we know if $f$ is twice differentiable
$$
\frac{f(x + h) - f(x)}{h} - f'(x) = (1/2)f''(x)h + o(h)
$$
where we are using 
[little o notation](http://xlinux.nist.gov/dads/HTML/littleOnotation.html)


When you calculate $f(x)$ on a computer, you hopefully get the nearest
representable floating point number, $\tilde{f}(x)$.  The maximum error
is therefore $|\tilde{f}(x)/f(x) - 1| \le \epsilon$ where $\epsilon$
is machine epsilon. For calculation purposes, it is convenient to write
this as $\tilde{f}(x) = f(x)(1 + \epsilon_f(x))$ where $|\epsilon_f(x)|\le
\epsilon$.


# Homework 4

_Homework 1_. Show $|(\tilde{f}(x + h) - \tilde{f}(x))/h - f'(x)|
\le (|f(x + h)| + |f(x)|)\epsilon/|h| + (1/2)|f''(x)h|$.
Show the value of $|h|$ that minimizes this expression
is approximately $2\sqrt{|\epsilon f(x)/f''(x)|}$.

<!--
_Solution 1_. The derivative with respect to $|h|$ is
$-(|f(x+h)| + |f(x)|)\epsilon/|h|^2 + (1/2)|f''(x)|$,
hence the optimum value for $|h|$ is approximately $2\sqrt{\epsilon |f(x)/f''(x)|}$.
-->

_Homework 2_. Write a version of `fms::option::black::value` that
uses references instead of pointers. How would you handle optional values?

_Homework 3_. Write a version of `fms::option::black::value` that
returns a `std::tuple` of values. How would you handle optional values?

_Homework 4_. Show how to use
[`std::tie`](http://en.cppreference.com/w/cpp/utility/tuple/tie)
to capture the return values of the
function in homework 3. Can you use `std::ignore` to handle optional values?

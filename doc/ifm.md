# Implementation of Financial Models

<!--rationale
Provide students with skills they can use to be immediately successful.

"The biggest predictor of whether you'll succeed, Laszlo Bock outlines
in 'Work Rules!', is how you fare in a sample work test."

http://www.businessinsider.com/how-google-hires-people-2013-6
http://www.wsj.com/articles/at-google-the-science-of-working-better-1427673486
http://www.wsj.com/articles/book-review-work-rules-by-laszlo-bock-1428361249
http://www.hachettebookgroup.com/titles/laszlo-bock/work-rules/9781455554799/

Understand the mechanics of creating software.
Access and use data availabe from the internet.
Document what you build. Contract between you and client.
Test all software components.
-->

This course will teach you how to design, document, implement, test,
and distribute financial models. We will use C++14 and third party
libraries to create self-contained Excel add-ins.

Instructor
:	Keith A. Lewis [[kal@kalx.net](mailto:kal@kalx.net)] 646 662-7113

Teaching Assistant
:	TBD

Office Hours
:	One hour before class and by appointment

# Grading
Weekly homework assignments (50% with lowest not counted) and a one hour
in class final project (50%). Homework is due at the
beginning of each class. _No late homework will be accepted_.

# Prerequisites

## Courses
(_list of program courses_)

## Lesson 0 (prior to first class)
Create an account using your Cornell
NetID on [codeplex](https://codeplex.com).

Get a Dreamspark license from technology support. (???)

### Windows
Install [Visual Studio 2013, Excel](https://www.dreamspark.com/)
and [the xll library](https://xll.codeplex.com)

### OSX and Linux
Install [VirtualBox](https://www.virtualbox.org/)
and download the virtual machine.

## Lesson 1 (25-Aug-2015) Mechanics
[Clone](http://blogs.msdn.com/b/visualstudioalm/archive/2013/02/06/set-up-connect-and-publish-using-visual-studio-with-git.aspx) [xllgsl](https://xllgsl.codeplex.com)  

This lesson offers a quick review of modern C++ and covers the mechanics of
building software and creating Excel add-ins.

C++
:	[What's new in C++14?](http://herbsutter.com/elements-of-modern-c-style/)
`auto`, lambdas, smart(er) pointers, range based `for` loops, r-value
references, uniform initialization, 

Programming style
:	Use global functions and
[value types](https://akrzemi1.wordpress.com/2012/02/03/value-semantics/).
Lightweight objects.

[Excel Add-ins](https://xll.codeplex.com/wikipage?title=User)
:	The library defines classes and functions that make creating add-ins easy.

-	The [AddIn](http://xll.codeplex.com/wikipage?title=AddInn)
	class tells Excel how to call your C++ code.
-	The [OPER](http://xll.codeplex.com/wikipage?title=OPER)
	class is a variant data type correponding to a cell or range
	of cells in Excel.
-	The [FP](http://xll.codeplex.com/wikipage?title=FP)
	class is a 2-dimensional array of floating point numbers.

_Homework_. Document, implement, and test functions from the GSL library.

_Additional Reading_:
[C++ is C++](http://xllblog.com/2014/10/01/c-is-c/).
[From Mathematics to Generic Programming](http://www.informit.com/articles/article.aspx?p=2314360)

## Lesson 2 (1-Sep-2015) Root Finding and Optimization
Clone [xllfloat](https://xllfloat.codeplex.com)

A common problem is to find where a function is zero or at a
minimum/maximum value.

There is no general method for achieving this.
You have to know something about the function involved,
but the general theme is to find a good initial estimate,
choose a method for improving it, and decide when the
solution is good enough.

Floating Point Numbers
:	IEEE 64-bit model

Improving estimates
:	Bisection, secant, Newton, inverse quadratic

Termination
:	Classical criteria. Best possible solutions.

_Homework_. Root finding

_Reading_. [HP Solve Algorithm]

## Lesson 3 (8-Sep-2015) Building curves
Clone [libfms](https://libfms.codeplex.com)  
Clone [xllinet](https://xllinet.codeplex.com)  

Data sources  
:	getting internet data into Excel
<!--
bbalibor.com is now theice.com/iba/libor
euribor.org
https://research.stlouisfed.org/fred2/release?rid=253
-->

Instruments  
:	cash deposits, forward rate agreements, swaps, OIS

Bootstrapping  
:	build the curve with hedging instruments

Interpolation  
:	interpolate instruments, not curves

_Homework_. Yield curve interpolation.

_Reading_.
[Fixed Income Theory](http://kalx.net/ftap/fit.html) 
[InterestRateInstruments and MarketConventionsGuide](http://www.opengamma.com/sites/default/files/interest-rate-instruments-and-market-conventions.pdf)

## Lesson 4 (22-Sep-2015) Multiple Yield Curves
After 2008, yields that were previously identical began trading at
non-zero spreads. This lesson shows how to use classical theory
to match current market data.

Recovery and Default  
:	Recovery as a fraction of remaining present value
	at default time.

Basis Swaps
:	xEyEn - x month vs. y month over n years

_Homework_.
Fitting market data.

_Reading_.
[Bootstrapping the Illiqidity](http://www.bianchetti.org/finance/bootstrappingtheilliquidity-v1.0.pdf)

## Lesson 5 (29-Sep-2015) LIBOR Market Model
The LMM has parameters that map directly to market data:
futures and at-the-money caplet volatilities.
The correlation parameters preserve the futures and caplet values.

_Homework_. Pricing swaptions.

_Reading_. [LIBOR Market Model](http://kalx.net/lmm.pdf)

## Lesson 6 (6-Oct-2015) Volatility Smiles
Clone [xllgjr](https://xllgjr.codeplex.com)  

One drawback of the LMM is that it cannot fit caplet volatility smiles.
The generalized Jarrow-Rudd model uses pertubation of the cumulants of
the lognormal distribution to achieve smiles, but it turns out it is
better to perturb the cumulants of the normal distribution.

In this lesson we fit eurodollar call and put options.

_Homework_. Fitting market data.

_Reading_. [Normal Jarrow-Rudd](http://kalx.net/njr.pdf)

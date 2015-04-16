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
:	Keith A. Lewis [kal@kalx.net](mailto:kal@kalx.net) 646 662-7113

Teaching Assistant
:	TBD

Office Hours
:	One hour before class and by appointment

# Grading
Weekly homework assignments (50% with lowest not counted) and a one hour
in class final project (50%). Homework is due at the
beginning of each class. _No late homework will be accepted_.

# Prerequisites.

## Courses
_list of program courses_

## Software
- [VirtualBox](https://www.virtualbox.org/)
- [Visual Studio 2013, Excel](https://www.dreamspark.com/)
- [The xll library](https://xll.codeplex.com)

## Lesson 0. (prior to first class)
Create an account on [codeplex](https://codeplex.com)

### Windows
Install Visual Studio 2013, Excel, and the xll library.

### OSX and Linux
Install VirtualBox and download the virtual machine.

## Lesson 1. Mechanics
Clone [xllgsl](https://xllgsl.codeplex.com)  

This lesson covers the mechanics of building software and
creating Excel add-ins.

C++14  

- Value types and functional programming style.
- Lambda expressions, r-value references.
- Smart pointers. `std::unique_ptr` and `std::shared_ptr`

_Homework_. Document, implement, and test functions from the GSL library.

## Lesson 2. Building curves
Clone [libfms](https://libfms.codeplex.com)  
Clone [xllinet](https://xllinet.codeplex.com)  

Data sources  
:	How to get internet data into Excel
<!--
bbalibor.com is now theice.com/iba/libor
euribor.org
https://research.stlouisfed.org/fred2/release?rid=253
-->

Instruments  
:	cash deposits, forward rate agreements, swaps

Bootstrapping  
:	build the curve with hedging instruments

Interpolation  
:	interpolate instruments, not curves

## Lesson 3. Multiple Yield Curves
After 2008, yields that were previously identical began trading at
non-zero spreads. This lesson shows how to use classical theory
to match current market data.

Recovery and Default  
:	Recovery as a fraction of remaining present value and the
	algebra associated with a default time.
Credit Default Swaps  
:	Pay one or more premiums to insure against default.

## Lesson 4. LIBOR Market Model
The mathematical model
Designing the implementation
Testing the components

## Lesson 5. Fixed Income Instruments
Documentation  
SEF's  
CME Eurodollar MID Curve options  
Swaptions  
Using the model for pricing  

## Lesson 6. Volatility Smiles
Clone [xllgjr](https://xllgjr.codeplex.com)  

One drawback of the LMM is that it cannot fit caplet volatility smiles.
The generalized Jarrow-Rudd model uses pertubation of the cumulants of
the lognormal distribution to achieve smiles, but it turns out it is
better to perturb the cumulants of the normal distribution.

In this lesson we fit eurodollar call and put options

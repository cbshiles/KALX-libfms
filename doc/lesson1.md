---
title: <a href="index.html">Implementation of Financial Models</a>
...

# Lesson 1

> <i>"Faire de la bonne cuisine demande un certain temps.
Si on vous fait attendre,
c'est pour mieux vous servir, et vous plaire."</i>

## The software development process

Reading: Chapter 2 of [The Mythical Man Month](http://www.cs.virginia.edu/~evans/greatworks/mythical.pdf),
[The Seven Principles of Software Testing](http://se.ethz.ch/~meyer/publications/testing/principles.pdf),
[Becoming a better programmer](http://www.stroustrup.com/CVu263interview.pdf)
[Floating Point Numbers](http://xllfloat.codeplex.com/)

Financial institutions have many problems to solve and only a small
fraction of those are amenable to mathematical analysis. Getting the math
right takes thought and skill, but that isn't enough. To be useful to
the business line it must be implemented as software they find valuable.

You can increase your value as a quant by understanding how to communicate
effectively with people writing the checks. The first thing to establish
is a common vocabulary. If you don't understand terminology being used
don't be shy about asking, but don't expect it to be explained twice.

After developing a model that the business is (not too un)happy with
you will need to work with the technology group to implement it in their
production systems and perhaps with risk managers to get model approval.

Often the problem you are trying to solve will not be completely
specified. The first step is to write a document describing the problem
and your proposed solution. If you are lucky, the business person you
are working with will read it and work with you to reach a satisfactory
agreement on what needs to be done. At a minimum, it will help *you*
understand the problem domain better.

The next step is to write code and unit tests. There is a vast literature
on this but we will take a pragmatic approach:

- Get the math right first. The easiest bugs to fix are the ones not there.

- Do code reviews. Everybody makes mistakes.

- Testing is not optional. It is tedious, boring, and absolutely essential.

We will use Excel add-ins to present the models we develop. Everyone
knows how to use Excel and it will get you a front row seat with the
business line. They will look at it, tell you what's right, what you
got wrong, and "Oh, yeah. I forgot to tell you I also wanted ..."

Developing software is an iterative process. You should update your
documentation based on feedback, incorporate that into your code, add
more tests, and build a new version of the add-in. Rinse, repeat.

## Mechanics

### Source code control

Learn how to use your tools.
I will assume you know how to `clone` a git repository, `add` new files
you create, `commit` your changes, and how to `push` and `pull` to/from
the git repository.

Read about
[branching and merging](http://git-scm.com/book/en/Git-Branching-Basic-Branching-and-Merging).
You will be merging from `master` to your branch, the opposite of what
you will be doing on the job. Your grade will be based on the work you
do on your branch.

### Compiling C++

There is a reason people like using languages like Matlab or python. 
They are easy to use and forgiving of programming errors. C++ has 
many failure modes. It is a large and complicated language with a lot 
of baggage inherited from C. Fortunately, some of the smartest people
on this planet have been hard at work standardizing new features that
make it possible to get the benefits of C++ without needing to learn
the entire language. 

Using Visual Studio 2013 will make your life easier. View Team Explorer,
Connect, Clone, https://git01.codeplex.com/libfms to any folder. View
Solution Explorer, right click on a project, and build. You will also
need to use Visual Studio to build Excel add-ins.

### The xll Library

See [the xll library](http://xll.codeplex.com/wikipage?title=User)
documentation.

## Floating Point Numbers

The project [xllfloat](http://xllfloat.codeplex.com/)
contains routines for inspecting IEEE 64-bit
floating point numbers. A subset of these have been
included in the `xllfms` Excel add-in project.

# Homework

Due September 15 at 5pm. Late homework will not be accepted. Each
exercise is worth 20 points. Give a mathematicaly convincing argument
for your work.

_Exercise 1_. The error function is $\mathrm{erf}(x) = c\int_0^x e^{-t^2}\,dt$
with $c$ chosen so that $\lim_{x\to\infty}\mathrm{erf}(x) = 1$.
Use $\int_{-\infty}^\infty e^{-\pi t^2}\,dt = 1$ to find $c$.

_Exercise 2_. The standard normal cumulative distribution is
$N(x)=\int_{-\infty}^x e^{-t^2/2}\,dt/\sqrt{2\pi}$. Express this
in terms of the complementary error function
$\mathrm{erfc}(x) = 1 - \mathrm{erf}(x)$.

_Exercise 3_. If $N$ is a normally distributed random variable
show $Ee^N = e^{E\,N + \mathrm{Var}(N)/2}$.

_Exercise 4_. If $N$ is a normally distributed random variable
show $Ee^N f(N) = Ee^N E f(N + \mathrm{Var}(N))$.

More generally, $Ee^N f(N_1,\dots) = Ee^N E f(N_1 + \mathrm{Cov}(N,N_1),\dots)$
if $N$, $N_1$, \dots are jointly normal.

_Exercise_ 5. If $N$ and $N_1$ are jointly normal
show $EN f(N_1) = EN Ef(N_1) + \mathrm{Cov}(N,N_1) E f'(N_1)$.
(_Hint_: Take the derivative of $Ee^{aN} f(N_1)$ with respect to $a$.)

This shows if $N$ and $\log F$ are jointly normal then
$EN g(F) = EN Eg(F) + \mathrm{Cov}(N,\log F) Eg'(F)F$.
The last term can be reduced to $EFg'(F) = EF Eg'(Fe^{\mathrm{Var}(F)})$.

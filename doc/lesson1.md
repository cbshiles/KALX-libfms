---
title: <a href="index.html">Implementation of Financial Models</a>
...

# Lesson 1

> <i>"Faire de la bonne cuisine demande un certain temps.
Si on vous fait attendre,
c'est pour mieux vous servir, et vous plaire."</i>

## The software development process

Reading: Chapter 2 of [The Mythical Man Month](http://www.cs.virginia.edu/~evans/greatworks/mythical.pdf),
[The Seven Principles of Software Testing](http://se.ethz.ch/~meyer/publications/testing/principles.pdf).

Financial institutions have many problems to solve and only a small
fraction of those are amenable to mathematical analyis. Getting the math
right takes thought and skill, but that isn't enough. To be useful to
the business line it must be implemented as software they find valuable.

You can increase your value as a quant by understanding how to communicate
effectively with people writing the checks. The first thing to establish
is a common vocabulary. If you don't understand terminology being used
don't be shy about asking, but don't expect it to be explained twice.

After developing a model that the business is (not too un)happy with
you will need to work with the technology group to implement it in their
production systems and perhaps with risk managers to get model approval.

We will use the term BP to denote a business person, TP for a technology
person, and RM for a risk manager.

Often the problem you are trying to solve will not be completely
specified. The first step is to write a document describing the problem
and your proposed solution. If you are lucky, the BP you are working
with will read it and work with you to reach a satisfactory agreement
on what needs to be done. At a minimum, it will help you understand the
problem domain better. It will also come in handy to wave under your
boss's nose if/when the BP complains about your deliverable.

The next step is to write code and unit tests. There is a vast literature
on this but we take a pragmatic approach:

- Get the math right first. The easiest bugs to fix are the ones not there.

- Do code reviews. Everybody makes mistakes.

- Testing is not optional. It is tedious, boring, and absolutely essential.

We will use Excel add-ins to present the models we develop. Everyone
knows how to use Excel and it will get you a front row seat with
any BP. They will look at it, tell you what's right, what you got
wrong, and "Oh, yeah. I forgot to tell you I also wanted ..."

You probably wont impress any TP's with Excel, but don't underestimate how
grateful a RM might be to get an add-in, spreadsheet, and help file that
can be used to help them solve an immediate problem.

Developing software is an interative process. You should update your
documentation based on feedback, incorporate that into your code, add
more tests, and build a new version of the add-in. Rinse, repeat.

## Mechanics

### Souce code control

Before writing a line of code you first have to understand your tools.

I will assume you know how to `clone` a git repository, `add` new files
you create, `commit` your changes, and how to `push` and `pull` to/from
the git repository.

Read about
[`branch`ing and `merge`ing](http://git-scm.com/book/en/Git-Branching-Basic-Branching-and-Merging)
because you are going to be doing this. A lot. It is easy to mess up
so be sure you understand the workflow.

Create your own branch of the repository.
[Send me](mailto:kal278@cornell.edu?subject=Codeplex%20branch&body=My%20codeplex%20branch%20name%20is:)
the name you choose. Your codeplex id would be a fine choice.
You can add and remove files to your heart's content on your branch without
affecting `master`.

Everyone assumes `master` can be cloned and built cleanly.

### Compiling C++

There is a reason people like using languages like Matlab or python.
They are easy to use and more forgiving of programming errors.  C++ has
many failure modes. It is a large and complicated language with a lot
of baggage inherited from C. Some of the smartest people on this planet
have been hard at work standardizing new features that make it possible
to get the benefits of C++ without needing to learn the entire language.


Using Visual Studio 2013 will make your life easier. View Team Explorer,
Connect, Clone, https://git01.codeplex.com/libfms to any folder. View
Solution Explorer, right click on a project, and build. You will also
need to use Visual Studio if you want to build Excel add-ins.

You are welcome to use any build system you like on unix, but I can
only help you with using command-line tools. A possibility to
consider is running a virtual Windows box so you can also create
add-ins. [!!!instructions on how to do this???]

```
$ cd <directory>
$ git clone https://git01.codeplex.com/libfms
$ cd libfms/src
$ . .fmsrc
$ make
```

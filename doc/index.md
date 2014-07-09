# Implementation of Financial Models

This course will teach you how to use mathematics to model financial
products and implement them using modern C++.

## Prerequisites
Version control is an essential tool for creating software.
Install a [git](http://git-scm.com/) client and read the documentation.

Clone [libfms](http://libfms.codeplex.com) and set up a codeplex
account. Use the [Discussions](http://libfms.codeplex.com/discussions) tab
for any project related questions.

You will need a modern [C++](http://www.isocpp.org/) compiler.

- Windows: [Visual Studio 2013 for Windows](http://www.visualstudio.com/en-us/products/visual-studio-express-vs.aspx)
- Linux: Either [gcc 4.8.3](http://gcc.gnu.org/)
or [llvm 3.4.1](http://llvm.org/)
- OSX: [XCode 5.1](https://developer.apple.com/downloads/) or
[OSX-gcc-installer](https://github.com/kennethreitz/osx-gcc-installer)
(Apple Developer account required.)

For Windows install Excel and the [xll](https://xll.codeplex.com) library.

## Books
No books are required for this course. 

- [A Tour of C++](http:www.stroustrup.com/Tour.html)
is a quick overview of modern C++ at the expert level
- [Programming -- Principles and Practice Using C++](http:www.stroustrup.com/programming.html)
is a beginner level introduction to modern C++.
- [Elements of Modern C++ Style](http://herbsutter.com/elements-of-modern-c-style/)
is a brief online guide.

## Lessons

[Lesson 1](lesson1.html)
  ~ The software development process
[Lesson 2](lesson2.html)
  ~ Functions and add-ins
[Lesson 3](lesson3.html)
  ~ Classes and embedding objects in Excel.
[Lesson 4](lesson4.html)
  ~ Yield curve bootstraping.

use ensure
prefer global functions
locality
use value types

portfolio: document
http://www.youtube.com/watch?v=vxv74Mjt9_0&index=10&list=PLHxtyCq_WDLXFAEA-lYoRNQIezL_vaSX-

value(instrument, model, implementation)

template<class I, class J>
class pwf {
	I b, e; // sorted
	J x;
};

template<class I, class J>
I::value pwf::value(typename J::value_type t, const pwf<I,J>& c,
	bool extrapolate = false)
{
	I i = lower_bound(c.b, c.e, t);
	if (i == c.e) {
		ensure (extrapolate);

		return *advance(c.x, distance(c.b, c.e) - 1);
	}

	return *advance(c.x, i - c.b);
}

pwf::integral(t, bf, ef)

pair<FI,FI> bootstrap(

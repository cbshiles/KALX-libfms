# Implementation of Financial Models

This course will teach you how to use mathematics to model financial
knowledge and produce high quality software. We will be using modern
C++ to write portable code and Excel add-ins to access to the models.
[access, make available, reveal,...]

## Prerequisites
A [git](http://git-scm.com/) client. Read the documentation.
Clone [libfms](http://libfms.codeplex.com).
Install a modern [C++](http://www.isocpp.org/) compiler.

- Windows: [Visual Studio 2013 for Windows]
(http://www.visualstudio.com/en-us/products/visual-studio-express-vs.aspx)
- Linux: Either [gcc] or [llvm]
- OSX: Either [XCode 5.1](https://developer.apple.com/downloads/) or
[OSX-gcc-installer](https://github.com/kennethreitz/osx-gcc-installer)

## Lectures

[Lecture 1](lecture1.html)
  ~ The software development process
[Lecture 2](lecture2.html)
  ~ Functions and add-ins
[Lecture 3](lecture3.html)
  ~ Classes and embedding objects in Excel.
[Lecture 4](lecture4.html)
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

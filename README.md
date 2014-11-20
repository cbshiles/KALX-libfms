# libfms
## Finance, Mathematics, and Software

Mathematics can be used to model aspects of the financial world, but the math has to be implemented on a computer to be useful.

This library uses modern C++ to provide a foundation for solving real-world financial problems. It is not designed to be comprehensive, the intent is to provide tools that can be composed to solve more complicated and interesting problems. Existing libraries were not written with an eye toward the coming revolution in [multicore processing](http://www.gotw.ca/publications/concurrency-ddj.htm).

Two things are clear about how to leverage off of however the silicon dust settles: write functions and use [value types](http://msdn.microsoft.com/en-us/library/hh438479.aspx). Functions have no side effects so they are [thread-safe](http://en.wikipedia.org/wiki/Thread_safety). Value types keep data local. Both make it easier to reason about code correctness and can be used as components for concurrent processing. The C++ tradition has always been about getting the most out of the latest hardware. Computers are evolving from the pervasive effect John [von Neumann](http://en.wikipedia.org/wiki/Von_Neumann_architecture) had on computing to a new world where quantity will have a profound qualitative effect on previously intractable problems.

### Get the Source
Run Visual Studio 2013. Use [git](http://msdn.microsoft.com/en-us/library/hh850437.aspx) to clone:
*  the [xll8](http://xll8.codeplex.com/SourceControl/latest) library.
*  [libfms] https://libfms.codeplex.com/SourceControl/
Open `libfms` and build the project `xllfms`.

### Library Organization
The project `xllfms` consists of Excel add-in functions that call platform-independent code in other projects. The `AddInX` class specifies how to hook up Excel to C++. The function you tell Excel to call takes data from Excel, calls C++, and return a result. Functional languages are all the rage these days, but spreadsheets have been purely functional since [VisiCalc](http://www.bricklin.com/firstspreadsheetquestion.htm).
All of the other projects are "header only". Just `#include` what you need and start using them. The _project_`.cpp` file calls the test routines at the bottom of each header file. No need for a unit testing framework, C++ is sufficiently expressive without introducing another dependency.

[root](root/README.md) - root finding
[prob](prob/README.md) - probability related function
[option](option/README.md) - option pricing
[datetime](datetime/README.md) - date and time routines
[curve](curve/README.md) - piece-wise flat forward curve bootstrap
[instrument](instrument/README.md) - fixed income instruments

## Remarks

prob not converging

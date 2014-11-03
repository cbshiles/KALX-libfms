# libfms
## Finance, Mathematics, and Software

Mathematics can be used to model aspects of the financial world, but the math has to be implimented on a computer to be useful.

This library uses modern C++ to provide a foundation for solving real-world financial problems. It is not designed to be comprehensive, the intent is to provide tools that can be composed to solve more complicated and interesting problems. Existing libraries were not written with an eye toward the coming revolution in [multicore processing](http://www.gotw.ca/publications/concurrency-ddj.htm).

Two things are clear about how to leverage off of however the silicon dust settles: write functions and use value types. Functions have no side effects. Value types keep data local. Both make it easier to reason about code correctness and can be used as components for concurrend processing. The C++ tradition has always been about getting the most out of the latest hardware. Computers are evolving from the profound and pervasive effect John [von Neumann](http://en.wikipedia.org/wiki/Von_Neumann_architecture) had on computing. It's about time.

### Get the Source
Run Visual Studio 2013. Use [git](http://msdn.microsoft.com/en-us/library/hh850437.aspx) to clone:
*  the [xll8](http://xll8.codeplex.com/SourceControl/latest) library.
*  [libfms] https://libfms.codeplex.com/SourceControl/latest#README.md
Open `libfms` and build the project `xllfms`.

### Library Organization
Projects are header only files. Each project has a `.cpp` file with the project name. It calls test routines that are defined in each header.
The project `xllfms` consists of Excel add-in functions that call the platform-indepenent code in other projects.

[root](root/README.md) - root finding
[prob](prob/README.md) - probability related functions
[option](option/README.md) - option pricing
[datetime](datetime/README.md) - date and time routines
[curve](curve/README.md) - piecewise flat forward curve bootstrap
[instrument](instrument/README.md) - fixed income instruments

## Remarks

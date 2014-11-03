# libfms
## Finance, Mathematics, and Software

Mathematics can be used to model aspects of the financial world, but the math has to be implimented on a computer to be useful.

This library uses modern C++ to provide a foundation for solving real-world financial problems. It is not designed to be comprehensive, the intent is to provide tools that can be composed to solve more complicated and interesting problems. Existing libraries were not written with an eye toward the coming revolution in [multicore processing](http://www.gotw.ca/publications/concurrency-ddj.htm).

Two things are clear about how to leverage off of however the silicon dust settles with this: write functions and use value types. Functions have no side effects. Value types keep data local. The C++ tradition has always been about getting the most out of the latest hardware. It is evolving from the profound and pervasive effect John von Neumann had on computing. [von Neumann architecture](http://en.wikipedia.org/wiki/Von_Neumann_architecture). 

[root](root/README.md) - root finding
[prob](prob/README.md) - probability related functions
[option](option/README.md) - option pricing
[datetime](datetime/README.md) - date and time routines
[curve](curve/README.md) - piecewise flat forward curve bootstrap
[instrument](instrument/README.md) - fixed income instruments
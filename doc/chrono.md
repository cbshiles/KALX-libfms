Notes on `<chrono>`
==================
C++ 2011 introduced `<chrono>` for dealing with `clocks`, `time_points`'s
and `duration`'s. It is not a replacement for `<ctime>` but there is
some overlap.

Computers are going to keep getting faster and programmers need facilities
to take advantage of that.  A _`duration`_ is parameterized by the data
type used to represent it and a period. The value of the data type is
given by the member function `count()`. The period is in units of seconds
expressed as a `std::ratio`, an artifact of `time_t` traditionally being
time in seconds since unix epoch: midnight 1970-01-01. The duration is
the count times ratio in seconds.

It is a good approximation to think of a `std::ratio` as a rational
number. The ratio is determined by template parameters
`ratio<a,b>`. The members `num` and `den` are generated at
compile time by meta template magic (the good kind) and are
guaranteed to satisfy `den > 0` and the greatest common
factor of `num` and `den` is 1. There are classes `ratio_add`
for addition and likewise for `ratio_subtract`, `ratio_multiply`,
and `ratio_divide`.

You can add two `duration`s to get a new duration. The count
is the sum of the counts.

There are three standard clocks in the `std::chrono` namespace:
`system_clock`, `steady_clock`, and `high_resolution_clock`.  All clocks
implement `now()` that returns a _`time_point`_ representing the current
time. Only `system_clock` implements `to_time_t` and `from_time_t`. The
usual implementation is `to_time_t()` returns `time(0)` from `<ctime>`.
Recall `time_t` is typically time in seconds from unix epoch: midnight
1970-01-01.

Every clock is free to define its own epoch and `time_point`s
are 
If count is an integral value the calculations are exact.
If count is a floating point value things are more complicated.

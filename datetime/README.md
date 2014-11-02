# Datetime
Date and time routines.
The `datetime::date` class uses [`time_t`](http://en.cppreference.com/w/cpp/chrono/c/time_t) to store dates in [ Coordinated UniversalTime](http://en.wikipedia.org/wiki/Coordinated_Universal_Time) (aka UTC, GMT, and Zulu).
When creating a date the local lime is converted to UTC based on time zone and daylight savings of the program using the date. Client programs are responsible for converting from UTC to local (wall clock) time.

The file `dt.h` defines constants and lightweight functions for converting between Excel serial dates and `time_t`.
The file `datetime.h' defines the `date` class. It uses `time_t` to represent dates. In addition to the usual date functions it provides member functions for financial calculations such as holiday calendars and rolling conventions.
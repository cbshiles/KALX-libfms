# Datetime
Date and time routines.
The `datetime::date` class uses [`time_t`](http://???) to store dates in [Universal Coordinated Tim(http://???) (aka UTC, GMT, and Zulu).
When creating a date the local lime is converted to UTC based on time zone and daylight savings of the program using the date.
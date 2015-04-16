/*
Under which market convention are Euribor rates quoted ?

1)Which is the market convention under which the Euribor rates are quoted, i.e. what happens if a specific maturity falls on a non-business day?
If the maturity date of a trade falls on a non-business day, the maturity date shall be moved to the next business day. 

2) Are there any exceptions to the above rule?

The exception to this will be the end-end quotes or quotes for 1,2,3 ... months where the value date of the trade falls at month-end. If the corresponding maturity date falls on a non-business day, the maturity date will be brought back to the last business day of that month.
A 1 week quote, or 2 and 3 weeks, will always be for a period of seven days or more (or 14 or 21 resp). If the maturity date falls on a non-business day, the maturity date should be moved to the next business day, regardless of what calendar month it falls in. Anything less than this should not be termed 1,2 or 3 weeks but becomes a broken-dated short date quote.

3)What is the current market convention used for quotes at the end of the month, i.e. is the Euribor 1 month quote for 28 February intended for a M/M depo maturing on 28 March or on 31 March (assuming obviously they are business days)?
In line with 2) above the maturity date for this will be 31 March and not 28 March. 
*/

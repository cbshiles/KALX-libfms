% UNIFIED DERIVATIVES
% Keith A. Lewis
% KALX, LLC

# Background

Before learning about derivative securities you need to know something
about the primary securities they are based on, who the market
participants are, what kinds of securities are traded, the markets
available for trading, and the motivations of the participants.

The name _derivative securities_ is a bit misleading. A derivative is
quite different from a security like a currency, stock, or bond. If you
stuff a deriviative under your mattress it will eventually be worthless.
Derivatives don't provide equity in a company that allows you to influence
decisions on how it is run. If your counterparty goes bankrupt there
is no preferred treatment on the assets of the company like what bond
holders receive.

> A derivative is a legal contract between two counterparties for
> future exchanges of things of value.

Every financial _transaction_ is the exchange at some point in time of
some quantity of a security for a quantity of another security between
two counterparties. Usually one of the securities is the currency of
the country you live in.

Owning a security involves cash flows. In the spot foreign exchange
market you get paid the difference between the rates of interest in the
currency pairs you hold each day, stocks pay dividends on dividend dates,
bonds pay coupons on a regular schedule.  It is important to distinguish
the price of an instrument from the cash flows associated with owning it.

## Participants

Every transaction has a buyer and a seller. Don't confuse these nouns with
the verbs buy and sell. The buyer always decides whether or not to buy
or sell based on the prices offered by a seller. A buyer can also decide
to go long or short. If a buyer goes long it means they own something
that they believe increases in value if the market goes up. If a buyer
goes short, they believe they make money if the market goes down. Prices
are determined by the market. The value of a transaction is usually a
subjective judgement made by a buyer, but models can be used to make
this more objective.

You can already figure out what _buy side_/_sell side_ means. These are also
referred to as _retail/wholesale_ (?) and price _taker/maker_.

Sellers make a market for buyers. They provide prices for buyers who
decide to buy at the ask, or sell at the bid. The ask price is also
called the offer, but the seller is not really offering anything other
than to allow the buyer to transact. The price also depends on the
amount being transacted and who the buyer and seller are. Markets are
never perfectly liquid, something the classical theory of mathematical
finance likes to assume. Sellers make their living off of this asymmetry,
among other things.

There are also exchanges and broker-dealers that facilitate trading. They
act as both buyers and sellers to facilitate transactions. Exchanges
provide their customers access to liquidity providers. The exchange
aggregates these quotes and show their customers the best bid/ask spread
currently available. Broker-dealers provide a similar service but often
hold an inventory of trades when they can't match a buyer and a seller
or want to trade their own account. Exchanges make money proportional
to the volume of trades whereas broker-dealers are can take advantage
of market movements instead of making money only on the spread. Or take
a hit on market movements. Unlike broker-dealers, no exchange has every
gone bankrupt.

## Securities

Securities are currencies, bonds, stocks, mortgages, and
commodities. Stocks are called equity because they entail partial
ownership in a company. Owning stock gives you some say in how the company
is run. Bonds are called debt because the company issuing the bond is
on the hook to pay it back. If a company defaults, the bond holders
are first in line and the stock holders get what is left over. Bonds
are also called fixed-income instruments since they usually pay a fixed
coupon. This is not the only example of historical terminology being a
hindrance to a unified understanding of financial products.

## Cash Flows

Owning a security involves cash flows. Exchanging currencies involves
the difference between the interest rates (roll), bonds pay coupons
and principal, stocks pay dividends if long or may require carry if
short. Mortgages can't be shorted and pay interest and potentially early
principal. Commodities require storage costs.

Primary securities can be bundled, or repackaged into mutual funds,
mortgage-backed securities, exchange traded funds, special purpose
vehicles and an assortment of other securities. Often the purpose is to
take advantage of tax, accounting, or regulatory considerations. Something
we will assiduously avoid considering, as does most of the mathematical
finance literature, even though these are a very important component of
the financial world.

## Derivatives

A derivative security is a contract between a buyer and a seller for a
sequence of exchanges of other securities. The most common are futures,
forwards, and options. The following chapters will show in detail how
these are the building blocks of all derivative securities. One example
are swaps. They are just a portfolio of forward contracts.

## Markets

Immediate transactions are called spot (or cash) trades. These can be
exchange traded or over-the-counter.

Exchanges provide nearly instantaneous access to transactions via market
orders. The price cannot be guaranteed by the exchange. It depends on
the current order book and other market orders that might get placed
before yours.

The order book consists of limit orders. A limit order is a way for
buyers to act like sellers. You can offer to buy or sell some quantity
of an instrument at a price.  If the market moves to the level you offer,
then you can acquire or relinquish the underlying at the price you set.

OTC transaction are done directly between two counterparties and involve
machinery more complicated than setting up a margin account with an
exchange. A single trade can take weeks or months of negotiation
and involve setting up collateral agreements in place of margin
accounts. Exchanges provide a fixed menu of trades, the value added by
what used to be called investment banks are custom tailored trades.

Now we have Swap Execution Facilities (SEF) that are similar to exchanges
that trade interest rate swaps. They were created to streamline OTC
transactions for vanilla swaps.

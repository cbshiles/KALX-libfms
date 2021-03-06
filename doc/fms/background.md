% UNIFIED DERIVATIVES
% Keith A. Lewis
% KALX, LLC

# Background

Before learning about derivative securities you need to know something
about who the market participants are,
the primary securities they are based on,
and the markets available for trading.

The name _derivative securities_ is a bit misleading. A derivative is
quite different from a security like a stock, bond, or currency. If
you stuff a deriviative under your mattress it will eventually be
worthless.  Derivatives don't provide equity in a company that allows
you to influence decisions on how it is run. If a company goes bankrupt
there is no preferred treatment on the assets of the company that bond
holders receive. Currencies are a very different creature that big
banks control access to. 

> _A derivative is a legal contract between two counterparties for
> future exchanges of cash flows._

Owning a security involves cash flows.
Stocks pay dividends.
Bonds pay coupons on a regular schedule and principal at maturity.
In the spot foreign exchange market you get paid the difference between
the rates of interest in the currency pairs you hold each day.

Derivatives use market traded securities to manufacture arbitrary cash
flow streams. There is a mathematical theory that can be used to determine
the trades required to do so. As with any theory, it has assumptions
that hold to greater or lesser degree.

It is important to distinguish the _price_ of an instrument from the
cash flows associated with owning it. Market traded instruments have
prices. There is a mathematial theory that can provide a _value_
for a derivative instrument given the cash flows specified in a contract.

The value a model provides is not a price.
It is used for pricing derivatives, and people do transactions based
on that, but one of
the serious shortcomings of the theory is that it does not provide a
good measure of how accuate the value is. Risk management of that
uncertainty is still in it's early stages.

## Participants

Every transaction has a _buyer_ and a _seller_.  Don't confuse these
nouns with the verbs buy and sell. The buyer always decides whether
or not to buy or sell based on the prices offered by a seller. A buyer
can also decide to go _long_ or _short_. If a buyer goes long it means
they own something that they believe increases in value if the market
goes up. If a buyer goes short, they believe they make money if the
market goes down. Prices are determined by the market. The value of a
transaction is a subjective judgement made by a buyer, but models can
be used to make this more objective.

You can already figure out what _buy side_/_sell side_ means. These are also
referred to as price _taker/maker_.

Sellers make a market for buyers. They provide prices for buyers who
decide to buy at the ask, or sell at the bid. The ask price is also
called the offer, but the seller is not really offering anything other
than to allow the buyer to transact. The price also depends on the
amount being transacted and who the buyer and seller are. Markets are
never perfectly liquid, something the classical theory of mathematical
finance likes to assume. Sellers make their living off of this asymmetry,
among other things.

There are also _exchanges_ and _broker-dealers_ that facilitate
trading. They act as both buyers and sellers to provide _liquidity_.
The exchange aggregates quotes and shows their customers the best
bid/ask spread currently available. They take a fraction of that
spread and make their money based on the _volume_ of trades.
Broker-dealers provide a similar service but often hold an inventory of
trades when they can't match a buyer and a seller or want to trade their
own account.  Broker-dealers can take advantage of market movements
instead of making money only on the spread. Or take a hit on market
movements. Unlike broker-dealers, no exchange has every gone bankrupt.

## Securities

There are many more securities than just currencies, bonds, and stocks.
Commodities are also securities and futures are derivatives that allow
speculators to reduce the risk producers faced.  Convertible bonds start
out as bonds but contain a provision allowing the holder to convert
them into shares of stock.  Mortgage backed securities have cash
flows determined by the interest and principal paid on a collection
of mortgages. Credit default swaps provide insurance in the event a
company defaults.

There are even securities that are based on the weather or future earnings
of celebrities like
[David Bowie](view-source:http://en.wikipedia.org/wiki/Celebrity_bond#Bowie_Bonds).
The mathematical theory behind valuing
these products is not up to the inventivness of those trying to make a
buck off of people who have money but don't really understand what they
are buying.

<!--|

### Currencies

### Stocks
Stocks are called equity because they entail partial ownership in a
company. Owning stock gives you some say in how the company is run.

### Bonds
Bonds
are called debt because the company issuing the bond is on the hook
to pay it back. If a company defaults, the bond holders are first in
line and the stock holders get what is left over. Bonds are also called
fixed-income instruments since they usually pay a fixed coupon. This is
not the only example of historical terminology being a hindrance to a
unified understanding of financial products.
## Cash Flows

Owning a security involves cash flows.

Exchanging currencies involves the _roll_, the difference between the
interest rates. If another country has a higher interest rate you can
exchange your currency and get paid that rate less your rate. If exchange
rates stay constant, you could convert back and make the difference
over that period of time. But exchange rates change.

Stocks pay dividends. Usually. Some tech stocks pay no dividends because
investors believe their price will grow 

Bonds pay coupons and principal,
Mortgages can't be shorted and pay interest and potentially early
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

|-->

## Markets

Exchanges provide nearly instantaneous access to transactions via _market
orders_. The price cannot be guaranteed by the exchange.  You get _filled_
depending on the _limit orders_ in the current _order book_.

A limit order is a way for buyers to act like sellers. You can offer to
buy or sell some quantity of an instrument at a price.  If the market
moves to the level you offer, then you can get filled at the price you
set. But that might never happen.

Opening an account on an exchange involve giving them _margin_.  If the
exchange sells you a _futures_ the price and cash flow associated
with entering the contract is zero. In fact, the price of a futures is
always zero.  Your margin account is adjusted each day with the change
in the price of the underlying times then number of contracts you hold.
If your margin goes to zero you get a _margin call_. If you cannot supply
that, the exchange takes you out of your contracts and keeps your margin.

OTC transaction are done between two counterparties and involve machinery
more complicated than setting up a margin account with an exchange. A
single trade can take weeks or months of negotiation and involve setting
_collateral agreements_ in place of margin accounts. Exchanges provide a
fixed menu of trades, the value added by what used to be called investment
banks are custom tailored trades.

New ways of trading are continually invented.  Dark pools are markets with
limited access to enable large trades to occur without the price movements
that would otherwise happen if traded on an exchange.
Swap Execution Facilities (SEF) are similar to exchanges for interest
rate swaps. They help standardize OTC trades and provide centralized
_clearing_ to mitigate counterparty risk. There are many more
examples.

The mathematical models and software implementations are always far
behind the inventiveness of the financial world. Even the simple models
currently used do not have a well developed theory for managing risk and
the implementations do not permit correlations between different markets.
These are difficult problems that this note will make a first stab at
addressing.

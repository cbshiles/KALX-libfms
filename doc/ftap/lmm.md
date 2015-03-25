# The LIBOR Market Model

Let $r_t$ be the _short rate_, $1\mapsto \exp(r_t,\dt)$ over $[t,t+dt]$.

$D(0,t) = Ee^{-\int_0^t} r_s\,ds}$ is the _discount_ to time $t$.

The _forward rate_, $f(t)$, is defined by $D(0,t) = e^{-\int_0^t f(s)\,ds}$. 

Let $\phi_t = E[r_t]$ be the _futures rate_.

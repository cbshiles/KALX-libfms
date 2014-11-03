# Option
## Dependencies: prob root
The Fischer Black forward value of an European put option with strike $k$ expiring at $t$ is $E\max\{k - F_t, 0\}$,
where $F_t = fe^{-\sigma^2t/2 + \sigma B_t}$, $f$ is the forward, and $B_t$ is Brownian motion.
Using $Ee^N = e^{EN + \Var(N)/2}$ and $Ee^N f(N) Ee^N E f(N + \Var N)$ when $N$ is normally distributed we have

  $E\max\{k - F_t, 0\} = E(k - F_t)1(F_t\le k) = kP(F_t \le k) - fP(F_te^{\sigma^2t} \le k)$.

  Note $F_t \le k$ iff $B_t/\sqrt{t} \le \log(k/f)/\sigma\sqrt{t} + \sigma\sqrt{t}/2$.
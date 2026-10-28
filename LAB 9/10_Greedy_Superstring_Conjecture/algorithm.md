# Question 10: Greedy Superstring Conjecture Simulation and Analysis

## Problem Statement
Given a set of $N$ strings $\mathcal{S} = \{s_1, s_2, \dots, s_N\}$, find the shortest common superstring $\mathcal{T}$ that contains every $s_i \in \mathcal{S}$ as a substring. (We assume without loss of generality that no string is already a proper substring of another).

---

## Greedy Superstring Approximation Algorithm

### 1. Conceptual Principle
Finding the absolute Shortest Common Superstring (SCS) is NP-hard and MAX-SNP-hard. The classical **Greedy Heuristic** operates by greedily maximizing the overlap between pairs of strings:
- Given two strings $s_i$ and $s_j$, their overlap $\text{ov}(s_i, s_j)$ is the length of the longest proper suffix of $s_i$ that matches a proper prefix of $s_j$.
- In each round, the pair $(s_i, s_j)$ with the maximum overlap $\text{ov}(s_i, s_j)$ is merged into a single composite string $s_i \circ s_j$ of length $|s_i| + |s_j| - \text{ov}(s_i, s_j)$.
- This process repeats until only one superstring remains.

### 2. The 2-Conjecture and Recent Breakthrough
- **The Conjecture (Blum et al., 1991)**: For decades, it was conjectured that the greedy superstring heuristic always achieves an approximation ratio of at most $2$:
$$\frac{|\text{Greedy}(\mathcal{S})|}{|\text{OPT}(\mathcal{S})|} \le 2$$
- In landmark theoretical results (Blum et al. 1994, Teng & Yao 1997, Paluch 2014), upper bounds of $4$, $3.5$, and $2.5$ were proven.
- **Recent September 2026 Breakthrough**: Researchers disproved the strict 2-conjecture by constructing an intricate family of counterexample string sets that force the greedy heuristic into suboptimal overlap cascades, yielding an asymptotic approximation ratio of $\ge 2.25$.

---

## Pseudocode

```text
Algorithm GreedySuperstring(S, N):
    Input: Set of N strings S = {s_1, s_2, ..., s_N}
    Output: Shortest merged superstring

    While size(S) > 1:
        max_overlap = -1
        best_i = -1, best_j = -1

        For each pair (u, v) in S with u != v:
            val = ComputeOverlap(u, v)
            If val > max_overlap:
                max_overlap = val
                best_u = u, best_v = v

        merged = best_u + best_v[max_overlap:]
        Remove best_u and best_v from S
        Insert merged into S

    Return the single remaining string in S
```

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(N^3 \cdot L^2)$ naive / $\mathcal{O}(N^2 L)$ with Aho-Corasick or KMP | $N - 1$ merge rounds, evaluating $\mathcal{O}(N^2)$ candidate pairs with prefix-suffix matching on strings of length up to $L$. |
| **Auxiliary Space** | $\mathcal{O}(N \cdot L)$ | Memory required to store the dynamic list of merged superstrings. |

# Question 2: Coin Change - Total Number of Ways

## Problem Statement
Given an array of distinct positive integers representing coin denominations $C = \{c_1, c_2, \dots, c_n\}$ and a target amount $V$, find the total number of distinct combinations of coins that sum up to $V$. You may assume an infinite supply of each coin denomination. The order of coins does not matter (e.g., $1 + 2$ and $2 + 1$ are considered the same combination).

---

## Dynamic Programming Formulation

### State Definition
Let $dp[v]$ denote the total number of distinct combinations of coins that sum to amount $v$, for $0 \le v \le V$.

### Base Case
- $dp[0] = 1$ (There is exactly 1 way to make amount 0: by choosing zero coins).
- $dp[v] = 0$ for $1 \le v \le V$.

### Recurrence Relation
To avoid counting permutations of the same set of coins in different orders (e.g., $(1, 2)$ vs $(2, 1)$), the outer loop iterates over each coin denomination $c \in C$, and the inner loop updates amounts $v$ from $c$ to $V$:
$$dp[v] = dp[v] + dp[v - c] \quad \text{for } c \le v \le V$$

---

## Pseudocode

```text
Algorithm CoinChangeTotalWays(C, n, V):
    Input: Array C of n distinct coin denominations, target amount V
    Output: Total number of distinct coin combinations

    Initialize array dp[0..V] with 0
    dp[0] = 1

    For i = 0 to n - 1:
        coin = C[i]
        For v = coin to V:
            dp[v] = dp[v] + dp[v - coin]

    Return dp[V]
```

---

## Correctness & Combination Property
- **Why Combinations instead of Permutations?**:
  Processing coins one by one in the outer loop ensures that all instances of coin $c_1$ are chosen before considering coin $c_2$, which in turn are chosen before coin $c_3$, etc. Thus, coins appear in a fixed canonical order, preventing distinct orderings like $1+2$ and $2+1$ from being counted multiple times.
- **Unbounded Supply**:
  Iterating $v$ from $coin$ upwards to $V$ allows coin $c$ to be used multiple times (as $dp[v - coin]$ already includes combinations using coin $c$).

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(n \cdot V)$ | Nested loop: $n$ coin types $\times$ amount range up to $V$. |
| **Auxiliary Space** | $\mathcal{O}(V)$ | Single 1D array of size $V + 1$ (space-optimized from 2D DP). |

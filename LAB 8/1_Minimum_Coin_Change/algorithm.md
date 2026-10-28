# Question 1: Minimum Coin Change Problem

## Problem Statement
Given an integer array of coin denominations $C = \{c_1, c_2, \dots, c_n\}$ representing coins of different values, and an integer target amount $V$, find the minimum number of coins needed to make up that amount. You may assume an infinite supply of each coin denomination. If that amount of money cannot be made up by any combination of the coins, return $-1$.

---

## Dynamic Programming Formulation

### State Definition
Let $dp[v]$ be the minimum number of coins required to make up amount $v$, where $0 \le v \le V$.

### Base Cases
- $dp[0] = 0$ (Zero coins needed for amount 0).
- $dp[v] = \infty$ for all $1 \le v \le V$ (initially unreachable).

### Recurrence Relation
For each amount $v$ from $1$ to $V$:
$$dp[v] = \min_{\substack{c \in C \\ c \le v}} \left\{ dp[v - c] + 1 \right\}$$

### Reconstruction of Optimal Coins
To reconstruct the coins chosen, maintain an array `parent[v]` storing the coin $c$ that achieved the minimum $dp[v]$. Tracing backwards from $V$ using `parent[v]` gives the exact coins used.

---

## Pseudocode

```text
Algorithm MinCoinChange(C, n, V):
    Input: Array C of n coin denominations, target amount V
    Output: Minimum coin count and reconstructed coin list

    Initialize dp[0..V] with INFINITY
    Initialize parent[0..V] with -1
    dp[0] = 0

    For v = 1 to V:
        For i = 0 to n - 1:
            If C[i] <= v and dp[v - C[i]] != INFINITY:
                If dp[v - C[i]] + 1 < dp[v]:
                    dp[v] = dp[v - C[i]] + 1
                    parent[v] = C[i]

    If dp[V] == INFINITY:
        Return -1

    // Reconstruct coins
    curr = V
    coins_used = []
    While curr > 0:
        coins_used.append(parent[curr])
        curr = curr - parent[curr]

    Return dp[V], coins_used
```

---

## Correctness Proof
- **Optimal Substructure**: The optimal solution to making change for amount $V$ with last coin $c$ consists of $c$ plus the optimal solution to making change for amount $V - c$. If a strictly smaller set of coins existed for $V - c$, replacing it would yield a smaller set for $V$, contradicting optimality.
- **Overlapping Subproblems**: Subproblems $dp[v]$ are reused across different coin combinations. DP computes each state once in bottom-up order.

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(n \cdot V)$ | Target amounts $1 \dots V$ evaluated across $n$ coin denominations. |
| **Auxiliary Space** | $\mathcal{O}(V)$ | 1D array of size $V + 1$ for DP values and parent tracking. |

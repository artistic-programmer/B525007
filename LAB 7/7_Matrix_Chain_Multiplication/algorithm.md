# Question 7: Matrix Chain Multiplication (MCM) Dynamic Programming

## Problem Statement
Given a sequence of $n$ matrices $A_1, A_2, \dots, A_n$ where matrix $A_i$ has dimension $p_{i-1} \times p_i$, find the optimal parenthesization that minimizes the total number of scalar multiplications and construct the parenthesized ordering.
- Implement the Dynamic Programming solution in C with interactive user input.
- Derive the time and space complexity.

---

## Dynamic Programming Formulation

### Subproblem Definition
Let $m[i][j]$ be the minimum number of scalar multiplications required to multiply the matrix chain $A_i A_{i+1} \dots A_j$ (where $1 \le i \le j \le n$).

### Recurrence Relation
$$m[i][j] = \begin{cases} 0 & \text{if } i = j \\[8pt] \min_{i \le k < j} \left\{ m[i][k] + m[k+1][j] + p_{i-1} \cdot p_k \cdot p_j \right\} & \text{if } i < j \end{cases}$$

### Split Table Storage
To reconstruct the optimal matrix multiplication order, store the optimal split index $k$ in table $s[i][j]$:
$$s[i][j] = \arg\min_{i \le k < j} \left\{ m[i][k] + m[k+1][j] + p_{i-1} \cdot p_k \cdot p_j \right\}$$

---

## Reconstruction of Optimal Parenthesization

Recursive printing algorithm:
- `PrintOptimalParens(s, i, j)`:
  - If $i == j$: Print $A_i$.
  - Else: Print `(`, `PrintOptimalParens(s, i, s[i][j])`, `PrintOptimalParens(s, s[i][j]+1, j)`, `)`.

---

## Pseudocode

```text
Algorithm MatrixChainOrder(p, n):
    Input: Array p of n + 1 dimensions (p[0..n])
    Output: Min multiplication count m[1][n] and split table s

    Initialize 2D arrays m[n+1][n+1] and s[n+1][n+1] with zeros

    For i = 1 to n:
        m[i][i] = 0

    For L = 2 to n:                 // L is chain length
        For i = 1 to n - L + 1:
            j = i + L - 1
            m[i][j] = INFINITY
            For k = i to j - 1:
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]
                If q < m[i][j]:
                    m[i][j] = q
                    s[i][j] = k

    Return m[1][n] and s
```

---

## Complexity Analysis

| Metric | Complexity | Derivation |
|---|---|---|
| **Time Complexity** | **$\mathcal{O}(n^3)$** | 3 nested loops: Chain length $L$ ($1 \dots n$), start index $i$ ($1 \dots n$), split point $k$ ($i \dots j$). Total operations: $\sum_{L=2}^n (n - L + 1)(L - 1) = \frac{n^3 - n}{6} = \mathcal{O}(n^3)$. |
| **Auxiliary Space** | **$\mathcal{O}(n^2)$** | Requires $(n+1) \times (n+1)$ tables for $m$ and $s$. |

# Question 3: Longest Common Subsequence (LCS) with Reconstruction

## Problem Statement
Given two sequences $X = \langle x_1, x_2, \dots, x_m \rangle$ and $Y = \langle y_1, y_2, \dots, y_n \rangle$, compute the length of their longest common subsequence (LCS) and reconstruct the actual subsequence string.

---

## Dynamic Programming Formulation

### State Definition
Let $L[i][j]$ denote the length of the longest common subsequence of prefixes $X[1 \dots i]$ and $Y[1 \dots j]$, for $0 \le i \le m$ and $0 \le j \le n$.

### Base Cases
- $L[i][0] = 0$ for all $0 \le i \le m$ (LCS with an empty sequence has length 0).
- $L[0][j] = 0$ for all $0 \le j \le n$.

### Recurrence Relation
For $1 \le i \le m$ and $1 \le j \le n$:
$$L[i][j] = \begin{cases} L[i - 1][j - 1] + 1 & \text{if } X[i] = Y[j] \\[6pt] \max(L[i - 1][j],\, L[i][j - 1]) & \text{if } X[i] \ne Y[j] \end{cases}$$

---

## Subsequence String Reconstruction

Backtrack from $(m, n)$ down to $(0, 0)$:
1. If $X[i - 1] == Y[j - 1]$: character belongs to LCS. Append $X[i - 1]$, decrement both $i$ and $j$.
2. Else if $L[i - 1][j] \ge L[i][j - 1]$: move up ($i = i - 1$).
3. Else: move left ($j = j - 1$).
4. Reverse the collected characters to produce the LCS in original left-to-right order.

---

## Pseudocode

```text
Algorithm LongestCommonSubsequence(X, Y, m, n):
    Input: String X of length m, String Y of length n
    Output: LCS length and reconstructed LCS string

    Initialize 2D array L[m + 1][n + 1] with 0

    For i = 1 to m:
        For j = 1 to n:
            If X[i - 1] == Y[j - 1]:
                L[i][j] = L[i - 1][j - 1] + 1
            Else:
                L[i][j] = MAX(L[i - 1][j], L[i][j - 1])

    // Backtrack to reconstruct string
    i = m, j = n
    lcs_str = []
    While i > 0 and j > 0:
        If X[i - 1] == Y[j - 1]:
            lcs_str.append(X[i - 1])
            i = i - 1
            j = j - 1
        Else If L[i - 1][j] >= L[i][j - 1]:
            i = i - 1
        Else:
            j = j - 1

    Reverse lcs_str
    Return L[m][n], lcs_str
```

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(m \cdot n)$ | Grid of size $(m + 1) \times (n + 1)$ filled in $\mathcal{O}(1)$ per cell; backtracking takes $\mathcal{O}(m + n)$. |
| **Auxiliary Space** | $\mathcal{O}(m \cdot n)$ | 2D table of size $(m + 1) \times (n + 1)$ to enable full subsequence reconstruction. |

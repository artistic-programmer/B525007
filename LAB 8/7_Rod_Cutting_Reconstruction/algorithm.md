# Question 7: Rod Cutting with Reconstruction

## Problem Statement
Given a rod of length $n$ inches and an array of prices $P = [p_1, p_2, \dots, p_n]$, where $p_i$ denotes the market price of a rod piece of length $i$ inches, determine:
1. The maximum revenue obtainable by cutting up the rod and selling the pieces.
2. The exact lengths of the pieces that constitute the optimal decomposition (reconstruction).

---

## Dynamic Programming Formulation

### State Definition
Let $R[j]$ denote the maximum revenue obtainable for a rod of length $j$, where $0 \le j \le n$.

### Base Case
- $R[0] = 0$ (A rod of length 0 generates 0 revenue).

### Recurrence Relation
For rod length $j$ from $1$ to $n$:
$$R[j] = \max_{1 \le i \le j} \left\{ p_i + R[j - i] \right\}$$

### Cut Reconstruction Table
To retrieve the exact cut lengths, maintain an array $s[j]$ storing the first cut size $i$ that achieved the optimal revenue $R[j]$:
$$s[j] = \arg\max_{1 \le i \le j} \left\{ p_i + R[j - i] \right\}$$

After computing the tables, the optimal piece lengths are obtained by traversing:
- Print piece length $s[n]$
- Update remaining rod length: $n \leftarrow n - s[n]$
- Repeat until remaining length is 0.

---

## Pseudocode

```text
Algorithm ExtendedBottomUpCutRod(P, n):
    Input: Array P[1..n] of piece prices, rod length n
    Output: Maximum revenue R[n] and cut list

    Initialize arrays R[0..n] and s[0..n] with 0

    For j = 1 to n:
        max_val = -INFINITY
        For i = 1 to j:
            If P[i] + R[j - i] > max_val:
                max_val = P[i] + R[j - i]
                s[j] = i
        R[j] = max_val

    // Reconstruct cuts
    cuts = []
    rem = n
    While rem > 0:
        cuts.append(s[rem])
        rem = rem - s[rem]

    Return R[n], cuts
```

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(n^2)$ | Outer loop runs $n$ times; inner loop runs $j$ times: $\sum_{j=1}^n j = \frac{n(n+1)}{2} = \mathcal{O}(n^2)$. |
| **Auxiliary Space** | $\mathcal{O}(n)$ | Two 1D arrays of size $n + 1$ ($R$ and $s$). |

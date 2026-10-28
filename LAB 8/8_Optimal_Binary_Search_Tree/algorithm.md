# Question 8: Optimal Binary Search Trees (OBST)

## Problem Statement
Given a set of $n$ distinct sorted keys $K = \langle k_1, k_2, \dots, k_n \rangle$ with search probabilities $p_1, p_2, \dots, p_n$, and $n + 1$ dummy keys $d_0, d_1, \dots, d_n$ representing unsuccessful searches with probabilities $q_0, q_1, \dots, q_n$, find the minimum expected search cost of a binary search tree and construct the optimal tree structure.

---

## Dynamic Programming Formulation

### State Definition
- Let $e[i][j]$ be the expected search cost of an optimal BST containing keys $k_i \dots k_j$ and dummy keys $d_{i-1} \dots d_j$ (for $1 \le i \le j+1 \le n+1$).
- Let $w[i][j]$ be the sum of all search probabilities in the subtree:
  $$w[i][j] = \sum_{l=i}^j p_l + \sum_{l=i-1}^j q_l$$
- Let $root[i][j]$ denote the root key index $r$ ($i \le r \le j$) that minimizes $e[i][j]$.

### Base Cases
- When $j = i - 1$, the subtree contains no real keys, only the dummy key $d_{i - 1}$:
  $$e[i][i - 1] = q_{i - 1} \quad \text{for all } 1 \le i \le n + 1$$
  $$w[i][i - 1] = q_{i - 1} \quad \text{for all } 1 \le i \le n + 1$$

### Recurrence Relation
For subtree length $l = 1 \dots n$:
$$w[i][j] = w[i][j - 1] + p_j + q_j$$
$$e[i][j] = \min_{i \le r \le j} \left\{ e[i][r - 1] + e[r + 1][j] + w[i][j] \right\}$$
$$root[i][j] = \arg\min_{i \le r \le j} \left\{ e[i][r - 1] + e[r + 1][j] + w[i][j] \right\}$$

---

## Tree Structure Reconstruction

Recursive function:
- `PrintOptimalBST(root, i, j, parent, is_left)`:
  - If $i > j$: Dummy key $d_{j}$ is a child of parent.
  - Else: Key $k_r$ (where $r = root[i][j]$) is the node. Recursively construct left child `root[i][r - 1]` and right child `root[r + 1][j]`.

---

## Complexity Analysis

| Metric | Standard DP | With Knuth's Optimization |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(n^3)$ | $\mathcal{O}(n^2)$ |
| **Auxiliary Space** | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ |
| **Output** | Minimum expected cost $e[1][n]$ and optimal root hierarchy |

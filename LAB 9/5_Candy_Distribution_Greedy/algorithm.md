# Question 5: Candy Distribution Problem (Bi-directional Slope Greedy)

## Problem Statement
$n$ children stand in a line, each assigned an integer rating. You are distributing candies according to two rules:
1. Each child must receive at least 1 candy.
2. Children with a higher rating than their immediate left or right neighbor must receive strictly more candies than that neighbor.

Find the minimum total number of candies needed, and output the candy allocation for each child.

---

## Bi-Directional Slope Greedy Algorithm

### 1. Conceptual Principle
A child's candy count is determined by two independent constraints:
- **Left Neighbor Condition**: If $\text{rating}[i] > \text{rating}[i - 1]$, then $\text{candies}[i] > \text{candies}[i - 1]$.
- **Right Neighbor Condition**: If $\text{rating}[i] > \text{rating}[i + 1]$, then $\text{candies}[i] > \text{candies}[i + 1]$.

Solving both constraints simultaneously in a single directional pass is challenging because increasing a child's candy count to satisfy their left neighbor can violate their relationship with their right neighbor, or vice versa. By decomposing the problem into **two independent directional greedy sweeps**, we can satisfy both conditions with minimal candies.

### 2. Algorithmic Steps
1. Initialize an array $\text{candies}[0 \dots n - 1]$ where every entry is $1$ (satisfying Rule 1).
2. **Left-to-Right Pass**:
   - Iterate $i$ from $1$ to $n - 1$:
   - If $\text{rating}[i] > \text{rating}[i - 1]$, set:
     $$\text{candies}[i] = \text{candies}[i - 1] + 1$$
3. **Right-to-Left Pass**:
   - Iterate $i$ from $n - 2$ down to $0$:
   - If $\text{rating}[i] > \text{rating}[i + 1]$, set:
     $$\text{candies}[i] = \max\left(\text{candies}[i], \; \text{candies}[i + 1] + 1\right)$$
4. Compute total candies: $\sum_{i=0}^{n-1} \text{candies}[i]$.

---

## Pseudocode

```text
Algorithm CandyDistribution(ratings, n):
    Input: Array of ratings of n children
    Output: Minimum total candies and individual allocations

    Initialize candies[0..n - 1] with 1

    // Left-to-right sweep
    For i = 1 to n - 1:
        If ratings[i] > ratings[i - 1]:
            candies[i] = candies[i - 1] + 1

    // Right-to-left sweep
    For i = n - 2 down to 0:
        If ratings[i] > ratings[i + 1]:
            candies[i] = MAX(candies[i], candies[i + 1] + 1)

    total_candies = SUM(candies)
    Return total_candies, candies
```

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(n)$ | Two linear passes over the array of size $n$. |
| **Auxiliary Space** | $\mathcal{O}(n)$ | Array of size $n$ storing candies per child. |

# Question 3: Application of Sorting-III

## Problem Statement
Given a set $S$ of $n$ integers and an integer $T$, give an $\mathcal{O}(n^{k-1} \log n)$ algorithm to test whether $k$ of the integers in $S$ add up to $T$. By choosing the proper input representation, write a program in C to validate your algorithm.

---

## Input & Output Representation

### Data Structures
The set $S$ is represented as an array of $n$ integers.

```c
typedef struct {
    bool found;
    int* subset;  // array of k chosen integers
    int k;
} KSumResult;
```

---

## Algorithmic Strategy: Generalized $k$-Sum via $(k-1)$-Tuple Enumeration & Binary Search

### High-Level Idea
To achieve the exact worst-case time bound $\mathcal{O}(n^{k-1} \log n)$:
1. **Sort the array $S$** in ascending order: $\mathcal{O}(n \log n)$.
2. Iterate through all combinations of $(k - 1)$ distinct elements from $S$:
   $$(s_{i_1}, s_{i_2}, \dots, s_{i_{k-1}}) \quad \text{such that } 0 \le i_1 < i_2 < \dots < i_{k-1} < n$$
3. For each $(k-1)$-tuple, calculate the required $k$-th value:
   $$R = T - \sum_{j=1}^{k-1} s_{i_j}$$
4. Perform a **binary search** for $R$ in the remaining sorted portion of $S$ (specifically within indices $[i_{k-1} + 1, n-1]$): $\mathcal{O}(\log n)$.
5. If $R$ is found at index $i_k$, then $(s_{i_1}, s_{i_2}, \dots, s_{i_{k-1}}, s_{i_k})$ is a valid $k$-element subset summing to $T$.

---

## Pseudocode

```text
Algorithm KSumTest(S, n, k, T):
    Input: Array S of n integers, integer k >= 1, target T
    Output: True with chosen elements if k elements sum to T, else False

    1. Sort(S, 0, n - 1)    // O(n log n)
    2. chosen_indices = Array of size k

    3. Function Search(level, start_idx, current_sum):
           // Base case: we have chosen (k - 1) elements
           If level == k - 1:
               remainder = T - current_sum
               // Binary search in range [start_idx, n - 1]
               idx = BinarySearch(S, start_idx, n - 1, remainder)
               If idx != -1:
                   chosen_indices[k - 1] = idx
                   Return True
               Return False

           // Recursive choice for level from 0 to k - 2
           For i = start_idx to n - (k - level):
               chosen_indices[level] = i
               If Search(level + 1, i + 1, current_sum + S[i]) == True:
                   Return True

           Return False

    4. Result = Search(0, 0, 0)
    5. Return Result
```

---

## Mathematical Correctness Proof

1. **Exhaustive Coverage**:
   - The recursive search generates all $\binom{n}{k-1}$ combinations of $k-1$ distinct indices in strictly increasing order $i_1 < i_2 < \dots < i_{k-1}$.
2. **Distinctness of $k$-th element**:
   - Binary search is restricted to the sub-array $S[i_{k-1} + 1 \dots n - 1]$.
   - This ensures $i_{k-1} < i_k$, guaranteeing all $k$ chosen indices are strictly distinct.
3. **Soundness & Completeness**:
   - Soundness: If binary search succeeds, $\sum_{j=1}^{k-1} S[i_j] + S[i_k] = \text{current\_sum} + R = T$.
   - Completeness: Any $k$-subset summing to $T$ can be indexed in sorted order $i_1 < i_2 < \dots < i_k$. Its first $k-1$ elements will be examined by the combination generator, and the $k$-th element $S[i_k] = T - \sum_{j=1}^{k-1} S[i_j]$ will be found by binary search in $S[i_{k-1} + 1 \dots n-1]$.

---

## Complexity Analysis

| Step | Complexity | Notes |
|---|---|---|
| Initial Sorting | $\mathcal{O}(n \log n)$ | One-time preprocessing |
| Number of $(k-1)$-tuples | $\binom{n}{k-1} = \frac{n(n-1)\cdots(n-k+2)}{(k-1)!} = \mathcal{O}(n^{k-1})$ | Outer loop combinations |
| Binary Search per tuple | $\mathcal{O}(\log n)$ | Search in remaining subarray |
| **Total Time** | $\mathcal{O}(n \log n + n^{k-1} \log n) = \mathbf{\mathcal{O}(n^{k-1} \log n)}$ | Matches requested bound |
| **Auxiliary Space** | $\mathcal{O}(k)$ | Recursion stack and tuple buffer |

# Question 5: Maximum Sum Increasing Subsequence (MSIS)

## Problem Statement
Given an array of $n$ positive integers $A = [a_0, a_1, \dots, a_{n-1}]$, find the maximum possible sum of a strictly increasing subsequence, and reconstruct the elements forming this subsequence.

---

## Dynamic Programming Formulation

### State Definition
Let $MSIS[i]$ denote the maximum sum of a strictly increasing subsequence ending with element $A[i]$, for $0 \le i < n$.

### Base Case
- $MSIS[i] = A[i]$ for all $0 \le i < n$ (A single element $A[i]$ has sum equal to its own value).

### Recurrence Relation
For each index $i$ from $0$ to $n - 1$:
$$MSIS[i] = A[i] + \max \left( 0, \; \max_{\substack{0 \le j < i \\ A[j] < A[i]}} MSIS[j] \right)$$

### Global Maximum Sum
$$\text{Max Sum} = \max_{0 \le i < n} MSIS[i]$$

### Subsequence Reconstruction
Maintain `parent[i] = j` storing the predecessor that contributed the maximum sum to $MSIS[i]$. Backtrack from the index achieving $\max MSIS[i]$ to reconstruct the exact elements.

---

## Pseudocode

```text
Algorithm MaxSumIncreasingSubsequence(A, n):
    Input: Array A of n positive integers
    Output: Maximum sum and reconstructed subsequence

    Initialize MSIS[0..n - 1] = A[0..n - 1]
    Initialize parent[0..n - 1] with -1

    max_sum = A[0]
    best_end = 0

    For i = 1 to n - 1:
        For j = 0 to i - 1:
            If A[j] < A[i] and MSIS[j] + A[i] > MSIS[i]:
                MSIS[i] = MSIS[j] + A[i]
                parent[i] = j

        If MSIS[i] > max_sum:
            max_sum = MSIS[i]
            best_end = i

    // Reconstruct subsequence
    subseq = []
    curr = best_end
    While curr != -1:
        subseq.append(A[curr])
        curr = parent[curr]

    Reverse subseq
    Return max_sum, subseq
```

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(n^2)$ | Double loop checking pairs $(j, i)$ for $0 \le j < i < n$. |
| **Auxiliary Space** | $\mathcal{O}(n)$ | Arrays of size $n$ for $MSIS$ and $parent$ indices. |

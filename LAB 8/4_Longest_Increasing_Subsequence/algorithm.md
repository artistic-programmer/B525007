# Question 4: Longest Increasing Subsequence (LIS)

## Problem Statement
Given an integer array $A = [a_0, a_1, \dots, a_{n-1}]$, find the length of the longest subsequence such that all elements of the subsequence are strictly increasing. Reconstruct and display the actual increasing subsequence.

---

## Dynamic Programming Formulation

### State Definition
Let $LIS[i]$ denote the length of the longest strictly increasing subsequence that ends with element $A[i]$, for $0 \le i < n$.

### Base Case
- $LIS[i] = 1$ for all $0 \le i < n$ (Every individual element forms an increasing subsequence of length 1).

### Recurrence Relation
For each index $i$ from $0$ to $n - 1$:
$$LIS[i] = 1 + \max_{\substack{0 \le j < i \\ A[j] < A[i]}} LIS[j]$$
If no such $j$ exists, $LIS[i] = 1$.

### Global Maximum Length
The length of the overall LIS is:
$$\text{Max Length} = \max_{0 \le i < n} LIS[i]$$

### Subsequence Reconstruction
Maintain a `parent[i]` array storing the predecessor index $j$ that yielded the maximum $LIS[i]$. Starting from the index with maximum $LIS$ value, follow `parent` pointers to reconstruct the elements, then reverse the sequence.

---

## Pseudocode

```text
Algorithm LongestIncreasingSubsequence(A, n):
    Input: Array A of n integers
    Output: Maximum LIS length and reconstructed subsequence

    Initialize LIS[0..n - 1] with 1
    Initialize parent[0..n - 1] with -1

    max_len = 1
    best_end = 0

    For i = 1 to n - 1:
        For j = 0 to i - 1:
            If A[j] < A[i] and LIS[j] + 1 > LIS[i]:
                LIS[i] = LIS[j] + 1
                parent[i] = j

        If LIS[i] > max_len:
            max_len = LIS[i]
            best_end = i

    // Reconstruct sequence
    subseq = []
    curr = best_end
    While curr != -1:
        subseq.append(A[curr])
        curr = parent[curr]

    Reverse subseq
    Return max_len, subseq
```

---

## Complexity Analysis

| Metric | DP Approach | Binary Search Approach ($\mathcal{O}(n \log n)$) |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(n^2)$ | $\mathcal{O}(n \log n)$ |
| **Auxiliary Space** | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ |
| **Reconstruction** | Trivial via `parent` array | Via predecessor indices |

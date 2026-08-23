# Question 2: Application of Sorting-II

## Problem Statement
Given two sets $S_1$ and $S_2$ (each of size $n$), and a target number $x$, describe an $\mathcal{O}(n \log n)$ algorithm for finding whether there exists a pair of elements $(a, b)$ with $a \in S_1$ and $b \in S_2$ such that:
$$a + b = x$$
By choosing the proper input representation, write a program in C to validate your algorithm.

---

## Input & Output Representation

### Data Structures
Sets $S_1$ and $S_2$ are represented as integer arrays of size $n$.

```c
typedef struct {
    bool found;
    int a; // element from S1
    int b; // element from S2
} PairResult;
```

---

## Algorithmic Strategies

### Primary Approach: Dual Sorting + Two Pointers ($\mathcal{O}(n \log n)$)

1. **Sort $S_1$** in ascending order: $\mathcal{O}(n \log n)$.
2. **Sort $S_2$** in ascending order: $\mathcal{O}(n \log n)$.
3. **Two-Pointer Search**:
   - Place pointer $i$ at the start of $S_1$ ($i = 0$).
   - Place pointer $j$ at the end of $S_2$ ($j = n - 1$).
   - At each iteration:
     - Compute $\text{current\_sum} = S_1[i] + S_2[j]$.
     - If $\text{current\_sum} == x$: Pair found! Return $(S_1[i], S_2[j])$.
     - If $\text{current\_sum} < x$: We need a larger sum. Since $S_1$ is sorted, increment $i \leftarrow i + 1$.
     - If $\text{current\_sum} > x$: We need a smaller sum. Since $S_2$ is sorted, decrement $j \leftarrow j - 1$.
   - If $i \ge n$ or $j < 0$, no such pair exists.

### Alternative Approach: Single Sort + Binary Search ($\mathcal{O}(n \log n)$)

1. Sort $S_2$ in ascending order: $\mathcal{O}(n \log n)$.
2. For each element $a \in S_1$:
   - Binary search for required complement $target = x - a$ in $S_2$: $\mathcal{O}(\log n)$.
   - If found, return $(a, target)$.
3. Total time: $\mathcal{O}(n \log n) + n \times \mathcal{O}(\log n) = \mathcal{O}(n \log n)$.

---

## Pseudocode (Dual Sort + Two Pointers)

```text
Algorithm FindTwoSumPair(S1, S2, n, x):
    Input: Arrays S1 and S2 of size n, target integer x
    Output: Pair (a, b) such that a in S1, b in S2, a + b = x, or (False, 0, 0)

    1. Sort(S1, 0, n - 1)      // O(n log n)
    2. Sort(S2, 0, n - 1)      // O(n log n)

    3. i = 0                  // Pointer to start of S1
    4. j = n - 1              // Pointer to end of S2

    5. While i < n and j >= 0:
           sum = S1[i] + S2[j]
           If sum == x:
               Return (True, S1[i], S2[j])
           Else If sum < x:
               i = i + 1       // Increase sum
           Else:
               j = j - 1       // Decrease sum

    6. Return (False, 0, 0)
```

---

## Correctness Proof

- **Invariant**: At any step during the two-pointer traversal, no pair $(S_1[p], S_2[q])$ with $p < i$ or $q > j$ can sum to $x$.
- When $S_1[i] + S_2[j] < x$:
  - For any $k \le j$, $S_1[i] + S_2[k] \le S_1[i] + S_2[j] < x$.
  - Hence, element $S_1[i]$ cannot form a sum $x$ with any element in $S_2[0 \dots j]$. Thus, it is safe to eliminate $S_1[i]$ by advancing $i \leftarrow i + 1$.
- When $S_1[i] + S_2[j] > x$:
  - For any $k \ge i$, $S_1[k] + S_2[j] \ge S_1[i] + S_2[j] > x$.
  - Hence, element $S_2[j]$ cannot form a sum $x$ with any element in $S_1[i \dots n-1]$. Thus, it is safe to eliminate $S_2[j]$ by decrementing $j \leftarrow j - 1$.
- Therefore, the algorithm never skips a valid pair and will terminate with the correct answer in at most $2n$ comparisons.

---

## Complexity Analysis

| Phase | Time Complexity | Space Complexity |
|---|---|---|
| Sorting $S_1$ and $S_2$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(1)$ aux (in-place) / $\mathcal{O}(n)$ |
| Two-Pointer Traversal | $\mathcal{O}(n)$ (at most $2n$ steps) | $\mathcal{O}(1)$ aux |
| **Total** | **$\mathcal{O}(n \log n)$** | **$\mathcal{O}(1)$ auxiliary** |

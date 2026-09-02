# Question 2: Find K-th Smallest Element Without Sorting

## Problem Statement
Find the $K$-th smallest element in a given list of $N$ numbers without sorting the list. Do the complexity analysis of your algorithm.

---

## Input & Output Representation

### Data Structures
The input is an unsorted list of $N$ integers and a 1-indexed integer $K$ ($1 \le K \le N$).

```c
typedef struct {
    int kth_element;
    int k;
    int n;
} SelectionResult;
```

---

## Algorithmic Strategy: Order-Statistic QuickSelect

### Conceptual Principle
1. Sorting the full list to retrieve the element at index $K-1$ requires $\mathcal{O}(N \log N)$ operations, which does unnecessary work sorting elements outside rank $K$.
2. **QuickSelect** finds the element of rank $K$ in $\mathcal{O}(N)$ average time:
   - Convert 1-indexed $K$ to 0-indexed rank `target_rank = K - 1`.
   - Pick a pivot $P$ uniformly at random to guarantee randomized expected linear performance.
   - Partition array around $P$ into $A[low \dots p-1] \le P$ and $A[p+1 \dots high] \ge P$.
   - If pivot index $p == target\_rank$, $A[p]$ is the exact $K$-th smallest element.
   - If $target\_rank < p$, recurse into the left subarray.
   - If $target\_rank > p$, recurse into the right subarray.

---

## Pseudocode

```text
Algorithm FindKthSmallest(A, N, K):
    Input: Unsorted array A of size N, integer K (1 <= K <= N)
    Output: The K-th smallest value in A

    target_rank = K - 1
    low = 0
    high = N - 1

    While low <= high:
        pivot_idx = RandomizedPartition(A, low, high)

        If pivot_idx == target_rank:
            Return A[pivot_idx]
        Else If target_rank < pivot_idx:
            high = pivot_idx - 1
        Else:
            low = pivot_idx + 1

    Return -1
```

---

## Correctness Proof

- **Partition Invariant**: After partitioning $A[low \dots high]$ with pivot element $P$ placed at index $p$:
  - Every element in $A[low \dots p-1]$ is $\le P$.
  - Every element in $A[p+1 \dots high]$ is $\ge P$.
  - Element $P$ is at its true sorted position $p$.
- If $p == K-1$, exactly $K-1$ elements in the entire array are smaller than or equal to $P$. By definition, $P$ is the $K$-th smallest element.
- Since partitioning is sound, discarding the side that does not contain $K-1$ preserves the target element.

---

## Complexity Analysis

| Metric | Complexity | Derivation / Notes |
|---|---|---|
| **Average Time Complexity** | $\mathcal{O}(N)$ | Expected recurrence: $T(N) = T(N/2) + cN \implies T(N) = \mathcal{O}(N)$. |
| **Best Time Complexity** | $\mathcal{O}(N)$ | Single partition pass when pivot falls exactly on rank $K-1$. |
| **Worst Time Complexity** | $\mathcal{O}(N^2)$ | Occurs if pivot selected is always min/max (mitigated by randomized pivot selection to $\mathcal{O}(N)$ expected). |
| **Auxiliary Space** | $\mathcal{O}(1)$ | Iterative loop partitioning uses zero auxiliary stack space. |

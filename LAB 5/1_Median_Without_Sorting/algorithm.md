# Question 1: Find Median of N Numbers Without Sorting

## Problem Statement
Find the median of a list of $N$ numbers without sorting the list. Do the complexity analysis of your algorithm.

---

## Input & Output Representation

### Data Structures
The input is an unsorted array of $N$ numbers.

```c
typedef struct {
    double median;
    int comparisons;
} MedianResult;
```

---

## Algorithmic Strategy: QuickSelect (Hoare's Selection Algorithm)

### Key Observation
1. Sorting the entire list requires $\mathcal{O}(N \log N)$ time. However, to find only the median element (the element at order statistic $k = \lfloor N/2 \rfloor$), sorting the rest of the array is unnecessary.
2. **QuickSelect** applies the Divide-and-Conquer partitioning strategy of QuickSort. Instead of recursing into both left and right partitions, QuickSelect recurses **only into the single partition containing the target rank $k$**.
3. For an even number of elements $N$, the median is defined as the average of the two central order statistics: $\text{rank}_1 = N/2 - 1$ and $\text{rank}_2 = N/2$.

### Partitioning Mechanism
Using Lomuto or Hoare partitioning:
- Pick a pivot element $P$.
- Rearrange the array into $A[low \dots pivot\_idx - 1] \le P$ and $A[pivot\_idx + 1 \dots high] \ge P$.
- Compare $pivot\_idx$ with target rank $k$:
  - If $pivot\_idx == k$: Return $A[pivot\_idx]$.
  - If $k < pivot\_idx$: Recurse on left subarray $A[low \dots pivot\_idx - 1]$.
  - If $k > pivot\_idx$: Recurse on right subarray $A[pivot\_idx + 1 \dots high]$.

---

## Pseudocode

```text
Algorithm QuickSelect(A, low, high, k):
    Input: Array A, indices low and high, target order statistic k
    Output: The k-th smallest element in A[low..high]

    If low == high:
        Return A[low]

    pivot_idx = Partition(A, low, high)

    If pivot_idx == k:
        Return A[k]
    Else If k < pivot_idx:
        Return QuickSelect(A, low, pivot_idx - 1, k)
    Else:
        Return QuickSelect(A, pivot_idx + 1, high, k)

Algorithm FindMedian(A, N):
    Input: Unsorted array A of size N
    Output: Median value as double

    If N is odd:
        Return QuickSelect(A, 0, N - 1, N / 2)
    Else:
        left_med  = QuickSelect(A, 0, N - 1, N / 2 - 1)
        right_med = QuickSelect(A, 0, N - 1, N / 2)
        Return (left_med + right_med) / 2.0
```

---

## Correctness Proof

- **Invariant**: At each step, the element at index $pivot\_idx$ is placed in its exact final position as if the entire array were sorted.
- Since $pivot\_idx$ is globally correct, if $pivot\_idx == k$, $A[k]$ is guaranteed to be the element at order statistic $k$.
- By eliminating half of the array at each step on average, QuickSelect converges directly on the median element without ordering the remaining elements.

---

## Complexity Analysis

| Case | Time Complexity | Recurrence / Derivation |
|---|---|---|
| **Average Case** | $\mathcal{O}(N)$ | $T(N) = T(N/2) + \mathcal{O}(N) \implies T(N) = N + \frac{N}{2} + \frac{N}{4} + \dots = 2N = \mathcal{O}(N)$ |
| **Best Case** | $\mathcal{O}(N)$ | Pivot splits array in half at step 1: $\mathcal{O}(N)$ work. |
| **Worst Case** | $\mathcal{O}(N^2)$ | Bad pivots (e.g. sorted input with last-element pivot): $T(N) = T(N-1) + O(N)$. Prevented via Randomized / Median-of-Three pivot selection. |
| **Auxiliary Space** | $\mathcal{O}(1)$ | Iterative QuickSelect requires $\mathcal{O}(1)$ auxiliary space ($\mathcal{O}(\log N)$ stack for recursive). |

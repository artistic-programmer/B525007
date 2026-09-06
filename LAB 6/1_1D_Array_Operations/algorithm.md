# Question 1: 1D Array Operations and Their Complexities

## Problem Statement
Given an array with $n$ unsorted integer elements, derive the worst-case computational complexity and implement in C the following 9 operations:
1. Finding the maximum element.
2. Finding the first and second largest elements.
3. Finding the mean.
4. Finding the median.
5. Finding the standard deviation.
6. Finding the mode.
7. Removing all duplicates.
8. Reversing the elements of the array.
9. Partitioning the array with respect to a random pivot element so that all elements less than the pivot appear **after** all elements greater than or equal to the pivot.

---

## Data Structures & Functions

```c
typedef struct {
    int max;
    int first_largest;
    int second_largest;
    double mean;
    double median;
    double std_dev;
    int mode;
    int mode_frequency;
    int unique_count;
} ArrayStats;
```

---

## Detailed Algorithmic Procedures & Complexity Derivations

### (i) Finding the Maximum Element
- **Procedure**: Initialize `max = arr[0]`. Iterate $i$ from 1 to $n-1$; if `arr[i] > max`, update `max = arr[i]`.
- **Complexity**: $\mathcal{O}(n)$ time ($n-1$ comparisons), $\mathcal{O}(1)$ space.

### (ii) Finding First and Second Largest Elements
- **Procedure**: Track `first` and `second`. If `arr[i] > first`, `second = first`, `first = arr[i]`. Else if `arr[i] > second` and `arr[i] != first`, `second = arr[i]`.
- **Complexity**: $\mathcal{O}(n)$ time (single pass), $\mathcal{O}(1)$ space.

### (iii) Finding the Mean
- **Procedure**: Accumulate $\text{sum} = \sum_{i=0}^{n-1} \text{arr}[i]$. Return $\text{sum} / n$.
- **Complexity**: $\mathcal{O}(n)$ time ($n$ additions), $\mathcal{O}(1)$ space.

### (iv) Finding the Median
- **Procedure**: Use **QuickSelect** to find order statistic $k = \lfloor n/2 \rfloor$ without full sorting.
- **Complexity**: $\mathcal{O}(n)$ average time, $\mathcal{O}(1)$ auxiliary space.

### (v) Finding the Standard Deviation
- **Procedure**: Compute mean $\mu$. Sum squared differences $\sum_{i=0}^{n-1} (\text{arr}[i] - \mu)^2$, compute variance $\sigma^2 = \text{sum\_sq} / n$, return $\sigma = \sqrt{\sigma^2}$.
- **Complexity**: $\mathcal{O}(n)$ time (two passes), $\mathcal{O}(1)$ space.

### (vi) Finding the Mode
- **Procedure**: Count element frequencies using frequency table or sorting.
- **Complexity**: $\mathcal{O}(n \log n)$ using sorting or $\mathcal{O}(n)$ using hash map.

### (vii) Removing All Duplicates
- **Procedure**: Preserve unique elements by checking prior presence or using boolean frequency table.
- **Complexity**: $\mathcal{O}(n)$ time with frequency table / hash set, $\mathcal{O}(n)$ space.

### (viii) Reversing the Array
- **Procedure**: Two pointers $left = 0, right = n-1$. Swap $\text{arr}[left]$ and $\text{arr}[right]$, increment $left$, decrement $right$.
- **Complexity**: $\mathcal{O}(n)$ time ($\lfloor n/2 \rfloor$ swaps), $\mathcal{O}(1)$ space.

### (ix) Reverse Pivot Partitioning
- **Procedure**: Partition array around pivot $P$ such that elements $\ge P$ are placed in the left segment and elements $< P$ are placed in the right segment.
- **Complexity**: $\mathcal{O}(n)$ single pass partitioning, $\mathcal{O}(1)$ space.

---

## Complexity Summary Table

| Operation | Worst-Case Time | Auxiliary Space | Technique |
|---|---|---|---|
| (i) Find Maximum | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | Single pass scan |
| (ii) First & Second Largest | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | Dual variable tracking |
| (iii) Find Mean | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | Accumulative summation |
| (iv) Find Median | $\mathcal{O}(n)$ Avg / $\mathcal{O}(n^2)$ Worst | $\mathcal{O}(1)$ | QuickSelect |
| (v) Standard Deviation | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | Two-pass variance formula |
| (vi) Find Mode | $\mathcal{O}(n \log n)$ / $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | Frequency distribution |
| (vii) Remove Duplicates | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | Set filtering |
| (viii) Reverse Array | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | Two-pointer swap |
| (ix) Reverse Pivot Partition | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | In-place partition scan |

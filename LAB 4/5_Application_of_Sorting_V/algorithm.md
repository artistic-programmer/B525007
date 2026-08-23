# Question 5: Application of Sorting-V

## Problem Statement
Given a list $I$ of $n$ intervals, specified as $(x_i, y_i)$ pairs, return a list where all overlapping intervals are merged.

**Example**:
- Input: $I = \{(1, 3), (2, 6), (8, 10), (7, 18)\}$
- Expected Output: $\{(1, 6), (7, 18)\}$

Your algorithm should run in worst-case $\mathcal{O}(n \log n)$ time complexity. By choosing a suitable input and output representation, write a program in C to validate your algorithm.

---

## Input & Output Representation

### Data Structures
Each interval is represented by a start coordinate and an end coordinate:

```c
typedef struct {
    int start; // x_i
    int end;   // y_i
} Interval;
```

---

## Algorithmic Strategy: Sort by Start Time + Single Linear Pass

### Key Principles
1. **Sort Intervals**:
   - Sort the input array of intervals in ascending order based primarily on start points $x_i$.
   - If two intervals have the same start point, sort by their end points $y_i$ ascending:
     $$I_1 \le I_2 \iff (I_1.\text{start} < I_2.\text{start}) \lor (I_1.\text{start} == I_2.\text{start} \land I_1.\text{end} \le I_2.\text{end})$$
   - Sorting takes $\mathcal{O}(n \log n)$ time.

2. **Sequential Merging Pass**:
   - Initialize the first merged interval with $I[0]$:
     $$\text{cur\_start} = I[0].\text{start}, \quad \text{cur\_end} = I[0].\text{end}$$
   - For each subsequent interval $I[i]$ for $i = 1 \dots n-1$:
     - **Case 1: Overlapping ($I[i].\text{start} \le \text{cur\_end}$)**
       - Since intervals are sorted by start time, $I[i].\text{start} \ge \text{cur\_start}$.
       - Thus, interval $I[i]$ overlaps or touches the current interval.
       - Extend the current interval's right boundary:
         $$\text{cur\_end} = \max(\text{cur\_end}, I[i].\text{end})$$
     - **Case 2: Disjoint ($I[i].\text{start} > \text{cur\_end}$)**
       - Interval $I[i]$ is strictly to the right of the current interval.
       - Commit $(\text{cur\_start}, \text{cur\_end})$ to the output list.
       - Start a new merged interval with $I[i]$:
         $$\text{cur\_start} = I[i].\text{start}, \quad \text{cur\_end} = I[i].\text{end}$$
   - Finally, commit the last active merged interval $(\text{cur\_start}, \text{cur\_end})$ to the output list.

---

## Pseudocode

```text
Algorithm MergeOverlappingIntervals(I, n):
    Input: Array I of n intervals with start and end
    Output: List of merged disjoint intervals

    1. If n <= 0: Return empty list

    2. Sort(I, 0, n - 1) by start ascending, then end ascending // O(n log n)

    3. Allocate Output array of size n
    4. out_count = 0

    5. cur_start = I[0].start
    6. cur_end   = I[0].end

    7. For i = 1 to n - 1:
           If I[i].start <= cur_end:
               cur_end = Max(cur_end, I[i].end)
           Else:
               Output[out_count++] = Interval(cur_start, cur_end)
               cur_start = I[i].start
               cur_end   = I[i].end

    8. Output[out_count++] = Interval(cur_start, cur_end)
    9. Return (Output, out_count)
```

---

## Correctness Proof

- **Transitivity of Overlap**: Because the intervals are sorted by start coordinate, all intervals that can potentially overlap with the current merged block $[\text{cur\_start}, \text{cur\_end}]$ appear consecutively in the sorted sequence.
- **Completeness**: If an interval $I[k]$ has $I[k].\text{start} > \text{cur\_end}$, no subsequent interval $I[m]$ with $m > k$ can overlap with $[\text{cur\_start}, \text{cur\_end}]$ because $I[m].\text{start} \ge I[k].\text{start} > \text{cur\_end}$.
- Hence, the current block is complete and can be finalized safely without future modifications.

---

## Complexity Analysis

| Phase | Time Complexity | Space Complexity |
|---|---|---|
| Sorting Intervals | $\mathcal{O}(n \log n)$ | $\mathcal{O}(1)$ aux (in-place) / $\mathcal{O}(n)$ |
| Linear Merge Scan | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ (output list) |
| **Total** | **$\mathcal{O}(n \log n)$** | **$\mathcal{O}(n)$** |

# Question 1: Application of Sorting-I

## Problem Statement
Assume that we are given $n$ pairs of items as input, where the first item is a number and the second item is one of three colours (**red**, **blue**, or **yellow**). Further assume that the items are already sorted by number. 

Give an $\mathcal{O}(n)$ algorithm to sort the items by colour (**all reds before all blues before all yellows**) such that the numbers for identical colours stay sorted (i.e., stable sorting). By choosing the proper input representation, write a program in C to validate your algorithm.

---

## Input & Output Representation

### Data Structures
Each item is represented as a structure containing:
- An integer `number`
- An enumeration `color` where:
  - `RED` ($0$) represents **Red**
  - `BLUE` ($1$) represents **Blue**
  - `YELLOW` ($2$) represents **Yellow**

```c
typedef enum {
    COLOR_RED = 0,
    COLOR_BLUE = 1,
    COLOR_YELLOW = 2
} Color;

typedef struct {
    int number;
    Color color;
} Item;
```

---

## Algorithmic Strategy: Stable 3-Way Bucket Partition / Counting Distribution

### Key Observation
1. The input items are **already sorted by number**:
   $$\text{item}[0].\text{number} \le \text{item}[1].\text{number} \le \dots \le \text{item}[n-1].\text{number}$$
2. The alphabet of colours is small and fixed: $|\Sigma| = 3$ (Red, Blue, Yellow).
3. If we process the input array sequentially from left to right ($0$ to $n-1$) and distribute elements into 3 separate buckets (one for each color), elements within each bucket will naturally preserve their relative order by number.
4. Concatenating the Red bucket, Blue bucket, and Yellow bucket yields the desired sorted array.

### Mathematical Formulation
Let the input array be $A[0 \dots n-1]$.
We count the occurrences of each color:
- $c_R = \sum_{i=0}^{n-1} [A[i].\text{color} == \text{RED}]$
- $c_B = \sum_{i=0}^{n-1} [A[i].\text{color} == \text{BLUE}]$
- $c_Y = \sum_{i=0}^{n-1} [A[i].\text{color} == \text{YELLOW}]$

Starting output indices:
- Red starts at index $0$
- Blue starts at index $c_R$
- Yellow starts at index $c_R + c_B$

A single pass distributes each element $A[i]$ into its designated slot:
- If $A[i].\text{color} == \text{RED}$, placed at $pos_R++$
- If $A[i].\text{color} == \text{BLUE}$, placed at $pos_B++$
- If $A[i].\text{color} == \text{YELLOW}$, placed at $pos_Y++$

---

## Pseudocode

```text
Algorithm StableColorSort(A, n):
    Input: Array A of n Items (already sorted by number)
    Output: Array B of n Items sorted by color (R < B < Y) with number order preserved

    1. Initialize count[3] = {0, 0, 0}
    2. For i = 0 to n - 1:
           count[A[i].color] = count[A[i].color] + 1

    3. Initialize pos[0] = 0                       // Red starting position
    4. Initialize pos[1] = count[0]                // Blue starting position
    5. Initialize pos[2] = count[0] + count[1]     // Yellow starting position

    6. Allocate array B of size n
    7. For i = 0 to n - 1:
           c = A[i].color
           B[pos[c]] = A[i]
           pos[c] = pos[c] + 1

    8. Return B
```

---

## Correctness & Stability Proof

1. **Color Ordering**:
   - All Red items are placed in range $[0, c_R - 1]$.
   - All Blue items are placed in range $[c_R, c_R + c_B - 1]$.
   - All Yellow items are placed in range $[c_R + c_B, n - 1]$.
   - Hence, all Reds strictly precede all Blues, which strictly precede all Yellows.

2. **Stability within Same Color**:
   - For any two items $A[i]$ and $A[j]$ with $i < j$ and $A[i].\text{color} == A[j].\text{color} == c$:
     - Since the input is sorted by number, $A[i].\text{number} \le A[j].\text{number}$.
     - Item $A[i]$ is processed before $A[j]$, so it receives an output slot index $pos_c$ strictly smaller than the slot index assigned to $A[j]$.
     - Therefore, within each color, the relative order of numbers is preserved.

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(n)$ | Pass 1 counts color frequencies in $\mathcal{O}(n)$. Pass 2 distributes items into output slots in $\mathcal{O}(n)$. Total operations: $2n + \mathcal{O}(1) = \mathcal{O}(n)$. |
| **Auxiliary Space** | $\mathcal{O}(n)$ | Requires output array $B$ of size $n$ and fixed counters $\mathcal{O}(1)$. |

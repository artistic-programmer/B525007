# Question 4: Minimum Cost to Connect Sticks (Optimal Merge Pattern)

## Problem Statement
You have $n$ sticks of lengths $L_1, L_2, \dots, L_n$. Connecting any two sticks of lengths $x$ and $y$ costs $x + y$ and results in a single stick of length $x + y$. Find the minimum total cost to connect all $n$ sticks into a single stick.

---

## Greedy Min-Heap Strategy (Huffman Optimal Merge Pattern)

### 1. Conceptual Principle
Connecting sticks can be represented as building a binary merge tree:
- Each stick $L_i$ appears as a leaf at some depth $d_i$.
- The total cost incurred across all operations is:
  $$\text{Total Cost} = \sum_{i=1}^n L_i \cdot d_i$$
- To minimize the sum of products $\sum L_i d_i$, larger stick lengths must have smaller depths, and smaller stick lengths must have larger depths.
- This is identical to **Huffman's greedy algorithm**: repeatedly merge the two smallest elements.

### 2. Algorithmic Steps
1. Insert all $n$ stick lengths into a Min-Heap.
2. Initialize `total_cost = 0`.
3. While the Min-Heap contains more than 1 stick:
   - Extract the two minimum stick lengths $x$ and $y$.
   - Compute merge cost $c = x + y$.
   - Add $c$ to `total_cost`.
   - Push the new combined stick $c$ back into the Min-Heap.
4. When 1 stick remains, return `total_cost`.

---

## Pseudocode

```text
Algorithm MinCostConnectSticks(sticks, n):
    Input: Array of n stick lengths L[1..n]
    Output: Minimum total connection cost

    If n <= 1:
        Return 0

    Initialize MinHeap H
    For each length in sticks:
        H.insert(length)

    total_cost = 0

    While H.size > 1:
        x = H.extract_min()
        y = H.extract_min()
        cost = x + y
        total_cost += cost
        H.insert(cost)

    Return total_cost
```

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Heap Construction** | $\mathcal{O}(n)$ | Bottom-up heapify or $n$ insertions in $\mathcal{O}(n \log n)$. |
| **Merge Iterations** | $\mathcal{O}(n \log n)$ | $n - 1$ merge steps, each performing 2 extractions and 1 insertion in $\mathcal{O}(\log n)$. |
| **Total Time Complexity** | **$\mathcal{O}(n \log n)$** | Optimal comparison-based merge bound. |
| **Auxiliary Space** | **$\mathcal{O}(n)$** | Min-Heap storage for $n$ elements. |

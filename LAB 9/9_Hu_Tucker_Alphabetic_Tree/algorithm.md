# Question 9: Hu-Tucker Alphabetic Binary Tree Algorithm

## Problem Statement
Given an ordered sequence of $N$ positive weights $w_1, w_2, \dots, w_N$ corresponding to alphabetic symbols (or sorted search keys), construct an **Optimal Alphabetic Binary Tree** that minimizes the total weighted path length:
$$\text{Cost} = \sum_{i=1}^N w_i \cdot \text{depth}(i)$$
subject to the strict constraint that the **leaves must appear in their given linear order from left to right** (unlike standard Huffman coding where leaves can be permuted arbitrarily).

---

## The Hu-Tucker Algorithm (1971)

The classic dynamic programming approach (Knuth / Gilbert-Moore) solves optimal binary search trees in $\mathcal{O}(N^2)$ time. The **Hu-Tucker Algorithm** provides a faster, greedy-based construction in $\mathcal{O}(N \log N)$ (or $\mathcal{O}(N^2)$ simulation) via a 3-phase procedure:

### Phase 1: Combination (Greedy Pairing)
- Maintain a sequence of nodes (initially all $N$ leaves).
- Two nodes $u$ and $v$ (with $u$ to the left of $v$) are **compatible** if every node lying strictly between them in the sequence is an internal node (already formed by a previous merge).
- In each step, find the compatible pair $(u, v)$ that minimizes $w(u) + w(v)$ (with tie-breaking favoring earlier positions).
- Merge $u$ and $v$ into a new internal node $z$ with weight $w(z) = w(u) + w(v)$, placing $z$ at the position of $u$, and deleting $v$.
- Repeat for $N - 1$ merges until only one root node remains.

### Phase 2: Level Assignment
- Traverse the tree produced in Phase 1 to compute the depth/level $l_i$ of each original leaf $i$ ($1 \le i \le N$).

### Phase 3: Recombination (Order Restoration)
- Using only the computed leaf levels $\{l_i\}$, reconstruct the final tree from the bottom up:
  - While nodes at maximum depth remain, pair adjacent nodes at the bottom level from left to right into a parent at depth $l - 1$.
  - The resulting tree has identical leaf depths $\{l_i\}$ and strictly preserves the original alphabetic ordering.
- Calculate the total cost $\sum_{i=1}^N w_i \cdot l_i$.

---

## Pseudocode

```text
Algorithm HuTucker(weights, N):
    Input: Array of N weights in alphabetic order
    Output: Tree levels l[1..N] and minimum weighted path length

    // Phase 1: Combination
    nodes = list of N leaf nodes with initial weights and is_internal = False
    While length(nodes) > 1:
        Find compatible pair (u, v) with min weight w(u) + w(v)
        z = new InternalNode(weight = w(u) + w(v), left = u, right = v)
        Replace u with z in nodes; remove v

    // Phase 2: Level Assignment
    Compute depth of each original leaf in the Phase 1 tree:
    For each leaf i: l[i] = depth(leaf_i)

    // Phase 3: Recombination & Cost Evaluation
    TotalCost = 0
    For i = 1 to N:
        TotalCost += weights[i] * l[i]

    Return l, TotalCost
```

---

## Complexity Analysis

| Phase | Time Complexity | Auxiliary Space |
|---|---|---|
| **Phase 1: Combination** | $\mathcal{O}(N^2)$ array / $\mathcal{O}(N \log N)$ heap-based | $\mathcal{O}(N)$ |
| **Phase 2: Level Assignment** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ recursion stack |
| **Phase 3: Recombination** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ |
| **Total** | $\mathcal{O}(N^2)$ direct / $\mathcal{O}(N \log N)$ with priority queues | $\mathcal{O}(N)$ |

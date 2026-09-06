# Question 4: Sorting via Subsequence Reversal Procedure

## Problem Statement
Given a permutation $p$ of integers $1 \dots n$, sort it into increasing order $[1 \dots n]$ using only subsequence reversals `reverse(p, i, j)`.
1. **Mathematical Proof**: Show that any permutation can be sorted using at most $\mathcal{O}(n)$ reversals.
2. **$\mathcal{O}(n \log^2 n)$ Cost Reversal Algorithm**: When the cost of `reverse(p, i, j)` equals its length $|j - i| + 1$, design, analyze, and prove an algorithm sorting $p$ with total reversal cost $\mathcal{O}(n \log^2 n)$.

---

## Part 1: Mathematical Proof for O(n) Reversals

### Theorem
Any permutation $p$ of $n$ elements can be sorted using at most $n-1 = \mathcal{O}(n)$ reversal operations.

### Proof by Selection Reversal
- Iterate $i$ from 1 to $n-1$:
  - Find position $pos$ of target integer $i$ in $p[i \dots n]$.
  - If $pos \ne i$, perform `reverse(p, i, pos)`.
- **Effect**: Element $i$ is moved directly to its correct position $i$.
- **Count**: At most 1 reversal is performed per index $i$. For $n$ elements, at most $n-1$ reversals are required.
- **Conclusion**: Total number of reversals is bounded by $\mathcal{O}(n)$. $\blacksquare$

---

## Part 2: Divide-and-Conquer Reversal Sort in O(n log^2 n) Cost

### Cost Model
Each operation `reverse(p, i, j)` incurs a cost equal to its range length $L = j - i + 1$.

### Block Reversal (Triple Reversal Trick)
To swap two adjacent contiguous blocks $A$ (length $a$) and $B$ (length $b$) in array $[A B] \to [B A]$:
1. `reverse(A)` (cost $a$) $\to [A^R B]$
2. `reverse(B)` (cost $b$) $\to [A^R B^R]$
3. `reverse(A^R B^R)` (cost $a+b$) $\to [B A]$
- **Total Block Swap Cost**: $a + b + (a+b) = 2(a+b) = \mathcal{O}(a+b)$.

### Divide-and-Conquer Algorithm Structure
1. **Divide**: Split permutation $p[low \dots high]$ into left half $p[low \dots mid]$ and right half $p[mid+1 \dots high]$.
2. **Base Case**: Subarray of size $\le 1$ is already sorted.
3. **Partition & Block Swap**:
   - Count how many elements in the left half belong to the upper range ($> mid$), say $k$ elements.
   - Count how many elements in the right half belong to the lower range ($\le mid$), which must also equal $k$.
   - Use Block Reversals to move all elements $\le mid$ into the left half and $> mid$ into the right half.
4. **Recurse**: Recursively sort left subarray $p[low \dots mid]$ and right subarray $p[mid+1 \dots high]$.

---

## Pseudocode

```text
Algorithm ReverseSubsequence(p, i, j):
    While i < j:
        Swap(p[i], p[j])
        i = i + 1
        j = j - 1

Algorithm BlockSwap(p, start_A, len_A, start_B, len_B):
    ReverseSubsequence(p, start_A, start_A + len_A - 1)
    ReverseSubsequence(p, start_B, start_B + len_B - 1)
    ReverseSubsequence(p, start_A, start_B + len_B - 1)

Algorithm ReversalSortDC(p, low, high):
    If low >= high:
        Return

    mid = low + (high - low) / 2

    ReversalSortDC(p, low, mid)
    ReversalSortDC(p, mid + 1, high)

    // Merge step using block reversals
    MergeSubarrays(p, low, mid, high)
```

---

## Complexity Analysis & Recurrence Proof

- **Reversal Cost per Merge Level**:
  At level $k$ of the recursion tree (tree depth $\log n$), block swaps across $n$ elements incur work $\mathcal{O}(n \log n)$.
- **Recurrence Relation**:
  $$T(n) = 2 T(n/2) + \mathcal{O}(n \log n)$$
- **Solving via Master Theorem / Substitution**:
  $$T(n) = \sum_{j=1}^{\log n} \mathcal{O}(n \log n) = \mathcal{O}(n \log^2 n)$$

| Metric | Complexity | Derivation / Notes |
|---|---|---|
| **Number of Reversals** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(\log n)$ reversals per merge level across $\log n$ levels. |
| **Total Reversal Cost** | **$\mathcal{O}(n \log^2 n)$** | Sum of lengths reversed: $T(n) = 2T(n/2) + \mathcal{O}(n \log n) = \mathcal{O}(n \log^2 n)$. |
| **Auxiliary Space** | $\mathcal{O}(\log n)$ | Recursion stack depth. |

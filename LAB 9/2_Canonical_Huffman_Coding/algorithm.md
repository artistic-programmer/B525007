# Question 2: Canonical Huffman Coding

## Problem Statement
Given a set of symbols and their respective frequencies, construct a prefix-free binary code of minimum expected length, and output the **Canonical Huffman Codebook** (where codes are sorted primarily by bit-length and secondarily lexicographically by symbol).

---

## Canonical Huffman Code Algorithm

### 1. Classical Huffman Tree Construction
1. Create a leaf node for each unique symbol with its given frequency.
2. Insert all leaf nodes into a Min-Heap (priority queue keyed by frequency).
3. While the heap contains more than 1 node:
   - Extract the two minimum frequency nodes $u$ and $v$.
   - Create an internal node with weight $\text{freq}(u) + \text{freq}(v)$, with $u$ as left child and $v$ as right child.
   - Insert the new internal node back into the Min-Heap.
4. Traverse the resulting tree to determine the code length $L_i$ for each symbol $s_i$.

### 2. Canonical Codebook Assignment
A canonical Huffman code has the property that all codes of a given length are consecutive binary integers:
1. Sort all symbols in ascending order of their code lengths $L_i$.
2. For symbols of identical code length, break ties lexicographically by symbol character.
3. Assign the binary code to the first symbol:
   $$\text{code}_0 = 0 \quad (\text{represented in } L_0 \text{ bits})$$
4. For each subsequent symbol $i$ from 1 to $n - 1$:
   $$\text{code}_i = (\text{code}_{i - 1} + 1) \ll (L_i - L_{i - 1})$$
   (Increment previous integer by 1, then bit-shift left by length difference).

---

## Pseudocode

```text
Algorithm CanonicalHuffman(symbols, freqs, n):
    1. Build standard Huffman Tree using Min-Heap
    2. Extract bit lengths L[1..n] for all symbols
    3. Sort symbols array by (L[i], symbol[i]) ascending
    4. code = 0
       canonical_codes[0] = FormatBinary(code, L[0])
    5. For i = 1 to n - 1:
           code = (code + 1) << (L[i] - L[i - 1])
           canonical_codes[i] = FormatBinary(code, L[i])
    6. Return canonical_codes
```

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Tree Construction** | $\mathcal{O}(n \log n)$ | $n$ inserts and extracts from binary Min-Heap. |
| **Canonical Sorting** | $\mathcal{O}(n \log n)$ | Sorting $n$ code-length tuples. |
| **Bit Assignment** | $\mathcal{O}(n)$ | Single pass bit manipulation and formatting. |
| **Overall Complexity** | **$\mathcal{O}(n \log n)$** | Time to build tree and sort codebook. |
| **Auxiliary Space** | **$\mathcal{O}(n)$** | Memory for tree nodes, heap, and code tables. |

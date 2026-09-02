# Question 4: Implement HeapSort of N Random Elements Stored in a File

## Problem Statement
Implement HeapSort to sort $N$ randomly generated elements stored in a file. Do the complexity analysis of your algorithm.

---

## Input & Output Representation

### Data Structures & Files
- **Input File**: `input_heap.txt` (contains $N$ randomly generated integers).
- **Output File**: `output_heap_sorted.txt` (contains $N$ sorted integers in non-decreasing order).

```c
typedef struct {
    int size;
    int capacity;
} MaxHeap;
```

---

## Algorithmic Strategy: Binary Max-Heap Sort

### Conceptual Overview
HeapSort is a comparison-based sorting algorithm using a Binary Max-Heap data structure:
1. **File I/O Initialization**:
   - Write $N$ random numbers to `input_heap.txt`. Read into array $A[0 \dots N-1]$.
2. **Phase 1: Build Max-Heap ($\mathcal{O}(N)$)**:
   - Convert array $A$ into a Max-Heap where $A[i] \ge A[2i + 1]$ and $A[i] \ge A[2i + 2]$.
   - Perform `heapify` (bottom-up sift-down) starting from the last non-leaf node $i = \lfloor N/2 \rfloor - 1$ down to root $0$.
3. **Phase 2: Heap Extraction & Sort ($\mathcal{O}(N \log N)$)**:
   - At each step $i = N - 1$ down to $1$:
     - Swap root $A[0]$ (the maximum element in current heap) with $A[i]$.
     - Reduce heap size by 1.
     - Restore Max-Heap property by calling `heapify(A, i, 0)`.
4. **File Persistence & Verification**:
   - Write sorted array to `output_heap_sorted.txt`. Verify non-decreasing order.

---

## Pseudocode

```text
Algorithm Heapify(A, heap_size, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    If left < heap_size and A[left] > A[largest]:
        largest = left

    If right < heap_size and A[right] > A[largest]:
        largest = right

    If largest != i:
        Swap(A[i], A[largest])
        Heapify(A, heap_size, largest)

Algorithm BuildMaxHeap(A, N):
    For i = floor(N / 2) - 1 down to 0:
        Heapify(A, N, i)

Algorithm HeapSort(A, N):
    BuildMaxHeap(A, N)           // O(N)

    For i = N - 1 down to 1:
        Swap(A[0], A[i])          // Move current max to end
        Heapify(A, i, 0)          // Restore heap property in O(log i)
```

---

## Correctness Proof

- **Max-Heap Invariant**: After `BuildMaxHeap`, $A[0]$ contains the maximum element in $A[0 \dots N-1]$.
- **Loop Invariant**: At the start of iteration $i$ during extraction:
  - Subarray $A[i+1 \dots N-1]$ contains the $(N - 1 - i)$ largest elements of the original array, fully sorted in non-decreasing order.
  - Subarray $A[0 \dots i]$ forms a valid Max-Heap containing the remaining elements.
- Swapping $A[0]$ with $A[i]$ places the $(N-i)$-th largest element into index $i$, and calling `Heapify(A, i, 0)` restores the Max-Heap property. By induction, $A$ is fully sorted when $i = 0$.

---

## Complexity Analysis

| Phase | Time Complexity | Mathematical Proof / Explanation |
|---|---|---|
| **Build Max-Heap** | $\mathcal{O}(N)$ | Nodes at height $h$ number at most $\lceil N/2^{h+1} \rceil$. Work per node = $\mathcal{O}(h)$. Total work: $\sum_{h=0}^{\lfloor \log N \rfloor} \frac{N}{2^{h+1}} \cdot \mathcal{O}(h) = \mathcal{O}\left(N \sum \frac{h}{2^h}\right) = \mathcal{O}(N)$. |
| **Heap Extraction Pass** | $\mathcal{O}(N \log N)$ | $N - 1$ iterations. Each iteration extracts max and calls `Heapify` of height $\mathcal{O}(\log N)$. Total: $\sum_{i=1}^{N-1} \mathcal{O}(\log i) = \mathcal{O}(N \log N)$. |
| **Overall Time Complexity** | **$\Theta(N \log N)$** | Guaranteed $\Theta(N \log N)$ in **Best**, **Average**, and **Worst** cases. |
| **Auxiliary Space** | **$\mathcal{O}(1)$** | In-place sorting requiring zero additional array allocations. |

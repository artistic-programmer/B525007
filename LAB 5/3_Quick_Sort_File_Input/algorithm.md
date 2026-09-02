# Question 3: Implement QuickSort of N Random Elements Stored in a File

## Problem Statement
Implement QuickSort to sort $N$ randomly generated elements stored in a file and write the sorted output to a destination file.

---

## Input & Output Representation

### Data Structures & File Paths
- **Input File**: `input_random.txt` (contains $N$ randomly generated integers).
- **Output File**: `output_sorted.txt` (contains $N$ sorted integers in non-decreasing order).

```c
typedef struct {
    int n;
    const char *input_filename;
    const char *output_filename;
} QuickSortFileJob;
```

---

## Algorithmic Strategy: Divide-and-Conquer QuickSort

### Key Principles
1. **File I/O Stream Processing**:
   - Generate $N$ random integers and write them to `input_random.txt`.
   - Open `input_random.txt`, read $N$ elements into a dynamic memory buffer $A[0 \dots N-1]$.
2. **Divide-and-Conquer QuickSort**:
   - **Divide**: Partition the array $A[low \dots high]$ around pivot $P = A[high]$ into two subarrays $A[low \dots p-1] \le P$ and $A[p+1 \dots high] \ge P$.
   - **Conquer**: Recursively apply QuickSort to the left subarray $A[low \dots p-1]$ and right subarray $A[p+1 \dots high]$.
   - **Combine**: Subarrays are sorted in-place; no explicit combination step is needed.
3. **Persist Result**:
   - Open `output_sorted.txt` and write the sorted array $A$ line-by-line / space-delimited.

---

## Pseudocode

```text
Algorithm QuickSort(A, low, high):
    Input: Array A of integers, indices low and high
    Output: Array A sorted in non-decreasing order

    If low < high:
        pivot_idx = Partition(A, low, high)
        QuickSort(A, low, pivot_idx - 1)
        QuickSort(A, pivot_idx + 1, high)

Algorithm Partition(A, low, high):
    pivot = A[high]
    i = low - 1

    For j = low to high - 1:
        If A[j] <= pivot:
            i = i + 1
            Swap(A[i], A[j])

    Swap(A[i + 1], A[high])
    Return i + 1

Algorithm QuickSortFileWorkflow(N, in_file, out_file):
    1. GenerateNRandomElementsToFile(N, in_file)
    2. A = ReadElementsFromFile(N, in_file)
    3. QuickSort(A, 0, N - 1)
    4. WriteElementsToFile(A, N, out_file)
    5. VerifySortedFile(out_file)
```

---

## Correctness Proof

- **Partition Correctness**: Lomuto partitioning guarantees that upon returning index $p$, $A[k] \le A[p]$ for all $k < p$, and $A[m] \ge A[p]$ for all $m > p$.
- **Inductive Base**: Subarrays of size 0 or 1 are trivially sorted.
- **Inductive Step**: Assuming QuickSort correctly sorts subarrays of size $< N$, recursively sorting $A[low \dots p-1]$ and $A[p+1 \dots high]$ yields a fully sorted array across $A[low \dots high]$.

---

## Complexity Analysis

| Metric | Time Complexity | Derivation / Notes |
|---|---|---|
| **Average Time Complexity** | $\Theta(N \log N)$ | Balanced partitioning recurrence: $T(N) = 2T(N/2) + \Theta(N) \implies T(N) = \Theta(N \log N)$. |
| **Best Time Complexity** | $\Theta(N \log N)$ | Pivot divides array into equal halves at every recursive level. |
| **Worst Time Complexity** | $\mathcal{O}(N^2)$ | Occurs when pivot selected is always minimum or maximum element. Mitigated using randomized pivot or median-of-three. |
| **Auxiliary Space** | $\mathcal{O}(\log N)$ | Call stack depth for balanced recursion. |

# Maximum and Minimum using Divide and Conquer

A C implementation to find the minimum and maximum elements of an array using the **Divide and Conquer** approach while keeping the number of comparisons within the required `3n/2` bound.

## Method Used

The array is recursively divided into two halves.

For each half, the minimum and maximum elements are found recursively. The results are then combined using:

- One comparison to find the overall minimum.
- One comparison to find the overall maximum.

For two elements, only one comparison is required.

## Complexity

- **Time Complexity:** `O(n)`
- **Space Complexity:** `O(log n)` due to recursion.

For even `n`, the number of comparisons is:

```text
3n/2 - 2
```

Therefore:

```text
3n/2 - 2 < 3n/2
```

which satisfies the required comparison bound.

## Build

```bash
gcc main.c -o max_min
```

## Run

### Windows

```bash
.\max_min.exe
```

### Linux/macOS

```bash
./max_min
```

## Validation

The program counts every comparison performed by the algorithm and displays the actual number of comparisons along with the theoretical `3n/2` bound.

### Example

```text
Enter number of elements: 8
Enter 8 elements:
8 3 12 5 7 2 15 4

Minimum = 2
Maximum = 15
Number of comparisons = 10

Theoretical bound (3n/2) = 12.0
Result: Comparison bound is satisfied.
```

## Conclusion

The Divide and Conquer approach finds both the minimum and maximum in linear time while requiring fewer comparisons than finding them independently.
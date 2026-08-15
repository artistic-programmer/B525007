# Binary Search vs Ternary Search

A C program that compares recursive Binary Search and Ternary Search on sorted arrays. The number of element comparisons performed by both algorithms is recorded and visualized using GNUPlot.

## Methods Used

### Binary Search

The sorted array is divided into two nearly equal parts using one middle element. Based on the comparison with the target, one half is discarded and the search continues recursively.

- Time Complexity: `O(log₂ n)`
- Space Complexity: `O(log n)` due to recursion

### Ternary Search

The sorted array is divided into three nearly equal parts using two middle elements. Based on two comparisons, one of the three sections is selected recursively.

- Time Complexity: `O(log₃ n)`
- Space Complexity: `O(log n)` due to recursion

## Comparison

Although ternary search reduces the search space to one-third at every step, it performs up to two element comparisons per recursive level. Binary search generally requires fewer total comparisons.

The program validates this by running both algorithms on the same sorted arrays and plotting their comparison counts.

## Project Structure

```text
07-Binary-vs-Ternary-Search/
│
├── binary_search.c
├── ternary_search.c
├── main.c
│
├── scripts/
│   └── comparison.gnu
│
└── output/
    └── comparison.dat
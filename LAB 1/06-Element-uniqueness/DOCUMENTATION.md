# Element Uniqueness

A C implementation to determine whether an array contains duplicate elements using two different approaches:

1. **Sorting + Adjacent Comparison**
2. **Hash Map (Hash Table)**

The project compares both methods based on their time and space complexities.

---

## Project Structure

```
06-Element-Uniqueness/
│
├── UsingHashMap_OptimalSolution.c
├── UsingSorting_BetterSolution.c
│
├── UsingHashMap_OptimalSolution.exe
└── UsingSorting_BetterSolution.exe
```

---

## Approach 1 : Hash Map

### Algorithm

1. Traverse the array.
2. Insert every element into a hash table.
3. If an element already exists in the hash table, a duplicate is found.

### Complexity

- **Time Complexity:** `O(n)` (Average Case)
- **Space Complexity:** `O(n)`

---

## Approach 2 : Sorting

### Algorithm

1. Sort the array.
2. Compare every adjacent pair.
3. If two adjacent elements are equal, a duplicate exists.

### Complexity

- **Time Complexity:** `O(n log n)`
- **Space Complexity:** `O(1)` (Ignoring recursion stack)

---

## Requirements

- GCC Compiler

---

## Build

### Hash Map Solution

```bash
gcc UsingHashMap_OptimalSolution.c -o UsingHashMap_OptimalSolution
```

### Sorting Solution

```bash
gcc UsingSorting_BetterSolution.c -o UsingSorting_BetterSolution
```

---

## Run

### Windows

```bash
.\UsingHashMap_OptimalSolution.exe
```

or

```bash
.\UsingSorting_BetterSolution.exe
```

### Linux/macOS

```bash
./UsingHashMap_OptimalSolution
```

or

```bash
./UsingSorting_BetterSolution
```

---

## Conclusion

- The **Hash Map** approach is faster with an average time complexity of **O(n)** but requires additional memory.
- The **Sorting** approach requires less extra memory but takes **O(n log n)** time due to sorting.
- For sufficiently large values of **n**, the Hash Map approach generally performs better when additional memory is available.
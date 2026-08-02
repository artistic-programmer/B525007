# Find the Partition Point

A C program to find the partition point in a binary array containing a sequence of `0`s followed by a sequence of `1`s.

---

## Problem Statement

Given a sorted binary array of the form:

```
0 0 0 0 1 1 1 1
```

find the exact index where the transition from `0` to `1` occurs.

---

## Algorithm

The program uses **Binary Search** to efficiently locate the first occurrence of `1`, which represents the partition point.

---

## Complexity Analysis

- **Time Complexity:** `O(log n)`
- **Space Complexity:** `O(1)`

---

## Prerequisites

- GCC Compiler (`gcc`)

---

## Build

```bash
gcc main.c -o partition
```

---

## Run

**Windows**

```bash
.\partition.exe
```

**Linux/macOS**

```bash
./partition
```

---

## Sample Input

```
10
0 0 0 0 0 1 1 1 1 1
```

## Sample Output

```
Partition Point = 5
Transition occurs between index 4 and 5.
```

---

## Conclusion

Using **Binary Search** reduces the search time from **O(n)** (Linear Search) to **O(log n)**, making it an efficient solution for large sorted binary arrays.
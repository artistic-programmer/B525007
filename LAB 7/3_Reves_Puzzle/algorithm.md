# Question 3: Reve's Puzzle (4-Peg Towers of Hanoi)

## Problem Statement
There are $n$ disks of different sizes and 4 pegs ($A, B, C, D$). Initially, all $n$ disks are on peg $A$ in order of size (largest on bottom, smallest on top).
1. Devise an algorithm that transfers 8 disks from peg $A$ to peg $B$ in exactly **33 moves**.
2. Generalize the algorithm for an $n$-disk problem using the Frame-Stewart algorithm.
3. Derive the complexity analysis.

---

## The Frame-Stewart Divide-and-Conquer Algorithm

### Core Strategy
For $n$ disks and 4 pegs (Source $A$, Destination $B$, Auxiliaries $C, D$):
1. **Transfer Top $k$ Disks**: Move the top $k$ smallest disks from $A$ to $C$ using all 4 pegs ($R(k)$ moves).
2. **Transfer Bottom $n-k$ Disks**: Move the remaining $n-k$ largest disks from $A$ to $B$ using 3 pegs ($2^{n-k} - 1$ moves via standard 3-peg Hanoi).
3. **Transfer Top $k$ Disks to Destination**: Move the $k$ disks from $C$ to $B$ using all 4 pegs ($R(k)$ moves).

### Recurrence Relation
$$R(n) = 2 R(k) + 2^{n-k} - 1$$

### Optimal Partition Parameter $k$
The integer $k$ ($1 \le k < n$) that minimizes $R(n)$ is given by:
$$k(n) = n - \left\lfloor \sqrt{2n+1} + 0.5 \right\rfloor + 1 = n - \text{round}(\sqrt{2n})$$

---

## 8-Disk 33-Move Proof Verification

For $n = 8$ disks:
- Optimal $k(8) = 8 - \text{round}(\sqrt{16}) + 1 = 8 - 4 + 1 = 5$ (or $k=4$).
- Move recurrence evaluation:
  - $R(1) = 1$
  - $R(2) = 3$
  - $R(3) = 5$ ($k=1, 2(1) + 3 = 5$)
  - $R(4) = 9$ ($k=2, 2(3) + 3 = 9$)
  - $R(5) = 13$ ($k=2, 2(3) + 7 = 13$)
  - $R(8) = 2 \cdot R(5) + (2^{8-5} - 1) = 2(13) + (2^3 - 1) = 26 + 7 = \mathbf{33 \text{ moves}}$.

---

## Pseudocode

```text
Algorithm RevesPuzzle(n, source, dest, aux1, aux2):
    If n == 0:
        Return
    If n == 1:
        Print "Move disk 1 from ", source, " to ", dest
        Return

    k = n - Round(Sqrt(2 * n))

    // Step 1: Move top k disks to aux1 using all 4 pegs
    RevesPuzzle(k, source, aux1, dest, aux2)

    // Step 2: Move remaining n-k disks to dest using 3 pegs
    StandardHanoi3Pegs(n - k, k + 1, source, dest, aux2)

    // Step 3: Move k disks from aux1 to dest using all 4 pegs
    RevesPuzzle(k, aux1, dest, source, aux2)
```

---

## Complexity Analysis

| Metric | Complexity | Derivation / Notes |
|---|---|---|
| **Number of Moves** | $\mathcal{O}\left(2^{\sqrt{2n}}\right)$ | Sub-exponential move growth (much faster than $2^n - 1$). |
| **8-Disk Move Count** | **33 moves** | Matches exact puzzle specification. |
| **Time Complexity** | $\mathcal{O}\left(2^{\sqrt{2n}}\right)$ | Proportional to number of moves executed. |
| **Auxiliary Stack Space** | $\mathcal{O}(n)$ | Recursion stack depth. |

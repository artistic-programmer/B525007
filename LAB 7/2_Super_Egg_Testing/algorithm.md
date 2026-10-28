# Question 2: Super Egg Drop Testing Experiment (Dynamic Programming)

## Problem Statement
Determine the minimum number of egg drops guaranteed to find the critical highest safe floor in a building of $F$ floors using $E$ eggs in the worst case.
1. Solve the 2-egg, 100-floor puzzle.
2. Design a generalized Dynamic Programming solution for $E$ eggs and $F$ floors.
3. Analyze time and space complexity.

---

## 2-Egg, 100-Floor Special Case

### Optimal Stepping Strategy
With 2 eggs, dropping the first egg at equal intervals of $x$ floors causes unequal worst-case drops if the egg breaks high up. To equalize the total drops across all outcomes:
$$x + (x-1) + (x-2) + \dots + 1 = \frac{x(x+1)}{2} \ge 100$$
$$\frac{x(x+1)}{2} \ge 100 \implies x^2 + x - 200 \ge 0 \implies x = 14$$

### Drop Floor Sequence for 2 Eggs & 100 Floors
- Drop 1: Floor 14. If breaks $\to$ test floors 1..13 with 2nd egg (max 14 drops total).
- Drop 2: Floor 27 (14+13). If breaks $\to$ test floors 15..26 with 2nd egg (max 14 drops total).
- Drop 3..12: Floors 39, 50, 60, 69, 77, 84, 90, 95, 99, 100.
- **Worst-Case Guaranteed Drops**: **14 drops**.

---

## Generalized Dynamic Programming Solution for E Eggs and F Floors

### Approach 1: Min-Max Floor Recurrence
Let $DP[e][f]$ be the minimum number of drops needed to test $f$ floors using $e$ eggs in the worst case.

#### Recurrence Relation
$$DP[e][f] = 1 + \min_{1 \le k \le f} \max\left( DP[e-1][k-1],\, DP[e][f-k] \right)$$

#### Base Cases
- $DP[1][f] = f$ (With 1 egg, must test floors sequentially from 1 to $f$).
- $DP[e][0] = 0$ (0 floors requires 0 drops).
- $DP[e][1] = 1$ (1 floor requires 1 drop).

---

### Approach 2: Dual DP State (Moves vs Eggs)
Let $DP[m][e]$ be the maximum number of floors that can be tested using $m$ moves and $e$ eggs:
$$DP[m][e] = DP[m-1][e-1] + DP[m-1][e] + 1$$
We find the smallest move count $m$ such that $DP[m][E] \ge F$.

---

## Pseudocode (Approach 1: Min-Max DP)

```text
Algorithm SuperEggDrop(E, F):
    Input: Number of eggs E, Number of floors F
    Output: Minimum guaranteed drops in worst case

    Initialize 2D array DP[E + 1][F + 1]

    For f = 0 to F:
        DP[1][f] = f

    For e = 1 to E:
        DP[e][0] = 0
        DP[e][1] = 1

    For e = 2 to E:
        For f = 2 to F:
            min_drops = INFINITY
            For k = 1 to f:
                res = 1 + MAX(DP[e - 1][k - 1], DP[e][f - k])
                If res < min_drops:
                    min_drops = res
            DP[e][f] = min_drops

    Return DP[E][F]
```

---

## Complexity Analysis

| Algorithm Variant | Time Complexity | Auxiliary Space | Technique |
|---|---|---|---|
| **2-Egg 100-Floor Equation** | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Triangular sum inequality |
| **Standard DP (Approach 1)** | $\mathcal{O}(E \cdot F^2)$ | $\mathcal{O}(E \cdot F)$ | 2D Dynamic Programming |
| **Binary Search DP** | $\mathcal{O}(E \cdot F \log F)$ | $\mathcal{O}(E \cdot F)$ | DP + Binary Search for $k$ |
| **Dual State DP (Approach 2)** | **$\mathcal{O}(E \cdot \log F)$** | $\mathcal{O}(E)$ | State inversion DP |

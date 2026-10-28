# Question 4: Security Switches Puzzle (Baguenaudier / Gray Code)

## Problem Statement
A row of $n$ security switches (indexed $n \dots 1$ from left to right, where $1$ is rightmost) protects an entrance. Initially, all switches are ON ($11\dots1$).
Manipulations allowed:
1. **Rule (i)**: The rightmost switch $S_1$ may be turned ON or OFF at will.
2. **Rule (ii)**: Any other switch $S_i$ ($i > 1$) may be toggled if and only if switch $S_{i-1}$ is ON and all switches $S_{i-2} \dots S_1$ to its right are OFF (pattern `100...0`).
3. **Rule (iii)**: Only one switch toggled per move.

Devise an algorithm to turn off all switches in the minimum number of moves, prove its formula, and analyze complexity.

---

## Mathematical Formula for Minimum Moves

### Exact Closed-Form Expression
The minimum number of moves $S(n)$ required to turn off $n$ switches from initial state $11\dots1$ to $00\dots0$ is given by:
$$S(n) = \begin{cases} \dfrac{2^{n+1} - 2}{3} & \text{if } n \text{ is even} \\[8pt] \dfrac{2^{n+1} - 1}{3} & \text{if } n \text{ is odd} \end{cases}$$

### Sequence Table for Small $n$

| Switches $n$ | Minimum Moves $S(n)$ | Move Breakdown |
|:---:|:---:|:---|
| 1 | 1 | Toggle $S_1$ OFF |
| 2 | 2 | Toggle $S_1$ OFF, Toggle $S_2$ OFF |
| 3 | 5 | $S_1$ OFF, $S_3$ OFF, $S_1$ ON, $S_2$ OFF, $S_1$ OFF |
| 4 | 10 | $S(4) = (32 - 2)/3 = 10$ moves |
| 5 | 21 | $S(5) = (64 - 1)/3 = 21$ moves |
| 6 | 42 | $S(6) = (128 - 2)/3 = 42$ moves |

---

## Recursive Deactivation Strategy

To turn off $k$ switches (assuming switches $1 \dots k$ are ON):
- `TurnOff(k)`:
  1. `TurnOff(k - 2)` $\implies$ prepares right side pattern `100...0` at $k-1$.
  2. Toggle $S_k$ OFF.
  3. `TurnOn(k - 2)` $\implies$ restores right side to enable turning off $S_{k-1}$.
  4. `TurnOff(k - 1)`.

To turn on $k$ switches:
- `TurnOn(k)`:
  1. `TurnOn(k - 1)`.
  2. `TurnOff(k - 2)`.
  3. Toggle $S_k$ ON.
  4. `TurnOn(k - 2)`.

---

## Complexity Analysis

| Metric | Complexity | Derivation |
|---|---|---|
| **Recurrence Relation** | $S(n) = S(n-1) + 2 S(n-2) + 1$ | Solution $S(n) = \frac{2^{n+1} - 1.5 \pm 0.5}{3} = \Theta(2^n)$. |
| **Time Complexity** | $\mathcal{O}(2^n)$ | Exponential in number of switches $n$. |
| **Auxiliary Space** | $\mathcal{O}(n)$ | Recursion stack depth. |

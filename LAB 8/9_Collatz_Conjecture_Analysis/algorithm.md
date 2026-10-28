# Question 9: Collatz Conjecture Trajectory Analysis

## Problem Statement
The Collatz Conjecture (also known as the $3n + 1$ problem or Ulam conjecture) defines a recurrence relation for any strictly positive integer $n \ge 1$:
$$T(n) = \begin{cases} \dfrac{n}{2} & \text{if } n \text{ is even} \\[8pt] 3n + 1 & \text{if } n \text{ is odd} \end{cases}$$
The sequence terminates when $n = 1$. Design a modular C program with integer overflow handling (`unsigned long long`), dynamic memory allocation, and functional decomposition to analyze:
1. The exact trajectory, total stopping time (steps), and peak value for a single user-provided starting integer $n \ge 1$.
2. Statistical behavior across an interval $[a, b]$, identifying the starting number with the longest trajectory and highest peak value.

---

## Mathematical Formulation & Properties

### Sequence Generation
Given starting integer $n_0$:
$$n_{k+1} = T(n_k)$$
The stopping time $S(n_0)$ is the minimum index $k$ such that $n_k = 1$.

### Overflow Considerations
Intermediate terms in the $3n + 1$ sequence can grow significantly larger than the initial value $n_0$ (e.g., $n = 27$ reaches peak 9232 and takes 111 steps). Using 64-bit unsigned integers (`unsigned long long`) prevents arithmetic overflow for standard integer inputs up to millions.

---

## Dynamic Memory Allocation for Trajectory
Because the trajectory length is not known a priori:
- Allocate an initial buffer of capacity $C = 128$.
- Whenever step count reaches capacity, double the buffer capacity via `realloc`.
- Trim or return the exact dynamically allocated trajectory array.

---

## Pseudocode

```text
Algorithm CollatzTrajectory(n):
    Input: Positive integer n >= 1
    Output: Array of trajectory values, total steps, peak value

    capacity = 128
    path = Allocate array of size capacity
    steps = 0
    curr = n
    peak = n

    While curr != 1:
        path[steps++] = curr
        If steps >= capacity:
            capacity *= 2
            path = Reallocate(path, capacity)

        If curr is even:
            curr = curr / 2
        Else:
            curr = 3 * curr + 1

        If curr > peak:
            peak = curr

    path[steps++] = 1
    Return path, steps - 1, peak

Algorithm AnalyzeInterval(a, b):
    max_steps = 0, best_n_steps = a
    max_peak = 0, best_n_peak = a

    For x = a to b:
        steps, peak = ComputeStepsAndPeak(x)
        If steps > max_steps:
            max_steps = steps
            best_n_steps = x
        If peak > max_peak:
            max_peak = peak
            best_n_peak = x

    Return (best_n_steps, max_steps, best_n_peak, max_peak)
```

---

## Complexity Analysis

| Metric | Single Number $n$ | Interval $[a, b]$ |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(S(n))$ where $S(n)$ is stopping time | $\mathcal{O}\left(\sum_{x=a}^b S(x)\right)$ |
| **Auxiliary Space** | $\mathcal{O}(S(n))$ to store trajectory path | $\mathcal{O}(1)$ without storing full paths |
| **Overflow Handling** | 64-bit `unsigned long long` | 64-bit `unsigned long long` |

# Question 7: Minimise Deviation in Array

## Problem Statement
Given an array `nums` of $N$ positive integers, two types of operations can be applied to any element repeatedly:
1. If the element is **even**, divide it by $2$ ($x \leftarrow x / 2$).
2. If the element is **odd**, multiply it by $2$ ($x \leftarrow 2x$).

The **deviation** of the array is the difference between the maximum and minimum elements:
$$\text{deviation} = \max(A) - \min(A)$$

Find and return the **minimum possible deviation** achievable through any sequence of valid operations.

---

## Greedy Max-Heap Reduction Strategy

### 1. Conceptual Principle
- An odd element $x$ can only be multiplied by $2$ once; subsequent multiplications are redundant because dividing the resulting even number brings it right back to $x$. Hence, the maximum value an odd element can ever reach is $2x$.
- An even element can only be reduced by repeatedly dividing by $2$ until it turns odd.
- **Greedy Invariant**: If we initially bring every element to its theoretical maximum upper bound (by doubling all odd numbers), every subsequent operation can only **decrease** the values in the array.
- By tracking the current minimum `min_val` and repeatedly halving the current maximum extracted from a **Max-Heap**, we systematically compress the range until the current maximum becomes odd (at which point it can no longer be decreased, establishing the optimal lower bound for the range span).

### 2. Algorithmic Steps
1. Traverse the array:
   - If an element $x$ is odd, replace it with $2x$.
   - Insert each number into a **Max-Heap**.
   - Maintain the running minimum value `min_val` across all elements.
2. Initialize `min_deviation = MaxHeap.peek() - min_val`.
3. In a loop:
   - Extract the current maximum element $M$ from the Max-Heap.
   - Update `min_deviation = min(min_deviation, M - min_val)`.
   - If $M$ is **even**:
     - Halve it: $M' = M / 2$.
     - Update `min_val = min(min_val, M')`.
     - Insert $M'$ back into the Max-Heap.
   - If $M$ is **odd**:
     - $M$ cannot be reduced any further. Terminate the loop.
4. Return `min_deviation`.

---

## Pseudocode

```text
Algorithm MinimizeDeviation(nums, N):
    Input: Array nums of size N
    Output: Minimum deviation possible

    Initialize MaxHeap H
    min_val = INFINITY

    For each x in nums:
        If x % 2 != 0:
            x = x * 2
        H.insert(x)
        min_val = min(min_val, x)

    min_deviation = H.top() - min_val

    While H.top() % 2 == 0:
        max_val = H.extract_max()
        half_val = max_val / 2
        min_val = min(min_val, half_val)
        H.insert(half_val)
        min_deviation = min(min_deviation, H.top() - min_val)

    Return min_deviation
```

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(N \log(\max A) \log N)$ | Each element can be halved at most $\log(\max A)$ times, each requiring a heap extraction and insertion of cost $\mathcal{O}(\log N)$. |
| **Auxiliary Space** | $\mathcal{O}(N)$ | Space for the max-heap containing $N$ integers. |

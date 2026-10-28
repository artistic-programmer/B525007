# Question 1: Fractional Knapsack with Deterioration Rate

## Problem Statement
You have $n$ items with base values $v_i$, weights $w_i$, and decay rates $\lambda_i > 0$. If an item is consumed at time $t$, its effective value density decays according to:
$$\text{Density}_i(t) = \frac{v_i}{w_i} - \lambda_i \cdot t$$
Knapsack capacity is $W$. Determine the optimal scheduling order and fractional choices to maximize the total value collected.

---

## Greedy Algorithmic Formulation

### 1. Exchange Argument for Optimal Sequencing (Smith's Rule)
Suppose two items $A$ and $B$ are both selected. Consuming item $A$ takes time proportional to its weight $w_A$.
- **Schedule $A$ before $B$**: Item $B$ is delayed by time $w_A$. The decay penalty inflicted on $B$ is $\lambda_B \cdot w_A \cdot w_B$.
- **Schedule $B$ before $A$**: Item $A$ is delayed by time $w_B$. The decay penalty inflicted on $A$ is $\lambda_A \cdot w_B \cdot w_A$.
- **Optimality Criterion**:
  Scheduling $A$ before $B$ is strictly superior if:
  $$\lambda_A \cdot w_B \cdot w_A \ge \lambda_B \cdot w_A \cdot w_B \iff \frac{\lambda_A}{w_A} \ge \frac{\lambda_B}{w_B}$$
  Combined with initial value densities, items with higher effective density $\frac{v_i}{w_i}$ and higher decay sensitivity $\lambda_i$ should be processed earliest to capture maximum residual value before deterioration sets in.

### 2. Fractional Greedy Selection
1. Sort items in descending order of their priority metric:
   $$\text{Priority}_i = \frac{v_i}{w_i} + \alpha \cdot \lambda_i$$
2. Iterate through sorted items:
   - If knapsack remaining capacity $W_{rem} \ge w_i$: take full item ($f_i = 1.0$), advance time $t \leftarrow t + w_i$, and reduce $W_{rem} \leftarrow W_{rem} - w_i$.
   - If $0 < W_{rem} < w_i$: take fraction $f_i = W_{rem} / w_i$, advance time $t \leftarrow t + W_{rem}$, set $W_{rem} = 0$, and terminate.

---

## Pseudocode

```text
Algorithm DeterioratingFractionalKnapsack(items, n, W):
    Input: Array of items with (value v, weight w, decay lambda), capacity W
    Output: Optimal schedule, fractions taken, and total realized value

    Sort items in descending order of initial density / decay priority

    current_time = 0.0
    remaining_capacity = W
    total_value = 0.0

    For i = 0 to n - 1:
        If remaining_capacity <= 0:
            Break

        weight_taken = MIN(remaining_capacity, items[i].w)
        fraction = weight_taken / items[i].w

        // Average time of consumption during interval [t, t + weight_taken]
        avg_time = current_time + (weight_taken / 2.0)
        effective_density = (items[i].v / items[i].w) - (items[i].lambda * avg_time)
        If effective_density < 0:
            effective_density = 0

        item_value = effective_density * weight_taken
        total_value += item_value

        current_time += weight_taken
        remaining_capacity -= weight_taken

    Return total_value
```

---

## Complexity Analysis

| Phase | Time Complexity | Auxiliary Space |
|---|---|---|
| **Sorting Items** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(1)$ (in-place) / $\mathcal{O}(n)$ |
| **Greedy Scan** | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| **Overall Complexity** | **$\mathcal{O}(n \log n)$** | **$\mathcal{O}(n)$** |

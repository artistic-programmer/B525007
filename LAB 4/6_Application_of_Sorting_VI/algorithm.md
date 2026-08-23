# Question 6: Application of Sorting-VI

## Problem Statement
You are given a set $S$ of $n$ intervals on a line, with the $i$-th interval described by its left and right endpoints $(l_i, r_i)$. Give an $\mathcal{O}(n \log n)$ algorithm to identify a point $p$ on the line that is in the largest number of intervals.

**Example**:
- Input: $S = \{(10, 40), (20, 60), (50, 90), (15, 70)\}$
- Output: No point exists in all four intervals, but $p = 50$ is an example of a point in 3 intervals (specifically in $[20, 60]$, $[50, 90]$, and $[15, 70]$).

You can assume an endpoint counts as being in its interval (closed intervals $[l_i, r_i]$). By choosing a suitable input and output representation, write a program in C to validate your algorithm.

---

## Input & Output Representation

### Data Structures
Each interval is a closed segment $[l_i, r_i]$:

```c
typedef struct {
    double left;
    double right;
    int id;
} Interval;

typedef enum {
    ENDPOINT_RIGHT = -1, // Right endpoint (end of interval)
    ENDPOINT_LEFT  = +1  // Left endpoint (start of interval)
} EndpointType;

typedef struct {
    double coord;
    EndpointType type;
    int interval_id;
} Endpoint;

typedef struct {
    double point;
    int max_overlap_count;
} OverlapResult;
```

---

## Algorithmic Strategy: Sweep-Line with Closed-Interval Tie Breaking

### Key Principles
1. **Endpoint Decomposition**:
   - For each interval $[l_i, r_i]$, create two events:
     - $(l_i, \text{ENDPOINT\_LEFT}, i)$ with delta $+1$.
     - $(r_i, \text{ENDPOINT\_RIGHT}, i)$ with delta $-1$.
   - Total number of endpoints = $2n$.

2. **Crucial Sorting & Tie-Breaking Rule**:
   - Endpoints must be sorted in ascending order of coordinate `coord`.
   - **Tie-Breaking for Closed Endpoints**: If two endpoints share the exact same coordinate $x$:
     $$\text{ENDPOINT\_LEFT} (+1) \quad \text{must be processed BEFORE} \quad \text{ENDPOINT\_RIGHT} (-1)$$
   - **Why?** Since intervals are closed, a point at the boundary $p = x$ belongs to both an interval starting at $x$ and an interval ending at $x$. Incrementing the counter before decrementing ensures the overlap count at $p = x$ correctly includes both intervals simultaneously.

3. **Sweep-Line Traversal**:
   - Maintain `current_overlap = 0`, `max_overlap = 0`, `best_point = 0.0`.
   - Traverse the sorted endpoints:
     $$\text{current\_overlap} \leftarrow \text{current\_overlap} + E[i].\text{type}$$
     - If $\text{current\_overlap} > \text{max\_overlap}$:
       $$\text{max\_overlap} = \text{current\_overlap}, \quad \text{best\_point} = E[i].\text{coord}$$
   - Return `best_point` and `max_overlap`.

---

## Pseudocode

```text
Algorithm FindMaxOverlappingPoint(S, n):
    Input: Array S of n closed intervals [l[i], r[i]]
    Output: Optimal point p and maximum overlap count

    1. Allocate Endpoints array of size 2 * n
    2. For i = 0 to n - 1:
           Endpoints[2 * i]     = Endpoint(S[i].left,  +1, i)
           Endpoints[2 * i + 1] = Endpoint(S[i].right, -1, i)

    3. Sort Endpoints using comparator:
           If E1.coord != E2.coord:
               Return E1.coord < E2.coord
           Else:
               Return E1.type > E2.type   // +1 precedes -1

    4. current_overlap = 0
    5. max_overlap = 0
    6. best_point = S[0].left

    7. For i = 0 to 2 * n - 1:
           current_overlap = current_overlap + Endpoints[i].type
           If current_overlap > max_overlap:
               max_overlap = current_overlap
               best_point = Endpoints[i].coord

    8. Return (best_point, max_overlap)
```

---

## Correctness Proof

- **Discrete Invariance**: The number of active intervals containing point $x$, denoted $C(x) = \sum_{i=1}^n [l_i \le x \le r_i]$, is a piecewise constant step function that changes value only at the endpoints $\{l_i\} \cup \{r_i\}$.
- Because intervals are closed, the maximum value of $C(x)$ is always achieved at least at one of the left endpoints $l_i$ (or at a shared coordinate $x = l_i = r_j$).
- By ordering $+1$ before $-1$ at identical coordinates, the sweep-line correctly captures the maximum value of $C(x)$ at all boundary points.

---

## Complexity Analysis

| Step | Time Complexity | Space Complexity |
|---|---|---|
| Creating Endpoints | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ |
| Sorting $2n$ Endpoints | $\mathcal{O}(n \log n)$ | $\mathcal{O}(1)$ aux / $\mathcal{O}(n)$ |
| Sweep-Line Traversal | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| **Total** | **$\mathcal{O}(n \log n)$** | **$\mathcal{O}(n)$** |

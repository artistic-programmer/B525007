# Question 2: Dynamic Connected Components in a Grid (Number of Islands II)

## Problem Statement
Given an $R \times C$ 2D grid initially filled entirely with water ($0$), land cells ($1$) are added dynamically one by one at given coordinates $(r_1, c_1), (r_2, c_2), \dots, (r_k, c_k)$.
After each land cell addition, determine and output the **current number of 4-directionally connected land components (islands)**. Two land cells belong to the same island if they are adjacent horizontally or vertically.

---

## Disjoint Set Union (DSU) with 2D Coordinate Flattening

### 1. Conceptual Principle
Instead of executing a full 2D breadth-first/depth-first search after each cell addition (which costs $\mathcal{O}(R \times C)$ per operation, leading to $\mathcal{O}(K \cdot R \cdot C)$ total time), we model the problem as an **incremental dynamic connectivity** problem on a planar graph:
- **2D-to-1D Coordinate Flattening**:
  Map each cell $(r, c)$ in the $R \times C$ grid to a unique scalar index in $[0, R \cdot C - 1]$:
  $$\text{id}(r, c) = r \cdot C + c$$
- **Incremental Island Count**:
  1. When a cell $(r, c)$ turns from water to land:
     - Initialize a new disjoint set for $\text{id}(r, c)$ with `parent[id] = id`.
     - Increment `island_count` by $1$ (treating the cell as an isolated new island).
  2. Inspect its 4 orthogonal neighbors $(r \pm 1, c)$ and $(r, c \pm 1)$:
     - If a neighbor $(nr, nc)$ is within bounds and is already land:
       - Find the component roots: $root_1 = \text{find}(\text{id}(r, c))$, $root_2 = \text{find}(\text{id}(nr, nc))$.
       - If $root_1 \ne root_2$, merge the two components using union by rank and decrement `island_count` by $1$.
  3. The updated `island_count` reflects the exact number of connected components after the operation.

### 2. Algorithmic Steps
1. Initialize a grid of size $R \times C$ filled with $0$.
2. Initialize DSU structures of capacity $N = R \cdot C$:
   - `parent[i] = -1` (unactivated / water), `rank[i] = 0`.
3. Set `island_count = 0`.
4. For each incoming coordinate $(r, c)$:
   - If the cell is already land, skip union operations and report current `island_count`.
   - Set $\text{grid}[r][c] = 1$.
   - Activate DSU element: `parent[id] = id`, `rank[id] = 0`, increment `island_count++`.
   - For each direction $(\Delta r, \Delta c) \in \{(-1, 0), (1, 0), (0, -1), (0, 1)\}$:
     - Check neighbor $(nr, nc) = (r + \Delta r, c + \Delta c)$.
     - If $0 \le nr < R$ and $0 \le nc < C$ and $\text{grid}[nr][nc] == 1$:
       - If `find_root(id)` $\ne$ `find_root(nid)`:
         - `union_sets(id, nid)`
         - `island_count--`
   - Record and output the updated `island_count`.

---

## Pseudocode

```text
Algorithm DynamicIslands(R, C, operations):
    Input: Grid dimensions R, C and list of K operations [(r, c)]
    Output: Island count after each operation

    Initialize grid[R][C] with 0
    Initialize parent[R * C] with -1, rank[R * C] with 0
    island_count = 0

    For each (r, c) in operations:
        idx = r * C + c
        If grid[r][c] == 1:
            Output island_count
            Continue

        grid[r][c] = 1
        parent[idx] = idx
        island_count += 1

        For each (dr, dc) in [(-1,0), (1,0), (0,-1), (0,1)]:
            nr = r + dr, nc = c + dc
            If 0 <= nr < R and 0 <= nc < C and grid[nr][nc] == 1:
                nidx = nr * C + nc
                If Union(idx, nidx):
                    island_count -= 1

        Output island_count
```

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time per Land Addition** | $\mathcal{O}(\alpha(R \cdot C))$ | Inspects at most 4 neighbors, each performing DSU find/union with path compression and rank heuristics. |
| **Total Time Complexity** | $\mathcal{O}(K \cdot \alpha(R \cdot C))$ | Total cost across all $K$ land additions. |
| **Auxiliary Space** | $\mathcal{O}(R \cdot C)$ | Flattened DSU arrays (`parent`, `rank`) and 2D grid representation of size $R \times C$. |

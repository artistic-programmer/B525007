# Question 1: Online Graph-Bipartiteness Testing

## Problem Statement
A graph is bipartite if and only if it contains no odd-length cycles (equivalently, its vertices can be 2-colored such that no two adjacent vertices share the same color).
Given an undirected graph with $V$ vertices, edges arrive online one by one: $(u, v)$.
We must maintain whether the graph remains bipartite after each edge insertion:
- If adding edge $(u, v)$ does not introduce an odd cycle, add it to the graph and maintain the bipartite component structures.
- Otherwise, report that $(u, v)$ violates bipartiteness and skip (reject) it.

---

## Parity-Tracking Disjoint Set Union (DSU) Algorithm

### 1. Conceptual Principle
In a bipartite graph, every connected component is 2-colorable (colors $0$ and $1$).
Instead of re-running full BFS/DFS 2-coloring from scratch after every edge ($\mathcal{O}(V + E)$ per edge), we maintain a **Disjoint Set Union (DSU)** data structure with **potential / parity tracking**:
- Each node $x$ stores `parent[x]` and `parity[x]` $\in \{0, 1\}$, where `parity[x]` represents the color difference (distance modulo 2) between $x$ and its parent.
- During `find(x)` with path compression, the parity is updated transitively:
  $$\text{parity}[x] \leftarrow \text{parity}[x] \oplus \text{parity}[\text{old\_parent}]$$
- When querying an incoming edge $(u, v)$:
  1. Let $r_u = \text{find}(u)$ and $r_v = \text{find}(v)$.
  2. **Case 1 ($r_u = r_v$)**: $u$ and $v$ already belong to the same connected component.
     - The path between $u$ and $v$ through the tree has parity $\text{parity}[u] \oplus \text{parity}[v]$.
     - If $\text{parity}[u] = \text{parity}[v]$, adding the edge $(u, v)$ creates an **odd cycle** of length $\text{even} + 1 = \text{odd}$. Adding it violates bipartiteness $\implies$ **REJECT**.
     - If $\text{parity}[u] \ne \text{parity}[v]$, the existing path has odd length, so adding edge $(u, v)$ creates an even cycle $\implies$ **ACCEPT (redundant/safe)**.
  3. **Case 2 ($r_u \ne r_v$)**: $u$ and $v$ are in different components.
     - The two components can always be merged consistently without creating any cycles.
     - We link the root of the smaller rank component to the root of the larger rank component.
     - The new parity offset between $r_u$ and $r_v$ is set to $\text{parity}[u] \oplus \text{parity}[v] \oplus 1$ so that $u$ and $v$ end up with opposite parities $\implies$ **ACCEPT**.

### 2. Algorithmic Steps
1. Initialize for each vertex $i \in \{1 \dots V\}$:
   - `parent[i] = i`, `rank[i] = 0`, `parity[i] = 0`.
2. For each incoming edge $(u, v)$:
   - Compute $r_u = \text{find}(u)$, $r_v = \text{find}(v)$.
   - If $r_u == r_v$ and $\text{parity}[u] == \text{parity}[v]$:
     - Print rejection notice (violates bipartiteness).
   - Else:
     - If $r_u \ne r_v$:
       - `union_sets(u, v)`.
     - Print acceptance notice (bipartiteness preserved).
3. At termination, output the final component count and partition colors.

---

## Pseudocode

```text
Function Find(x):
    If parent[x] != x:
        orig_parent = parent[x]
        parent[x] = Find(parent[x])
        parity[x] = parity[x] ^ parity[orig_parent]
    Return parent[x]

Function AddEdge(u, v):
    ru = Find(u)
    rv = Find(v)
    If ru == rv:
        If parity[u] == parity[v]:
            Return REJECTED_ODD_CYCLE
        Else:
            Return ACCEPTED_EVEN_CYCLE
    Else:
        If rank[ru] < rank[rv]:
            Swap(ru, rv)
            Swap(u, v)
        parent[rv] = ru
        parity[rv] = parity[u] ^ parity[v] ^ 1
        If rank[ru] == rank[rv]:
            rank[ru] += 1
        Return ACCEPTED_MERGE
```

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity per Edge** | $\mathcal{O}(\alpha(V))$ | Amortized nearly constant time per edge insertion via path compression and union by rank. |
| **Total Time Complexity** | $\mathcal{O}(E \alpha(V))$ | For $E$ online edge queries on a graph of $V$ vertices. |
| **Auxiliary Space** | $\mathcal{O}(V)$ | Parent, rank, and parity arrays of size $V + 1$. |

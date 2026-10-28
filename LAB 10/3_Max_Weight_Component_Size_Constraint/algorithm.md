# Maximum Weight Component with Size Constraints

## 1. Problem Definition & Mathematical Formulation
Given an undirected graph $G = (V, E)$ initialized with $n = |V|$ isolated vertices, each vertex $v \in V$ is associated with a non-negative scalar weight $w_v \ge 0$. Edges are incrementally added to the graph one by one from a sequence of $m = |E|$ operations:
$$e_t = (u_t, v_t), \quad t \in \{1, 2, \dots, m\}$$

We are given a static component size constraint threshold $K \in \mathbb{N}$ ($1 \le K \le n$). At any point in time, the connected components partition the vertex set $V$ into disjoint subsets $\mathcal{C} = \{C_1, C_2, \dots, C_k\}$. For each component $C_i \in \mathcal{C}$:
- **Component Size**: $|C_i|$ (number of vertices in $C_i$)
- **Component Total Weight**: $W(C_i) = \sum_{v \in C_i} w_v$

A component $C_i$ is defined as **admissible** (or valid under the constraint) if:
$$|C_i| \le K$$

The objective is to compute, initially and after each incremental edge addition $e_t$:
$$W_{\max}^{(t)} = \max_{\substack{C_i \in \mathcal{C}^{(t)} \\ |C_i| \le K}} W(C_i)$$
If no component satisfies $|C_i| \le K$ (e.g., all components have grown strictly larger than $K$), then $W_{\max}^{(t)} = 0$.

---

## 2. Theoretical Analysis & Algorithm Design

### 2.1 Augmented Disjoint Set Union (DSU)
Standard DSU maintains disjoint partitions under incremental edge additions. To satisfy the query requirements, each equivalence class root $r$ is augmented with two metadata attributes:
1. `size[r]`: The cardinality of the connected component rooted at $r$.
2. `weight[r]`: The aggregate vertex weight of all members in the component rooted at $r$.

When an undirected edge $(u, v)$ is inserted:
1. Identify roots: $r_u = \text{find}(u)$ and $r_v = \text{find}(v)$.
2. If $r_u = r_v$, the vertices already belong to the same connected component. No structural or weight changes occur.
3. If $r_u \neq r_v$:
   - The two components will merge into a single component of size:
     $$\text{size}_{\text{new}} = \text{size}[r_u] + \text{size}[r_v]$$
   - Total component weight becomes:
     $$\text{weight}_{\text{new}} = \text{weight}[r_u] + \text{weight}[r_v]$$
   - Using union-by-rank or union-by-size, attach the smaller tree under the larger tree root (say $r_u$ becomes parent of $r_v$).
   - Update $\text{size}[r_u] \leftarrow \text{size}_{\text{new}}$ and $\text{weight}[r_u] \leftarrow \text{weight}_{\text{new}}$.

### 2.2 Maintaining the Maximum Admissible Weight
Because component sizes strictly increase monotonically under edge unions, an admissible component ($|C| \le K$) may become inadmissible ($|C| > K$) upon union.
To track the maximum admissible weight across all components efficiently:
- Maintain an active registry or max-heap of admissible components.
- Each component root $r$ has a flag or entry in the candidate set if $\text{size}[r] \le K$.
- When $r_u$ and $r_v$ merge:
  - Both old roots $r_u$ and $r_v$ are retired from the admissible candidate pool.
  - If $\text{size}_{\text{new}} \le K$, the new composite root is inserted into the admissible candidate pool with value $\text{weight}_{\text{new}}$.
  - The maximum weight among all current admissible roots is queried in $O(1)$ amortized time using a lazy-deletion max-heap or balanced search structure, or directly scanned in $O(V)$ in worst-case dense reporting.

---

## 3. Complexity Analysis
- **DSU Operations**: With path compression and union by rank, each `find` and `union` operation executes in $\mathcal{O}(\alpha(V))$ amortized time, where $\alpha$ is the Inverse Ackermann function.
- **Heap Updates**: Maintaining candidate weights via max-heap requires $\mathcal{O}(\log V)$ per union.
- **Total Time Complexity**: $\mathcal{O}(V + m \log V)$ for $m$ edge insertions.
- **Auxiliary Space Complexity**: $\mathcal{O}(V)$ to store `parent`, `rank`, `size`, and `weight` arrays alongside heap nodes.

# Reverse Time-Step DSU (Offline Dynamic Connectivity)

## 1. Problem Definition & Mathematical Formulation
Consider an undirected weighted graph $G = (V, E)$ with $|V| = n$ vertices and $|E| = m$ edges. Each vertex $i \in \{1, 2, \dots, n\}$ is assigned a non-negative scalar weight $a_i \ge 0$. A permutation $P = (p_1, p_2, \dots, p_n)$ defines an elimination sequence where vertices are iteratively destroyed one by one.

At time step $t \in \{1, 2, \dots, n\}$:
1. Vertex $p_t$ and all its incident edges are eliminated from the active graph.
2. The remaining active induced subgraph is $G_t = G[V \setminus \{p_1, \dots, p_t\}]$.
3. The connected components of $G_t$ are denoted by $\mathcal{C}_t = \{C_1, C_2, \dots, C_k\}$.
4. The weight of any component $C \in \mathcal{C}_t$ is defined as the sum of vertex values:
   $$W(C) = \sum_{v \in C} a_v$$
5. The goal is to compute the maximum component weight after each destruction step:
   $$\text{Ans}_t = \begin{cases} \max_{C \in \mathcal{C}_t} W(C) & \text{if } \mathcal{C}_t \neq \emptyset \\ 0 & \text{if } t = n \end{cases}$$

---

## 2. Algorithmic Formulation: Time-Reversal Reduction

### 2.1 The Destruction-to-Construction Duality
Directly maintaining connected components under vertex deletions is computationally prohibitive with basic disjoint-set structures. However, dynamic connectivity is symmetric under time-reversal:
- Destroying vertices in forward order $p_1 \to p_2 \to \dots \to p_n$ is mathematically equivalent to **constructing** the graph backwards from an initially empty vertex set in reverse order:
  $$p_n \to p_{n-1} \to \dots \to p_1$$

### 2.2 Reverse Offline Step Execution
Let $\mathcal{A}$ track the set of currently activated vertices, initialized to $\mathcal{A} = \emptyset$.
Initialize a global maximum component sum:
$$M \leftarrow 0$$
For step $i = n$ down to $1$ with vertex $u = p_i$:
1. Note that before adding $u$, the maximum component sum in the graph with vertices $\{p_{i+1}, \dots, p_n\}$ is exactly $\text{Ans}_i$.
   Thus, $\text{Ans}_i = M$.
2. Activate vertex $u$: $\mathcal{A} \leftarrow \mathcal{A} \cup \{u\}$.
3. Initialize DSU set for $u$:
   $$\text{parent}[u] \leftarrow u, \quad \text{weight}[u] \leftarrow a_u$$
   $$M \leftarrow \max(M, a_u)$$
4. For each adjacent vertex $v \in \text{Adj}(u)$:
   - If $v \in \mathcal{A}$:
     - Let $r_u = \text{find}(u)$ and $r_v = \text{find}(v)$.
     - If $r_u \neq r_v$:
       - Union $r_u$ and $r_v$. The combined component weight becomes:
         $$\text{weight}[\text{root}] \leftarrow \text{weight}[r_u] + \text{weight}[r_v]$$
       - Update global maximum: $M \leftarrow \max(M, \text{weight}[\text{root}])$.

After all iterations, output the sequence $\text{Ans}_1, \text{Ans}_2, \dots, \text{Ans}_n$.

---

## 3. Complexity Analysis
- **Adjacency Representation**: An adjacency list representation stores the $m$ undirected edges in $\mathcal{O}(V + E)$ space.
- **DSU Operations**: Each edge is traversed at most twice (once from each endpoint when activated). Total DSU operations are at most $2m$ `find` and $n-1$ `union` operations, each running in amortized $\mathcal{O}(\alpha(V))$.
- **Total Time Complexity**: $\mathcal{O}(V + E \cdot \alpha(V))$.
- **Auxiliary Space Complexity**: $\mathcal{O}(V + E)$ for adjacency lists and DSU tracking arrays.

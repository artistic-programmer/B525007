# Question 6: Edit Distance with Traceback Information

## Problem Statement
Given two strings $A$ of length $m$ and $B$ of length $n$, compute the minimum number of operations (insertions, deletions, or substitutions) required to transform string $A$ into string $B$, and output the complete step-by-step traceback of edit operations.

---

## Dynamic Programming Formulation (Levenshtein Distance)

### State Definition
Let $D[i][j]$ denote the minimum edit distance between prefix $A[1 \dots i]$ and prefix $B[1 \dots j]$, for $0 \le i \le m$ and $0 \le j \le n$.

### Base Cases
- $D[i][0] = i$ for all $0 \le i \le m$ (Requires $i$ deletions to transform $A[1 \dots i]$ to an empty string).
- $D[0][j] = j$ for all $0 \le j \le n$ (Requires $j$ insertions to transform an empty string to $B[1 \dots j]$).

### Recurrence Relation
For $1 \le i \le m$ and $1 \le j \le n$:
$$D[i][j] = \min \begin{cases} D[i - 1][j] + 1 & \text{(Deletion of } A[i]\text{)} \\[4pt] D[i][j - 1] + 1 & \text{(Insertion of } B[j]\text{)} \\[4pt] D[i - 1][j - 1] + \begin{cases} 0 & \text{if } A[i] = B[j] \text{ (Match/Keep)} \\ 1 & \text{if } A[i] \ne B[j] \text{ (Substitution)} \end{cases} \end{cases}$$

---

## Traceback Procedure
Starting at cell $(m, n)$ and following backwards to $(0, 0)$:
1. If $A[i - 1] == B[j - 1]$ and $D[i][j] == D[i - 1][j - 1]$: **Match / Keep** character; $i = i - 1, j = j - 1$.
2. Else if $D[i][j] == D[i - 1][j - 1] + 1$: **Substitute** $A[i - 1] \to B[j - 1]$; $i = i - 1, j = j - 1$.
3. Else if $D[i][j] == D[i - 1][j] + 1$: **Delete** $A[i - 1]$; $i = i - 1$.
4. Else if $D[i][j] == D[i][j - 1] + 1$: **Insert** $B[j - 1]$; $j = j - 1$.

Reverse the collected operations to display chronological edits from left to right.

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(m \cdot n)$ | $(m + 1) \times (n + 1)$ table filled with $\mathcal{O}(1)$ transitions; traceback takes $\mathcal{O}(m + n)$. |
| **Auxiliary Space** | $\mathcal{O}(m \cdot n)$ | 2D matrix required for path reconstruction. |

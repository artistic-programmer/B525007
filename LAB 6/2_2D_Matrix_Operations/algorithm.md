# Question 2: 2D Square Matrix Operations and Their Complexities

## Problem Statement
Given square matrices with $n$ rows and $n$ columns, derive the worst-case computational complexity and implement in C the following 7 matrix procedures:
1. Matrix Addition.
2. Matrix Multiplication.
3. Finding if the given matrix is a zero matrix.
4. Finding if the given matrix is a symmetric matrix.
5. Computing the determinant of the matrix.
6. Transposing the matrix in situ (in place).
7. Finding the eigenvalues and eigenvectors of the matrix.

---

## Detailed Algorithmic Procedures & Complexity Derivations

### (i) Matrix Addition
- **Procedure**: For matrices $A$ and $B$, compute $C[i][j] = A[i][j] + B[i][j]$ for all $0 \le i, j < n$.
- **Complexity**: $\mathcal{O}(n^2)$ time ($n^2$ additions), $\mathcal{O}(n^2)$ space for output matrix $C$.

### (ii) Matrix Multiplication
- **Procedure**: Compute $C[i][j] = \sum_{k=0}^{n-1} A[i][k] \cdot B[k][j]$.
- **Complexity**: $\mathcal{O}(n^3)$ time (3 nested loops), $\mathcal{O}(n^2)$ space.

### (iii) Zero Matrix Checking
- **Procedure**: Traverse matrix $A[i][j]$. If any $A[i][j] \ne 0$, return `false`. If loop completes, return `true`.
- **Complexity**: $\mathcal{O}(n^2)$ worst-case time, $\mathcal{O}(1)$ space.

### (iv) Symmetric Matrix Checking
- **Procedure**: Traverse upper triangle $i < j$. If $A[i][j] \ne A[j][i]$, return `false`. Return `true` if all match.
- **Complexity**: $\mathcal{O}(n^2)$ worst-case time ($\frac{n(n-1)}{2}$ comparisons), $\mathcal{O}(1)$ space.

### (v) Determinant Computation
- **Procedure**: Convert matrix to Upper Triangular form using **Gaussian Elimination with Partial Pivoting**. Determinant equals the product of diagonal elements multiplied by $(-1)^{\text{swaps}}$.
- **Complexity**: $\mathcal{O}(n^3)$ time, $\mathcal{O}(n^2)$ space.

### (vi) In Situ (In-Place) Transposition
- **Procedure**: For $i < j$, swap $A[i][j]$ with $A[j][i]$ in-place.
- **Complexity**: $\mathcal{O}(n^2)$ time ($\frac{n(n-1)}{2}$ swaps), $\mathcal{O}(1)$ auxiliary space.

### (vii) Eigenvalues and Eigenvectors
- **Procedure**: Compute characteristic polynomial $\det(A - \lambda I) = 0$ for $n=2$ or use QR decomposition iterations for general $n$. For $2 \times 2$ matrix:
  $$\lambda^2 - \text{tr}(A)\lambda + \det(A) = 0 \implies \lambda_{1,2} = \frac{\text{tr}(A) \pm \sqrt{\text{tr}(A)^2 - 4\det(A)}}{2}$$
  Solve $(A - \lambda I) \mathbf{v} = 0$ for eigenvectors.
- **Complexity**: $\mathcal{O}(n^3)$ time, $\mathcal{O}(n^2)$ space.

---

## Complexity Summary Table

| Operation | Worst-Case Time | Auxiliary Space | Primary Technique |
|---|---|---|---|
| (i) Matrix Addition | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | Element-wise sum |
| (ii) Matrix Multiplication | $\mathcal{O}(n^3)$ | $\mathcal{O}(n^2)$ | Triple nested loop |
| (iii) Zero Matrix Check | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | Early-exit scan |
| (iv) Symmetric Check | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | Upper-lower triangle check |
| (v) Determinant | $\mathcal{O}(n^3)$ | $\mathcal{O}(n^2)$ | Gaussian Elimination |
| (vi) In Situ Transposition | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | Diagonal reflection swap |
| (vii) Eigenvalues & Eigenvectors | $\mathcal{O}(n^3)$ | $\mathcal{O}(n^2)$ | Characteristic Eq / QR Iterations |

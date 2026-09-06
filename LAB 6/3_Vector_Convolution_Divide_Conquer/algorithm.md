# Question 3: Divide-and-Conquer Vector Convolution O(n log n)

## Problem Statement
The convolution of two vectors $A$ (length $m$) and $B$ (length $n$, with $n \ge m$) is a new vector $C$ of length $m + n - 1$ defined as:
$$C[k] = \sum_{j=0}^{m-1} A[j] B[k-j] \quad \text{for } 0 \le k < m + n - 1$$
Design an $\mathcal{O}(n \log n)$ Divide-and-Conquer algorithm for this operation, implement it in C with interactive user input, and prove its complexity and correctness.

---

## Algorithmic Strategy: Divide-and-Conquer FFT Convolution

### Key Observation
1. Direct evaluation of polynomial coefficient multiplication requires $m \cdot n = \mathcal{O}(n^2)$ operations.
2. Convolution in the time domain corresponds to **pointwise multiplication in the frequency domain** (Convolution Theorem):
   $$\mathcal{F}\{A * B\} = \mathcal{F}\{A\} \cdot \mathcal{F}\{B\}$$
3. By applying the **Cooley-Tukey Divide-and-Conquer Fast Fourier Transform (FFT)** algorithm, vector values can be transformed to frequency space in $\mathcal{O}(N \log N)$ time, multiplied pointwise in $\mathcal{O}(N)$ time, and transformed back via Inverse FFT (IFFT) in $\mathcal{O}(N \log N)$ time.

---

## Step-by-Step Divide-and-Conquer Algorithm

### Step 1: Zero-Padding & Array Dimensioning
- Find smallest power of two $N \ge m + n - 1$.
- Pad vectors $A$ and $B$ with zeros up to length $N$.

### Step 2: Recursive Cooley-Tukey FFT (Divide & Conquer)
- **Divide**: Split polynomial terms into even-indexed $A_{even}$ and odd-indexed $A_{odd}$ elements of size $N/2$.
- **Conquer**: Recursively compute FFT for $A_{even}$ and $A_{odd}$.
- **Combine (Butterfly Operation)**: For $k = 0 \dots N/2 - 1$, compute:
  $$\hat{A}[k] = \hat{A}_{even}[k] + \omega_N^k \cdot \hat{A}_{odd}[k]$$
  $$\hat{A}[k + N/2] = \hat{A}_{even}[k] - \omega_N^k \cdot \hat{A}_{odd}[k]$$
  where twiddle factor $\omega_N^k = e^{-2\pi i k / N} = \cos(2\pi k / N) - i \sin(2\pi k / N)$.

### Step 3: Pointwise Frequency Multiplication
- Compute $\hat{C}[k] = \hat{A}[k] \cdot \hat{B}[k]$ for all $0 \le k < N$.

### Step 4: Inverse FFT (IFFT)
- Apply IFFT using conjugate twiddle factors $e^{+2\pi i k / N}$, divide by $N$, and take the real component.

---

## Pseudocode

```text
Algorithm FFT(a, N, invert):
    If N == 1:
        Return

    Split a into a_even (size N/2) and a_odd (size N/2)
    FFT(a_even, N/2, invert)
    FFT(a_odd, N/2, invert)

    w = 1
    w_n = exp( (invert ? 2*PI*i/N : -2*PI*i/N) )

    For k = 0 to N/2 - 1:
        u = a_even[k]
        v = w * a_odd[k]
        a[k]       = u + v
        a[k + N/2] = u - v
        If invert:
            a[k] /= 2
            a[k + N/2] /= 2
        w = w * w_n

Algorithm ConvolutionFFT(A, m, B, n):
    N = 1
    While N < m + n - 1:
        N = N * 2

    Pad A and B with zeros to size N
    FFT(A, N, false)
    FFT(B, N, false)

    For k = 0 to N - 1:
        C[k] = A[k] * B[k]

    FFT(C, N, true)
    Return C[0 .. m + n - 2]
```

---

## Complexity Analysis

| Phase | Time Complexity | Mathematical Proof / Derivation |
|---|---|---|
| **Zero-Padding** | $\mathcal{O}(N)$ | $N < 2(m+n) = \mathcal{O}(n)$. |
| **FFT Transforms** | $\mathcal{O}(N \log N)$ | Recurrence $T(N) = 2T(N/2) + \mathcal{O}(N) \implies T(N) = \mathcal{O}(N \log N)$ by Master Theorem. |
| **Pointwise Multiply** | $\mathcal{O}(N)$ | $N$ complex multiplications. |
| **IFFT Transform** | $\mathcal{O}(N \log N)$ | Symmetric to FFT. |
| **Overall Time Complexity** | **$\mathcal{O}(n \log n)$** | $2 \cdot \mathcal{O}(N \log N) + \mathcal{O}(N) = \mathcal{O}(n \log n)$ for $n \ge m$. |
| **Auxiliary Space** | **$\mathcal{O}(N)$** | Space for $N$ complex numbers. |

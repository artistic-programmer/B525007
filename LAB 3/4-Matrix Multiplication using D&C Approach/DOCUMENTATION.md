# Matrix Multiplication using Strassen's Method

A C implementation of matrix multiplication using **Strassen's Divide and Conquer algorithm**.

## Method Used

Strassen's method divides each matrix into four submatrices and performs multiplication recursively.

Unlike the conventional matrix multiplication method, which requires **8 recursive matrix multiplications**, Strassen's method uses only **7 multiplications** along with matrix additions and subtractions.

The seven products are:

```text
M1 = (A11 + A22)(B11 + B22)
M2 = (A21 + A22)B11
M3 = A11(B12 - B22)
M4 = A22(B21 - B11)
M5 = (A11 + A12)B22
M6 = (A21 - A11)(B11 + B12)
M7 = (A12 - A22)(B21 + B22)
```

The four result submatrices are then calculated from these seven products.

## Complexity

Conventional Matrix Multiplication:

```text
O(n³)
```

Strassen's Method:

```text
T(n) = 7T(n/2) + O(n²)
```

Therefore:

```text
O(n^log₂7) ≈ O(n^2.807)
```

The algorithm also uses additional memory for submatrices created during recursion.

## Features

- Recursive Divide and Conquer implementation.
- Supports square matrices of arbitrary size.
- Automatically pads matrices to the next power of 2 internally.
- Prints the input matrices and resulting matrix.

## Project Structure

```text
Strassen-Matrix-Multiplication/
│
├── main.c
├── strassen.c
├── strassen.h
└── DOC.md
```

## Build

```bash
gcc main.c strassen.c -o strassen
```

## Run

### Windows

```bash
.\strassen.exe
```

### Linux/macOS

```bash
./strassen
```

## Example

### Input

```text
Enter matrix size n: 2

Enter Matrix A:
1 2
3 4

Enter Matrix B:
5 6
7 8
```

### Output

```text
Result using Strassen's Method:
19 22
43 50
```

## Conclusion

Strassen's algorithm reduces the number of recursive matrix multiplications from **8 to 7**, improving the asymptotic complexity from `O(n³)` to approximately `O(n^2.807)`.
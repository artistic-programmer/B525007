#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    double real;
    double imag;
} Complex;

Complex complex_add(Complex a, Complex b) {
    return (Complex){a.real + b.real, a.imag + b.imag};
}

Complex complex_sub(Complex a, Complex b) {
    return (Complex){a.real - b.real, a.imag - b.imag};
}

Complex complex_mul(Complex a, Complex b) {
    return (Complex){
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
}

/**
 * Recursive Cooley-Tukey FFT / IFFT: O(N log N)
 */
void fft(Complex a[], int n, bool invert) {
    if (n <= 1) return;

    Complex *a_even = (Complex *)malloc((n / 2) * sizeof(Complex));
    Complex *a_odd  = (Complex *)malloc((n / 2) * sizeof(Complex));

    for (int i = 0; i < n / 2; i++) {
        a_even[i] = a[2 * i];
        a_odd[i]  = a[2 * i + 1];
    }

    fft(a_even, n / 2, invert);
    fft(a_odd, n / 2, invert);

    double angle = 2 * M_PI / n * (invert ? -1 : 1);
    Complex w = {1.0, 0.0};
    Complex wn = {cos(angle), sin(angle)};

    for (int i = 0; i < n / 2; i++) {
        Complex u = a_even[i];
        Complex v = complex_mul(w, a_odd[i]);

        a[i]         = complex_add(u, v);
        a[i + n / 2] = complex_sub(u, v);

        if (invert) {
            a[i].real /= 2.0;
            a[i].imag /= 2.0;
            a[i + n / 2].real /= 2.0;
            a[i + n / 2].imag /= 2.0;
        }

        w = complex_mul(w, wn);
    }

    free(a_even);
    free(a_odd);
}

/**
 * Divide-and-Conquer Vector Convolution via FFT: O(n log n)
 */
double* vector_convolution_fft(const double A[], int m, const double B[], int n, int *out_len) {
    int req_len = m + n - 1;
    int N = 1;
    while (N < req_len) N <<= 1;

    Complex *fa = (Complex *)calloc(N, sizeof(Complex));
    Complex *fb = (Complex *)calloc(N, sizeof(Complex));

    for (int i = 0; i < m; i++) fa[i].real = A[i];
    for (int i = 0; i < n; i++) fb[i].real = B[i];

    // Compute FFT of A and B
    fft(fa, N, false);
    fft(fb, N, false);

    // Pointwise frequency multiplication
    for (int i = 0; i < N; i++) {
        fa[i] = complex_mul(fa[i], fb[i]);
    }

    // Inverse FFT
    fft(fa, N, true);

    double *C = (double *)malloc(req_len * sizeof(double));
    for (int i = 0; i < req_len; i++) {
        C[i] = fa[i].real;
    }

    *out_len = req_len;
    free(fa);
    free(fb);
    return C;
}

/**
 * Direct Naive Vector Convolution: O(m * n) for verification
 */
double* vector_convolution_naive(const double A[], int m, const double B[], int n, int *out_len) {
    int req_len = m + n - 1;
    double *C = (double *)calloc(req_len, sizeof(double));

    for (int k = 0; k < req_len; k++) {
        for (int j = 0; j < m; j++) {
            if (k - j >= 0 && k - j < n) {
                C[k] += A[j] * B[k - j];
            }
        }
    }

    *out_len = req_len;
    return C;
}

void print_vector(const char *label, const double vec[], int len) {
    printf("%s (size = %d): [", label, len);
    for (int i = 0; i < len; i++) {
        printf("%.2f%s", vec[i], (i < len - 1) ? ", " : "");
    }
    printf("]\n");
}

int main(void) {
    int m, n;
    printf("Enter length of Vector A (m): ");
    if (scanf("%d", &m) != 1 || m <= 0) {
        fprintf(stderr, "Invalid input for m!\n");
        return 1;
    }

    printf("Enter length of Vector B (n, where n >= m): ");
    if (scanf("%d", &n) != 1 || n < m) {
        fprintf(stderr, "Invalid input for n! (Must satisfy n >= m)\n");
        return 1;
    }

    double *A = (double *)malloc(m * sizeof(double));
    double *B = (double *)malloc(n * sizeof(double));

    printf("Enter %d numbers for Vector A: ", m);
    for (int i = 0; i < m; i++) scanf("%lf", &A[i]);

    printf("Enter %d numbers for Vector B: ", n);
    for (int i = 0; i < n; i++) scanf("%lf", &B[i]);
    printf("\n");

    print_vector("Input Vector A", A, m);
    print_vector("Input Vector B", B, n);
    printf("---------------------------------------------------------\n");

    int len_fft, len_naive;
    double *C_fft   = vector_convolution_fft(A, m, B, n, &len_fft);
    double *C_naive = vector_convolution_naive(A, m, B, n, &len_naive);

    print_vector("Result Vector C (Divide-and-Conquer FFT O(n log n))", C_fft, len_fft);
    print_vector("Verification Vector C (Direct Naive O(m*n))         ", C_naive, len_naive);

    free(A);
    free(B);
    free(C_fft);
    free(C_naive);
    return 0;
}

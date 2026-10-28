#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int min3(int a, int b, int c) {
    int m = a;
    if (b < m) m = b;
    if (c < m) m = c;
    return m;
}

typedef struct {
    char type; // 'M' = Match, 'S' = Substitute, 'I' = Insert, 'D' = Delete
    char src_char;
    char dst_char;
    int pos_a;
    int pos_b;
} EditOp;

int edit_distance(const char *A, const char *B, int m, int n, EditOp **ops_out, int *op_count) {
    int **D = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        D[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= m; i++) D[i][0] = i;
    for (int j = 0; j <= n; j++) D[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost = (A[i - 1] == B[j - 1]) ? 0 : 1;
            D[i][j] = min3(D[i - 1][j] + 1,        // Deletion
                           D[i][j - 1] + 1,        // Insertion
                           D[i - 1][j - 1] + cost  // Substitution or Match
                          );
        }
    }

    int distance = D[m][n];

    // Traceback
    EditOp *temp_ops = (EditOp *)malloc((m + n + 1) * sizeof(EditOp));
    int count = 0;
    int i = m, j = n;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1] && D[i][j] == D[i - 1][j - 1]) {
            temp_ops[count++] = (EditOp){'M', A[i - 1], B[j - 1], i, j};
            i--; j--;
        } else if (i > 0 && j > 0 && D[i][j] == D[i - 1][j - 1] + 1) {
            temp_ops[count++] = (EditOp){'S', A[i - 1], B[j - 1], i, j};
            i--; j--;
        } else if (i > 0 && D[i][j] == D[i - 1][j] + 1) {
            temp_ops[count++] = (EditOp){'D', A[i - 1], ' ', i, j};
            i--;
        } else if (j > 0 && D[i][j] == D[i][j - 1] + 1) {
            temp_ops[count++] = (EditOp){'I', ' ', B[j - 1], i, j};
            j--;
        }
    }

    EditOp *ops = (EditOp *)malloc(count * sizeof(EditOp));
    for (int k = 0; k < count; k++) {
        ops[k] = temp_ops[count - 1 - k];
    }
    free(temp_ops);

    *ops_out = ops;
    *op_count = count;

    for (int k = 0; k <= m; k++) free(D[k]);
    free(D);

    return distance;
}

int main(void) {
    char A[512], B[512];
    printf("Enter source string A: ");
    if (scanf("%511s", A) != 1) {
        fprintf(stderr, "Invalid input for string A!\n");
        return 1;
    }

    printf("Enter target string B: ");
    if (scanf("%511s", B) != 1) {
        fprintf(stderr, "Invalid input for string B!\n");
        return 1;
    }
    printf("\n");

    int m = (int)strlen(A);
    int n = (int)strlen(B);

    printf("Source String A (length %d) : \"%s\"\n", m, A);
    printf("Target String B (length %d) : \"%s\"\n", n, B);
    printf("---------------------------------------------------------\n");

    EditOp *ops = NULL;
    int op_count = 0;
    int dist = edit_distance(A, B, m, n, &ops, &op_count);

    printf("Minimum Edit Distance (Levenshtein) : %d operations\n\n", dist);
    printf("Detailed Traceback Steps:\n");
    int step = 1;
    for (int k = 0; k < op_count; k++) {
        if (ops[k].type == 'M') {
            printf("  Step %2d: [MATCH]      Keep '%c' at position %d\n", step++, ops[k].src_char, ops[k].pos_a);
        } else if (ops[k].type == 'S') {
            printf("  Step %2d: [SUBSTITUTE] Replace '%c' with '%c'\n", step++, ops[k].src_char, ops[k].dst_char);
        } else if (ops[k].type == 'D') {
            printf("  Step %2d: [DELETE]     Delete '%c' from source\n", step++, ops[k].src_char);
        } else if (ops[k].type == 'I') {
            printf("  Step %2d: [INSERT]     Insert '%c' into target\n", step++, ops[k].dst_char);
        }
    }
    printf("\n");

    if (ops) free(ops);
    return 0;
}

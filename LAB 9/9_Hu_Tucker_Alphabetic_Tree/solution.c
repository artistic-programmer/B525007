#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int weight;
    int is_internal; // 0 for initial leaf, 1 for internal node
    int original_index; // 0..N-1 for leaves, -1 for internal
    struct Node *left;
    struct Node *right;
} Node;

Node* create_leaf(int weight, int index) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->weight = weight;
    n->is_internal = 0;
    n->original_index = index;
    n->left = NULL;
    n->right = NULL;
    return n;
}

Node* create_internal(int weight, Node *left, Node *right) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->weight = weight;
    n->is_internal = 1;
    n->original_index = -1;
    n->left = left;
    n->right = right;
    return n;
}

// Two nodes i and j (with i < j) are compatible if every node strictly between them is internal
int are_compatible(Node **seq, int i, int j) {
    for (int k = i + 1; k < j; k++) {
        if (!seq[k]->is_internal) {
            return 0; // Found an intervening leaf
        }
    }
    return 1;
}

// Phase 2: Compute depth of each original leaf
void compute_leaf_depths(Node *root, int current_depth, int *depths) {
    if (!root) return;
    if (root->original_index != -1) {
        depths[root->original_index] = current_depth;
        return;
    }
    compute_leaf_depths(root->left, current_depth + 1, depths);
    compute_leaf_depths(root->right, current_depth + 1, depths);
}

void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void) {
    int n;
    printf("Enter number of alphabetic symbols: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error: Invalid number of symbols.\n");
        return 1;
    }

    int *weights = (int *)malloc(sizeof(int) * n);
    printf("Enter %d alphabetic weights: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &weights[i]) != 1 || weights[i] <= 0) {
            printf("Error: Invalid weight at index %d.\n", i);
            free(weights);
            return 1;
        }
    }

    printf("\n--- Hu-Tucker Optimal Alphabetic Tree Construction ---\n");
    printf("Alphabetic Symbols & Weights:\n  ");
    for (int i = 0; i < n; i++) {
        printf("S%d(w=%d)%s", i + 1, weights[i], (i == n - 1) ? "" : ", ");
    }
    printf("\n\n");

    if (n == 1) {
        printf("Trivial tree with 1 leaf: Depth = 0, Total Weighted Cost = 0\n");
        free(weights);
        return 0;
    }

    // Phase 1: Combination
    Node **seq = (Node **)malloc(sizeof(Node *) * (2 * n));
    int seq_len = n;
    for (int i = 0; i < n; i++) {
        seq[i] = create_leaf(weights[i], i);
    }

    printf("Phase 1: Compatible Pair Merges\n");
    int merge_step = 1;
    while (seq_len > 1) {
        int best_i = -1, best_j = -1;
        int min_sum = INT_MAX;

        for (int i = 0; i < seq_len; i++) {
            for (int j = i + 1; j < seq_len; j++) {
                if (are_compatible(seq, i, j)) {
                    int sum = seq[i]->weight + seq[j]->weight;
                    if (sum < min_sum) {
                        min_sum = sum;
                        best_i = i;
                        best_j = j;
                    }
                }
            }
        }

        printf("  Step %2d: Merged node %d (w=%d) and node %d (w=%d) -> New w=%d\n",
               merge_step++, best_i, seq[best_i]->weight, best_j, seq[best_j]->weight, min_sum);

        Node *new_node = create_internal(min_sum, seq[best_i], seq[best_j]);

        // Place new node at best_i, shift elements to delete best_j
        seq[best_i] = new_node;
        for (int k = best_j; k < seq_len - 1; k++) {
            seq[k] = seq[k + 1];
        }
        seq_len--;
    }

    Node *root = seq[0];

    // Phase 2: Level Assignment
    int *depths = (int *)malloc(sizeof(int) * n);
    compute_leaf_depths(root, 0, depths);

    printf("\nPhase 2: Leaf Depth / Level Assignment\n");
    long long total_cost = 0;
    printf("%-10s | %-10s | %-10s | %-16s\n", "Symbol", "Weight", "Depth", "Weighted Cost");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        long long cost = (long long)weights[i] * depths[i];
        total_cost += cost;
        printf("S%-9d | %-10d | %-10d | %-16lld\n", i + 1, weights[i], depths[i], cost);
    }

    printf("----------------------------------------------------\n");
    printf("Total Weighted Path Length (External Cost): %lld\n", total_cost);

    free_tree(root);
    free(seq);
    free(depths);
    free(weights);
    return 0;
}

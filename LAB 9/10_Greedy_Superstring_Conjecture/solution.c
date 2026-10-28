#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compute length of longest proper suffix of s1 that is a prefix of s2
int compute_overlap(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int max_ov = 0;

    int max_possible = (len1 < len2) ? len1 : len2;

    for (int k = 1; k <= max_possible; k++) {
        // Compare suffix of s1 of length k with prefix of s2 of length k
        if (strncmp(s1 + len1 - k, s2, k) == 0) {
            max_ov = k;
        }
    }
    return max_ov;
}

// Merge s1 and s2 with overlap ov
char* merge_strings(const char *s1, const char *s2, int ov) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    char *res = (char *)malloc(len1 + len2 - ov + 1);
    strcpy(res, s1);
    strcat(res, s2 + ov);
    return res;
}

int main(void) {
    int n;
    printf("Enter number of strings: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error: Invalid number of strings.\n");
        return 1;
    }

    char **strs = (char **)malloc(sizeof(char *) * n);
    int total_initial_len = 0;
    printf("Enter %d strings:\n", n);
    for (int i = 0; i < n; i++) {
        char buffer[1024];
        printf("  String %d: ", i + 1);
        if (scanf("%1023s", buffer) != 1) {
            printf("Error: Invalid string input.\n");
            return 1;
        }
        strs[i] = strdup(buffer);
        total_initial_len += strlen(buffer);
    }

    printf("\n--- Greedy Superstring Approximation Simulation ---\n");
    printf("Initial String Set:\n  ");
    for (int i = 0; i < n; i++) {
        printf("\"%s\"%s", strs[i], (i == n - 1) ? "" : ", ");
    }
    printf("\nTotal Concatenated Length without Merging: %d\n\n", total_initial_len);

    int count = n;
    int step = 1;

    while (count > 1) {
        int max_ov = -1;
        int best_i = -1;
        int best_j = -1;

        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                if (i != j) {
                    int ov = compute_overlap(strs[i], strs[j]);
                    if (ov > max_ov) {
                        max_ov = ov;
                        best_i = i;
                        best_j = j;
                    }
                }
            }
        }

        char *merged = merge_strings(strs[best_i], strs[best_j], max_ov);
        printf("Step %2d: Merged \"%s\" + \"%s\" with overlap %d -> \"%s\"\n",
               step++, strs[best_i], strs[best_j], max_ov, merged);

        free(strs[best_i]);
        free(strs[best_j]);

        strs[best_i] = merged;
        strs[best_j] = strs[count - 1];
        count--;
    }

    char *final_superstring = strs[0];
    int final_len = strlen(final_superstring);

    printf("\n--- Final Superstring Result ---\n");
    printf("Greedy Superstring: \"%s\"\n", final_superstring);
    printf("Final Length: %d (Saved %d characters, %.1f%% compression)\n",
           final_len,
           total_initial_len - final_len,
           100.0 * (total_initial_len - final_len) / (total_initial_len > 0 ? total_initial_len : 1));

    free(final_superstring);
    free(strs);
    return 0;
}

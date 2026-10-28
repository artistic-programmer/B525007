#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char name[50];
    int birth_year;
    int death_year;
    int id;
} Scientist;

typedef enum {
    EVENT_DEATH = -1,
    EVENT_BIRTH = +1
} EventType;

typedef struct {
    int year;
    EventType type;
    int scientist_id;
} Event;

typedef struct {
    int max_alive_count;
    int peak_start_year;
    int peak_end_year;
} PeakAliveResult;

// Comparator for events with strict tie-breaking rule
int compare_events(const void *a, const void *b) {
    const Event *e1 = (const Event *)a;
    const Event *e2 = (const Event *)b;

    if (e1->year != e2->year) {
        return e1->year - e2->year;
    }
    // Tie-breaker: Death (-1) comes BEFORE Birth (+1)
    return e1->type - e2->type;
}

PeakAliveResult find_best_time_to_be_alive(const Scientist scientists[], int n) {
    PeakAliveResult result = {0, 0, 0};
    if (n <= 0) return result;

    int num_events = 2 * n;
    Event *events = (Event *)malloc(num_events * sizeof(Event));
    if (!events) {
        fprintf(stderr, "Memory allocation error!\n");
        return result;
    }

    for (int i = 0; i < n; i++) {
        events[2 * i]     = (Event){scientists[i].birth_year, EVENT_BIRTH, scientists[i].id};
        events[2 * i + 1] = (Event){scientists[i].death_year, EVENT_DEATH, scientists[i].id};
    }

    qsort(events, num_events, sizeof(Event), compare_events);

    int current_alive = 0;
    int max_alive = 0;
    int best_start = 0;
    int best_end = 0;

    for (int i = 0; i < num_events; i++) {
        current_alive += events[i].type;

        if (current_alive > max_alive) {
            max_alive = current_alive;
            best_start = events[i].year;
            if (i + 1 < num_events) {
                best_end = events[i + 1].year;
            } else {
                best_end = events[i].year;
            }
        }
    }

    result.max_alive_count = max_alive;
    result.peak_start_year = best_start;
    result.peak_end_year   = best_end;

    free(events);
    return result;
}

int main(void) {
    int n;
    printf("Enter number of scientists (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for number of scientists n!\n");
        return 1;
    }

    Scientist *scientists = (Scientist *)malloc(n * sizeof(Scientist));
    if (!scientists) {
        fprintf(stderr, "Memory allocation error!\n");
        return 1;
    }

    printf("Enter details for %d scientists (Name BirthYear DeathYear):\n", n);
    for (int i = 0; i < n; i++) {
        scientists[i].id = i + 1;
        printf("Scientist #%d (Name Birth Death): ", i + 1);
        if (scanf("%s %d %d", scientists[i].name, &scientists[i].birth_year, &scientists[i].death_year) != 3) {
            fprintf(stderr, "Invalid input format!\n");
            free(scientists);
            return 1;
        }
    }
    printf("\n");

    printf("Scientist Index Log (%d entries):\n", n);
    for (int i = 0; i < n; i++) {
        printf("  [%2d] %-20s (Born: %4d, Died: %4d)\n",
               scientists[i].id, scientists[i].name, scientists[i].birth_year, scientists[i].death_year);
    }
    printf("---------------------------------------------------------\n");

    PeakAliveResult res = find_best_time_to_be_alive(scientists, n);

    printf("Maximum Scientists Simultaneously Alive : %d\n", res.max_alive_count);
    printf("Peak Time Window                        : Year %d to Year %d\n\n",
           res.peak_start_year, res.peak_end_year);

    printf("Scientists alive during peak window (Year %d to %d):\n",
           res.peak_start_year, res.peak_end_year);
    for (int i = 0; i < n; i++) {
        if (scientists[i].birth_year <= res.peak_start_year && scientists[i].death_year >= res.peak_end_year) {
            printf("  - %-20s (Lifespan: %d - %d)\n",
                   scientists[i].name, scientists[i].birth_year, scientists[i].death_year);
        }
    }
    printf("\n");

    free(scientists);
    return 0;
}

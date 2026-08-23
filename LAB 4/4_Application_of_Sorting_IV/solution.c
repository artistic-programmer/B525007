/**
 * DAA Lab-04 - Question 4
 * Application of sorting-IV:
 * Camera tracking entry/exit times to determine time of maximum simultaneous party attendees.
 * Time Complexity: O(n log n).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    EVENT_EXIT = -1,
    EVENT_ENTRY = +1
} EventType;

typedef struct {
    double time;
    EventType type;
    int person_id;
} Event;

typedef struct {
    int id;
    double entry;
    double exit;
} Person;

typedef struct {
    int max_people;
    double peak_start_time;
    double peak_end_time;
} PartyPeakResult;

// Comparator for sorting events chronologically
int compare_events(const void *a, const void *b) {
    const Event *e1 = (const Event *)a;
    const Event *e2 = (const Event *)b;

    if (e1->time < e2->time) return -1;
    if (e1->time > e2->time) return 1;

    // Tie-breaking (if needed): Entry (+1) before Exit (-1)
    if (e1->type > e2->type) return -1;
    if (e1->type < e2->type) return 1;

    return 0;
}

/**
 * Sweep-line algorithm to find maximum simultaneous guests: O(n log n)
 */
PartyPeakResult find_max_simultaneous_party_time(const Person persons[], int n) {
    PartyPeakResult result = {0, 0.0, 0.0};
    if (n <= 0) return result;

    int num_events = 2 * n;
    Event *events = (Event *)malloc(num_events * sizeof(Event));
    if (!events) {
        fprintf(stderr, "Memory allocation error!\n");
        return result;
    }

    // Populate events
    for (int i = 0; i < n; i++) {
        events[2 * i]     = (Event){persons[i].entry, EVENT_ENTRY, persons[i].id};
        events[2 * i + 1] = (Event){persons[i].exit,  EVENT_EXIT,  persons[i].id};
    }

    // Sort events: O(n log n)
    qsort(events, num_events, sizeof(Event), compare_events);

    // Sweep line
    int current_count = 0;
    int max_count = 0;
    double best_start = 0.0;
    double best_end = 0.0;

    for (int i = 0; i < num_events; i++) {
        current_count += events[i].type;

        if (current_count > max_count) {
            max_count = current_count;
            best_start = events[i].time;
            // Peak interval continues until next event
            if (i + 1 < num_events) {
                best_end = events[i + 1].time;
            } else {
                best_end = events[i].time;
            }
        }
    }

    result.max_people = max_count;
    result.peak_start_time = best_start;
    result.peak_end_time = best_end;

    free(events);
    return result;
}

int main(void) {
    printf("=========================================================\n");
    printf("  DAA Lab 04 - Question 4: O(n log n) Party Peak Attendance\n");
    printf("=========================================================\n\n");

    Person party_guests[] = {
        {1, 1.0, 4.5},
        {2, 2.0, 6.0},
        {3, 3.5, 7.0},
        {4, 4.0, 5.5},
        {5, 8.0, 9.5},
        {6, 5.0, 8.5}
    };
    int n = sizeof(party_guests) / sizeof(party_guests[0]);

    printf("Party Guest Log (%d attendees):\n", n);
    for (int i = 0; i < n; i++) {
        printf("  Person #%d: Entry = %4.1f, Exit = %4.1f\n",
               party_guests[i].id, party_guests[i].entry, party_guests[i].exit);
    }
    printf("\n");

    PartyPeakResult res = find_max_simultaneous_party_time(party_guests, n);

    printf("[RESULT] Maximum Simultaneous Guests = %d\n", res.max_people);
    printf("[RESULT] Peak Presence Window       = [%.2f to %.2f]\n\n",
           res.peak_start_time, res.peak_end_time);

    // List attendees active during peak window
    printf("Guests present during peak window:\n");
    for (int i = 0; i < n; i++) {
        if (party_guests[i].entry <= res.peak_start_time && party_guests[i].exit >= res.peak_end_time) {
            printf("  - Person #%d (entered at %.1f, left at %.1f)\n",
                   party_guests[i].id, party_guests[i].entry, party_guests[i].exit);
        }
    }
    printf("\n[SUCCESS] Verification passed!\n");

    return 0;
}

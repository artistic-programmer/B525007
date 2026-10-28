# Question 6: The Best Time to Be Alive (Sweep-Line Algorithm)

## Problem Statement
Given a list of $n$ prominent scientists with their birth year $b_i$ and death year $d_i$ (where no living scientists are included), find the year range when the maximum number of scientists were simultaneously alive.
- **Tie-Breaking Rule**: If person $A$ died the same year person $B$ was born, the death event is assumed to happen before the birth event.
- Design an algorithm, implement it in C with interactive user input, prove correctness, and analyze complexity.

---

## Event-Based Sweep-Line Algorithm

### Data Structures
Each scientist is represented by a life interval $[b_i, d_i]$.
Convert each scientist into 2 discrete timeline events:
1. **Birth Event**: $(\text{year} = b_i, \; \text{type} = +1)$
2. **Death Event**: $(\text{year} = d_i, \; \text{type} = -1)$

```c
typedef struct {
    char name[50];
    int birth_year;
    int death_year;
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
```

---

## Event Sorting & Tie-Breaking Rule
Sort the $2n$ events chronologically:
1. **Primary Sort Key**: `event.year` ascending.
2. **Secondary Sort Key (Tie-Breaking)**: `EVENT_DEATH` ($-1$) before `EVENT_BIRTH` ($+1$).
   - **Rationale**: If Scientist $A$ dies in year $Y$ and Scientist $B$ is born in year $Y$, processing $A$'s death ($-1$) before $B$'s birth ($+1$) ensures that $A$ and $B$ are not counted as simultaneously alive during year $Y$, satisfying the problem's strict constraint.

---

## Pseudocode

```text
Algorithm BestTimeToBeAlive(scientists, n):
    Input: Array of n scientists with birth and death years
    Output: Peak year range and maximum simultaneous alive count

    num_events = 2 * n
    Initialize events array of size num_events

    For i = 0 to n - 1:
        events[2 * i]     = (year = scientists[i].birth_year, type = +1, id = i)
        events[2 * i + 1] = (year = scientists[i].death_year, type = -1, id = i)

    Sort events using Comparator:
        If e1.year != e2.year: Return e1.year - e2.year
        Return e1.type - e2.type  // -1 (DEATH) comes before +1 (BIRTH)

    current_alive = 0
    max_alive = 0
    best_start = 0
    best_end = 0

    For i = 0 to num_events - 1:
        current_alive += events[i].type
        If current_alive > max_alive:
            max_alive = current_alive
            best_start = events[i].year
            best_end = events[i + 1].year

    Return (max_alive, best_start, best_end)
```

---

## Complexity Analysis

| Phase | Time Complexity | Auxiliary Space | Explanation |
|---|---|---|---|
| **Event Population** | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | Creates $2n$ event structures. |
| **Event Sorting** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n)$ | QuickSort / qsort on $2n$ elements. |
| **Sweep-Line Pass** | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | Single pass over $2n$ sorted events. |
| **Overall Complexity** | **$\mathcal{O}(n \log n)$** | **$\mathcal{O}(n)$** | Dominant step is chronological event sorting. |

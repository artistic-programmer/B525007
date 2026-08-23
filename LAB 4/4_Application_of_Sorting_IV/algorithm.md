# Question 4: Application of Sorting-IV

## Problem Statement
A camera at the door tracks the entry time $a_i$ and exit time $b_i$ (assume $b_i > a_i$) for each of $n$ persons $p_i$ attending a party. Give an $\mathcal{O}(n \log n)$ algorithm that analyses this data to determine the time when the most people were simultaneously present at the party. Assume that all entry and exit times are distinct (no ties). By choosing the proper input representation, write a program in C to validate your algorithm.

---

## Input & Output Representation

### Data Structures
Each guest is tracked by an entry and exit timestamp. An **Event** represents a discrete arrival or departure point in time.

```c
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
    int max_people;
    double peak_start_time;
    double peak_end_time;
} PartyPeakResult;
```

---

## Algorithmic Strategy: Sweep-Line Algorithm

### Conceptual Walkthrough
1. **Deconstruct Intervals into Events**:
   - For each person $p_i$ with interval $(a_i, b_i)$, generate two discrete events:
     - Entry Event: $(a_i, \text{EVENT\_ENTRY}, i)$
     - Exit Event: $(b_i, \text{EVENT\_EXIT}, i)$
   - Total number of events = $2n$.

2. **Sort Events Chronologically**:
   - Sort the $2n$ events in ascending order of timestamp: $\mathcal{O}(2n \log(2n)) = \mathcal{O}(n \log n)$.
   - (Since all times are distinct per problem constraints, no tie-breaking ambiguity exists).

3. **Sweep-Line Traversal**:
   - Initialize `current_count = 0`, `max_count = 0`, `peak_time = 0.0`.
   - Iterate through the sorted events sequentially:
     - If event is `EVENT_ENTRY`: `current_count = current_count + 1`
       - If `current_count > max_count`:
         - `max_count = current_count`
         - `peak_time = event.time`
     - If event is `EVENT_EXIT`: `current_count = current_count - 1`
   - The sweeping pass takes linear time $\mathcal{O}(n)$.

---

## Pseudocode

```text
Algorithm FindPartyPeak(Persons, n):
    Input: Array of n Persons with entry time a[i] and exit time b[i]
    Output: Peak headcount max_count and peak timestamp

    1. Events = Array of size 2 * n
    2. For i = 0 to n - 1:
           Events[2 * i]     = Event(Persons[i].a, +1, Persons[i].id)
           Events[2 * i + 1] = Event(Persons[i].b, -1, Persons[i].id)

    3. Sort(Events, 0, 2 * n - 1) by time ascending  // O(n log n)

    4. current_count = 0
    5. max_count = 0
    6. best_time = 0.0

    7. For i = 0 to 2 * n - 1:
           current_count = current_count + Events[i].type
           If current_count > max_count:
               max_count = current_count
               best_time = Events[i].time

    8. Return (max_count, best_time)
```

---

## Correctness Proof

- **Step Invariance**: The number of people present at time $t$ equals:
  $$P(t) = \sum_{i: a_i \le t} 1 - \sum_{i: b_i \le t} 1$$
- Since the camera logs are discrete and sorted chronologically:
  - Between consecutive events $E_k$ and $E_{k+1}$, no arrivals or departures occur, so $P(t)$ is constant on $[E_k.\text{time}, E_{k+1}.\text{time})$.
  - At each event $E_k$, $P(t)$ changes by exactly $E_k.\text{type} \in \{+1, -1\}$.
- Therefore, `current_count` accurately tracks $P(t)$ across the entire timeline, and the maximum value attained by `current_count` is globally optimal.

---

## Complexity Analysis

| Phase | Time Complexity | Space Complexity |
|---|---|---|
| Event Array Construction | $\mathcal{O}(n)$ ($2n$ items) | $\mathcal{O}(n)$ |
| Sorting Events | $\mathcal{O}(n \log n)$ | $\mathcal{O}(1)$ aux (in-place) / $\mathcal{O}(n)$ |
| Sweep-Line Scan | $\mathcal{O}(n)$ ($2n$ iterations) | $\mathcal{O}(1)$ |
| **Total** | **$\mathcal{O}(n \log n)$** | **$\mathcal{O}(n)$** |

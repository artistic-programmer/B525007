# Question 5: Hitting a Moving Target Puzzle

## Problem Statement
A computer game has a shooter and a moving target hiding along $n > 1$ spots on a straight line ($1 \dots n$). Between every two consecutive shots, the target moves to an adjacent hiding spot ($s_{t+1} \in \{s_t - 1, s_t + 1\}$). The shooter cannot see the target. Design a deterministic shooting algorithm that guarantees hitting the target in a finite number of shots, prove its correctness, and analyze its complexity.

---

## Parity-Based Deterministic Hitting Algorithm

### Key Theoretical Invariants
1. **Parity Flip**: At each time step, the target moves to an adjacent spot, so its position parity flips (EVEN $\to$ ODD $\to$ EVEN $\to \dots$).
2. **Phase 1 (Even-Start Hypothesis)**:
   - Assume target starts at an EVEN spot at time $t=1$.
   - Shoot spots $2, 3, 4, \dots, n-1$ at times $t = 1, 2, 3, \dots, n-2$.
   - **Proof of Phase 1 Hit**: As the shot position increments by +1 per step, if the target attempts to cross the shooter from right to left, they must occupy the same spot at some step $t$. If target started on an even spot, it cannot escape Phase 1.
3. **Phase 2 (Odd-Start Hypothesis)**:
   - If the target started on an ODD spot, it survives Phase 1.
   - However, after Phase 1 (which takes $n-2$ steps), the target's parity has flipped, meaning it is now guaranteed to be on an **EVEN** spot!
   - Repeat the shot sequence $2, 3, 4, \dots, n-1$ at times $t = n-1, n, \dots, 2n-4$.
   - Guaranteed hit during Phase 2!

---

## Guaranteed Shot Sequence

For $n \ge 3$ hiding spots, the deterministic shot sequence of length $2(n - 2)$ is:
$$\text{Shot Sequence} = [\underbrace{2, 3, 4, \dots, n-1}_{\text{Phase 1 (Even Start)}}, \; \underbrace{2, 3, 4, \dots, n-1}_{\text{Phase 2 (Odd Start)}}]$$

For $n = 2$ hiding spots:
$$\text{Shot Sequence} = [2, 2] \quad (\text{or } [1, 1])$$

---

## Pseudocode

```text
Algorithm GenerateShotSequence(n):
    Input: Number of hiding spots n (n > 1)
    Output: Array of shot locations guaranteeing a hit

    If n == 2:
        Return [2, 2]

    shots = Array of size 2 * (n - 2)
    idx = 0

    // Phase 1: Target starts on EVEN spot
    For spot = 2 to n - 1:
        shots[idx++] = spot

    // Phase 2: Target starts on ODD spot
    For spot = 2 to n - 1:
        shots[idx++] = spot

    Return shots
```

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Max Shots Required** | $2(n - 2) = \mathcal{O}(n)$ | Linear bound in number of hiding spots $n$. |
| **Time Complexity** | $\mathcal{O}(n)$ | Time to construct and execute shot sequence. |
| **Auxiliary Space** | $\mathcal{O}(n)$ | Space to store shot sequence array. |

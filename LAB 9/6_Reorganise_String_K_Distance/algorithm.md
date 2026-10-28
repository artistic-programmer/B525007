# Question 6: Reorganize String with K-Distance Apart

## Problem Statement
Given a string $S$ of length $N$ and an integer $K$, rearrange the characters of $S$ such that identical characters are placed at least distance $K$ apart (i.e., if $S[i] = S[j]$, then $|i - j| \ge K$). If no valid rearrangement exists, return an empty string (or state that it is impossible).

---

## Greedy Max-Heap with Cooldown Queue Algorithm

### 1. Conceptual Principle
To prevent high-frequency characters from being crowded out and forced into adjacent positions later in the string, we must greedily place the character with the **highest remaining frequency** as early as possible. However, once character $c$ is placed at index $i$, it is locked in a **cooldown window** and cannot be reused until index $i + K$.

### 2. Algorithmic Steps
1. Count the frequency of each unique character in $S$.
2. Insert all characters with non-zero frequency into a **Max-Heap**, ordered by frequency.
3. Maintain a **FIFO Cooldown Queue** of pairs `(character, remaining_frequency)`.
4. In each iteration $step = 0, 1, \dots, N - 1$:
   - Check the cooldown queue: if the queue has reached size $K$ (meaning the character at the front was placed $K$ steps ago), pop that character and, if its remaining count $> 0$, re-insert it into the Max-Heap.
   - If the Max-Heap is empty, no valid character is currently off cooldown $\implies$ rearrangement is impossible! Return empty string.
   - Extract the character $c$ with the largest remaining frequency from the Max-Heap.
   - Append $c$ to the output string.
   - Decrement its frequency by 1 and enqueue $(c, \text{count} - 1)$ into the cooldown queue.
5. If all $N$ characters are successfully placed, return the reorganized string.

---

## Pseudocode

```text
Algorithm ReorganizeStringKDistance(S, N, K):
    Input: String S of length N, integer K
    Output: Reorganized string or Empty String

    If K <= 1:
        Return S

    Count character frequencies in freq[256]
    Initialize MaxHeap H
    For c in Alphabet:
        If freq[c] > 0:
            H.insert((c, freq[c]))

    Initialize Queue Q
    result = ""

    While H is not empty:
        curr = H.extract_max()
        result.append(curr.char)
        curr.freq -= 1
        Q.push(curr)

        If Q.size == K:
            front = Q.pop()
            If front.freq > 0:
                H.insert(front)

    If Length(result) == N:
        Return result
    Else:
        Return "" (Impossible)
```

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(N \log |\Sigma|)$ | $N$ steps, each performing heap insert/extract on at most $|\Sigma| \le 256$ elements. |
| **Auxiliary Space** | $\mathcal{O}(N + |\Sigma|)$ | Output string buffer, Max-Heap, and queue of size $K$. |

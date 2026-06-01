# CPP09 ex02 — PmergeMe (Ford-Johnson Sort)

This document details the implementation of **ex02 (PmergeMe)**, explaining the header [PmergeMe.hpp](file:///c:/42AD/staff-evaluation/cpp09/ex02/PmergeMe.hpp), source file [PmergeMe.cpp](file:///c:/42AD/staff-evaluation/cpp09/ex02/PmergeMe.cpp), and [main.cpp](file:///c:/42AD/staff-evaluation/cpp09/ex02/main.cpp).

---

## 1. The Ford-Johnson Algorithm (Merge-Insertion Sort)

The **Ford-Johnson algorithm** (designed in 1959) is a comparison-optimal sorting algorithm. It is designed to sort elements using the **fewest possible comparisons**. 

The algorithm executes in five main phases:

```
                          Ford-Johnson Sorting Phases
                                       │
  1. Pairing: Pair adjacent elements. Max element is first, Min is second.
                                       │
  2. Sorting Maxima: Recursively sort the pairs by their first elements (maxima).
                                       │
  3. Main/Pending Chains: Create a sorted "Main Chain" from pair firsts,
     and an unsorted "Pending Chain" from pair seconds.
                                       │
  4. Jacobsthal Ordering: Generate insertion order indices using Jacobsthal numbers.
                                       │
  5. Binary Insertion: Insert pending elements into main chain based on index order,
     followed by any leftover odd element.
```

---

## 2. Walkthrough of Vector Sort Functions (`ex02/PmergeMe.cpp`)

To compare performance, the class implements the exact same logic using two different sequential containers: `std::vector` and `std::deque`. We will walk through the vector functions.

### [sort](file:///c:/42AD/staff-evaluation/cpp09/ex02/PmergeMe.cpp#L24-L61)
* **What it is for:** High-level controller for vector sorting.
* **How it works:**
  1. Aborts if array size is $\le 1$.
  2. Calls `makePairs` to group elements.
  3. Calls `sortPairs` to sort pairs based on the larger elements.
  4. Calls `buildMainChain` (larger elements, initially sorted) and `buildPendingChain` (smaller elements, unsorted).
  5. Generates the Jacobsthal index insertion sequence.
  6. Loops through the sequence, inserting elements from the pending chain into the main chain via `binaryInsert`.
  7. If an odd leftover element exists, inserts it.
  8. Assigns the sorted main chain back to the array.

### [makePairs](file:///c:/42AD/staff-evaluation/cpp09/ex02/PmergeMe.cpp#L63-L90)
* **What it is for:** Groups elements into ordered pairs.
* **How it works:**
  * If the array size is odd, sets `hasLeftover = true` and stores the final element in `leftover`.
  * Loops in steps of 2, creating pairs of `(max(a, b), min(a, b))`.
  * Returns the array of pairs.

### [sortPairs](file:///c:/42AD/staff-evaluation/cpp09/ex02/PmergeMe.cpp#L92-L106)
* **What it is for:** Sorts the pairs array.
* **Why it is needed:** Establishes the sorted backbone.
* **How it works:** Implements **Insertion Sort** on the pairs, comparing only `pair.first` (the maxima). Since the main chain consists of these first elements, sorting the pairs ensures the main chain is sorted.

### [generateJacobsthal](file:///c:/42AD/staff-evaluation/cpp09/ex02/PmergeMe.cpp#L132-L181)
* **What it is for:** Computes the insertion order index sequence.
* **Why it is needed:** Minimizes the number of comparisons.
* **How it works:**
  * **Jacobsthal Numbers** are defined by the recurrence:
    $$J_0 = 0, \quad J_1 = 1, \quad J_k = J_{k-1} + 2 J_{k-2}$$
    The sequence is: $0, 1, 3, 5, 11, 21, 43, 85, \dots$.
  * We generate Jacobsthal numbers up to the size of the pending chain.
  * To minimize comparisons, we insert elements in blocks. We start at the index matching the current Jacobsthal number and count down to the previous Jacobsthal number:
    * Block 1 (up to $J_2 = 3$): index `2`, then index `1` (index `0` is already in the main chain).
    * Block 2 (up to $J_3 = 5$): index `4`, then index `3`.
    * Block 3 (up to $J_4 = 11$): index `10`, then `9`, `8`, `7`, `6`.
  * This order ensures that when we insert an element, the size of the main chain is optimized to minimize the worst-case binary search comparisons.

### [binaryInsert](file:///c:/42AD/staff-evaluation/cpp09/ex02/PmergeMe.cpp#L183-L202)
* **What it is for:** Inserts a value into a sorted array.
* **Why it is needed:** Binary search finds the insertion index in $O(\log n)$ comparisons.
* **How it works:** Performs a binary lower-bound search using `left`, `right`, and `mid` pointers. Once the index `left` is resolved, calls `vector.insert` to write the element.

---

## 3. Comparing Vector and Deque Paths

The deque path (`dequeSort`, `makeDequePairs`, etc.) uses the **exact same logical steps** but works on `std::deque<int>` containers.

During evaluations, you will be asked to compare their behaviors:

| Aspect | `std::vector` | `std::deque` |
| :--- | :--- | :--- |
| **Memory Allocation** | Contiguous block of memory. | Segmented blocks (chunks) linked via a directory pointer map. |
| **Random Access** | Faster (direct pointer arithmetic). | Slightly slower (requires dereferencing chunk directory). |
| **Insertion Cost** | High. Inserting in the middle requires shifting all elements downstream in memory. | High in the middle (must shift elements in affected chunks), but $O(1)$ at both boundaries. |
| **Resizing Cost** | If capacity is exceeded, allocates a new larger block and copies all elements. | Adds a new chunk without copying existing elements. |

---

## 4. Main Program & Time Benchmarking (`ex02/main.cpp`)

The main entry point parses command line inputs, runs both paths, and reports execution times:

```cpp
        std::clock_t startVec = std::clock();
        fordSort.sort(vectorNumbers);
        std::clock_t endVec = std::clock();
        double timeVec = 1000000.0 * (endVec - startVec) / CLOCKS_PER_SEC;
```
* **What it is for:** Measures CPU execution time.
* **How it works:**
  * Uses `std::clock()` to get CPU clocks before and after.
  * Converts the clock diff to microseconds:
    $$\text{time} = 1,000,000.0 \times \left(\frac{\text{end} - \text{start}}{\text{CLOCKS\_PER\_SEC}}\right)$$

---

## Next Steps

Let's look at **common evaluation questions and answers** for C++ Module 09.

👉 Proceed to [04_Evaluation_Q_and_A.md](./04_Evaluation_Q_and_A.md)

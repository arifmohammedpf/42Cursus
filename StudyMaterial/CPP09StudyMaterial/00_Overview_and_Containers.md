# CPP09 — C++ Containers & Overview

Welcome to the C++ Module 09 Study Materials! This module focuses on the **C++ Standard Template Library (STL) containers**. The exercises require you to select and implement solutions using different container structures, demonstrating your understanding of container mechanics, operations complexity, and STL algorithms.

---

## 1. STL Container Taxonomy

C++ STL containers are divided into three main categories:

```
                            STL Containers
                                  │
         ┌────────────────────────┼────────────────────────┐
         ▼                        ▼                        ▼
Sequence Containers     Associative Containers     Container Adapters
 - std::vector            - std::map (Sorted Key-Val)  - std::stack (LIFO)
 - std::deque (Double-end)- std::set (Sorted Unique)   - std::queue (FIFO)
 - std::list (Linked List)- std::multimap / std::multiset-std::priority_queue
```

### A. Sequence Containers
These maintain the mathematical ordering of elements.
* **`std::vector`:** A dynamically resizing array.
  * *Memory:* Contiguous memory blocks.
  * *Complexity:* Random access is $O(1)$. Insert/erase at the end is amortized $O(1)$. Insert/erase in the middle is $O(n)$ because elements must be shifted.
* **`std::deque`:** A double-ended queue.
  * *Memory:* Non-contiguous chunks of contiguous memory (a directory of chunks).
  * *Complexity:* Random access is $O(1)$ (with slightly more overhead than vector). Insert/erase at both the front and the end is $O(1)$. Insert/erase in the middle is $O(n)$.
* **`std::list`:** A doubly-linked list.
  * *Memory:* Non-contiguous node allocations.
  * *Complexity:* Random access is $O(n)$ (must walk the list). Insert/erase at any known iterator position is $O(1)$.

### B. Associative Containers
These store elements as sorted key-value pairs or sorted unique values, implemented internally as self-balancing binary search trees (specifically **Red-Black Trees**).
* **`std::map`:** Key-Value associative array. Keys must be unique and are stored in sorted order.
  * *Complexity:* Search, insertion, and deletion are $O(\log n)$ due to tree traversal.
* **`std::set`:** Stores unique sorted keys.
  * *Complexity:* Search, insertion, and deletion are $O(\log n)$.

### C. Container Adapters
These are not independent containers. Instead, they wrap an existing sequence container (like vector, deque, or list) to provide a restricted interface.
* **`std::stack`:** Last-In, First-Out (LIFO) data structure.
  * *Default Underlying Container:* `std::deque`.
  * *Operations:* `push()`, `pop()`, `top()`, `size()`, `empty()`. All are $O(1)$.

---

## 2. C++ Module 09 Exercise Summary

In this project, you implement three distinct utilities:

| Exercise | Application | Primary Container | secondary Container | Key Learning Concept |
| :---: | | :---: | :---: | :---: |
| **ex00** | Bitcoin Exchange | `std::map<std::string, float>` | None | Database lookups, file parsing, associative keys. |
| **ex01** | RPN Calculator | `std::stack<int>` | None | Postfix notation parsing, LIFO execution. |
| **ex02** | PmergeMe | `std::vector<int>` | `std::deque<int>` | Ford-Johnson sort, algorithm implementation on different containers, performance benchmarking. |

### STL Rules in Module 09
* Each exercise must utilize at least one container.
* Once a container is used in an exercise, **you are forbidden from using it in the other exercises** (subject rules constraint).
  * *Current Setup:*
    * `ex00` uses **`std::map`**.
    * `ex01` uses **`std::stack`**.
    * `ex02` uses **`std::vector`** and **`std::deque`**.
    * This setup complies with the constraints since there is no overlapping usage across different exercises (except within the comparative paths of `ex02`).

---

## Next Steps

Let's look at the implementation of **ex00: Bitcoin Exchange**.

👉 Proceed to [01_ex00_Bitcoin_Exchange.md](./01_ex00_Bitcoin_Exchange.md)

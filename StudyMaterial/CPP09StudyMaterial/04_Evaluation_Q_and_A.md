# CPP09 — Evaluation Q&A Cheat Sheet

This document compiles the most common questions asked by 42 evaluators during the C++ Module 09 defense, along with clear, technical, and accurate answers to help you explain the project successfully.

---

## 1. ex00: Bitcoin Exchange

### Q1: Why did you choose `std::map` for ex00?
* **Answer:** `std::map` is a sorted associative container implemented as a Red-Black Tree. It stores key-value pairs (`date` string $\rightarrow$ `rate` float). Since dates sorted alphabetically match chronological sorting (e.g. `"2012-01-01"` < `"2012-01-02"`), the map maintains the database in chronological order automatically, enabling fast $O(\log n)$ search lookups.

### Q2: What is the difference between your custom recursive `lowerBound` string decrement search and the standard `std::map::lower_bound` algorithm?
* **Answer:**
  * **Our Custom Logic:** Decrements the day, month, and year values in the date string and recursively queries the map until a key matches. This works, but it can traverse through invalid calendar dates (e.g. February 30th) if they are missing from the map, and it requires multiple lookups.
  * **`std::map::lower_bound`:** A standard member function that searches the internal Red-Black Tree nodes directly in $O(\log n)$ time. It returns an iterator pointing to the first element that is not less than the key. If it doesn't match exactly, decrementing the iterator by one (`--it`) immediately gives the closest preceding date, requiring only a single tree traversal.

---

## 2. ex01: Reverse Polish Notation

### Q3: Why is `std::stack` the best container choice for ex01?
* **Answer:** Postfix expressions are evaluated using a Last-In, First-Out (LIFO) model. Operands are accumulated, and the most recently parsed operands are consumed by the next parsed operator. A stack is designed specifically to restrict access to this LIFO interface (`push`, `pop`, `top`), making the code clean and preventing illegal intermediate index modifications.

### Q4: Can you implement a stack using a vector?
* **Answer:** Yes. `std::stack` is a container adapter, not a standalone container. By default, it wraps `std::deque` but can be configured to use `std::vector` (e.g. `std::stack<int, std::vector<int> >`). A vector supports fast push/pop at the end ($O(1)$), making it a viable underlying storage structure.

---

## 3. ex02: PmergeMe (Ford-Johnson Sort)

### Q5: What is the mathematical goal of the Ford-Johnson algorithm?
* **Answer:** It aims to minimize the **number of comparisons** needed to sort a sequence. It does not minimize memory footprint or CPU operations (like element shifting), only comparisons.

### Q6: Why do we compare `std::vector` vs. `std::deque`?
* **Answer:** To demonstrate how underlying container memory layouts affect performance even when running the exact same algorithm:
  * `std::vector` stores elements in a contiguous block. Random access is fast, but inserting in the middle requires shifting all subsequent elements in memory.
  * `std::deque` stores elements in segmented chunks. Inserting in the middle can be slightly faster since only the affected chunks need shifting, but random access requires an extra pointer dereference.
  * Comparing their execution times in microseconds shows these physical performance differences.

### Q7: Why do we use Jacobsthal numbers to determine insertion order?
* **Answer:** When binary-inserting elements from the pending chain into the sorted main chain, the number of comparisons depends on the current size of the main chain. The Jacobsthal sequence defines boundaries that maximize the probability of performing binary searches with the minimum possible comparison queries. By inserting elements in blocks from a Jacobsthal boundary downwards, we keep comparisons optimal.

### Q8: What is the time complexity of your `PmergeMe` implementation?
* **Answer:**
  * **Comparisons:** The pairing and binary search steps take $O(n \log n)$ comparisons.
  * **Element shifting:** Inserting elements into the middle of vectors or deques takes $O(n)$ time. Performing this $n$ times results in an overall execution complexity of $O(n^2)$.
  * **Pair sorting:** Our implementation sorts pairs using an insertion sort, which has a worst-case complexity of $O(n^2)$.
  * Therefore, while the algorithm is optimized for comparisons, the physical runtime complexity remains **quadratic** ($O(n^2)$) due to element shifting.

---

## 4. Input Validations & STL Constraints

### Q9: How does the parser prevent integer overflow during string conversion?
* **Answer:** In `isValidNumber`, the string is converted to a `long long` using `std::atoll`. The value is then compared against `INT_MIN` and `INT_MAX`. It is only cast to a standard `int` if it falls within these bounds.

### Q10: Why does the subject require that once a container is used, it cannot be used in other exercises?
* **Answer:** To force students to learn different container types (associative `std::map`, adapter `std::stack`, sequential `std::vector` and `std::deque`) and understand their design differences, rather than using one container (like vector) for every task.

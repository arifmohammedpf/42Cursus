# C++ Modules 07 to 09 — Templates, STL & Algorithms

This document details the concepts of C++ Templates (parametric polymorphism), Standard Template Library (STL) containers, iterators, algorithms, and Module 09 advanced structures.

---

## 1. C++ Module 07: Templates & Generic Programming

Templates allow you to write generic functions or classes that work with any data type, shifting type binding from compile-time definition to compile-time instantiation.

### ex00 & ex01: Function Templates (`swap`, `min`, `max`, `iter`)
* **Concept Learned:** Function templates.
* **Why it is needed:** Avoids writing duplicate code for different types (e.g. writing separate `min` functions for int, float, double).
* **How it works:**
  * Defines a template prefix: `template <typename T>`.
  * The compiler generates concrete functions for each type used in the code at compile-time (template instantiation).
  * `iter` takes an array pointer, length, and a function pointer, applying the function to each array element generic-style.

### ex02: Class Templates (`Array`)
* **Concept Learned:** Class templates and memory allocation inside templates.
* **How it works:**
  * Implements a generic array class: `template <typename T> class Array`.
  * Mallocs the array using `new T[size]`.
  * Overloads the subscript operator (`operator[]`) to allow access:
    ```cpp
    T &operator[](unsigned int index) {
        if (index >= _size)
            throw std::out_of_range("Index out of bounds");
        return _elements[index];
    }
    ```
  * Performs boundaries check and throws exceptions on out-of-range queries.

---

## 2. C++ Module 08: STL Containers & Iterators

Module 08 introduces the C++ Standard Template Library (STL) containers and algorithms.

### ex00: Easyfind
* **Concept Learned:** STL algorithms and iterators.
* **Why it is needed:** Demonstrates how to search containers generically.
* **How it works:** Takes a container template type and searches for an integer using the standard `std::find` algorithm. Returns the iterator or throws an exception if not found:
  ```cpp
  typename T::iterator it = std::find(container.begin(), container.end(), value);
  ```

### ex01: Span
* **Concept Learned:** Storing ranges and calculations.
* **How it works:**
  * Implements a class that stores up to `N` integers.
  * `shortestSpan()`: Sorts the list and finds the minimum difference between adjacent numbers.
  * `longestSpan()`: Calculates the difference between the maximum and minimum elements using `std::min_element` and `std::max_element`.
  * Implements an iterator range insertion function to add multiple numbers at once using `std::copy` to avoid loop overhead.

### ex02: MutantStack (Inheriting from Stack)
* **Concept Learned:** Container adapters and accessing protected members.
* **Why it is needed:** The standard `std::stack` does **not** support iterators. This exercise asks you to add iterator support to the stack.
* **How it works:**
  * Inherits from `std::stack`: `class MutantStack : public std::stack<T>`.
  * In the standard template definition, `std::stack` has a protected member variable named **`c`**, which is the underlying container (usually `std::deque`).
  * We expose this container's iterators by defining `begin()` and `end()` functions that return `c.begin()` and `c.end()`:
    ```cpp
    typedef typename std::stack<T>::container_type::iterator iterator;
    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
    ```

---

## 3. C++ Module 09: Advanced STL Containers

Module 09 is the final capstone, applying container characteristics to solve complex problems under strict constraints.

### ex00: Bitcoin Exchange (`std::map`)
* **Key Concept:** Sorting and lookups in associative containers.
* **Mechanism:** Uses `std::map<std::string, float>` to store exchange rates chronologically, performing $O(\log n)$ binary lookups.

### ex01: RPN Calculator (`std::stack`)
* **Key Concept:** Postfix notation processing using container adapters.
* **Mechanism:** Uses `std::stack<int>` to store operands in a LIFO sequence, executing operations when operators are parsed.

### ex02: PmergeMe (`std::vector` vs. `std::deque`)
* **Key Concept:** Sorting algorithms and container comparison.
* **Mechanism:** Implements the Ford-Johnson (merge-insertion) sort algorithm on both `std::vector` (contiguous memory) and `std::deque` (segmented chunks) to compare execution times in microseconds.

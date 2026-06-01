# C++ Module 09 Codebase Study Materials

This directory contains comprehensive study materials for the **C++ Module 09** codebase. These resources are designed to help you understand C++ STL containers (vector, deque, map, stack), sequential and associative architectures, and complexity benchmarks, enabling you to explain the codebase clearly during your defense.

---

## 📖 Chapter Index

| Chapter | File | Description | Key Concepts Covered |
|:---:|---|---|---|
| **0** | [00_Overview_and_Containers.md](./00_Overview_and_Containers.md) | Introduction to C++ STL containers taxonomy. | Sequence containers (vector, deque, list), associative containers (map, set), container adapters (stack), and project constraints. |
| **1** | [01_ex00_Bitcoin_Exchange.md](./01_ex00_Bitcoin_Exchange.md) | Database lookup using associative maps. | `std::map` key-value pairs, chronological sorting, date parsing/validation, and recursive string decrement searching. |
| **2** | [02_ex01_RPN.md](./02_ex01_RPN.md) | Postfix arithmetic logic using stacks. | Reverse Polish Notation, `std::stack` LIFO architecture, string tokenization, and operator evaluation order. |
| **3** | [03_ex02_PmergeMe.md](./03_ex02_PmergeMe.md) | Ford-Johnson sorting and container comparison. | `std::vector` vs. `std::deque` memory layout differences, pairing logic, Jacobsthal index sequences, and execution time tracking. |
| **4** | [04_Evaluation_Q_and_A.md](./04_Evaluation_Q_and_A.md) | Viva defense cheat sheet for evaluations. | Red-Black Trees, $O(n^2)$ vs. $O(n \log n)$ complexity details, container selection justifications, and integer overflow checks. |

---

## 🛠️ How to Use These Materials

1. **Start with Chapter 0:** Understand the C++ STL container types and why specific classes are chosen for each exercise.
2. **Follow Code References:** Files and class methods are linked (e.g. `[BitcoinExchange.cpp]`) to let you jump straight to the source files on your system.
3. **Review the Q&A Cheat Sheet:** Use **Chapter 4** to prepare for evaluator questions, especially regarding the difference between your custom lookup algorithms and standard library functions.

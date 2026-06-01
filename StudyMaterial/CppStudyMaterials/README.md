# C++ Modules & OOP Codebase Study Materials

This directory contains comprehensive study materials for the **C++ Modules (00 to 09)**. These resources are designed to help you understand Object-Oriented Programming (OOP) concepts, memory allocation, operator overloading, inheritance, polymorphism, exceptions, type casting, templates, and the STL container suite, enabling you to explain the codebase clearly during your defenses.

---

## 📖 Chapter Index

| Chapter | File | Description | Key Concepts Covered |
|:---:|---|---|---|
| **0** | [00_OOP_Concepts_Overview.md](./00_OOP_Concepts_Overview.md) | The foundations of Object-Oriented Programming. | Encapsulation, Abstraction, Inheritance, Polymorphism (subtype vs. ad-hoc vs. parametric), Orthodox Canonical Class Form, and Stack vs. Heap memory allocation. |
| **1** | [01_Modules_00_to_02_Basics_and_Overloading.md](./01_Modules_00_to_02_Basics_and_Overloading.md) | Syntax basics, references, pointers, streams, and fixed-point math. | I/O streams, pointers to members, heap arrays allocations (`new`/`delete`), file operations, member function pointers, fixed-point math representation, and operator overloading. |
| **2** | [02_Modules_03_to_04_Inheritance_and_Polymorphism.md](./02_Modules_03_to_04_Inheritance_and_Polymorphism.md) | Object hierarchy, dynamic binding, and deep copies. | Base/derived constructors execution order, protected scopes, virtual tables (Vtable), slice effect preventions, virtual destructors, deep copy implementations, abstract classes, and interfaces. |
| **3** | [03_Module_05_Exceptions_and_Validation.md](./03_Module_05_Exceptions_and_Validation.md) | Exception handling structures and design patterns. | Try-catch blocks, custom nested exception classes, standard exception inheritance, exception specifications (`throw()`), error propagation, and the Factory Pattern. |
| **4** | [04_Module_06_Type_Casting.md](./04_Module_06_Type_Casting.md) | C++ casting mechanisms and RTTI. | `static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast` compile vs. runtime checks, raw pointer serialization, and reference dynamic casts. |
| **5** | [05_Modules_07_to_09_Templates_STL_and_Algorithms.md](./05_Modules_07_to_09_Templates_STL_and_Algorithms.md) | Generics, standard containers, iterators, and sorting. | Function and class templates, STL algorithms (`std::find`), iterator properties, container adapter extensions (`MutantStack`), maps, stacks, vectors, deques, and the Ford-Johnson sort. |

---

## 🛠️ How to Use These Materials

1. **Focus on OOP Pillars:** Read **Chapter 0** to build a strong theoretical foundation of how C++ structures objects.
2. **Revise Exercise Goals:** Use **Chapters 1 to 5** to study the specific concepts and learning outcomes for each C++ exercise.
3. **Trace Memory Behaviors:** Pay close attention to deep copies (Chapter 2), array allocations (Chapter 1), and exception safety (Chapter 3) as they are the most common focus areas during project evaluations.

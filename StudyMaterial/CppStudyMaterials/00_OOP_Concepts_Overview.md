# C++ & OOP Core Concepts Overview

Welcome to the C++ Modules Study Materials! This document provides a comprehensive overview of C++ and Object-Oriented Programming (OOP) concepts. Understanding these concepts is essential to pass your module defenses.

---

## 1. What is Object-Oriented Programming (OOP)?

**Object-Oriented Programming** is a programming paradigm based on the concept of "objects," which contain data (attributes/properties) and code (methods/functions). C++ is a multi-paradigm language that supports procedural, object-oriented, and generic programming.

The four pillars of OOP are:

```
                            The 4 Pillars of OOP
                                      │
         ┌───────────────────┬────────┴──────────┬───────────────────┐
         ▼                   ▼                   ▼                   ▼
   Encapsulation        Abstraction         Inheritance        Polymorphism
  - Private variables  - Abstract classes  - Parent/Child      - Virtual functions
  - Public getters     - Interfaces        - Code reusability  - Operator overloading
```

### A. Encapsulation
* **What it is:** Bundling data and methods that operate on that data within a single unit (a class), and restricting direct access to some of the object's components.
* **How C++ implements it:** Using access specifiers:
  * `private`: Accessible only within the class. (Default for `class`).
  * `protected`: Accessible within the class and its derived classes.
  * `public`: Accessible from outside the class.

### B. Abstraction
* **What it is:** Hiding complex implementation details and showing only the essential features of an object.
* **How C++ implements it:** Using abstract classes (classes with at least one pure virtual function) and header files (`.hpp`), which expose class declarations while hiding definition details (`.cpp`).

### C. Inheritance
* **What it is:** A mechanism where a new class (derived/child class) inherits attributes and behaviors from an existing class (base/parent class).
* **How C++ implements it:** E.g. `class Dog : public Animal {};`.

### D. Polymorphism
* **What it is:** The ability of different classes to respond to the same message (function call) in different ways.
* **Types of Polymorphism in C++:**
  1. **Ad-hoc Polymorphism (Function & Operator Overloading):** Multiple functions with the same name but different signatures, resolved at compile-time.
  2. **Subtype Polymorphism (Runtime Polymorphism):** Virtual functions. Resolving which class method to run at runtime using a virtual table (**Vtable**).
  3. **Parametric Polymorphism (Compile-time Polymorphism):** Templates. Defining functions or classes with generic types.

---

## 2. The Orthodox Canonical Class Form

Starting from Module 02, the subject requires all C++ classes to be written in the **Orthodox Canonical Class Form**. This guarantees that C++ compiler defaults do not cause unexpected memory corruption during copying or destruction.

A canonical class must implement four special member functions:

```cpp
class Canonical
{
public:
    Canonical();                             // 1. Default Constructor
    Canonical(const Canonical &src);          // 2. Copy Constructor
    Canonical &operator=(const Canonical &rhs); // 3. Copy Assignment Operator
    ~Canonical();                            // 4. Destructor
};
```

* **Why it is needed:** If your class allocates memory on the heap (using `new`), the default copy constructor and copy assignment operator provided by the compiler perform a **shallow copy** (copying the raw pointer addresses). This results in two objects pointing to the same heap memory, leading to double-free crashes on destruction. Implementing the canonical form allows you to write a **deep copy** (allocating new heap memory for the copy).

---

## 3. C++ Memory Management: Stack vs. Heap

| Feature | The Stack | The Heap |
| :--- | :--- | :--- |
| **Allocation** | Managed automatically by the CPU. | Managed manually by the programmer. |
| **Speed** | Extremely fast. | Slower (requires locating a free memory block). |
| **Lifetime** | Tied to the scope block (destroyed on function exit). | Lives until explicitly deleted or the program ends. |
| **Creation Keyword** | `Canonical obj;` | `Canonical *obj = new Canonical();` |
| **Destruction Keyword**| Automatic. | `delete obj;` (or `delete[] array;`) |
| **Risk** | Stack overflow (if calling deep recursion). | Memory leaks (if forgetting to delete). |

### Rules of `new` and `delete`
* Every call to `new` must have a corresponding call to `delete`.
* Every call to `new[]` (array allocation) must have a corresponding call to `delete[]`. Mixing them results in undefined behavior.

---

## Next Steps

Let's study the first three modules (Modules 00 to 02) covering namespaces, memory allocation, and operator overloading.

👉 Proceed to [01_Modules_00_to_02_Basics_and_Overloading.md](./01_Modules_00_to_02_Basics_and_Overloading.md)

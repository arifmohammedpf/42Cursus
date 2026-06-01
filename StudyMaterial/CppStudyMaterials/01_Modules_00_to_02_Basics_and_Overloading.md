# C++ Modules 00 to 02 — Basics, Memory & Overloading

This document walks through the conceptual targets and learning outcomes of C++ Modules 00, 01, and 02.

---

## 1. C++ Module 00: Namespaces, Classes, and Streams

Module 00 is an introduction to C++ syntax, namespaces, standard inputs/outputs, and basic class encapsulation.

### ex00: Megaphone
* **Concept Learned:** Namespaces and I/O streams.
* **Why it is needed:** Replaces C standard I/O (`printf`) with type-safe C++ streams (`std::cout`, `std::endl`).
* **How it works:** Iterates through command-line strings and prints them converted to uppercase.

### ex01: Phonebook
* **Concept Learned:** Class structure, encapsulation, and input stream handling.
* **Why it is needed:** Introduces public/private attributes, class instances (objects), and reading from standard input.
* **How it works:**
  * Implements `Contact` (private strings for name, phone, secrets) and `PhoneBook` classes.
  * Uses `std::cin` and `std::getline` to read user input.
  * Handles input stream failures (such as Ctrl+D EOF interrupts) gracefully.

---

## 2. C++ Module 01: Memory Allocation, References, and Pointers

Module 01 covers heap allocation, references, file streams, and pointers to class member functions.

### ex00 & ex01: Zombie Heap vs. Stack Allocations
* **Concept Learned:** Stack vs. Heap allocation, and arrays allocations.
* **Why it is needed:** Choosing the correct allocation strategy affects performance and memory safety.
* **How it works:**
  * **Stack allocation:** Instantiating objects directly inside a scope. They are destroyed automatically when the scope exits.
  * **Heap allocation (`new`):** Dynamic allocation. The object survives scope exits until explicitly destroyed using `delete`.
  * **Array allocation (`new[]`):** Allocating contiguous blocks of objects on the heap. Must be deleted using `delete[]`.

### ex02: HI THIS IS BRAIN
* **Concept Learned:** References vs. Pointers.
* **Why it is needed:** C++ introduces references, which are safer than pointers because they cannot be null or rebound to another variable after initialization.
* **How it works:** Compares printing string values and memory addresses using:
  * The raw string variable.
  * A pointer to the string (`std::string *ptr = &str;`).
  * A reference to the string (`std::string &ref = str;`).

### ex03: Weapon Pointers vs. References
* **Concept Learned:** Deciding when to store pointers vs. references inside a class.
* **Why it is needed:** References must be bound at construction and cannot be null. Pointers can be null and can change targets.
* **How it works:**
  * `HumanA` stores its `Weapon` as a reference (`Weapon &`) because HumanA is guaranteed to have a weapon at creation and it cannot be changed.
  * `HumanB` stores its `Weapon` as a pointer (`Weapon *`) because HumanB might not have a weapon initially (pointer is null) and can swap weapons later.

### ex04: Sed Is For Losers
* **Concept Learned:** File streams (`std::ifstream`, `std::ofstream`) and string algorithms.
* **Why it is needed:** Replaces C-style file handling (`fopen`, `fprintf`) with C++ streams.
* **How it works:** Opens an input file, reads it line-by-line, uses string methods (`find` and `insert`/`replace`) to replace all occurrences of a search string, and writes the output to a new `.replace` file.

### ex05: Harl 2.0 (Pointers to Member Functions)
* **Concept Learned:** Function pointers inside classes.
* **Why it is needed:** Avoids cascading, unmaintainable `if-else` blocks when routing inputs to class methods.
* **How it works:** Declares an array of pointers to Harl's member functions and maps input level strings (DEBUG, INFO, WARNING, ERROR) to their corresponding indexes, invoking the target function dynamically:
  ```cpp
  void (Harl::*complaints[])(void) = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error };
  ```

---

## 3. C++ Module 02: Orthodox Canonical Form and Fixed-Point Math

Module 02 introduces fixed-point representation math and operator overloading.

### ex00 & ex01: Fixed-Point Number Class
* **Concept Learned:** Orthodox Canonical Form, operator overloading, and fixed-point math.
* **Why it is needed:** Real-world systems often use fixed-point arithmetic instead of floating-point arithmetic to maintain precision on systems without a Floating Point Unit (FPU).
* **How it works:**
  * Implements constructors, copy constructors, destructors, and assignment operators.
  * Stores the number as an integer representing a fixed-point value with a constant number of fractional bits (e.g. `8` bits).
  * **Conversions:**
    * Integer to Fixed: Shift left by 8 bits (`int << 8`).
    * Float to Fixed: Multiply by $2^8$ (256) and round (`roundf(f * 256)`).
    * Fixed to Float: Divide by 256.0 (`(float)val / 256`).
  * Overloads the stream insertion operator (`<<`) to print fixed-point values directly.

### ex02: Operator Overloading
* **Concept Learned:** Overloading arithmetic, comparison, and increment/decrement operators.
* **How it works:** Overloads:
  * Comparison: `<` , `>`, `<=`, `>=`, `==`, `!=`.
  * Arithmetic: `+`, `-`, `*`, `/`.
  * Increment/Decrement: Pre-increment (`++obj`), Post-increment (`obj++` - returns a copy of the old state, then increments).
  * Static min/max functions to find the smallest or largest of two fixed-point references.

---

## Next Steps

Let's look at inheritance and runtime polymorphism in **Modules 03 and 04**.

👉 Proceed to [02_Modules_03_to_04_Inheritance_and_Polymorphism.md](./02_Modules_03_to_04_Inheritance_and_Polymorphism.md)

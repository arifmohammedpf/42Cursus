# C++ Module 06 — Type Casting & Identifications

This document explains the four C++ casting operators (`static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast`), pointer serialization, and dynamic type identification covered in C++ Module 06.

---

## 1. The 4 C++ Casts

C++ replaces C-style casts (e.g. `(int)f`) with four explicit casting operators. This increases readability and prevents accidental type conversions.

| Cast Type | Syntax | What It Is For | Why & How It Works |
| :--- | :--- | :--- | :--- |
| **`static_cast`** | `static_cast<Type>(val)` | Implicit conversions and downcasts. | Checked at compile-time. Used for standard conversions (like float to int, or base to derived pointer conversions). |
| **`dynamic_cast`** | `dynamic_cast<Type>(val)` | Safe downcasting in inheritance hierarchies. | Checked at **runtime**. Requires the base class to have at least one virtual function (polymorphic class). If the cast fails, it returns `NULL` (for pointers) or throws `std::bad_cast` (for references). |
| **`const_cast`** | `const_cast<Type>(val)` | Adding or removing `const` / `volatile` qualifiers. | Checked at compile-time. Allows modifying a const pointer target (use with caution). |
| **`reinterpret_cast`**| `reinterpret_cast<Type>(val)`| Low-level bit reinterpretation. | Reinterprets the raw bits of a pointer as another type or integer. Unchecked and highly platform-dependent. |

---

## 2. Walkthrough of Module 06 Exercises

### ex00: Scalar Converter
* **Concept Learned:** Scalar types parsing and `static_cast` conversions.
* **Why it is needed:** Converts values between standard types safely.
* **How it works:**
  * Parses a string representation of a scalar value (e.g. `'a'`, `42`, `42.0f`, `42.0`, `nan`, `+inf`).
  * Identifies the primary type.
  * Uses `static_cast` to convert the primary value into char, int, float, and double.
  * Formats the outputs, handling overflow limits and printing `"impossible"` or `"Non displayable"` where appropriate.

### ex01: Serialization
* **Concept Learned:** Low-level pointer serialization using `reinterpret_cast`.
* **Why it is needed:** Used to store pointer addresses in databases, send pointer data across network sockets, or interface with low-level systems.
* **How it works:**
  * **`serialize`**: Converts a pointer to a struct (`Data*`) into an unsigned integer type (`uintptr_t`) using `reinterpret_cast<uintptr_t>(ptr)`.
  * **`deserialize`**: Converts the integer back into a pointer using `reinterpret_cast<Data*>(raw_int)`.
  * Verifies that the deserialized pointer matches the original address.

### ex02: Identify Real Type
* **Concept Learned:** Run-Time Type Information (RTTI) and `dynamic_cast`.
* **Why it is needed:** Identifies which derived object type is pointed to by a base class pointer at runtime.
* **How it works:**
  * Creates an empty base class `Base` with a virtual destructor. Classes `A`, `B`, and `C` inherit from `Base`.
  * Implements two identification functions:
    1. **`identify(Base *p)` (Using Pointers):**
       * Tries to dynamic_cast the pointer to derived types: `dynamic_cast<A*>(p)`.
       * If successful (non-null), prints the type name (e.g. `"A"`).
       * If it fails (returns `NULL`), moves to the next type check.
    2. **`identify(Base &p)` (Using References):**
       * Tries to dynamic_cast the reference: `dynamic_cast<A&>(p)`.
       * *Crucial Difference:* A reference cannot be null. If the cast fails, `dynamic_cast` throws a `std::bad_cast` exception.
       * The function catches the exception inside a `try-catch` block and moves to the next check:
         ```cpp
         try {
             A &a = dynamic_cast<A&>(p);
             std::cout << "A" << std::endl;
         }
         catch (const std::exception &e) {} // Silent catch
         ```

---

## Next Steps

Let's look at C++ Templates, STL containers, and algorithms in **Modules 07 to 09**.

👉 Proceed to [05_Modules_07_to_09_Templates_STL_and_Algorithms.md](./05_Modules_07_to_09_Templates_STL_and_Algorithms.md)

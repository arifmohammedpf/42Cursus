# Chapter 3 — Evaluation Q&A Defense Cheat Sheet

This document compiles the most common questions asked by evaluators during the defense of C++ Module 02. Use it to verify your understanding and explain the core mechanics of the codebase confidently.

---

### Q1: What is a fixed-point number and why would we use it instead of a float?
* **Answer:** A fixed-point number represents real numbers using integer types by fixing the decimal point at a specific bit position. We use it for:
  1. **Determinism:** Floating-point math can result in different rounding behavior depending on the CPU architecture, compiler, or optimization flags. Fixed-point math uses integer registers, which are fully deterministic. This is critical for multiplayer games, simulation models, and financial systems.
  2. **Performance:** In systems without a hardware Floating-Point Unit (FPU), such as old CPUs or microcontrollers, floating-point math must be emulated in software, which is extremely slow. Integer operations (add, subtract, bit shifts) run in a fraction of the clock cycles.

---

### Q2: Why is the fractional bit count `_bits` static and const?
* **Answer:**
  * **`static`:** The scale of the fixed point (8 bits) is a class-wide rule. All instances of `Fixed` must use the exact same fractional bit offset for mathematical operations to make sense. Making it static ensures it is stored once in the class definition, rather than taking up memory inside each individual instance.
  * **`const`:** The scaling factor is fixed at compile-time and must never change at runtime. Making it `const` also allows the compiler to replace calculations involving `_bits` with direct constant shift instructions (e.g. `<< 8`), optimizing execution.

---

### Q3: What is the size of a `Fixed` object in memory? Why does it not have virtual functions?
* **Answer:** The size of a `Fixed` object is exactly **4 bytes** (the size of a single 32-bit integer, `_fixed`).
  * It does not contain virtual functions. If we added `virtual` to the destructor or any member function, the compiler would generate a Virtual Method Table (vtable) and insert a virtual pointer (`vptr`) into every object instance.
  * A `vptr` is 8 bytes on a 64-bit system. Double/triple-padding a lightweight utility class like `Fixed` from 4 bytes to 12 or 16 bytes would destroy cache alignment and performance, defeating the purpose of using fixed-point representation.

---

### Q4: Explain the difference between `Fixed a = b;` and `a = b;`? Which constructor/operator is called?
* **Answer:**
  * `Fixed a = b;` is **initialization**. It creates a new object `a` using the **Copy Constructor** (`Fixed(const Fixed &)`).
  * `a = b;` is **assignment**. Both objects `a` and `b` already exist. This calls the **Copy Assignment Operator** (`operator=`).

---

### Q5: Why does the copy assignment operator check `this != &rhs`? What would happen if we omitted it?
* **Answer:**
  * This is a self-assignment guard. It checks if an object is being assigned to itself (e.g. `a = a`).
  * If omitted in a simple class like `Fixed` (which only holds a primitive `int`), nothing catastrophic happens. However, in classes that manage dynamic memory (heap allocations), assigning an object to itself would cause it to delete its own buffer before copying from it, leading to a segmentation fault or memory corruption. Writing it here is a strict requirement of the Orthodox Canonical Form.

---

### Q6: Walk through step-by-step what happens when we execute:
`Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );`
* **Answer:**
  1. **Float Constructor for `Fixed( 5.05f )`**:
     * $5.05 \times 256 = 1292.8$.
     * `roundf(1292.8)` rounds it to `1293`.
     * A temporary `Fixed` object is created with `_fixed = 1293`.
  2. **Int Constructor for `Fixed( 2 )`**:
     * Shifting `2` left by 8 bits gives `512`.
     * A temporary `Fixed` object is created with `_fixed = 512`.
  3. **Arithmetic Operator `operator*`**:
     * Calls `toFloat()` on both:
       * Left: $\frac{1293.0}{256.0} = 5.05078125\text{f}$.
       * Right: $\frac{512.0}{256.0} = 2.0\text{f}$.
     * Multiplies the floats: $5.05078125 \times 2.0 = 10.1015625\text{f}$.
     * The operator returns `Fixed`. The compiler implicitly calls the float constructor using the product `10.1015625f`:
       * $10.1015625 \times 256 = 2586$.
       * Constructs a temporary `Fixed` object with `_fixed = 2586`.
  4. **Initialization of `b`**:
     * The Copy Constructor is called to copy the temporary object into `b`.
     * `b._fixed` becomes `2586`.
  5. **Clean-up**:
     * The destructors for all temporary intermediate objects are called at the end of the statement.

---

### Q7: Why does the post-increment operator `operator++(int)` return by value, while the pre-increment `operator++()` returns by reference?
* **Answer:**
  * **Pre-increment (`++a`)** changes the state of the object immediately and returns the object itself. Returning a reference (`Fixed&`) allows you to continue chaining operations (e.g. `++++a`) directly on the same memory block.
  * **Post-increment (`a++`)** must return the value of the object *before* the increment.
    * It copies the current object state to a temporary stack variable `tmp`.
    * It increments the actual object's value.
    * It returns `tmp`.
    * Because `tmp` is a local stack variable, it will be destroyed when the function returns. Returning it by reference would create a dangling reference, causing undefined behavior. Thus, it **must** be returned by value, which creates a copy.

---

### Q8: What does the `int` argument mean in `operator++(int)`? Does it have a name?
* **Answer:** It is a **dummy parameter** used solely as a signature differentiator at compile-time. It does not have a variable name because it is never used in the function body. The C++ compiler automatically passes `0` to this argument when it sees the post-increment syntax `obj++`. This is the only way C++ can distinguish `++obj` from `obj++` since they share the same function name.

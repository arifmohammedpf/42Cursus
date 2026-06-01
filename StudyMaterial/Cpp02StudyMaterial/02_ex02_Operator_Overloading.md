# Chapter 2 — Operator Overloading (ex02)

This chapter focuses on **ex02**, which introduces operator overloading in C++. Overloading operators allows our `Fixed` class to be treated like built-in primitive types (such as `int` or `float`) when performing calculations and comparisons.

---

## 1. Comparison Operators

The comparison operators check relationships between two `Fixed` numbers. They are defined as `const` member functions and return `bool`.

```cpp
bool Fixed::operator>(const Fixed &rhs) const
{
    return (this->_fixed > rhs.getRawBits());
}
```
* **Why we compare raw bits:** Since both operands are represented as fixed-point numbers with the same fractional bit scale (8 bits), we do not need to convert them to float or int first. Comparing the raw integer registers directly (`this->_fixed > rhs.getRawBits()`) is highly optimized ($O(1)$) and avoids floating-point round-off inaccuracies.
* **Overloaded list:** `operator>`, `operator<`, `operator>=`, `operator<=`, `operator==`, `operator!=`.

---

## 2. Arithmetic Operators

The arithmetic operators perform calculations between two `Fixed` numbers and return a brand-new `Fixed` object by value.

### How it works: [ex02/Fixed.cpp](file:///c:/42AD/staff-evaluation/cpp-modules/cpp02/ex02/Fixed.cpp#L90-L108)

Let's dissect the addition operator:
```cpp
Fixed Fixed::operator+(const Fixed &rhs) const
{
    return (this->toFloat() + rhs.toFloat());
}
```

1. **Extraction:** `this->toFloat()` converts the left operand to a `float`.
2. **Extraction:** `rhs.toFloat()` converts the right operand to a `float`.
3. **Float Addition:** They are added together: `lhs_float + rhs_float` (returning a temporary `float`).
4. **Implicit Conversion:** The return type of the function is `Fixed`. Because we have a single-argument float constructor `Fixed(const float num)`, the compiler implicitly converts the float sum back into a `Fixed` object.
5. **Return by Value:** The new `Fixed` object is returned by value (creating a temporary copy).

### ⚠️ Performance Tradeoff: Float vs. Integer Fixed-Point Math

* **The Codebase Approach:** The implementation uses floats to do arithmetic. This is simple and prevents integer overflows during multiplication.
* **The Pure Fixed-Point Approach:** In high-performance systems, we perform arithmetic directly on the raw integer bits:
  * **Addition/Subtraction:** `this->_fixed + rhs._fixed` (no scaling needed).
  * **Multiplication:** `(this->_fixed * rhs._fixed) >> 8` (requires scaling down by 256).
  * **Division:** `(this->_fixed << 8) / rhs._fixed` (requires scaling up by 256 before division).
* *Defense Note:* Be ready to explain that converting to float for arithmetic simplifies calculations but incurs the performance cost of converting from integer to float and back again.

---

## 3. Increment and Decrement Operators

The increment and decrement operators increase or decrease the value. They are divided into **Pre-operators** (`++a`) and **Post-operators** (`a++`).

### A. Pre-Increment (`++a`)
```cpp
Fixed & Fixed::operator++()
{
    this->_fixed = this->_fixed + 1;
    return (*this);
}
```
* **How it works:** Increments the internal raw value by `1` and returns a reference to the updated object (`*this`).
* **Why it returns by reference:** To allow chaining of pre-increments: `++++a` first increments `a`, then increments it again, operating on the same memory address.
* **What `+ 1` means mathematically:** Since our number is scaled by 256, adding `1` to the raw bits increases the actual value by $\frac{1}{256} = 0.00390625$ (the smallest possible fractional increment, or $\epsilon$). It does **not** add `1.0`!

### B. Post-Increment (`a++`)
```cpp
Fixed Fixed::operator++(int)
{
    Fixed tmp(*this);
    this->operator++();
    return (tmp);
}
```
* **The Dummy Parameter (`int`):** The `int` parameter in the argument list is a C++ convention. It has no variable name and is not used in the function body; it is only a marker that tells the compiler this is the **post-increment** operator. The compiler automatically passes a dummy argument `0` when `a++` is invoked.
* **How it works step-by-step:**
  1. **Copy:** Save the current state of the object in a temporary copy: `Fixed tmp(*this)`.
  2. **Increment:** Call the pre-increment operator to modify the current object's value: `this->operator++()`.
  3. **Return Copy:** Return the saved, unmodified temporary object `tmp` by value.
* **Why it returns by value:** `tmp` is a local variable stored on the stack. Returning a reference to `tmp` would result in a **dangling reference** (accessing memory that has been deallocated), leading to undefined behavior.

---

## 4. Static Min and Max Functions

The utility functions `min` and `max` compare two objects and return a reference to the smaller or larger one.

### Member Declaration:
```cpp
static Fixed        &min(Fixed &a, Fixed &b);
static Fixed        &max(Fixed &a, Fixed &b);
static const Fixed  &min(const Fixed &a, const Fixed &b);
static const Fixed  &max(const Fixed &a, const Fixed &b);
```

* **Why they are static:** They are helper utility functions that do not belong to a specific instance. They are invoked using the class name: `Fixed::max(a, b)`.
* **Why they are overloaded for `const`:**
  * If we pass `const Fixed` objects (like read-only inputs in a function), the compiler must call the `const` overloaded version.
  * The mutable overloads `Fixed &min(Fixed &a, Fixed &b)` allow the returned reference to be modified after lookup.
  * *Example:*
    ```cpp
    Fixed a(5), b(10);
    Fixed::max(a, b) = 42; // Returns a mutable reference to 'b', so 'b' becomes 42!
    ```

---

## Next Steps

Let's prepare for defense questions and answers on the concepts tested in C++ Module 02.

👉 Proceed to [03_Evaluation_Q_and_A.md](./03_Evaluation_Q_and_A.md)

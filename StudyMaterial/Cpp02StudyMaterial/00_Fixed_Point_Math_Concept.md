# C++ Module 02 — Fixed-Point Math Concepts

This document explains the mathematical foundations behind **fixed-point numbers**, detailing how fractional values are represented using integer registers and how conversions between integers, floats, and fixed-point numbers work.

---

## 1. What is a Fixed-Point Number?

A **fixed-point number** is a data structure used to represent real numbers (including fractions) using a standard integer storage type (like a 32-bit `int`). 

Unlike floating-point numbers (`float` or `double`), where the position of the decimal point can float (tracked dynamically using an exponent field), a fixed-point number has its decimal point **fixed** at a specific position. The integer bits are divided into a whole number part (integer part) and a fractional part.

```
       32-Bit Integer Layout as a Fixed-Point Number (with 8 Fractional Bits)
       
 ┌───────────────────────────────────────────┬────────────────────────┐
 │       24 Bits: Integer Part               │  8 Bits: Fractional    │
 └───────────────────────────────────────────┴────────────────────────┘
  31                                        8 7                      0
                                             ▲
                                      (Fixed Decimal)
```

---

## 2. Why Use Fixed-Point Math?

1. **Precision & Determinism:** Floating-point numbers can suffer from rounding errors that differ between processors or compilers. Fixed-point math is integer-based and fully deterministic, which is critical in physics engines, financial software, and games.
2. **Performance (No FPU):** Historical computers (and modern microcontrollers/embedded systems) do not have a dedicated Floating-Point Unit (FPU) to calculate float math. Integer operations (add, subtract, bit shifts) are significantly faster than software-emulated floating-point arithmetic.

---

## 3. The Math Behind Conversions

In C++ Module 02, the fractional part is fixed to **`8` bits**. This means $2^8 = 256$ is our scaling factor. 

### A. Converting an Integer to Fixed-Point
To convert a standard integer to fixed-point, we must shift the decimal point 8 positions to the left, which is equivalent to multiplying the integer by 256.
* **Math Formula:**
  $$\text{fixed} = \text{integer} \times 2^8$$
* **C++ Code:**
  ```cpp
  this->_fixed = num << 8; // (num << _bits)
  ```
  *Example:* Converting the integer `5`:
  `5` is `00000101` in binary. Shifting left by 8 bits yields `00000101 00000000` (binary for `1280`).

### B. Converting a Float to Fixed-Point
Since floats contain fractional values (e.g. `5.25`), we cannot use bitwise shifts directly. Instead, we multiply the float by the scaling factor `256` and round the result to the nearest integer to preserve precision.
* **Math Formula:**
  $$\text{fixed} = \text{round}(\text{float} \times 2^8)$$
* **C++ Code:**
  ```cpp
  this->_fixed = roundf(num * (1 << 8)); // roundf(num * 256)
  ```
  *Example:* Converting the float `5.25`:
  $$5.25 \times 256 = 1344.0 \quad \rightarrow \quad \text{roundf}(1344.0) = 1344$$
  The binary representation of `1344` is `00000101 01000000` (which is `5` in the upper 8 bits and `0.25` ($\frac{64}{256}$) in the lower 8 bits).

### C. Converting Fixed-Point back to Integer
To convert fixed-point back to a standard integer, we discard the fractional part by shifting the bits 8 positions to the right, which is equivalent to dividing by 256.
* **Math Formula:**
  $$\text{integer} = \text{fixed} / 2^8$$
* **C++ Code:**
  ```cpp
  return (this->_fixed >> 8);
  ```
  *Example:* Converting `1344` back to integer:
  $$1344 \gg 8 = 5$$

### D. Converting Fixed-Point back to Float
To convert fixed-point back to a float, we cast the raw bits to float and divide by the scaling factor `256.0` to restore the fractional value.
* **Math Formula:**
  $$\text{float} = \frac{\text{fixed}}{2^8}$$
* **C++ Code:**
  ```cpp
  return ((float)this->_fixed / (1 << 8)); // fixed / 256.0
  ```
  *Example:* Converting `1344` back to float:
  $$\frac{1344.0}{256.0} = 5.25$$

---

## Next Steps

Let's look at the implementation of **ex00 and ex01: Class Canonical Forms & Conversions**.

👉 Proceed to [01_ex00_and_ex01_Canonical_Form_and_Conversions.md](./01_ex00_and_ex01_Canonical_Form_and_Conversions.md)

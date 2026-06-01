# Chapter 1 — Canonical Form and Conversions (ex00 & ex01)

This chapter explains the transition of the `Fixed` class from a basic container for raw bits in **ex00** to a fully functional fixed-point representation with integer and float conversions in **ex01**.

---

## 1. The Orthodox Canonical Class Form (ex00)

C++ requires classes that manage resources or represent values to follow the **Orthodox Canonical Class Form** (often referred to as the Coplien Form). This ensures objects behave predictably when copied, assigned, or destroyed.

As seen in [ex00/Fixed.hpp](file:///c:/42AD/staff-evaluation/cpp-modules/cpp02/ex00/Fixed.hpp), a canonical class must implement four essential functions:
1. **Default Constructor:** Initializes an empty or zero-value object.
2. **Copy Constructor:** Initializes a new object as a copy of an existing object.
3. **Copy Assignment Operator (`operator=`):** Copies values from one existing object to another existing object.
4. **Destructor:** Cleans up when an object goes out of scope.

### Code Walkthrough: [ex00/Fixed.cpp](file:///c:/42AD/staff-evaluation/cpp-modules/cpp02/ex00/Fixed.cpp)

```cpp
// 1. Default Constructor
Fixed::Fixed(): _fixed(0)
{
    std::cout << "Default Constructor called" << std::endl;
}
```
* **What it is for:** Initializes the private raw value `_fixed` to `0`.
* **Why it is needed:** Without this, `_fixed` would hold garbage memory values, violating safety.

```cpp
// 2. Copy Constructor
Fixed::Fixed(const Fixed &object)
{
    std::cout << "Copy Constructor called" << std::endl;
    *this = object; // delegates work to the assignment operator
}
```
* **What it is for:** Creates a new instance by copying another instance.
* **Why it is needed:** Used when passing objects by value or initializing objects like `Fixed b(a)`.
* **How it works:** It delegates the copy logic to the copy assignment operator (`*this = object`), ensuring code reuse.

```cpp
// 3. Copy Assignment Operator
Fixed & Fixed::operator=(Fixed const &rhs)
{
    std::cout << "Copy Assignment Operator called" << std::endl;
    if (this != &rhs) // guard against self-assignment
        this->_fixed = rhs.getRawBits();
    return (*this); // returns a reference to allow chained assignments (a = b = c)
}
```
* **What it is for:** Overloads the `=` operator to handle value copies between two already existing objects.
* **How it works:**
  1. Checks if `this != &rhs` (verifying we aren't assigning an object to itself, e.g. `a = a`).
  2. Copies the raw bits of `rhs` to `this->_fixed`.
  3. Returns `*this` (dereferenced pointer) so operations can be chained.

```cpp
// 4. Destructor
Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}
```
* **What it is for:** Performs clean-up operations before the object is destroyed.

---

## 2. Raw Bits Getter and Setter

The class hides its inner representation (`_fixed`) but exposes two functions to view and modify it:

### [getRawBits](file:///c:/42AD/staff-evaluation/cpp-modules/cpp02/ex00/Fixed.cpp#L34-L38)
* **What it is for:** Returns the internal integer representation of the fixed-point number.
* **Why it is const:** Declaring it `const` ensures it can be called on const objects (e.g. `const Fixed b(10)`).

### [setRawBits](file:///c:/42AD/staff-evaluation/cpp-modules/cpp02/ex00/Fixed.cpp#L28-L32)
* **What it is for:** Manually sets the value of the raw bits without performing any scaling.

---

## 3. Conversions: Int and Float Constructors (ex01)

In **ex01**, the class is updated to accept standard `int` and `float` variables, converting them into our fixed-point scheme.

```cpp
private:
    int                 _fixed;
    static const int    _bits = 8; // scaling factor bits (2^8 = 256)
```

### A. The Integer Constructor
```cpp
Fixed::Fixed(int const num)
{
    std::cout << "Int Constructor called" << std::endl;
    this->setRawBits(num << this->_bits);
}
```
* **How it works:**
  * Shifting the integer left by 8 bits (`num << 8`) is mathematically equivalent to multiplying `num` by $2^8 = 256$.
  * This shifts the whole number into the integer part (bits 8–31) and leaves the fractional part (bits 0–7) as `0`.
  * *Example:* `10` in binary is `00001010`. Shifting left by 8 gives `00001010 00000000` (which is `2560`).

### B. The Float Constructor
```cpp
Fixed::Fixed(float const num)
{
    std::cout << "Float Constructor called" << std::endl;
    this->setRawBits(roundf(num * (1 << this->_bits)));
}
```
* **How it works:**
  * Since floats have fractional components (e.g., `42.42`), we cannot perform direct bitwise shifting.
  * Instead, we multiply the float by the scaling factor `(1 << 8)` which is `256.0f`.
  * We use `roundf()` to round the product to the nearest integer.
  * *Why `roundf` is necessary:* Direct casting to integer truncates the decimal part (rounding towards zero). Rounding ensures maximum precision.
  * *Example:* Converting `42.42f`:
    $$42.42 \times 256 = 10859.52$$
    $$\text{roundf}(10859.52) = 10860$$
    The binary for `10860` is `00101010 01101100`. The upper 8 bits represent `42` (`00101010`), and the lower 8 bits represent `0.42` ($\frac{108}{256} = 0.421875$, which is the closest approximation using 8 bits).

---

## 4. Converting Back: toFloat & toInt

To read the values back in standard forms, we write decoder functions:

### [toInt](file:///c:/42AD/staff-evaluation/cpp-modules/cpp02/ex01/Fixed.cpp#L61-L64)
```cpp
int Fixed::toInt() const
{
    return (this->_fixed >> this->_bits);
}
```
* **How it works:** Shifting right by 8 bits (`_fixed >> 8`) discards the 8 fractional bits, yielding the truncated integer part.
* *Example:* `10860 >> 8 = 42`.

### [toFloat](file:///c:/42AD/staff-evaluation/cpp-modules/cpp02/ex01/Fixed.cpp#L56-L59)
```cpp
float Fixed::toFloat() const
{
    return (roundf(this->_fixed) / (1 << this->_bits));
}
```
* **How it works:** 
  * Converts the raw bits to float and divides by the scaling factor `256.0f` to shift the decimal point 8 positions back to the right.
  * *Note on code style:* The expression uses `roundf(this->_fixed)`. While calling `roundf` on an integer is mathematically redundant (as integers have no fractional part), the cast/rounding ensures the value becomes a `float` before dividing by `(1 << 8)`, avoiding integer division.
  * *Example:*
    $$\frac{10860.0\text{f}}{256.0\text{f}} = 42.421875\text{f}$$

---

## 5. Stream Insertion Operator Overload

To print our `Fixed` objects directly using `std::cout << obj;`, we overload the `<<` operator.

### [operator<< Declaration](file:///c:/42AD/staff-evaluation/cpp-modules/cpp02/ex01/Fixed.hpp#L26) & [Implementation](file:///c:/42AD/staff-evaluation/cpp-modules/cpp02/ex01/Fixed.cpp#L50-L54)
```cpp
std::ostream & operator<<(std::ostream &out, Fixed const &rhs)
{
    out << rhs.toFloat();
    return (out);
}
```
* **Why it is a non-member function:** The left operand of `std::cout << a` is `std::ostream`, not `Fixed`. Member operator overloads require the left operand to be an instance of that class.
* **Why it returns `std::ostream&`:** Returning the output stream by reference allows chaining multiple outputs:
  ```cpp
  std::cout << "a is " << a << " and b is " << b << std::endl;
  ```

---

## Next Steps

Let's look at how we overload arithmetic, comparison, and increment/decrement operators.

👉 Proceed to [02_ex02_Operator_Overloading.md](./02_ex02_Operator_Overloading.md)

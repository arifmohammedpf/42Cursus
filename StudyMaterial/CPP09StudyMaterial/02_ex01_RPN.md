# CPP09 ex01 — RPN Calculator

This document details the implementation of **ex01 (Reverse Polish Notation)**, explaining the header [RPN.hpp](file:///c:/42AD/staff-evaluation/cpp09/ex01/RPN.hpp), source file [RPN.cpp](file:///c:/42AD/staff-evaluation/cpp09/ex01/RPN.cpp), and [main.cpp](file:///c:/42AD/staff-evaluation/cpp09/ex01/main.cpp).

---

## 1. RPN Concepts

**Reverse Polish Notation (RPN)**, or postfix notation, is a mathematical notation in which operators follow their operands.
* **Infix (Standard):** `(3 + 4) * 2`
* **Postfix (RPN):** `3 4 + 2 *`

### Advantages of RPN
* No parentheses are required to define operator precedence.
* The expression is parsed sequentially from left to right.
* Highly efficient to evaluate programmatically using a **Stack** data structure.

---

## 2. Class Design (`ex01/RPN.hpp`)

```cpp
class RPN
{
    private:
        std::stack<int> _stack;
```
* **What it is for:** Accumulates operands during evaluation.
* **Why it is needed:** Implements LIFO (Last-In, First-Out) operations. 
* **How it works:** Numbers are pushed onto the stack. When an operator is parsed, the top two numbers are popped, the operation is applied, and the result is pushed back.

---

## 3. Evaluation Engine (`ex01/RPN.cpp`)

### [calculate](file:///c:/42AD/staff-evaluation/cpp09/ex01/RPN.cpp#L69-L97)
* **What it is for:** Parses the expression string and orchestrates evaluation.
* **Why it is needed:** Validates tokens and calculates the final result.
* **How it works:**
  1. Wraps the input string inside `std::stringstream` to split tokens by space.
  2. Iterates through tokens:
     * If the token is an operator (`+`, `-`, `*`, `/`), calls `doOperation`.
     * If the token is a single digit (`isdigit`), converts it to an integer using `atoi` and pushes it to the stack.
     * Any other token (like alphabets or multi-digit numbers if forbidden by the subject constraints) throws a `runtime_error`.
  3. After reading all tokens, verifies that `_stack.size() == 1`. If the size is different (e.g. too many numbers and not enough operators), throws an error.
  4. Prints the final result at `_stack.top()`.

```
Parsing Expression: "3 4 + 2 *"
  Token: "3" ──► Push to Stack ──────► Stack: [3]
  Token: "4" ──► Push to Stack ──────► Stack: [3, 4]
  Token: "+" ──► Pop 4 (b), Pop 3 (a)
                 Result: 3 + 4 = 7
                 Push 7 to Stack ────► Stack: [7]
  Token: "2" ──► Push to Stack ──────► Stack: [7, 2]
  Token: "*" ──► Pop 2 (b), Pop 7 (a)
                 Result: 7 * 2 = 14
                 Push 14 to Stack ───► Stack: [14]
  End of String. Stack size is 1. Outputs 14.
```

### [doOperation](file:///c:/42AD/staff-evaluation/cpp09/ex01/RPN.cpp#L37-L67)
* **What it is for:** Executes an arithmetic operation.
* **Why it is needed:** Applies operator logic.
* **How it works:**
  1. Asserts stack size is at least 2. If fewer, throws an error (indicates missing operand).
  2. Pops the top element as `b` (the second operand).
  3. Pops the next top element as `a` (the first operand).
  * *Important order detail:* Postfix subtraction/division order is `a - b` and `a / b` (reversing operands relative to pop order).
  4. Evaluates the operator:
     * **`+`**: `a + b`
     * **`-`**: `a - b`
     * **`*`**: `a * b`
     * **`/`**: Checks if `b == 0`. If so, throws a division-by-zero error. Otherwise evaluates `a / b`.
  5. Pushes the result back onto the stack.

---

## 4. Main Program (`ex01/main.cpp`)

```cpp
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    try
    {
        RPN rpn(argv[1]);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    return (0);
}
```
* Binds command line inputs and uses a try/catch block to output clean `"Error"` messages if invalid tokens or division-by-zero occur.

---

## Next Steps

Let's look at the implementation of **ex02: PmergeMe**.

👉 Proceed to [03_ex02_PmergeMe.md](./03_ex02_PmergeMe.md)

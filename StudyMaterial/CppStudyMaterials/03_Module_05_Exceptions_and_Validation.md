# C++ Module 05 — Exception Handling & Factories

This document explains the exception handling structures, custom exception classes, exception safety, and the factory pattern covered in C++ Module 05.

---

## 1. Exception Handling Concepts

C++ provides a type-safe mechanism to handle errors, separating the code that detects errors from the code that processes them.

* **`throw`**: Signals that an error has occurred, halting execution of the current scope and searching for a handler.
* **`try`**: Encapsulates a block of code that might throw an exception.
* **`catch`**: Intercepts and processes the thrown exception object.

```cpp
try {
    if (grade < 1)
        throw Bureaucrat::GradeTooHighException();
}
catch (const std::exception &e) {
    std::cerr << "Exception caught: " << e.what() << std::endl;
}
```

---

## 2. Walkthrough of Module 05 Exercises

### ex00: The Bureaucrat & Custom Exceptions
* **Concept Learned:** Exception handling and custom exception classes.
* **Why it is needed:** Replaces error return codes (like `-1` or `NULL`) which can be easily ignored, forcing the caller to handle the error.
* **How it works:**
  * Defines a `Bureaucrat` class with a grade ranging from `1` (highest) to `150` (lowest).
  * If a transaction attempts to set a grade outside this range (e.g. `151`), it throws an exception.
  * **Implementing Custom Exceptions:**
    * In C++, custom exceptions should inherit from `std::exception`:
      ```cpp
      class GradeTooHighException : public std::exception {
      public:
          virtual const char* what() const throw() {
              return "Grade is too high!";
          }
      };
      ```
    * **`throw()` Specifier:** The `throw()` specifier is an exception specification. It tells the compiler: "this function is guaranteed not to throw any exceptions." (In C++11, this is replaced by `noexcept`).

### ex01 & ex02: Forms and Concrete Implementations
* **Concept Learned:** Linking classes and catching exceptions inside operations.
* **Why it is needed:** Demonstrates how errors propagate up the call stack to be caught by the appropriate handler.
* **How it works:**
  * Creates an abstract `AForm` class that requires a minimum grade to sign and execute.
  * If a Bureaucrat's grade is too low to sign the form, it throws a `GradeTooLowException`.
  * Implements derived concrete forms:
    * **`ShrubberyCreationForm`**: Writes an ASCII tree diagram to a target file.
    * **`RobotomyRequestForm`**: Simulates drilling noises and checks for a 50% success probability using the random number generator `rand()`.
    * **`PresidentialPardonForm`**: Outputs a formal pardon statement.

### ex03: The Intern (Factory Pattern)
* **Concept Learned:** The Factory Method Pattern.
* **Why it is needed:** Decouples form creation logic from the calling function. The caller can request a form by passing a string name, without knowing the specific concrete class constructor.
* **How it works:**
  * Implements an `Intern` class.
  * The method `makeForm(std::string formName, std::string target)` searches for a match of the form name string and instantiates the correct concrete form on the heap.
  * Utilizes pointers to member functions or clean routing mappings to avoid large `if-else` blocks.

---

## Next Steps

Let's look at type conversions and castings in **Module 06**.

👉 Proceed to [04_Module_06_Type_Casting.md](./04_Module_06_Type_Casting.md)

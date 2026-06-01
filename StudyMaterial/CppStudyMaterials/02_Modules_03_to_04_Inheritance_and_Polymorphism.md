# C++ Modules 03 & 04 — Inheritance & Polymorphism

This document explains the concepts of class inheritance, constructors execution order, virtual tables, subtype polymorphism, deep copies, abstract classes, and interfaces covered in C++ Modules 03 and 04.

---

## 1. C++ Module 03: Inheritance & Child Classes

Module 03 teaches you how to create child classes that inherit data and behaviors from a parent class, and how constructors/destructors behave in inheritance hierarchies.

### ex00 & ex01: ClapTrap & ScavTrap (Inheritance)
* **Concept Learned:** Class inheritance and constructors execution order.
* **Why it is needed:** Avoids repeating duplicate code across classes. A child class automatically gets the attributes (like hit points) and methods (like take damage) of the parent.
* **How it works:**
  * `ScavTrap` inherits from `ClapTrap`: `class ScavTrap : public ClapTrap`.
  * **Constructor Order:** When `ScavTrap` is instantiated, the **Base constructor (ClapTrap) runs first**, followed by the **Derived constructor (ScavTrap)**.
  * **Destructor Order:** When destroyed, the **Derived destructor runs first**, followed by the **Base destructor**.
  * **Protected Access:** Changing ClapTrap attributes from `private` to `protected` allows derived classes (like ScavTrap) to access them directly while still blocking external access.

### ex02: FragTrap
* **Concept Learned:** Code reuse.
* **How it works:** Extends ClapTrap, overriding parameters and adding specific behaviors (like `highFivesGuys`).

---

## 2. C++ Module 04: Polymorphism & Interfaces

Module 04 covers **subtype polymorphism**, abstract classes, and virtual tables (Vtables).

### ex00: Subtype Polymorphism (Animal, Dog, Cat)
* **Concept Learned:** Subtype polymorphism and virtual functions.
* **Why it is needed:** Allows a base pointer to call the correct derived class method at runtime.
* **How it works:**
  * Defines a base class `Animal` with a virtual function: `virtual void makeSound() const;`.
  * `Dog` and `Cat` inherit from `Animal` and override `makeSound`.
  * **The Virtual Table (Vtable):** If a base class has at least one virtual function, the compiler creates a Vtable for that class. Every object instance contains a hidden pointer (the `vptr`) pointing to this table. At runtime, when a virtual function is called through a base pointer (`Animal *a = new Dog()`), the program looks up the correct derived method (`Dog::makeSound`) in the Vtable.
  * **The "Slice Effect" Warning:** If `virtual` is omitted from `makeSound` in `Animal`, compile-time binding occurs. Calling `makeSound` through an `Animal *a` pointer pointing to a `Dog` object will execute `Animal::makeSound`, ignoring the derived class override.
  * **Virtual Destructors:** If a class has virtual functions, its destructor **must be virtual** (`virtual ~Animal()`). Otherwise, deleting a derived object through a base pointer (`delete a;`) will only invoke the base destructor, leaking any heap memory allocated by the derived class.

### ex01: Deep Copies & Brains
* **Concept Learned:** Deep copy implementation.
* **Why it is needed:** Verifies that copy operations duplicate data rather than just pointer addresses.
* **How it works:**
  * `Dog` and `Cat` classes contain a pointer to a `Brain` object allocated on the heap (`new Brain()`).
  * The copy constructor and assignment operator of `Dog`/`Cat` are overridden to allocate a new `Brain` and copy the ideas array, rather than performing a shallow copy of the pointer address.

### ex02: Abstract Classes
* **Concept Learned:** Pure virtual functions.
* **Why it is needed:** Prevents instantiating generic base classes. (e.g. you should be able to instantiate a `Dog` or `Cat`, but not a generic `Animal` object).
* **How it works:** Sets a virtual function to `0` to make it a **pure virtual function**:
  ```cpp
  virtual void makeSound() const = 0;
  ```
  This makes `Animal` an **Abstract Class**. Any attempt to instantiate it directly (`Animal a;`) will fail with a compile error. Derived classes must override this pure virtual function to be instantiable.

### ex03: Interfaces (Materia, Characters)
* **Concept Learned:** Interfaces.
* **Why it is needed:** Defines a contract of what derived classes must implement, separating interface from implementation.
* **How it works:**
  * C++ does not have an explicit `interface` keyword. Instead, an interface is implemented as a **Pure Abstract Class** that contains only pure virtual functions and no data members.
  * Implements `AMateria`, `ICharacter` (interface for players), and `IMateriaSource` (interface for cloning materias).

---

## Next Steps

Let's study exception handling and runtime safety in **Module 05**.

👉 Proceed to [03_Module_05_Exceptions_and_Validation.md](./03_Module_05_Exceptions_and_Validation.md)

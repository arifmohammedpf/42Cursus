# C++ Module 02 Codebase Study Materials

This directory contains comprehensive study materials for the **C++ Module 02** codebase. These resources are designed to help you understand fixed-point arithmetic representation, the Orthodox Canonical Class Form, and operator overloading, enabling you to explain the codebase clearly during your defense.

---

## 📖 Chapter Index

| Chapter | File | Description | Key Concepts Covered |
|:---:|---|---|---|
| **0** | [00_Fixed_Point_Math_Concept.md](./00_Fixed_Point_Math_Concept.md) | Fixed-point math equations & scaling theory. | Fractional bits scaling ($2^8 = 256$), shift conversions, and float rounding mathematics. |
| **1** | [01_ex00_and_ex01_Canonical_Form_and_Conversions.md](./01_ex00_and_ex01_Canonical_Form_and_Conversions.md) | Canonical class requirements & conversions. | Orthodox Canonical Class Form, getRawBits/setRawBits, integer & float constructor implementations, and `toInt()` / `toFloat()`. |
| **2** | [02_ex02_Operator_Overloading.md](./02_ex02_Operator_Overloading.md) | Overloading comparison, math, and increment operators. | Direct bit comparison, float-math delegation tradeoff, pre- vs. post-increment dummy parameter syntax, and static utility overloads. |
| **3** | [03_Evaluation_Q_and_A.md](./03_Evaluation_Q_and_A.md) | Viva defense cheat sheet for evaluations. | Sizing of `Fixed`, self-assignment guards, trace simulation of expressions, virtual table checks, and return types (reference vs value). |

---

## 🛠️ How to Use These Materials

1. **Start with Chapter 0:** Solidify the math behind fixed-point conversions and binary representations.
2. **Follow Code References:** Files and lines are linked (e.g. [Fixed.cpp](file:///c:/42AD/staff-evaluation/cpp-modules/cpp02/ex00/Fixed.cpp)) to let you jump straight to the source files on your system.
3. **Review the Q&A Cheat Sheet:** Use **Chapter 3** to prepare for typical evaluator questions and test yourself on compiling or running expressions.

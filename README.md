# 📚 Serendipity Booksellers — Point of Sale System

> A fully functional, menu-driven **Point-of-Sale (POS) and Inventory Management System** built in C++ as part of a 16-chapter Object-Oriented Programming curriculum. Each chapter introduces new programming concepts that are progressively integrated into this single, evolving software project — from basic I/O and functions all the way through classes, inheritance, polymorphism, file I/O, and the Standard Template Library.

---

## 🧭 What Is This Project?

Serendipity Booksellers is a small bookstore that needed a software solution to replace its manual processes. This program turns a personal computer into a fully featured **cash register**, **inventory database**, and **reporting engine** — all in one console application.

What makes this project unique is its structure: it isn't built all at once. It is developed **chapter by chapter**, with each iteration replacing, refining, and expanding on what came before. The result is a codebase that reflects real-world software evolution — from a simple menu stub to a fully object-oriented system with file persistence, dynamic memory, exception handling, and class hierarchies.

---

## ✨ Features

- 🧾 **Cashier Module** — multi-title transactions, automatic ISBN lookup, quantity validation, tax calculation, and formatted receipt output
- 📦 **Inventory Module** — full CRUD (Create, Read, Update, Delete) for up to 20 books
- 📊 **Report Module** — six report types with sorting and pagination
- 🔍 **Smart Search** — title and ISBN lookup with partial match support via `bookMatch()`
- 💾 **File Persistence** — inventory stored and retrieved from a binary file
- 🏗️ **OOP Architecture** — class hierarchy with base, derived, and utility classes
- ⚠️ **Exception Handling** — graceful recovery from file failures and memory allocation errors

---

## 🗂️ Project Structure

```
SerendipityBooksellers/
├── src/
│   ├── main.cpp            # Entry point, global definitions
│   ├── mainmenu.cpp        # Main menu logic
│   ├── cashier.cpp         # Cashier & POS module
│   ├── invmenu.cpp         # Inventory menu + CRUD operations
│   ├── bookinfo.cpp        # Overloaded book display functions
│   ├── reports.cpp         # Report module (6 report types)
│   └── serendipity.h       # Shared header — prototypes, classes, includes
├── .gitignore
└── README.md
```

---

## 📖 Curriculum Roadmap

This project is built across 16 chapters. Each chapter adds new C++ concepts directly into the program:

| Chapter | Topic | What Was Built |
|---------|-------|----------------|
| 1 | Intro to Computers | Project spec — defined all 3 modules |
| 2 | Intro to C++ | Menu screens — `mainmenu`, `invmenu`, `bookinfo` stubs |
| 3 | Expressions & Interactivity | Cashier input, tax calculation, sales slip output |
| 4 | Making Decisions | Input validation, `switch` statements in all menus |
| 6 | Functions | Modular `.cpp` files, header files, stub functions |
| 7 | Arrays | Parallel arrays for inventory (`bookTitle`, `isbn`, `author`, etc.) |
| 9 | Pointers | Multi-title cashier, automatic ISBN lookup, pointer-based cart |
| 10 | C-Strings | Replaced `string` arrays with 2D `char` arrays |
| 11 | Structured Data | Replaced parallel arrays with a `BookData` struct + setter functions |
| 12 | File I/O | Replaced struct array with binary file — full file-based inventory |
| 13 | Classes | Converted `BookData` struct to a class with private members + accessors |
| 14 | More Classes | Added `bookMatch()`, refactored search functions, additional class design |
| 15 | Inheritance & Polymorphism | Split into `BookData` (base) → `InventoryBook` → `SoldBook` hierarchy |
| 16 | Exceptions & STL | Exception handlers for file failures and dynamic memory errors |

---

## 🧠 Skills Demonstrated

### Core C++ Concepts
- **Modular Programming** — split across multiple `.cpp` files with a unified shared header
- **Function Overloading** — `bookinfo()` has 5 overloads for flexible book display
- **Parallel Arrays → Structs → Classes** — data architecture evolves across chapters
- **Pointers & Dynamic Memory** — pointer-based cart in cashier, dynamic `SoldBook` arrays
- **2D Arrays & C-Strings** — full transition from `string` objects to `char` arrays
- **File I/O** — binary file read/write for persistent inventory storage
- **Input Validation** — handles bad input, out-of-range values, and string/int mismatches
- **`std::format` & `iomanip`** — formatted receipt and report output
- **Header Guards** — `#ifndef` / `#define` used correctly throughout

### Object-Oriented Design
- **Encapsulation** — private member variables with public getters and setters
- **Inheritance** — `BookData` → `InventoryBook` → `SoldBook` class hierarchy
- **Polymorphism & Virtual Functions** — runtime behavior through derived classes
- **Static Members** — `taxRate` and `total` shared across all `SoldBook` instances
- **Member Functions** — `setTitle`, `setISBN`, `isEmpty`, `removeBook`, `bookMatch`, and more

### Software Engineering
- **Iterative Development** — software grows and refactors with each chapter
- **CRUD Operations** — complete inventory management (add, lookup, edit, delete)
- **Sorting Algorithms** — reports sorted by quantity, cost, and date in descending order
- **Exception Handling** — `try/catch` blocks for file open failures and `new` allocation errors
- **Receipt Generation** — multi-item cart with subtotal, tax, and total calculation

---

## 🚀 Getting Started

### Requirements
- C++20 or later (uses `<format>`)
- `g++`, `clang++`, or Xcode on macOS

### Compile & Run
```bash
g++ -std=c++20 src/main.cpp src/mainmenu.cpp src/cashier.cpp src/invmenu.cpp src/bookinfo.cpp src/reports.cpp -o serendipity
./serendipity
```

---

## 📋 Module Status

| Module | Status |
|--------|--------|
| Main Menu | ✅ Complete |
| Cashier | ✅ Complete |
| Inventory CRUD | ✅ Complete |
| Reports | 🔄 In Progress |
| File Persistence | 🔄 In Progress |
| Class Hierarchy | 🔄 In Progress |
| Exception Handling | ⏳ Upcoming |

---

## 👩‍💻 Author

**Andrea Ongomefen**
Course: CS226 — Object-Oriented Programming
Textbook: *Starting Out with C++* — Tony Gaddis, Pearson Education

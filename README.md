APC-Arbitrary-Precision-Calculator

A C-based Arbitrary Precision Calculator that performs addition, subtraction, multiplication, and division on large integers using doubly linked lists.

📌 Project Overview

APC (Arbitrary Precision Calculator) is a Data Structures based project developed in the C programming language. It is designed to perform arithmetic operations on very large numbers that exceed the size limits of standard data types such as int, long, and long long.

Instead of using built-in numeric types, the calculator stores each digit of the number in a doubly linked list, enabling accurate and efficient computation for large integers.

✨ Features

Supports Addition, Subtraction, Multiplication, and Division

Handles very large integers

Implemented using Doubly Linked Lists

Modular and structured programming

Dynamic Memory Allocation

Command-line based execution

Accurate sign handling (+ / -)

🛠️ Technologies Used

Programming Language: C

Data Structures: Doubly Linked Lists

Compiler: GCC

Platform: Linux / Windows

📂 Project Structure

APC-Arbitrary-Precision-Calculator/
│
├── main.c
├── add.c
├── sub.c
├── mul.c
├── div.c
├── list.c
├── main.h
├── README.md
└── Makefile (optional)

⚙️ How to Compile and Run

Step 1: Compile the Program
gcc *.c -o apc

Step 2: Run the Program
./apc

🧮 Sample Operations

Input : 9876543210123456789 + 123456789
Output : 9876543333580244578

Input : 999999999999 - 888888888888
Output : 111111111111

🎯 Learning Outcomes

Strong understanding of Pointers and Dynamic Memory

Deep knowledge of Linked Lists

Experience in implementing Big Number Arithmetic

Improved problem-solving and debugging skills

Hands-on practice with modular C programming

👨‍💻 Developed By

Nakul Anil Vadar
Embedded Systems & IoT Engineer

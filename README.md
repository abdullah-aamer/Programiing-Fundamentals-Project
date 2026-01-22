# Quiz Application – Programming Fundamentals Project

**Project Type:** Academic / Programming Fundamentals (PBL Project)  
**Language:** C++  
**Author:** Muhammad Abdullah Bin Aamer  
**Institution:** National University of Technology (NUTECH), Islamabad  

---

## Project Overview
This is a **console-based Quiz Application** developed as a **Project-Based Learning (PBL)** assignment for the first semester of BS Computer Science.  
The application simulates a professional exam environment with **timed questions**, **demo practice tests**, and **result tracking**. It demonstrates key **programming fundamentals** such as loops, conditional statements, functions, arrays, and **file handling**.

---

## Features
The application contains **six main options**:

1. **Start Test** – Begin a new test. Includes:  
   - **Student information input**: Student ID, Name, Course, Date automatically recorded  
   - **Demo Test**: Optional practice test  
   - **Main Test**: 20 multiple-choice questions with **90-second timer per question**  
   - **Result Calculation**: Scores, percentage, and pass/fail status  
   - **Result Saving**: Automatically saves results in `results.txt` using file handling  

2. **View Instructions** – Displays guidance for using the application.  

3. **View Result History** – Shows saved results and supports:  
   - Viewing all results  
   - Searching by Student ID  
   - Highest Marks  
   - Average Marks  
   - Most Recent Result  

4. **Admin Panel** – Placeholder for future features (requires advanced logic and security).  

5. **About Application** – Displays project and developer details.  

6. **Exit** – Close the application.  

---

## Technical Details
- **Language:** C++  
- **Libraries Used:**  
  - `<iostream>` – Input/output operations  
  - `<conio.h>` – Keyboard input handling  
  - `<ctime>` – Date and time recording  
  - `<windows.h>` – Sleep and Beep functions  
  - `<fstream>` – File handling for storing results  

- **Key Programming Concepts Applied:**  
  - Conditional statements (if/else, switch)  
  - Loops (for, while, do-while)  
  - Functions  
  - Arrays and strings  
  - File handling (saving and reading results)  
  - Basic timer implementation for questions  

- **Data Storage:**  
  - Results are saved in `results.txt`  
  - Format: `StudentID | Name | Course | Correct/Total | Percentage | Status | Date/Time`  

---

## How to Run
1. Open the project folder in your preferred C++ IDE (e.g., Code::Blocks, Visual Studio, DevC++).  
2. Compile the `main.cpp` file.  
3. Run the executable.  
4. Navigate the **menu** using number keys `[1-6]`.  
5. Follow on-screen instructions to attempt demo or main tests.  

---

## Learning Outcomes
- Gained experience with **C++ programming fundamentals**  
- Learned to implement **timed assessments** and **interactive console applications**  
- Practiced **file handling** to save and read user data  
- Built understanding of **modular programming** using functions and arrays  

---



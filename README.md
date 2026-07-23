# DEVCORE-GPA-CALC

A lightweight GPA Letter Grade Converter written in C.

This project converts a student's numerical score into its corresponding letter grade based on the grading system defined by Accra Technical University. It also includes an automated test suite to verify that every score range returns the correct grade.

---

## Features

- Convert numerical scores (0–100) into letter grades (LG)
- Convert letter grades (LG) to grade value (GV)
- Calculate grade point (GP)
- Validate invalid inputs
- Modular source code using header files
- Automated unit-style test program
- Organized project structure
- Ready for future GUI integration

---

## Grade Scale

| Score Range   | Grade   |
|---------------|---------|
| 85 - 100      | A+      |
| 80 - 84       | A       |
| 75 - 79       | B+      |
| 70 - 74       | B       |
| 65 - 69       | C+      |
| 60 - 64       | C       |
| 55 - 59       | D+      |
| 50 - 54       | D       |
| 0 - 49        | F       |
| Outside 0-100 | INVALID |

---

# Project Structure

```
DEVCORE-GPA-CALC/
│
├── docs/
│   ├── solutions/
│   │   ├── getch_flowchart.drawio.png
│   │   ├── gpa_calculator_research.md
│   │   ├── getcrs_flowchart.drawio.png
│   │   ├── getscr_flowchart.drawio.png
│   │   ├── gpcalc_flowchart.drawio.png
│   │   ├── lgconv_flowchart.drawio.png
│   │   ├── scrconv_flowchart.drawio.png
│   │   ├── solution_getch.md
│   │   ├── solution_getcrs.md
│   │   ├── solution_getscr.md
│   │   ├── solution_gpcalc.md
│   │   ├── solution_lgconv.md
│   │   └── solution_srconv.md
│   ├── worksheet/
│   │   ├── commands.txt
│   │   ├── dictionary.md
│   │   ├── markdown_cheatsheet.md
│   │   ├── naming_std.md
│   │   └── scratch_pad.txt
│   └── setup.md
│   
│
├── include/
│   └── gpa.h
│
├── obj/
│   ├── scrconv.exe
│
├── src/
│   ├── getch.c
│   ├── getscr.c
|   ├── gpcalc.c
|   ├── scrconv.c
|   ├── getcrs.c
│   └── lgconv.c
         
├── test/
│   └── test_scrconv.c
│
├── ui/
│   └── gui.c
│
├── .gitignore
├── LICENSE
├── main.c
└── README.md
└── test_gpconv.exe
```

---

# Requirements

- GCC Compiler
- C99 or newer
- Visual Studio Code (recommended)
- MSYS2 MinGW64 (Windows)

---

# Building

Compile the application:

```bash
gcc main.c src/scrconv.c -Iinclude -o obj/scrconv.exe
```

Compile the test program:

```bash
gcc test/test_scrconv.c src/scrconv.c -Iinclude -o obj/test_scrconv.exe
```

---

# Running

Run the main program:

```bash
./obj/scrconv.exe
```

Example:

```
Enter a score: 82
A
```

Run the test suite:

```bash
./obj/test_scrconv.exe
```

Expected output:

```
===== GPA Converter Tests =====

[PASS] Score: 100 -> A+
[PASS] Score: 99 -> A+
...

[PASS] Score: 0 -> F
```

---

# Source Files

## main.c

Application entry point.

Responsibilities:

- Read user input
- Call the GPA conversion function
- Display the resulting letter grade

---

## include/gpa.h

Header file.

Contains:

- Function declarations
- Public interface of the GPA converter

---

## src/scrconv.c

Core application logic.

Responsibilities:

- Validate input
- Convert numerical score
- Return corresponding letter grade

## src/gpnum.c

---

## test/test_scrconv.c

Automated testing program.

Responsibilities:

- Test every valid score range
- Compare expected and actual outputs
- Display PASS/FAIL results

---

# Function Documentation

## scrconv()

```c
char *scrconv(int score);
```

Converts a numerical score into a letter grade.

### Parameters

| Name | Type | Description |
|------|------|-------------|
| score | int | Student score between 0 and 100 |

### Returns

Returns a string containing:

- A+
- A
- B+
- B
- C+
- C
- D+
- D
- F
- INVALID

---

# Design Goals

This project follows several software engineering principles:

- Modular programming
- Separation of concerns
- Reusable functions
- Simple testing
- Maintainable code
- Clear documentation

---

# Future Improvements

Planned enhancements include:

- GPA calculation from multiple courses
- Credit hour support
- CGPA calculation
- Student records
- File storage
- GTK graphical user interface
- Makefile support
- Continuous Integration (CI)
- GitHub Actions for automated testing

---

# Coding Style

Project conventions:

- C99 standard
- 4-space indentation
- Meaningful variable names
- Comment major code sections
- One responsibility per function

---

# Testing

The project includes an automated test suite that verifies:

- Every valid grade boundary
- Every score range
- Invalid values
- Expected output strings

Testing currently covers the complete grading scale.

---

# Authors

**DEVCORE Team**

Software Engineering Project

Accra Technical University

---

# License

This project is licensed under the MIT License.

See the `LICENSE` file for details.
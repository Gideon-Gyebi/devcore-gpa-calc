# Naming Standard For a Uniform Code

|**Item**                 |**Convention**           |**Example**                   |
|-------------------------|-------------------------|------------------------------|
|**Header Files**         |lowercase                |`gpa.h`                       |
|**Source Files**         |lowercase                |`main.c`, `scrconv.c`         |
|**Documentation Files**  |snake_case               |`gpa_calculator_research.md`  |
|                         |                         |`solution_scrconv.md`         |
|**Variables**            |camelCase                |`gradeLetter`, `creditHour`,  |
|                         |                         |`gradePoint`                  |
|**Functions**            |lowercase (abbreviated)  |`scrconv()`, `lgconv()`       |
|**Struct Types**         |PascalCase               |`Semester`, `Course`          |
|**Struct Variables**     |camelCase                |`studentRecord`               |
|**Header Guards**        |UPPER_CASE               |`#ifndef GPA_H`               |
|**Constants (optional)** |UPPER_CASE               |`MAX_COURSES`, `MAX_SCORE`    |
|**Macros**               |UPPER_CASE               |`#define MAX_COURSES 10`      |
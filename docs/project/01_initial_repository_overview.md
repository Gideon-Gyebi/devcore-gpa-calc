# Initial Repository Overview

> Assessment snapshot of `Gideon-Gyebi/devcore-gpa-calc` on branch `gideon`. Static review only: no compilation or test execution was performed.

## 1. Project at a glance

The repository contains a modular C application that collects course details, converts numerical scores into the Accra Technical University (ATU) letter-grade scale, calculates weighted grade points, totals credit hours and grade points, and calculates semester GPA. It includes separate source modules, a shared header, tests, setup notes, solution documents and a GTK4 UI source file that was empty in the inspected snapshot.

**Technology direction:** C calculation backend; GTK4 desktop frontend; VS Code, MSYS2 MinGW64 and GCC; Windows as the initial target.

## 2. Repository structure

```text
devcore-gpa-calc/
├── README.md
├── main.c
├── include/gpa.h
├── src/
│   ├── getch.c
│   ├── getcrs.c
│   ├── getnumcrs.c
│   ├── getscr.c
│   ├── gpacalc.c
│   ├── gpcalc.c
│   ├── lgconv.c
│   ├── savechgp.c
│   ├── scrconv.c
│   ├── tchcalc.c
│   └── tgpcalc.c
├── test/                 # function tests and input fixtures
├── ui/gui.c              # empty in inspected snapshot
└── docs/
    ├── setup.md
    ├── solutions/        # implementation and research notes
    ├── flowcharts/
    └── worksheet/        # commands, naming and team notes
```

| Area | Responsibility |
|---|---|
| `main.c` | Current CLI orchestration |
| `include/gpa.h` | Constants, record structure and function prototypes |
| `src/` | Input, conversion, aggregation and GPA functions |
| `test/` | Function-level tests and input fixtures |
| `ui/` | Planned GTK4 interface |
| `docs/solutions/` | Learning notes and implementation explanations |
| `docs/setup.md` | Windows/MSYS2/GTK4 setup |

## 3. Current application flow

```text
Start
  |
getnumcrs() — number of courses
  |
For each course:
  getcrs() -> getch() -> getscr()
  -> scrconv() -> lgconv() -> gpcalc()
  -> savechgp()
  |
tchcalc() — total credit hours
  |
tgpcalc() — total weighted grade points
  |
gpacalc() — semester GPA
  |
Display result
```

The current `main.c` obtains course name, credit hours and score, converts the score to a letter grade and grade value, calculates weighted grade points, stores credit hours and grade points, and finally calculates semester GPA.

## 4. Function inventory

| Function | Responsibility |
|---|---|
| `getnumcrs()` | Collect number of courses |
| `getcrs()` | Select or manually enter course name |
| `getch()` | Collect credit hours |
| `getscr()` | Collect numerical score |
| `scrconv()` | Convert score to letter grade |
| `lgconv()` | Convert letter grade to grade value |
| `gpcalc()` | Calculate grade value × credit hours |
| `savechgp()` | Store credit hours and grade points |
| `tchcalc()` | Sum credit hours |
| `tgpcalc()` | Sum grade points |
| `gpacalc()` | Calculate semester GPA |

### GPA formula

`Course Grade Points = Grade Value × Credit Hours`

`Semester GPA = Σ(Grade Value × Credit Hours) / Σ(Credit Hours)`

## 5. ATU grading scale

| Score | Letter | Grade value |
|---:|:---:|---:|
| 85–100 | A+ | 5.0 |
| 80–84 | A | 4.5 |
| 75–79 | B+ | 4.0 |
| 70–74 | B | 3.5 |
| 65–69 | C+ | 3.0 |
| 60–64 | C | 2.5 |
| 55–59 | D+ | 2.0 |
| 50–54 | D | 1.5 |
| 0–49 | F | 0.0 |
| Outside 0–100 | INVALID | N/A |

## 6. Current record structure

The inspected header defines:

```c
#define MAX_COURSES 15

typedef struct
{
    float creditHour;
    float gradePoint;
} GpaRecord;
```

This is sufficient for summing totals, but not for retaining a complete course result for a GUI table. `main.c` prints selected course and grade details, while `savechgp()` stores only credit hours and grade points.

An illustrative future structure discussed was:

```c
typedef struct
{
    char courseName[100];
    int score;
    char letterGrade[3];
    float gradeValue;
    float creditHour;
    float gradePoint;
} GpaRecord;
```

This is illustrative only, not an approved schema or existing repository change. Agree on exact fields and types before implementation.

## 7. Important code-review observations

> Static observations only. These are not verified runtime failures; no build or test run was performed.

### A. Input handling
- CLI input functions use `scanf()` and manual buffer clearing.
- Some failure paths may leave variables uninitialized before later conditions use them.
- Input handling should deliberately cover invalid text and `EOF`.
- Manual course-name input should handle empty input and newline behaviour.

### B. Validation
- `getch()` restricts credit hours to 1–3, while `gpcalc()` may accept zero.
- Backend functions should enforce their own contracts, not rely only on CLI validation.
- `lgconv()` returning 0 for an unknown grade is ambiguous because F also maps to 0.

### C. Portability and tests
- `savechgp.c` includes `GPA.h`, while the file is `gpa.h`; this case difference can fail on case-sensitive systems.
- A helper in `test_gpcalc.c` appears to return `int` while the tested function returns `float`.
- `test_tchcalc.c` contains a zero-length array, not standard C99.
- Some CLI tests appear to require manual interaction.

### D. Documentation and integration
- README describes an earlier converter and outdated build commands.
- `docs/setup.md` includes GTK4 setup, but `ui/gui.c` was empty in the inspected snapshot.
- No Makefile or CMake configuration was observed.
- Terminal `get*()` functions should not be called by GTK callbacks.

## 8. GTK4 readiness and architecture

```text
+-----------------------------+
| GTK4 Frontend               |
| Forms, widgets, tables      |
+--------------+--------------+
               |
               v
+-----------------------------+
| Application / Integration   |
| Validate values, call API   |
+--------------+--------------+
               |
               v
+-----------------------------+
| C Calculation Backend       |
| Grade, points, totals, GPA  |
+--------------+--------------+
               |
               v
+-----------------------------+
| Future Storage              |
| Deferred to later phase     |
+-----------------------------+
```

GTK4 should collect and display information. The calculation backend should remain independent of GTK4 and reusable in tests. GTK widgets replace terminal prompts; the GUI should not call `getnumcrs()`, `getcrs()`, `getch()` or `getscr()`.

## 9. Overall assessment

| Area | Assessment |
|---|---|
| Modular C structure | Good foundation |
| Grade conversion | Implemented in separate functions |
| Semester GPA | Present in CLI flow |
| Course record retention | Partial |
| Input robustness | Needs review |
| Tests | Present; quality and coverage need review |
| README | Needs updating |
| GTK4 frontend | Not implemented in inspected snapshot |
| Build automation | No Makefile/CMake observed |

**Overall:** The repository is a useful foundation for a semester GPA calculator. Priorities are backend stability, a complete course-result record, test quality and GTK4 integration without coupling the calculation engine to the GUI.

## 10. Suggested immediate priorities

1. Confirm function contracts and validation rules.
2. Stabilize backend error handling.
3. Agree on the complete course-result structure.
4. Test grade boundaries, weighted points, totals and GPA.
5. Build GTK4 input and results views.
6. Integrate the UI with the reusable C backend.
7. Update README and build instructions.

---
*Initial assessment snapshot. Reassess against the latest branch before treating this as current implementation status.*

# Gideon Role 3 API Signatures and Data Flow

**Workstream:** Data Model and API Design  
**Owner:** Gideon  
**Scope:** Input and output contracts for the semester-calculation integration API

## Progress

- **Input** — covered in section 1 of this document.
- **Output** — covered in section 2 of this document.
- **Contract** — to be completed next session.
- **Data Flow** — to be completed next session.

This note turns the recorded project decisions into an API design for implementation.

## 1. Input contract

The GTK UI collects the course count and, for every course, its name, score and credit hours. It stores those values in a fixed-size `CourseResult` array and passes the array and count to the integration function.

On entry, the integration function reads `courseName`, `score` and `creditHour`. The UI does not need to fill `letterGrade`, `gradeValue` or `gradePoint`; those are calculated fields.

| Input | Type | Rule |
|---|---|---|
| `courseCount` | `int` | From 1 through `MAX_COURSES` (15). |
| `courseName` | `char[100]` | Bounded, null-terminated name. |
| `score` | `float` | Supports decimal percentage scores; range and grade-boundary handling follow the established ATU scale. |
| `creditHour` | `float` | From 1.0 through 3.0. |

## 2. Output contract

On successful calculation, the integration function fills the calculated fields in each input `CourseResult` and writes the semester totals into a `SemesterSummary`. The UI reads these values for the course results table and GPA summary.

| Output | Stored in | Meaning |
|---|---|---|
| `letterGrade` | Each `CourseResult` | Letter grade for that course, as display text. |
| `gradeValue` | Each `CourseResult` | Numeric value assigned to the letter grade. |
| `gradePoint` | Each `CourseResult` | Course grade value multiplied by its credit hours. |
| `totalCreditHours` | `SemesterSummary` | Sum of course credit hours. |
| `totalGradePoints` | `SemesterSummary` | Sum of course grade points. |
| `gpa` | `SemesterSummary` | Semester GPA calculated from total grade points and total credit hours. |

The summary is derived from the course results; it does not replace or duplicate the per-course records. `SemesterSummary` is the proposed name for the summary structure that the integration API returns through an output parameter.

```c
/* Proposed summary structure, declared in include/gpa.h */
typedef struct
{
    float totalCreditHours;
    float totalGradePoints;
    float gpa;
} SemesterSummary;
```

The API declaration becomes:

```c
/* include/semester_api.h */
GpaStatus calculate_semester(
    CourseResult courses[],
    int courseCount,
    SemesterSummary *summary
);
```

`GpaStatus` indicates whether the call succeeded; its values and error behavior are the next contract section. The UI uses the course fields and summary after a successful call.

## 3. Proposed file placement and connections

```text
include/gpa.h
  Defines MAX_COURSES, CourseResult and SemesterSummary
       ↑ included by                         ↑ included by
include/semester_api.h                    src/semester_api.c
  Includes gpa.h                           Includes both headers
  Declares calculate_semester(...)         Coordinates existing backend calls
       ↑ included by                              ↑ called by
ui/gui.c  ───── calls calculate_semester(courses, count, &summary) ───────┘
  Collects input fields; reads course results and summary after success
```

`include/gpa.h` already exists and currently defines `GpaRecord` with only `creditHour` and `gradePoint`. The agreed direction is to extend this shared header with the full `CourseResult`; this input note does not replace or move that struct. `include/semester_api.h` and `src/semester_api.c` are proposed integration files and do not exist yet. The GTK frontend will include the API header, not call terminal input functions.

## 4. Header sketch

The following shows how the struct and API declaration connect. It is an implementation sketch for the approved direction; the integration status type belongs to the explicit status/error contract.

```c
/* include/gpa.h */
#ifndef GPA_H
#define GPA_H

#define MAX_COURSES 15
#define COURSE_NAME_LENGTH 100

typedef struct
{
    char courseName[COURSE_NAME_LENGTH];
    float score;
    char letterGrade[3];
    float gradeValue;
    float creditHour;
    float gradePoint;
} CourseResult;

typedef struct
{
    float totalCreditHours;
    float totalGradePoints;
    float gpa;
} SemesterSummary;

/* Existing backend declarations remain here. */

#endif
```

```c
/* include/semester_api.h */
#ifndef SEMESTER_API_H
#define SEMESTER_API_H

#include "gpa.h"

/* GpaStatus is defined as part of the status/error contract. */
GpaStatus calculate_semester(
    CourseResult courses[],
    int courseCount,
    SemesterSummary *summary
);

#endif
```

## 5. UI call site

The UI obtains values from GTK widgets, fills the input fields, then calls the integration API. It does not call `getcrs()`, `getscr()` or `getch()`; those functions read from the terminal.

```c
/* ui/gui.c */
#include "semester_api.h"

static void on_calculate_clicked(GtkButton *button, gpointer user_data)
{
    CourseResult courses[MAX_COURSES];
    SemesterSummary summary;
    int courseCount = collect_course_inputs(courses);

    GpaStatus status = calculate_semester(courses, courseCount, &summary);

    /* On success, show each CourseResult and the SemesterSummary in GTK. */
}
```

`collect_course_inputs()` above is a placeholder for the GTK code that reads the current form; it is not an existing project function.

## 6. Backend handoff and score type

The input model uses `float score` to support decimal percentages. The current `scrconv(int score)` cannot accept that value. The backend adaptation work must change `scrconv()` and any dependent declarations or calls to accept `float`, while retaining the established ATU grade bands and GPA formula. GTK and the integration layer must pass the score without truncating its fractional part.

```text
GTK fields
   │ courseCount + CourseResult[].courseName / score / creditHour
   ▼
calculate_semester(courses, courseCount, &summary)
   │ validates the input contract; coordinates calculations
   ▼
scrconv(float score) → lgconv(letterGrade) → gpcalc(gradeValue, creditHour)
   │
   └─ tchcalc/tgpcalc → gpacalc; fills SemesterSummary and CourseResult fields
```

The actual `include/gpa.h` and backend sources still contain the current CLI-era declarations and `GpaRecord`. This note describes the target connection for team handoff; it does not claim those proposed files or changes have been implemented.

## 7. Existing project locations

```text
include/gpa.h       Shared course/backend declarations; extend with CourseResult
include/            Add semester_api.h for the UI-facing integration declaration
src/                Add semester_api.c to coordinate existing calculations
ui/gui.c            GTK input collection; include semester_api.h and call API
test/               Add integration checks when implementation/testing is assigned
docs/Workstream/Data Model and API Design/Deliverable/role-3-api-signatures-and-data-flow-gideon.md
                    This Role 3 API and data-flow handoff
```

## How other workstreams use this handoff

As listed in [section 6.2 of the team discussion](../../../archive/Requirements_and_Data_Model_Team_Discussion_v2.md):

- **Workstream 2 — Backend adaptation:** update `scrconv()` to accept the agreed `float` score and reuse backend functions.
- **Workstream 3 — GTK4 frontend:** collect the input fields and display the per-course results and semester summary.
- **Workstream 4 — Application integration:** implement the proposed API call and connect UI values to backend calculations.
- **Workstream 5 — Testing and quality assurance:** verify the input/output behavior; add error cases after the contract is defined.
- **Workstream 6 — Documentation and release readiness:** carry the implemented API and data flow into project documentation.

Workstream 1 uses this API design alongside the agreed course-result and summary models.

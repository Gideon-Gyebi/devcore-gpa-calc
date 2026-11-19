# Gideon Role 3 API Signatures and Data Flow

**Workstream:** Data Model and API Design  
**Owner:** Gideon  
**Scope:** Input, output, API contract and data flow for semester calculation

## Progress

- **Input** — covered in section 1 of this document.
- **Output** — covered in section 2 of this document.
- **Validation** — to be completed next session in section 3.
- **Contract** — covered in section 4; proposed status and error behavior is ready for lead review.
- **Data Flow** — covered in section 5.

This note turns the recorded project decisions into an API design for implementation.

## 1. Input contract

The GTK UI collects the course count and, for every course, its name, score and credit hours. It stores those values in a fixed-size `CourseResult` array and passes the array and count to the integration function.

On entry, the integration function reads `courseName`, `score` and `creditHour`. The UI does not need to fill `letterGrade`, `gradeValue` or `gradePoint`; those are calculated fields.

| Input | Type | Rule |
|---|---|---|
| `courseCount` | `int` | From 1 through `MAX_COURSES` (15). |
| `courseName` | `char[100]` | Must be bounded, null-terminated, and not empty or whitespace-only. |
| `score` | `float` | From 0.0 through 100.0, with at most one decimal place; use the established ATU grade boundaries. |
| `creditHour` | `float` | Only 1.0, 1.5, 2.0, 2.5 or 3.0 is allowed. |

These input rules are settled. Section 3 records the validation behavior still to be specified.

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

The complete API declaration, including its status and error details, appears in section 4. The UI uses the course fields and summary after a successful call.

## 3. Validation — next session

**Owner:** Gideon. The field rules are listed in section 1; this section will define how the API enforces them before calculation.

Work to complete:

- Specify checks for blank/whitespace names, name capacity and termination, score range and one-decimal precision, and the five allowed credit-hour values.
- Decide whether and how the UI normalizes course-name capitalization, and ensure the API still validates the received string.
- Define the validation order and when the backend calculation functions may be called.
- Specify how invalid input affects existing calculated fields and displayed results.

## 4. API contract

`calculate_semester()` is the single API the GTK layer calls. It receives the entered course records, validates them, fills calculated course fields, writes the semester summary, and returns a status. It does not print messages or access GTK widgets.

```c
/* include/semester_api.h */
#ifndef SEMESTER_API_H
#define SEMESTER_API_H

#include "gpa.h"

typedef enum
{
    GPA_STATUS_SUCCESS,
    GPA_STATUS_INVALID_ARGUMENT,
    GPA_STATUS_INVALID_COURSE_COUNT,
    GPA_STATUS_INVALID_COURSE_NAME,
    GPA_STATUS_INVALID_SCORE,
    GPA_STATUS_INVALID_CREDIT_HOUR,
    GPA_STATUS_CALCULATION_ERROR
} GpaStatus;

/* errorCourseIndex is zero-based; use -1 for errors not tied to one course. */
GpaStatus calculate_semester(
    CourseResult courses[],
    int courseCount,
    SemesterSummary *summary,
    int *errorCourseIndex
);

#endif
```

`typedef enum { ... } GpaStatus` defines named return codes for the API. `calculate_semester()` returns `GPA_STATUS_SUCCESS` when the calculation succeeds, or another status to identify why it could not proceed. The UI checks that value to decide whether to display results or show an error message. `GpaStatus` describes the API call; it is separate from `CourseResult.letterGrade`, which holds the course's letter grade as text.

| Contract item | Behavior |
|---|---|
| Valid call | `courses`, `summary` and `errorCourseIndex` are non-null; `courseCount` is 1 through `MAX_COURSES`. |
| Validation | The integration layer enforces the rules in section 1; validation details are listed for completion in section 3. |
| Success | Return `GPA_STATUS_SUCCESS`; all calculated fields and `summary` are valid for the UI to display; set `*errorCourseIndex` to `-1`. |
| Input error | Return the matching status; for a course-specific error, set `*errorCourseIndex` to its zero-based array index. For a general error, set it to `-1`. |
| Failure outputs | The UI must not display calculated fields or the summary unless the status is success. |
| Presentation | The UI turns the status into user-facing feedback; the API and calculation functions do not print UI messages. |

## 5. Data flow

```text
ui/gui.c
  Reads GTK fields into CourseResult[].courseName, .score and .creditHour
  Includes semester_api.h; calls calculate_semester(...)
                 │
                 ▼
src/semester_api.c
  Validates courseCount and every course input
  Calls scrconv(float score) → lgconv(letterGrade) → gpcalc(gradeValue, creditHour)
  Fills CourseResult[].letterGrade, .gradeValue and .gradePoint
  Calls tchcalc/tgpcalc → gpacalc; fills SemesterSummary
                 │
          status + results
                 ▼
ui/gui.c displays the results on success, or shows feedback for the returned status
```

```text
include/gpa.h
  Defines MAX_COURSES, CourseResult and SemesterSummary
       ↑ included by                         ↑ included by
include/semester_api.h                    src/semester_api.c
  Defines GpaStatus                         Includes both headers; calls backend
  Declares calculate_semester(...)                    ↑
       ↑ included by                                   │
ui/gui.c  ───────── calls API ─────────────── existing src/ calculation functions
```

The GTK layer must not call terminal input functions (`getcrs()`, `getscr()`, `getch()`). The existing `include/gpa.h` and backend sources still contain legacy `GpaRecord` and integer-score declarations; backend adaptation replaces them with the agreed model and float-score path. `include/semester_api.h` and `src/semester_api.c` are new integration files. The UI snippet’s `collect_course_inputs()` is only illustrative and is not an existing function.

```c
/* ui/gui.c — call-site sketch */
#include "semester_api.h"

CourseResult courses[MAX_COURSES];
SemesterSummary summary;
int courseCount = collect_course_inputs(courses);
int errorCourseIndex;

GpaStatus status = calculate_semester(
    courses, courseCount, &summary, &errorCourseIndex
);
```

## **MUST IMPLEMENT — changes required for the new API and data flow**

The following existing-code updates are required before the new integration API can use the agreed model. File paths are based on the current repository; implementation ownership can be assigned across backend, API and UI workstreams.

| File or files | Required implementation change |
|---|---|
| `include/gpa.h` | Replace `GpaRecord` with `CourseResult`; define `SemesterSummary`; update backend declarations for float scores and `CourseResult` arrays. `CourseResult.letterGrade` is `char[3]`. |
| `src/getscr.c`, `include/gpa.h` | Change score input and return type from `int` to `float`; retain the 0–100 range and accept no more than one digit after the decimal point. |
| `src/scrconv.c`, `include/gpa.h` | Change `scrconv()` to accept `float`; preserve the established ATU grade bands and invalid-score behavior. |
| `src/getch.c` | Enforce the allowed credit-hour set: 1.0, 1.5, 2.0, 2.5 or 3.0. |
| `src/getcrs.c` and the integration validation | Reject empty and whitespace-only names; safely fit and terminate names in the 100-character field. Apply consistent capitalization if the UI formatter rule is adopted. |
| `src/savechgp.c`, `src/tchcalc.c`, `src/tgpcalc.c`, `include/gpa.h` | Replace or retire the legacy `GpaRecord` storage path. Retained storage and aggregate functions operate on `CourseResult` fields (`creditHour`, `gradePoint`). Correct `savechgp.c`’s `GPA.h` include to `gpa.h` if it remains. |
| `main.c` | Update the CLI score variable, record storage and formatting to the new types if the CLI remains buildable during migration. |
| `test/test_getscr.c`, `test/test_scrconv.c`, `test/test_getch.c`, `test/test_getcrs.c` | Update coverage for decimal scores, one-decimal precision, allowed credit-hour values, and rejected blank names. |
| `test/test_savechgp.c`, `test/test_tchcalc.c`, `test/test_tgpcalc.c` | Replace `GpaRecord` fixtures and calls with the new model, or remove tests for retired helpers. |
| `include/semester_api.h`, `src/semester_api.c` | Add the UI-facing API declaration and implementation. Validate inputs, coordinate calculations, fill course results and populate `SemesterSummary`. |
| `ui/gui.c` | Collect the agreed inputs, call the integration API, and display course results and semester summary from its outputs. |

This is an implementation-impact checklist, not a claim that these edits have been made. The current source still contains the legacy type and integer-score path.

## How other workstreams use this handoff

As listed in [section 6.2 of the team discussion](../../../archive/Requirements_and_Data_Model_Team_Discussion_v2.md):

- **Workstream 2 — Backend adaptation:** update `scrconv()` to accept the agreed `float` score and reuse backend functions.
- **Workstream 3 — GTK4 frontend:** collect the input fields and display the per-course results and semester summary.
- **Workstream 4 — Application integration:** implement the proposed API call and connect UI values to backend calculations.
- **Workstream 5 — Testing and quality assurance:** verify input/output behavior and test the statuses and error cases in section 4.
- **Workstream 6 — Documentation and release readiness:** carry the implemented API and data flow into project documentation.

Workstream 1 uses this API design alongside the agreed course-result and summary models.

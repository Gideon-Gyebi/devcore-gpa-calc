# Gideon Role 3 API Signatures and Data Flow

**Workstream:** Data Model and API Design  
**Owner:** Gideon  
**Scope:** Input, output, API contract and data flow for semester calculation

## Progress

- **Input Contract** — covered in section 1 of this document.
- **Output Contract** — covered in section 2 of this document.
- **Validation** — covered in section 3; name-capitalization formatting remains a UI choice.
- **API Contract** — covered in section 4; proposed status and error behavior is ready for lead review.
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

These input rules are settled. Section 3 specifies how the API validates them.

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

## 3. Validation

**Owner:** Gideon. The integration API enforces these rules before it calls calculation functions. GTK may also check inputs to give immediate feedback, but API validation remains required.

| Check | API rule | Result on failure |
|---|---|---|
| Required arguments | `courses`, `summary` and `errorCourseIndex` must not be null. | `GPA_STATUS_INVALID_ARGUMENT`; index `-1` when available. |
| Course count | Must be 1 through `MAX_COURSES` (15). | `GPA_STATUS_INVALID_COURSE_COUNT`; index `-1`. |
| Course name | Must contain a null terminator within its 100-character array, have at least one non-whitespace character, and fit within the buffer (up to 99 text bytes plus terminator). | `GPA_STATUS_INVALID_COURSE_NAME`; set the course's zero-based index. |
| Score | Must be finite, from 0.0 through 100.0, and represent no more than one decimal place. When checking tenths, account for normal floating-point representation tolerance. | `GPA_STATUS_INVALID_SCORE`; set the course's zero-based index. |
| Credit hours | Must be finite and equal to 1.0, 1.5, 2.0, 2.5 or 3.0. | `GPA_STATUS_INVALID_CREDIT_HOUR`; set the course's zero-based index. |

Check the general arguments and count first, then inspect courses in array order. For each course, check name, score and credit hours in that order. Stop at the first failure, return its status, and set `errorCourseIndex` to that course's zero-based position. Only begin calculations after all course inputs pass validation.

The API rejects blank names but does not change capitalization. A GTK formatter may apply a consistent style; agree that presentation rule with the UI workstream separately. On validation failure, the UI preserves entered inputs and treats calculated fields and the summary as invalid; it displays feedback using the returned status and course index.

## 4. API contract

`calculate_semester()` is the single API the GTK layer calls. It receives the entered course records, validates them, fills calculated course fields, writes the semester summary, and returns a status. It does not print messages or access GTK widgets.

```c
/* include/semester_api.h */
#ifndef SEMESTER_API_H
#define SEMESTER_API_H

#include "gpa.h"

typedef enum
{
    GPA_STATUS_SUCCESS,             /* Calculation completed. */
    GPA_STATUS_INVALID_ARGUMENT,    /* A required pointer is null. */
    GPA_STATUS_INVALID_COURSE_COUNT,
    GPA_STATUS_INVALID_COURSE_NAME,
    GPA_STATUS_INVALID_SCORE,
    GPA_STATUS_INVALID_CREDIT_HOUR,
    GPA_STATUS_CALCULATION_ERROR
} GpaStatus;

/* One array record per course; the API fills calculated fields in place. */
GpaStatus calculate_semester(
    CourseResult courses[],
    int courseCount,
    SemesterSummary *summary,
    int *errorCourseIndex /* zero-based failing course; -1 for general errors */
);

#endif
```

`GpaStatus` is a set of named return codes. The function returns one status; it is separate from `CourseResult.letterGrade`, which holds the course's letter grade as text.

The caller allocates the storage. `courses` is an array with one `CourseResult` per entered row; `calculate_semester()` receives the whole array in one call and processes its first `courseCount` elements one by one. It writes each course's calculated fields back into that same element. The API does not allocate, retain or free the array. The caller also supplies one `SemesterSummary` and one `errorCourseIndex` integer; the API fills them. The index identifies the first failing course, not a list of errors.

| Contract item | Meaning and output use |
|---|---|
| Required arguments | `courses`, `summary` and `errorCourseIndex` must point to caller-owned storage; `courseCount` must be 1 through `MAX_COURSES`. |
| `GPA_STATUS_SUCCESS` | Calculation completed; course results and `summary` are ready to display; index is `-1`. |
| `GPA_STATUS_INVALID_ARGUMENT` | A required pointer was null; index is `-1` when its output pointer is available. |
| `GPA_STATUS_INVALID_COURSE_COUNT` | Count is outside 1–`MAX_COURSES`; index is `-1`. |
| `GPA_STATUS_INVALID_COURSE_NAME`, `GPA_STATUS_INVALID_SCORE`, `GPA_STATUS_INVALID_CREDIT_HOUR` | The first invalid course field; index is that course's zero-based array position. |
| `GPA_STATUS_CALCULATION_ERROR` | A backend calculation failed; index is `-1` unless the failure is tied to a specific course. |

On any non-success status, the UI must not display the calculated fields or summary as current results. The UI translates the status into user-facing feedback; the API and calculation functions do not print UI messages.

## 5. Data flow

```text
GTK UI — ui/gui.c
  One course row fills one element: courses[0], courses[1], ... courses[n-1]
  The UI owns the array, one SemesterSummary, courseCount and errorCourseIndex

                         │
                         │ One call sends the entire array and courseCount
                         ▼

Integration API — src/semester_api.c
  Checks the arguments and validates every course before calculation

                         │
                         │ After validation, processes each course in array order
                         ▼

Existing calculation backend — src/*.c
  For each course: scrconv(score) → lgconv(letterGrade)
                   → gpcalc(gradeValue, creditHour)
  Totals: tchcalc(...) + tgpcalc(...) → gpacalc(...)

                         │
                         │ Writes outputs into the caller's records
                         ▼

Integration API — src/semester_api.c
  Fills each courses[i].letterGrade, .gradeValue and .gradePoint
  Fills the one SemesterSummary and returns GpaStatus
  Sets errorCourseIndex to the first invalid course, or -1 for a general error

                         │
                         │ One return: status + updated array + summary + index
                         ▼

GTK UI — ui/gui.c
  On success, reads courses[0..courseCount-1] for result rows and summary once
  On error, uses GpaStatus and errorCourseIndex to show feedback
```

```text
include/gpa.h
  Shared definitions: MAX_COURSES, CourseResult, SemesterSummary

include/semester_api.h
  Includes gpa.h; defines GpaStatus and declares calculate_semester(...)

src/semester_api.c
  Includes semester_api.h; coordinates the existing calculation functions

ui/gui.c
  Includes semester_api.h; calls the API and displays its returned results
```

The GTK layer must not call terminal input functions (`getcrs()`, `getscr()`, `getch()`). The existing `include/gpa.h` and backend sources still contain legacy `GpaRecord` and integer-score declarations; backend adaptation replaces them with the agreed model and float-score path. `include/semester_api.h` and `src/semester_api.c` are new integration files.

```c
/* Illustrative caller-owned state; the actual GTK application state is not implemented yet. */
#include "semester_api.h"

typedef struct
{
    CourseResult courses[MAX_COURSES]; /* One record for each course row. */
    SemesterSummary summary;           /* One summary for the whole semester. */
    int courseCount;
} AppState;

static void calculate_button_clicked(AppState *app)
{
    int errorCourseIndex = -1; /* One index output, not an array of indexes. */

    /* One call sends all entered rows; the API processes them row by row. */
    GpaStatus status = calculate_semester(
        app->courses,
        app->courseCount,
        &app->summary,
        &errorCourseIndex
    );

    if (status == GPA_STATUS_SUCCESS)
    {
        /* Read app->courses[0..courseCount-1] for result rows and app->summary once. */
    }
    else
    {
        /* Use status and errorCourseIndex to show feedback. */
    }
}
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

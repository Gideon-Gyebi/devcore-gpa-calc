# Role 2 Data Structures and Field Types

**Workstream:** Data Model and API Design  
**Role:** Role 2 — Supporter A  
**Contributor:** Jormo  
**Main responsibility:** Define and document the shared course and semester data structures

## 1. Introduction

This document defines the responsibilities and proposed deliverables for Role 2 (Supporter A: Data Structures and Field Types) in the semester GPA calculation project. The role focuses on the design and documentation of the data structures used to store individual course information and the overall semester calculation results.

The document uses the available Role 3 API and data-flow handoff as a reference. The structures and field types described below are proposals in the current team documentation and should be confirmed with the relevant teammates before they are treated as final implementation decisions.

## 2. Role Objective

The main objective of Role 2 is to establish a consistent data model for the GPA calculation system. This means identifying the information that must be stored, choosing suitable C data types, defining input validation expectations, and ensuring that the shared structures are documented in the correct header file.

## 3. Scope of Responsibilities

- Review the proposed `CourseResult` structure and confirm the fields required for each course.
- Review the proposed `SemesterSummary` structure and confirm the fields required for the semester totals.
- Choose and document suitable C data types for every field.
- Define validation requirements for input fields such as course name, score, and credit hours.
- Document the agreed structures in the shared `include/gpa.h` header file.
- Coordinate with Gideon (Role 3) so the API uses the same agreed structure definitions.
- Avoid creating duplicate `CourseResult` or `SemesterSummary` definitions in separate header files.

## 4. Proposed Data Structures

The Role 3 handoff identifies two structures that the project needs: `CourseResult` for each course and `SemesterSummary` for the semester-wide totals.

### 4.1 CourseResult

`CourseResult` stores the input information and calculated results for one course.

| Field | Proposed C type | Purpose |
|---|---|---|
| `courseName` | `char[100]` | Stores the course name as a bounded, null-terminated string. |
| `score` | `float` | Stores the course percentage score, including decimal values. |
| `letterGrade` | `char[3]` | Stores the letter-grade display text. |
| `gradeValue` | `float` | Stores the numeric value assigned to the letter grade. |
| `creditHour` | `float` | Stores the credit hours assigned to the course. |
| `gradePoint` | `float` | Stores the course grade value multiplied by its credit hours. |

Proposed structure:

```c
typedef struct
{
    char courseName[100];
    float score;
    char letterGrade[3];
    float gradeValue;
    float creditHour;
    float gradePoint;
} CourseResult;
```

### 4.2 SemesterSummary

`SemesterSummary` stores the overall results calculated from the course records. It does not replace the individual `CourseResult` records.

| Field | Proposed C type | Purpose |
|---|---|---|
| `totalCreditHours` | `float` | Stores the sum of the credit hours for all courses. |
| `totalGradePoints` | `float` | Stores the sum of the course grade points. |
| `gpa` | `float` | Stores the semester GPA calculated from total grade points and total credit hours. |

Proposed structure:

```c
typedef struct
{
    float totalCreditHours;
    float totalGradePoints;
    float gpa;
} SemesterSummary;
```

## 5. Field Validation Requirements

The following validation points are based on the current Role 3 input description. They describe the checks expected at the data-model boundary; exact error handling and any additional score rules should be agreed with the team.

| Field | Validation requirement | Status / note |
|---|---|---|
| `courseCount` | Must be an integer from 1 through `MAX_COURSES` (15). | Specified in the Role 3 handoff. |
| `courseName` | Must fit within the 100-character array and be null-terminated. | Specified as a bounded name; decide whether empty names are rejected. |
| `score` | Must support decimal percentage values. | The exact accepted minimum, maximum, and boundary rules must follow the agreed ATU grading scale. |
| `creditHour` | Must be from 1.0 through 3.0. | Specified in the Role 3 handoff. |
| `letterGrade` | Must hold the resulting grade display text. | Calculated output, not required as GTK input. |
| `gradeValue` | Must hold the numeric value assigned to the letter grade. | Calculated output, not required as GTK input. |
| `gradePoint` | Must represent `gradeValue` multiplied by `creditHour`. | Calculated output, not required as GTK input. |

## 6. Proposed Location in the Project

The shared data structures should be defined in `include/gpa.h`, according to the current team handoff. That header already exists and currently contains `GpaRecord` with `creditHour` and `gradePoint`. The agreed direction is to extend the shared header with the full `CourseResult` definition and the `SemesterSummary` definition, while coordinating any changes with the team.

Relevant project locations:

- `include/gpa.h` — shared definitions for `MAX_COURSES`, `CourseResult`, `SemesterSummary`, and existing backend declarations.
- `include/semester_api.h` — proposed API declaration file owned by the integration/API work, not a second home for the data structures.
- `src/semester_api.c` — proposed integration implementation file.
- `ui/gui.c` — GTK frontend that collects inputs and uses the agreed structures.

## 7. Coordination with Role 3

Role 2 and Role 3 depend on the same data model, but they have different responsibilities. Role 2 defines and documents the shared structures and their field types. Gideon's Role 3 work defines the API signature, input/output contract, and data flow between the GTK frontend and backend.

| Role 2 — Supporter A | Role 3 — Gideon |
|---|---|
| Defines `CourseResult` and `SemesterSummary` fields and types. | Defines `calculate_semester()` and its function parameters. |
| Defines input field validation expectations. | Defines the API input/output contract and return status. |
| Documents the structures in `include/gpa.h`. | Documents the API declaration and integration files. |
| Coordinates the agreed structure definitions. | Uses the agreed structures to connect GTK and backend calculations. |

## 8. Expected Deliverables

- A reviewed `CourseResult` structure with agreed field names and C data types.
- A reviewed `SemesterSummary` structure with agreed field names and C data types.
- A written validation specification for the input fields.
- The agreed structure definitions documented in `include/gpa.h`.
- Confirmation from Role 3 that the API uses the same shared definitions.

## 9. Items to Confirm with the Team

The available handoff describes the proposed model but does not settle every implementation detail. These points should be confirmed before the structures are finalized:

- Confirm that the field names and types in both structures are accepted by the team.
- Confirm the exact permitted score range and how ATU grade boundaries are applied.
- Confirm whether a course name may be empty and how whitespace-only names are handled.
- Confirm whether credit hours must always be whole or half values, or whether any decimal value from 1.0 to 3.0 is accepted.
- Confirm the required handling of invalid input and whether the structures need any additional fields.
- Confirm how the existing `GpaRecord` and backend declarations will coexist with or transition to `CourseResult`.

## 10. Conclusion

Role 2 provides the common data foundation used by the semester GPA calculation project. By defining clear structures, appropriate field types, and validation expectations in the shared header, this role helps the GTK frontend, backend calculations, and integration API work with one consistent representation. The proposed model must be reviewed and agreed with the team before it is treated as final.

**Reference basis:** Jormo's Role 2 document and Gideon's “Role 3 API Signatures and Data Flow” handoff. Proposals and open items above are preserved as stated in the source document.

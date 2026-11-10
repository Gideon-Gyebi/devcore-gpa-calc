# GKGDev Core 5 — Assessment 01
## Results Review and Technical Discussion Guide

**Project:** ATU GPA Calculator "C" Project  
**Assessment ID:** GKG-PA-01-v1  
**Purpose:** Review assessment performance, clarify technical misunderstandings, and identify areas requiring further learning before task allocation.

---

# 1. Assessment Results Overview

| Contributor | Score | Percentage | Diagnostic Band |
|---|---:|---:|---|
| Comfort | 58/100 | 58% | Developing understanding |
| Jormo | 88/100 | 88% | Strong demonstrated understanding |

### General observations

- **Comfort:** Needs reinforcement in GPA calculations, backend function responsibilities, data structures, and application architecture.
- **Jormo:** Demonstrated strong overall understanding, with specific gaps in function responsibilities and architectural separation.
- **Both contributors:** Should participate in a technical discussion to establish a consistent understanding of the backend, frontend, integration layer, and development sequence.

These results are diagnostic. They are not permanent labels and do not prove practical coding ability.

# 2. Comfort — Individual Discussion

**Assessment result: 58/100**

## 2.1 Areas demonstrated correctly

Comfort answered correctly on project objective and MVP scope, the C/GTK4 technology direction, basic grading-scale interpretation, some weighted grade-point calculations, score-to-letter-grade conversion, total credit-hour calculation, development sequencing, and general MVP prioritization.

## 2.2 Areas requiring discussion

### A. GPA calculation — Questions 7 and 9

Comfort should revisit the relationship between grade value, credit hours, weighted grade points, and semester GPA.

Discuss:
1. Why do we multiply grade value by credit hours?
2. Why do we divide total weighted grade points by total credit hours?
3. Why is a simple average of course grade values not always the correct semester GPA?

Reference calculation:

| Course | Grade Value | Credit Hours | Weighted Grade Points |
|---|---:|---:|---:|
| A | 5.0 | 3 | 15.0 |
| B | 3.5 | 2 | 7.0 |
| **Total** | | **5** | **22.0** |

\[
GPA = \frac{22}{5} = 4.40
\]

### B. Existing data structure — Question 10

Comfort selected that `GpaRecord` stores the student's name and semester GPA. The inspected structure currently contains:

```c
typedef struct {
    int creditHour;
    double gradePoint;
} GpaRecord;
```

Discuss:
- What does each member represent?
- Why is `creditHour` necessary?
- What does `gradePoint` represent in the current implementation?
- What additional information is required for a complete course-by-course results table?
- Why distinguish the current structure from a proposed expanded structure?

### C. Codebase familiarity — Questions 11 and 12

Revisit:
- The purpose of `MAX_COURSES` and why its current value is 15.
- The role of `gpacalc()`.
- What happens when total credit hours are zero or negative.

The inspected implementation returns `-1.0` from `gpacalc()` when total credit hours are zero or negative.

**Discussion question:** Why should a GPA calculation function reject an invalid total-credit condition instead of attempting division?

### D. Application architecture — Questions 14, 16, 17, 18, 21 and 24

| Component | Responsibility |
|---|---|
| GTK4 frontend | Collect user input and display results |
| Integration layer | Coordinate validated interface values and backend calls |
| C backend | Perform grading and GPA calculations |
| Future storage layer | Persist semester records when that feature is approved |

Discuss:
- Why should GTK4 not directly use terminal-oriented input functions?
- Why should the backend remain independent of GTK4?
- What happens when interface code and calculation logic are tightly coupled?
- Why is the expanded `GpaRecord` structure not automatically an approved implementation?

**Key clarification:** GTK4 widgets collect input. Validated values pass through the integration layer to the calculation backend.

## 2.3 Recommended learning priorities

1. Revisit weighted grade points and semester GPA.
2. Understand the existing `GpaRecord` structure.
3. Study the purpose of the major backend functions.
4. Understand the separation between GTK4, integration, and backend.
5. Review input validation and invalid calculation conditions.

# 3. Jormo — Individual Discussion

**Assessment result: 88/100**

## 3.1 Areas demonstrated correctly

Jormo demonstrated understanding of the project objective and MVP scope, ATU grading scale, weighted grade-point and semester GPA calculations, existing data structure, `MAX_COURSES`, `gpacalc()` behavior, `tchcalc()` responsibility, development sequence, architectural matching, and most applied scenarios.

## 3.2 Areas requiring discussion

### A. Backend conversion functions — Question 13

Jormo selected `lgconv()` instead of `scrconv()`.

| Function | Responsibility |
|---|---|
| `scrconv()` | Convert numerical score into a letter grade |
| `lgconv()` | Convert letter grade into grade value |

Discuss:
- Why are these two conversion operations separate?
- What happens after a numerical score is converted into a letter grade?
- Where does weighted grade-point calculation fit into this sequence?

### B. Integration layer — Question 14

Jormo selected the GTK4 frontend instead of the application/integration layer.

Discuss:
- What happens between collecting input and calculating GPA?
- Why should validated interface values pass through an integration layer?
- Should GTK4 contain the GPA calculation implementation?
- How can the backend be tested independently of the GUI?

### C. GTK4 callbacks and terminal input — Question 16

Jormo answered True to the statement that GTK4 should directly call terminal-oriented functions such as `getnumcrs()` and `getscr()`. The correct answer is False.

Discuss:
- What is the difference between terminal input and GTK4 widget input?
- Why would a terminal input function be unsuitable inside a graphical callback?
- How should values collected by GTK4 reach the backend?

## 3.3 Recommended learning priorities

1. Distinguish `scrconv()` from `lgconv()`.
2. Understand the responsibilities of the integration layer.
3. Understand GTK4 callback behavior and separation from terminal input.
4. Review the complete data flow from user input to GPA output.

# 4. Joint Technical Discussion

The objective is to establish shared understanding before assigning further implementation responsibilities.

## Topic 1 — GPA calculation workflow

```text
Numerical Score
      |
      v
scrconv()
      |
      v
Letter Grade
      |
      v
lgconv()
      |
      v
Grade Value
      |
      v
gpcalc()
      |
      v
Weighted Grade Points
      |
      v
Total GPA Calculation
```

Discuss:
1. What does each function receive as input?
2. What does each function return?
3. Which function calculates weighted grade points?
4. Which functions calculate total credit hours and semester GPA?
5. How should invalid inputs or calculation errors be handled?

## Topic 2 — Frontend, integration and backend separation

```text
+----------------------+
|     GTK4 Frontend    |
| Input and Results    |
+----------+-----------+
           |
           v
+----------------------+
|  Integration Layer   |
| Validation and       |
| Backend Coordination |
+----------+-----------+
           |
           v
+----------------------+
|      C Backend       |
| Grading and GPA      |
| Calculations         |
+----------------------+
```

Discuss:
- Why should the backend not depend on GTK4?
- What should be validated before values reach the backend?
- Which component should coordinate the calculation process?
- How can we test the backend without launching the GUI?

## Topic 3 — Course records and data structures

Review the current `GpaRecord` structure and compare it with the information required by the MVP.

Discuss:
- Course name.
- Numerical score.
- Letter grade.
- Grade value.
- Credit hours.
- Weighted grade points.

**Decision required:** Agree on the required course-record fields and an appropriate data structure before implementing the full course-entry and results workflow. The expanded structure remains a proposal until formally agreed.

## Topic 4 — Input validation and error handling

Discuss how the application should respond to:
- Scores below 0 or above 100.
- Zero or negative credit hours.
- Empty course names, if course names are required.
- No courses entered.
- Exceeding the supported course limit.
- Invalid or incomplete user input.

**Decision required:** Agree on acceptable input ranges, validation responsibilities, and how errors should be communicated to the user.

## Topic 5 — Development sequence

The sequence used in Assessment 01 was:

1. Requirements and data-model decisions.
2. Backend contracts and validation.
3. Automated backend tests.
4. GTK4 course-entry interface.

Discuss:
- Are the requirements sufficiently clear?
- Have backend function contracts been agreed?
- Are the necessary backend tests in place?
- What must be completed before GUI integration begins?

# 5. Proposed Discussion Meeting Agenda

| No. | Discussion item | Suggested time |
|---:|---|---:|
| 1 | Review assessment results and individual learning gaps | 10 min |
| 2 | GPA calculation and backend function responsibilities | 15 min |
| 3 | Frontend, integration and backend architecture | 15 min |
| 4 | Course records and data structures | 10 min |
| 5 | Input validation and error handling | 10 min |
| 6 | Development sequence and next actions | 10 min |
| | **Total** | **70 min** |

The meeting should prioritize understanding and agreement rather than rushing into implementation.

# 6. Decisions and Action Items

| Item | Required outcome | Status |
|---|---|---|
| GPA calculation workflow | Shared understanding of calculation sequence | To discuss |
| Backend function contracts | Agreed inputs, outputs and responsibilities | To discuss |
| Integration layer | Agreed role and interface/backend data flow | To discuss |
| Course data structure | Agreed fields and structure | To discuss |
| Input validation | Agreed accepted ranges and error behavior | To discuss |
| Backend testing | Identified tests and expected behavior | To discuss |
| GTK4 integration | Clear prerequisites before UI implementation | To discuss |

## Meeting decision record

| Decision | Agreed outcome | Responsible person | Target date |
|---|---|---|---|
| | | | |
| | | | |
| | | | |
| | | | |

# 7. Task-Readiness Considerations

| Contributor | Current evidence | Recommended next step |
|---|---|---|
| Comfort | Developing understanding; gaps in GPA calculations, backend concepts and architecture | Targeted foundational teaching before an independent implementation task |
| Jormo | Strong demonstrated understanding; limited gaps in conversion functions and architecture | Guided technical assignment, with practical verification where necessary |

Neither assessment result independently establishes practical implementation or integration ability.

Any practical exercise should be short, focused, and introduced only where useful to verify a particular concept. The coordinator retains final authority over task allocation.

# 8. Closing Discussion

Before assigning the next development tasks, the team should be able to explain, in its own words:

1. How the ATU semester GPA is calculated.
2. What each major backend function does.
3. How a course record is represented.
4. How GTK4 communicates with the C backend.
5. Why the backend must remain independently testable.
6. Which requirements and technical decisions must be agreed upon before implementation proceeds.

**Expected outcome:** A shared technical understanding, resolved architectural questions, documented decisions, and clear next steps for each contributor.

---

**GKGDev Core 5 — Project Discussion and Assessment Review**

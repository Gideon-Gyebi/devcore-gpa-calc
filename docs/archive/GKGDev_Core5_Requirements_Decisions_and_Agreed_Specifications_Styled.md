# GKGDev Core 5 — Requirements, Decisions and Agreed Specifications

*Formal project reference derived from the team discussion and accepted requirements*

**Project:** ATU GPA Calculator “C” Project  
**Team:** GKGDev Core 5  
**Institution:** Accra Technical University

## Document control

| Item | Description |
|---|---|
| Source basis | Requirements and Data Model Team Discussion, Version 2; team meeting dictations; project overview, governance plan, architecture note and MVP checklist |
| Purpose | Record agreed direction, accepted proposals, justified inferences, open matters, diagrams and implementation sequence |
| Status convention | **AGREED** = explicitly accepted; **INFERRED** = carried forward from an accepted proposal or established requirement; **OPEN** = not confirmed or awaiting action |

## 1. Project purpose and established foundations

The project is a desktop semester GPA calculator for Accra Technical University (ATU), implemented in C with a GTK4 graphical interface. The current CLI implementation and its calculation work form the foundation for the GUI; the team is not restarting the calculation engine.

- **MVP:** semester GPA using the established ATU grading scale.
- Preserve and reuse the CLI backend and existing tests where practical.
- GTK4 owns data entry, interaction and presentation.
- An application/integration layer coordinates values and results between GTK4 and C calculation functions.
- Terminal-oriented input functions must not be called from GTK callbacks.
- Persistent storage, CGPA, export and analytics remain Phase 2 or later unless scope is formally changed.

**AGREED:** Carry forward the existing MVP scope, grading approach, calculation foundation and layered architecture. Do not reopen settled foundations without a concrete reason.

## 2. Course-result data model

The team reviewed the proposed course-result model and the questions in Sections 2.1–2.6. The starting recommendations in the discussion document are carried forward wherever the team did not dictate a different decision. Therefore, the outcomes below are recorded as **AGREED** where explicitly stated and **INFERRED** where the accepted starting recommendation supplies the decision. No Section 2 item is left open.

### 2.1 Why we need to decide this

**AGREED / CARRIED FORWARD:** The current `GpaRecord` stores only `creditHour` and `gradePoint`. That is sufficient for accumulating totals, but it does not retain all information required to display a complete per-course result in GTK4.

For the MVP, the application retains the input and calculated result for every course during the active calculation session. A course-result structure is therefore required to represent one completed course calculation.

### 2.2 Proposed course-result structure

**INFERRED FROM THE ACCEPTED STARTING RECOMMENDATION:** Use the more descriptive name `CourseResult`, because the structure represents one course and its calculated result, not the semester GPA itself. Retain the fixed-size course collection and the proposed course fields, applying the field-representation decisions described below.

```c
#define MAX_COURSES 15
#define COURSE_NAME_LENGTH 100

typedef enum {
    GRADE_A_PLUS,
    GRADE_A,
    GRADE_B_PLUS,
    GRADE_B,
    GRADE_C_PLUS,
    GRADE_C,
    GRADE_D_PLUS,
    GRADE_D,
    GRADE_E
} LetterGrade;

typedef struct {
    char courseName[COURSE_NAME_LENGTH];
    int score;
    LetterGrade letterGrade;
    float gradeValue;
    float creditHour;
    float gradePoint;
} CourseResult;
```

**Implementation note:** The enum members above illustrate the enum representation. The exact enumerator names and complete grade mapping must match the already-established ATU grading scale; this document does not redefine the grade bands or GPA formula.

### 2.3 What each field represents

| Field | Agreed / inferred meaning |
|---|---|
| `courseName` | Fixed-size character array identifying the course in the results table. The source proposal uses 100 characters; retain safe input handling and prevent overflow. |
| `score` | Integer score entered for the course, consistent with the existing CLI input rules. |
| `letterGrade` | Calculated grade represented internally as an enum; convert it to display text for GTK. |
| `gradeValue` | Numerical value assigned to the letter grade, using the existing calculation types/signatures unless a demonstrated technical issue requires a change. |
| `creditHour` | Course credit hours. Retain the existing floating-point representation for compatibility with the current backend and input rules. |
| `gradePoint` | Weighted grade points for the course. Keep the existing field name for compatibility; it represents the course contribution used in semester totals. |

### 2.4 Decisions to make — recorded outcomes

| Decision | Recorded outcome | Status |
|---|---|---|
| Structure name | Use `CourseResult`, since the structure represents one course and its calculated result. | **INFERRED — accepted starting recommendation** |
| Course-name storage | Use a fixed-size character array for the MVP, with a 100-character buffer as shown in the proposal and safe input handling. | **INFERRED — accepted starting recommendation** |
| Letter-grade representation | Use an enum internally where it makes comparison and validation clearer; convert the enum to display text for GTK. | **INFERRED — accepted starting recommendation** |
| Numeric types | Keep types consistent with the agreed input rules and existing backend signatures; avoid changing working functions without a clear reason. Use `int` for score and retain the proposed floating-point calculation fields. | **INFERRED — accepted starting recommendation** |
| Course limit | Retain the existing `MAX_COURSES` limit of 15. | **AGREED / carried forward** |
| Storage during calculation | Use a fixed-size array because the course limit remains fixed for the MVP. | **INFERRED — accepted starting recommendation** |
| Semester summary | Derive total credit hours, total weighted grade points and semester GPA from the course results; use a clear summary result for the integration/UI contract and avoid duplicate stored values without a reason. | **INFERRED — accepted starting recommendation** |

### 2.5 One-course data flow

The team carried forward the proposed data flow from course entry through validation and calculation to the completed course result and GTK display.

```text
COURSE INPUT
Course name + score + credit hours
             |
             v
      VALIDATE UI INPUT
             |
             v
   EXISTING CALCULATION LOGIC
       |          |          |
       v          v          v
   Letter      Grade       Weighted
   grade       value       grade points
       \          |          /
        \         |         /
         v        v        v
       BUILD COMPLETE COURSE RESULT
                    |
                    v
        STORE RESULT FOR ACTIVE SESSION
                    |
                    v
          DISPLAY COURSE IN GTK TABLE
```

Semester totals and GPA are calculated from the course-result collection and returned as a clear summary for presentation.

### 2.6 Questions the team should settle — recorded outcomes

| Question | Recorded outcome |
|---|---|
| What is the final structure name? | `CourseResult`. |
| Which fields must be stored, and which can be derived? | Retain the course input and per-course result fields in the active-session record so the results table can be populated. Derive semester totals and GPA from the course collection rather than storing duplicate summary values without a reason. |
| What types should each field use? | Follow the proposed field types and keep consistency with existing backend signatures: integer score; fixed-size character storage for course name; enum for letter grade; existing floating-point calculation fields. |
| What is the course-name length limit? | Use the proposed 100-character fixed-size buffer with safe input handling. |
| Enum, text or both for letter grade? | Enum internally, with a conversion to display text for GTK. |
| Retain the fixed-size course array? | Yes. Retain `MAX_COURSES = 15` and a fixed-size collection for the MVP. |
| How should semester totals and GPA be represented and returned? | Return a clear semester-summary result containing total credit hours, total weighted grade points and semester GPA, derived from the course records. |
| Where should validation errors be represented? | Use explicit status/error reporting in the application/integration contract. The GUI decides how to present the error; the calculation backend does not print UI messages. |

**Section 2 outcome:** The course-result model and its data-flow direction are treated as settled for the project specification. The exact implementation declarations should remain consistent with the existing backend and the ATU grading scale; this is not an invitation to reopen the agreed grading bands or GPA formula.

## 3. Backend function contracts and integration

**AGREED:** The team accepted the three-layer architecture and the architecture diagram as presented.

```text
GTK4 FRONTEND
  Forms, widgets, course entry, actions and result presentation
          |
          v
APPLICATION / INTEGRATION LAYER
  Receive values, validate/coordinate calls, prepare result data
          |
          v
C CALCULATION BACKEND
  Grade conversion, weighted points, totals and semester GPA
```

- GTK calls a small application/integration function rather than coordinating multiple backend calls directly.
- Integration receives the simplest suitable input representation compatible with the approved course-result model and backend.
- Integration returns structured results GTK can display without repeating GPA calculations.
- Status/error reporting is explicit. GUI presents user-facing messages; backend does not print UI messages.
- Preserve existing backend functions where practical; add a wrapper/integration API where needed.

**INFERRED:** The calculation engine remains independently testable without launching GTK; GTK-specific code must not leak into calculation functions.

## 4. GTK4 interface requirements

### 4.1 Main-window navigation

**AGREED:** Option B — separate pages or tabs — was selected. Single-page and two-pane options were rejected.

- After course entry and Calculate, the application automatically switches to the results page.
- Users may still switch between pages manually at any time.

### 4.2 Course entry

- User may specify an initial course count; corresponding rows appear.
- **Add Course** adds one row at a time.
- Each row has its own remove control.
- Enforce the existing agreed maximum course limit.
- Each row contains course name, score and credit hours; field order may be chosen for usability.

### 4.3 Actions and recalculation state

- **Calculate** is an explicit user action.
- No separate **Edit Course** button is required; users return to the course-entry page and edit fields directly.
- After successful calculation, **Recalculate** is disabled. Any subsequent input change enables it; clicking it disables it again until another change.
- **Reset** replaces Clear and requires confirmation. Confirming Reset clears course entries and displayed results.

### 4.4 Results and GPA summary

- Results table: course name, score, letter grade, grade value, credit hours and weighted grade points.
- Semester summary: total credit hours, total weighted grade points and GPA.
- Summary appears below the results table.
- A **third dedicated summary page is agreed**. It contains the GPA summary prominently, in bold and colour-coded by classification.
- Users can reach the summary by scrolling below the results table or switching directly to the third page.
- GPA must be visually prominent.

**Agreed page model**

```text
Page 1 — Course Entry
  Course rows • Add Course • per-row Remove • Calculate • Reset

Page 2 — Results
  Per-course results table
  Semester totals and summary below the table

Page 3 — GPA Summary
  Prominent GPA and classification colour treatment

Calculate automatically opens Page 2.
Manual navigation between pages remains available.
```

### 4.5 Validation and feedback

- Inline validation feedback is the preferred approach to implement and evaluate.
- Preserve entered values when validation fails so users can correct the problem.

### 4.6 Window and usability

- Main window is resizable and has a minimum size.
- If the results table is wider than the window, retain column sizes and provide horizontal scrolling rather than compressing columns.
- Results area is not hidden until the first successful calculation.
- Show welcome/instruction message on first launch. After acknowledgement it should not automatically reappear; a Help button remains available.
- When no course has been entered, show the specified **“No Course”** message at the bottom.
- When maximum course count is reached, show a message and enforce the limit.

**OPEN:** Whether Reset should cause the first-launch welcome message to reappear was not confirmed.

### 4.7 User flow and wireframe

- Distinguish UI buttons/actions from functions in the user-flow description.
- Do not ambiguously label CALCULATE, RECALCULATE or RESET as functions.
- Remove the separate Edit action from the end of the flow.
- Represent Recalculate and Reset as distinct buttons/actions.
- Prepare a wireframe for the user-flow UI. This is a required deliverable and is also listed in implementation work.

## 5. Testing strategy

**AGREED:** Section 5.1 was introductory context. All proposed Section 5.2 GUI/integration test areas and example checks were accepted. Additional checks may be added during development if new vulnerabilities or risks are identified.

- Existing backend tests protect grade conversion, weighted points, totals and GPA.
- New GUI/integration tests cover widgets, user actions, data flow, display updates, validation and error propagation.
- Manual GUI testing with a documented checklist is required during early UI development and for visual/usability checks.
- Automated integration-function tests should be used where possible without launching GTK.
- Automated GTK tests should be considered where practical, but setup must not delay the first working interface.
- End-to-end acceptance checklist is required before MVP release.

```text
EXISTING BACKEND TESTS
Grade conversion • Weighted points • Totals • GPA
          |
          v
Protect calculation logic

NEW GUI / INTEGRATION TESTS
Widgets • User actions • Data flow • Display • Errors
          |
          v
Protect application behaviour
          |
          v
END-TO-END MVP ACCEPTANCE
```

## 6. Workstream responsibilities and shared ownership

**AGREED:** Work is divided by responsibility area, with a lead, supporting members and shared review. The lead coordinates and tracks completion but does not carry the entire workload.

| Workstream | Lead focus | Supporting contribution / outputs |
|---|---|---|
| Data model and API design | Coordinate course-result structure and data exchanged between layers | Review field types, naming, memory approach and function contracts; approved structure and summary representation |
| Backend adaptation | Identify minimal changes or wrappers to expose backend to GUI | Review existing functions, implement focused changes, preserve behaviour and update tests where needed |
| GTK4 frontend | Coordinate main window, layout, widgets and interaction design | Implement UI components; main window, course-entry rows, actions, results table and GPA summary |
| Application integration | Coordinate data flow between GTK widgets and calculation backend | Value collection, conversion, result handling and error propagation |
| Testing and quality assurance | Maintain test plan and track GUI workflow verification | Test cases, manual checks, automation, defect reproduction/retesting and reports |
| Documentation and release readiness | Keep technical documentation and build/run instructions aligned | Architecture/data-model notes, GUI usage notes, README/setup updates and MVP completion checklist |

### 6.3 Assignment and scheduling rule

- Assignment sheet remains open because one member was absent; names can be entered when assignments are made.
- Do not assign all workstreams at once. Assign roles for one workstream, complete it, then allocate the next.
- If two workstreams can reasonably proceed simultaneously, roles may be assigned to both.
- Staged allocation avoids scheduling and availability problems caused by committing to every workstream too early.

**AGREED:** Place this scheduling rule before the assignment table in Section 6.3.

### 6.4 Task ownership and reporting

- Every task needs a clear owner; identify a supporting reviewer where useful.
- Workstream leads report progress and blockers during team check-ins.

## 7. Decision, research and action tracking

The decision/action log consolidates decisions and follow-up questions. Each item should have a status, decision or research question, owner and review date.

| Status | Meaning | Next action |
|---|---|---|
| **AGREED** | Team accepts an option or documented variation | Record exact decision and use it during implementation |
| **RESEARCH** | More evidence is needed before choosing | Assign research owner, define question and agree when findings will be presented |
| **DEFERRED** | Topic is not required to proceed or is outside MVP | Record when or under what condition it should be revisited |

**AGREED:** The decision/action log is the consolidated record for decisions and notes captured across the discussion.

## 8. Meeting outputs and unresolved questions

Expected outputs include an approved data model, integration contract, GTK4 interface direction, wireframe, GUI/integration test plan, workstream assignments and decision/research log.

The team specifically identified item 7 — unresolved questions in the decision/research log — as requiring attention. Unresolved questions must have an owner and review date.

## 9. Agreed implementation sequence

1. Finalise and document the course-result data model.
2. Agree and document the GUI-facing backend/integration contract.
3. Produce and approve the GTK4 wireframe or screen sketch.
4. Begin GTK4 course-entry interface development.
5. Implement the integration layer and connect the existing backend. This may proceed alongside independent UI work where practical.
6. Implement the results table and GPA summary.
7. Run GUI, integration and end-to-end tests.
8. Update README, setup instructions and project documentation.

## 10. Accepted and updated diagrams

### 10.1 Accepted architecture

```text
GTK4 FRONTEND
Forms • Widgets • Course entry • Actions • Results
       | UI values / results
       v
APPLICATION / INTEGRATION LAYER
Validation • Coordination • Structured result preparation
       | function calls
       v
C CALCULATION BACKEND
Grade conversion • Weighted points • Totals • GPA
```

The team accepted the three-layer architecture. Future storage remains outside MVP.

### 10.2 Updated three-page interface

```text
[PAGE 1: COURSE ENTRY]
Course rows + Add Course + per-row Remove + Calculate + Reset
                     |
              Calculate clicked
                     v
[PAGE 2: RESULTS]
Results table + semester totals below table
                     |
        Scroll down OR navigate manually
                     v
[PAGE 3: GPA SUMMARY]
Prominent GPA + colour-coded classification

Manual navigation between pages remains available.
```

### 10.3 Accepted testing flow

```text
EXISTING BACKEND TESTS -> protect calculation logic
NEW GUI / INTEGRATION TESTS -> protect application behaviour
                 |
                 v
        END-TO-END MVP ACCEPTANCE
```

### 10.4 Updated workstream allocation

```text
Assign Workstream 1 -> complete / review
          |
          v
Assign next workstream
(or assign two together only when they can proceed in parallel)
          |
          v
Continue staged allocation; keep unassigned slots open.
```

## 11. Open matters and implementation cautions

The only outstanding assignment matter recorded from the meeting is in **Section 6.3**:

- The workstream assignment sheet remains open because one member was absent.
- Lead and supporting-member names can be entered when the team makes the assignments.
- Allocate workstream responsibilities progressively: one workstream at a time, or two together only when they can be handled simultaneously.

All other sections, including Section 2, are recorded as agreed or inferred from the accepted starting recommendations. They are not marked open.

Implementation should preserve the established ATU grading scale, GPA formula, tested backend behaviour and MVP scope. If a concrete technical defect is found, document it with evidence rather than reopening settled decisions by default.

*This document records team direction. It does not claim that implementation tasks have already been completed or that the illustrative code structure is approved.*

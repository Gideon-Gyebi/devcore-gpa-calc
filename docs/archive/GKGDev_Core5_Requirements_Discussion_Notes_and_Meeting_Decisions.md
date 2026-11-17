# GKGDev Core 5 — Requirements Discussion Notes and Meeting Decisions

*Section-by-section record of the team's discussion, dictated notes and outcomes*

**Project:** ATU GPA Calculator “C” Project  
**Team:** GKGDev Core 5  
**Institution:** Accra Technical University

## Document purpose and reading guide

This document preserves the team's meeting notes for colleague review or use as context for another AI. It records what was discussed and agreed, rather than converting every proposal into a new requirement.

- **AGREED** means the user explicitly reported that the team accepted the item.
- **ACCEPTED PROPOSAL** means the team adopted the starting recommendation or proposed direction.
- **INFERRED** means the decision follows from the accepted direction but was not separately stated.
- **OPEN** means the team left the item unassigned or unresolved.
- Where the exact Section 2 dictation is not available in the retained record, the limitation is marked rather than inventing notes.

## 1. Meeting context

The team used *Requirements and Data Model Team Discussion, Version 2* as the agenda and reference. The discussion carried forward the established semester-GPA MVP, ATU grading scale, existing CLI calculation backend and GTK4 direction. The purpose was to settle the remaining data-model, integration, interface, testing and team-work arrangements.

## 2. Course-result data model

The meeting covered Sections 2.1–2.5 before moving to Section 3. The retained meeting summary confirms that the user supplied notes for Sections 2.1–2.5 and that some matters had previously been listed for revisit. However, the exact dictated notes and final choices for each Section 2 question are not present in the accessible retained record.

| Discussion point | Available meeting record |
|---|---|
| 2.1 — Why a course-result model is needed | Introductory rationale: existing record holds only aggregate credit-hour and grade-point values; GUI requires complete per-course result information. |
| 2.2 — Proposed structure | Source presented illustrative `GpaRecord` with `courseName`, `score`, `letterGrade`, `gradeValue`, `creditHour` and `gradePoint`. Proposal, not automatically approved schema. |
| 2.3 — Field meanings | Team reviewed field purposes and possible choices. Exact dictated outcomes are not recoverable here. |
| 2.4 — Decisions to make | Prior summary records structure name as settled; stored/derived fields and letter-grade representation had been revisit items; fixed-size course array was recorded as retained; semester summary was to be represented in table form. Exact final choices/types are not fully available. |
| 2.5 — One-course data flow | Source flow: course name, score and credit hours → validation/calculation → complete course result → session storage → GTK table. Exact meeting amendments are not recoverable. |

**Record limitation:** Do not treat the illustrative code in the source discussion as the final approved structure. Reconcile exact Section 2 choices against the team's original dictated notes before implementation.

## 3. Backend function contracts and integration

### 3.1 Architecture

The team agreed with the architecture diagram as presented. The diagram was considered complete and to contain everything needed in the contract.

```text
GTK4 FRONTEND
     |
     v
APPLICATION / INTEGRATION LAYER
     |
     v
C CALCULATION BACKEND
```

### 3.2 Five integration points

The user reported that the team accepted all five proposed points:

1. GTK calls a small application/integration function instead of coordinating multiple backend calls directly.
2. Integration receives the simplest suitable input representation compatible with the approved course-result model and backend.
3. Integration returns structured results GTK can display without repeating GPA calculations.
4. Status/error reporting is explicit; GUI presents errors and backend does not print UI messages.
5. Preserve existing functions where practical and add a wrapper/integration API for a clean GUI-facing contract.

### 3.3 Contract review checklist

The checklist was reviewed briefly. The user reported no additional notes because everything was clear and understood.

**Outcome:** Section 3 was recorded as agreed.

## 4. GTK4 interface requirements

### 4.1 Main window layout

- Chose **Option B: separate pages or tabs**.
- Rejected Option A (single-page) and Option C (two-pane).
- After course details are entered and Calculate is clicked, the application automatically switches to the results page.
- Users can still switch between pages manually.

### 4.2 Course-entry interaction

- User enters the number of courses initially; corresponding rows appear.
- Add Course adds rows one at a time.
- Each row has its own remove button.
- Enforce the existing agreed maximum course count.
- Each row contains course name, score and credit hours; field order is flexible.

### 4.3 Calculation and editing actions

- Calculate is an explicit button.
- Add Course adds another row; Remove Course removes a specific row.
- A separate Edit Course button/action is not needed. The user returns to the course-entry page and edits existing fields.
- After successful calculation, Recalculate is disabled/greyed out.
- When any input changes after calculation, Recalculate becomes enabled.
- After Recalculate is clicked, it becomes disabled again until another change.
- This state indicates whether edits remain uncalculated.
- Use Reset instead of Clear. Reset requires confirmation.
- On confirmation, Reset clears form entries and the results table/fields.

### 4.4 Results presentation

- The team agreed with everything in Section 4.4.
- Results table: course name, score, letter grade, grade value, credit hours and weighted grade points.
- Semester summary: total credit hours, total weighted grade points and GPA.
- Summary appears below the results table.
- **A third page is agreed, not undecided.** Initial design was two pages: course entry on Page 1; results table with summary below on Page 2.
- Because a long results table could push the GPA summary below the visible area, a third dedicated summary page was added.
- Third page contains only the GPA summary, prominently displayed in bold and colour-coded by classification (for example, First Class and Second Class Upper).
- User may scroll below the table or switch directly to the third page.
- GPA itself should be visually prominent.

### 4.5 Validation and feedback

Inline feedback was the preferred approach to implement/try. Preserve user entries when validation fails.

### 4.6 Window and usability behaviour

1. Window should be resizable.
2. Enforce a minimum window size.
3. If results table is wider than window, retain column sizes and allow horizontal scrolling; do not compress text into cramped columns.
4. Results area should not remain hidden until first successful calculation.
5. Show welcome/instruction message on first launch. After acknowledgement, it should not automatically appear again. A Help button remains available to reopen instructions. Reset might bring it back, but this was not confirmed.
6. When no course has been entered, display a **“No Course”** message at the bottom.
7. When maximum course count is reached, display a message and enforce the limit.

### 4.7 Proposed user flow

- Clearly distinguish buttons/actions from functions.
- Avoid ambiguous capitalised labels such as CALCULATE with a bracket label that could make it look like a function.
- Remove “Edit” from the end of the flow.
- Represent Recalculate and Reset as separate buttons/actions, explicitly identified as actions rather than functions.
- Prepare a wireframe for the user-flow UI. This is a required deliverable and is also on the Section 8 implementation list.

**Outcome:** Section 4 was fully recorded as agreed, with welcome-message-after-Reset behaviour left unconfirmed.

## 5. Testing

### 5.1 Existing test coverage

The user described 5.1 as introductory. The discussion began at 5.2.

### 5.2 GUI and integration test coverage

The team agreed with all example checks and test areas in the document. Further checks may be added during development if a vulnerability or uncovered risk is identified.

### 5.3 How existing and new tests fit together

The team agreed with the displayed flow: existing backend tests protect calculation logic; new GUI/integration tests protect widgets, user actions, data flow, display and errors; both contribute to end-to-end MVP acceptance.

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

### 5.4 Testing approach

The team agreed with the starting recommendation and everything presented in 5.4, and intended to implement it:

- Manual GUI testing with a checklist.
- Automated integration-function tests without GTK where practical.
- Automated GTK tests where practical, without delaying the first working interface.
- End-to-end acceptance checks before MVP release.

**Outcome:** Section 5 was recorded as agreed.

## 6. Workstream responsibilities and shared ownership

### 6.1 How work is organised

The team accepted the introductory rules and proposed organisation.

### 6.2 Proposed workstreams

The team agreed with all workstreams, the lead and supporting-member roles, and the example task/deliverable descriptions. Everything was clear.

### 6.3 Suggested assignment sheet

- One member was absent, so the assignment sheet was left open.
- Names can be entered into lead and supporting-member fields when assignments are made.
- The team decided not to assign roles for every workstream at once.
- Assign roles for one workstream, then assign a new workstream's roles/responsibilities after completing the previous one.
- If two workstreams can be handled simultaneously, roles may be assigned for both.
- The reason is to avoid scheduling problems and overcommitting when future availability is uncertain.
- Place this staged-allocation note in Section 6.3 before the assignment table.

### 6.4 How tasks should be shared

- Tasks need clear ownership.
- Progress and blockers must be reported.
- The workstream lead reports progress and blockers during team check-ins.

**Outcome:** Section 6 was recorded. Individual role assignments remain open.

## 7. Decision, research and action tracking

The team reviewed this section and the decision/action log table. The log is intended to collect answers and notes recorded across the sections.

- The log records topic, status, decision/research question, owner and review date.
- Source statuses: **AGREED, RESEARCH and DEFERRED**.

## 8. What should we leave this meeting with?

The team reviewed the expected meeting outputs. The user identified item 7 — the decision and research log — as needing attention: unresolved questions should be reviewed and/or assigned an owner.

## 9. What happens after this discussion?

The team reviewed and accepted the proposed order of activities as the sequence to follow. The source allows some work to happen in parallel once dependencies are clear.

1. Finalise and document the course-result data model.
2. Agree and document the GUI-facing backend/integration contract.
3. Produce and approve the GTK4 wireframe or screen sketch.
4. Begin GTK4 course-entry interface development.
5. Implement the integration layer and connect the existing backend.
6. Implement results table and GPA summary.
7. Run GUI, integration and end-to-end tests.
8. Update README, setup instructions and project documentation.

## 10. Consolidated follow-up points

| Follow-up | Status / note |
|---|---|
| Section 2 exact data-model choices | Reconcile exact field/type/representation choices from original team dictation before implementation; do not infer missing details |
| GTK4 user-flow wireframe | Required deliverable |
| Welcome message after Reset | Not confirmed |
| Workstream assignments | Assignment sheet remains open because one member was absent |
| Unresolved questions | Each should have an owner and review date |
| Implementation sequence | Follow Section 9; parallelise only where dependencies permit |

*End of meeting notes. The formal decisions/specifications document is the project-direction reference; this document supports it with the discussion record and reported outcomes.*

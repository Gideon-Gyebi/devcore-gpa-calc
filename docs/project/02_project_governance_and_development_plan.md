# GPA Calculator — Project Understanding, Roadmap and Working Agreement

> Project: GKGDev Core 5 — ATU GPA Calculator  
> Repository: Gideon-Gyebi/devcore-gpa-calc  
> Working reference: `gideon` branch; repository default branch is `main`.  
> Role: Team direction and governing agreement.

## 1. Updated project understanding

The team is building a desktop GPA Calculator in C with a GTK4 graphical interface. The first release calculates **semester GPA only**, using the ATU grading scale. The goal is to ship a functional and testable MVP rather than delaying delivery for CGPA, persistence or analytics.

### MVP user journey
1. Open the application.
2. Enter course name, score and credit hours for each course.
3. Calculate letter grade, grade value and weighted grade points.
4. View each course's result in a table.
5. View total credit hours, total weighted grade points and semester GPA.
6. Correct inputs and calculate again.

| MVP scope | Deferred |
|---|---|
| Semester GPA | CGPA |
| ATU grading scale | Multiple grading systems |
| Course names, scores, credit hours | Student accounts |
| Per-course results | Cloud sync |
| Semester totals and GPA | Database history |
| GTK4 desktop interface | Web/mobile app |
| Validation and tests | Analytics suite |

## 2. Project development roadmap

### Phase 1 — Semester GPA MVP

| Workstream | Expected outcome |
|---|---|
| Backend stabilization | Clear contracts and reliable validation |
| Course record model | Retain all fields needed by the UI |
| GTK4 interface | Course form and actions |
| Results presentation | Per-course table and semester summary |
| Integration | GUI calls the C backend |
| Testing | Unit and end-to-end acceptance checks |
| Documentation | README/setup match the delivered app |

**MVP completion criteria**
- Every valid score maps to the correct ATU grade.
- Invalid score, credit-hour and course-count inputs are handled clearly.
- Weighted points and GPA are correct.
- UI displays all course results and semester totals.
- Backend can be tested independently of GTK4.
- Teammates can follow setup instructions to build and run the app.

### Phase 2 — Records and CGPA

After the MVP is stable: save semester results, retrieve past semesters, calculate CGPA, export results and allow deliberate clearing of stored records. Storage (JSON/file/database) remains an open decision.

### Phase 3 — Extended features

Potential reporting, analytics, usability enhancements and broader platform support. These are not MVP commitments.

## 3. Frontend and backend architecture

```text
+--------------------------------------+
| GTK4 FRONTEND                        |
| Course form • Add/remove • Calculate |
| Results table • GPA summary          |
+-------------------+------------------+
                    | validated values
                    v
+--------------------------------------+
| APPLICATION / INTEGRATION LAYER      |
| Validate • Call backend • Build data |
+-------------------+------------------+
                    | function calls
                    v
+--------------------------------------+
| C GPA CALCULATION BACKEND            |
| Score->grade • Grade value           |
| Weighted points • Totals • GPA       |
+-------------------+------------------+
                    v
+--------------------------------------+
| FUTURE STORAGE — PHASE 2             |
| Semester records / export / CGPA     |
+--------------------------------------+
```

| Layer | Owns | Should not own |
|---|---|---|
| GTK4 frontend | Widgets, interaction and display | GPA formulas or terminal `scanf()` input |
| Integration | Pass validated UI values to backend; coordinate results | GTK-specific code inside calculation functions |
| C backend | Grade mapping, weighted points, totals and GPA | GTK widgets or window state |
| Future storage | Persist and retrieve semester records | MVP calculation rules |

**Important rule:** Existing `get*()` functions are terminal-oriented. GTK uses its own widgets to collect inputs and then calls the calculation functions. Do not call `getnumcrs()`, `getcrs()`, `getch()` or `getscr()` from the GTK flow.

## 4. Course records — one important concept

The current `GpaRecord` stores only `creditHour` and `gradePoint`. That is enough for totals but insufficient for a course-results table. The MVP should retain complete course results in memory for the active calculation session.

Illustrative proposal:

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

This is a proposal, not an approved schema or a repository change. Agree on course-name limits, numeric types, letter-grade representation, error handling, array limit and naming before implementing.

### One-course data flow

```text
Course name + score + credit hours
                 |
              Validate
                 |
       scrconv(score) -> grade
                 |
       lgconv(grade) -> grade value
                 |
   gpcalc(value, hours) -> points
                 |
       Save complete course record
                 |
        Display row in GTK table
```

For MVP, in-memory storage is enough. Persistent storage is a Phase 2 decision.

## 5. Updated assessment and priorities

| Area | Assessment from inspected snapshot | Priority |
|---|---|---|
| Grade conversion | Modular functions exist | Verify boundaries |
| Weighted points | Function exists | Verify formula and validation |
| Semester GPA | Present in CLI | Test invalid totals |
| Course record | Stores only two aggregate fields | Extend after agreement |
| CLI input | Terminal-oriented | Keep out of GTK flow |
| GTK4 UI | `ui/gui.c` was empty | Build MVP UI |
| Tests | Several files exist | Review and run |
| README/setup | README is stale | Update after integration |
| CGPA/storage | Future direction | Defer |

### Engineering priorities
1. Agree on accepted score, credit-hour and course-count ranges and error behaviour.
2. Stabilize backend validation and unambiguous error handling.
3. Agree on complete course-result data structure.
4. Test grade boundaries, invalid values, weighted points, totals and GPA.
5. Implement GTK4 course-entry interface.
6. Implement results table and GPA summary.
7. Integrate and verify the complete application.
8. Update README and build instructions.

Static-review notes to recheck against current source include the `GPA.h`/`gpa.h` case mismatch, test helper return type mismatch, zero-length test array and input-failure handling. These are observations, not confirmed runtime failures.

## 6. Development working agreement

1. **Preserve existing code:** no unnecessary rewrites; make focused changes.
2. **Explain before implementing:** teach the concept, purpose and trade-offs.
3. **Research before recommending:** use current documentation for GTK4, Windows/MSYS2, compiler and build decisions.
4. **Debug collaboratively:** identify root cause and explain the fix.
5. **Respect team decisions:** do not silently change scope, architecture or data model.
6. **Avoid over-engineering:** deliver semester GPA MVP first.
7. **Keep backend independent:** GTK4 handles input/presentation; C handles calculation.
8. **No repository writes without explicit instruction:** describe proposed writes before making them.
9. **Use `gideon` as working reference unless directed otherwise:** default branch is `main`.
10. **Reassess after commits:** refresh findings when substantial code is pushed.

## 7. Suggested next steps

### First team alignment session
- Confirm MVP feature list and acceptance criteria.
- Confirm maximum courses and credit-hour rules.
- Agree on course-record structure.
- Agree on backend function contracts and error conventions.
- Confirm GTK4 screen layout and results fields.
- Assign owners for backend, tests, UI and integration.

### Implementation sequence

```text
[1] Requirements + data model
             |
[2] Backend contracts + validation
             |
[3] Automated backend tests
             |
[4] GTK4 course-entry interface
             |
[5] Results table + GPA summary
             |
[6] UI/backend integration
             |
[7] Full MVP test + README update
             |
          MVP RELEASE
             |
     Phase 2: CGPA / storage
```

**Definition of done:** A teammate can build and launch the app using documented steps, enter a realistic semester's courses, calculate GPA, inspect every course result, and reproduce the result using the ATU grading scale. Invalid input is handled clearly and the backend remains independently testable.

---
**Governance note:** This document records the team's current understanding. Discuss and agree on scope or architecture changes, then update this document so it remains a reliable source of truth.

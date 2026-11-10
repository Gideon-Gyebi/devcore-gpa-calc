# GKGDev Core 5 --- Requirements and Data Model Discussion

**Project:** ATU GPA Calculator "C" Project\
**Team:** GKGDev Core 5\
**Document:** Team discussion draft --- Version 2\
**Purpose:** Settle the remaining design decisions required to move from
the tested CLI backend to the GTK4 desktop application.

------------------------------------------------------------------------

## 1. Purpose of this discussion

The project already has an agreed MVP scope, an established ATU grading
scale and calculation approach, and a working command-line
implementation with tests. Those decisions and completed work are
recorded in the project governance and repository documentation.

**This meeting is not intended to restart those discussions.** It is
intended to decide how the existing calculation work will support the
graphical application, what information each course record must retain,
what the GTK4 interface should look like, how the interface will be
tested, and how the team will share the work.

### Existing foundations we are carrying forward

-   The MVP is a semester GPA calculator using the ATU grading scale.
-   The CLI backend already implements the core calculation flow and has
    associated tests.
-   The grading scale and GPA calculation approach have already been
    researched and documented.
-   The application is intended to use a GTK4 frontend, an
    application/integration layer and an independent C calculation
    backend.
-   The terminal-oriented input functions are not to be called from GTK
    callbacks.
-   Persistent storage, CGPA and other Phase 2 features remain outside
    the MVP unless the team formally changes the scope.

> **Meeting principle:** Preserve completed work. Revisit an existing
> decision only if a specific technical issue, test result or new
> requirement gives us a reason to do so.

------------------------------------------------------------------------

## 2. Main discussion area: Course-result data model

### 2.1 Why we need to decide this

The current `GpaRecord` structure stores only `creditHour` and
`gradePoint`. That is sufficient for accumulating totals, but it does
not retain all the information required to display a complete result for
each course in the GTK4 interface.

For the MVP, the application needs to retain the input and calculated
result for every course during the active calculation session. The team
therefore needs to agree on the structure that represents one completed
course calculation.

The governance document already contains an illustrative proposal. It is
a starting point for discussion, not an approved design.

### 2.2 Proposed course-result structure

``` c
#define MAX_COURSES 15

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

### 2.3 What each field represents

  ------------------------------------------------------------------------
  Field                   Purpose                 Discussion
  ----------------------- ----------------------- ------------------------
  `courseName`            Identifies the course   Is a fixed-size
                          in the results table.   character array
                                                  suitable? What maximum
                                                  length should we allow?

  `score`                 Retains the numerical   Should this remain an
                          score entered for the   `int`, consistent with
                          course.                 the current CLI rules?

  `letterGrade`           Retains the calculated  Should we use a
                          grade, such as A+, A or character array or an
                          B+.                     enum with a separate
                                                  display conversion?

  `gradeValue`            Retains the numerical   Should this be `float`
                          value assigned to the   or `double`?
                          letter grade.           

  `creditHour`            Retains the course's    Should this be an
                          credit hours.           integer type if only
                                                  whole credit hours are
                                                  valid, or remain
                                                  floating-point?

  `gradePoint`            Retains the weighted    Should we keep this
                          grade points for that   name, or use a more
                          course.                 explicit name such as
                                                  `weightedGradePoints`?
  ------------------------------------------------------------------------

### 2.4 Decisions to make

  -----------------------------------------------------------------------
  Decision                Possible approaches     Starting recommendation
  ----------------------- ----------------------- -----------------------
  Structure name          Keep `GpaRecord`;       Consider `CourseResult`
                          rename to               because the structure
                          `CourseResult`; choose  represents one course
                          another name.           and its calculated
                                                  result, not the
                                                  semester GPA itself.

  Course-name storage     Fixed-size character    Fixed-size array is
                          array; dynamically      simpler for the current
                          allocated string.       MVP. Agree on a limit
                                                  and safe input
                                                  handling.

  Letter-grade            Character array; enum;  Discuss an enum if it
  representation          store both enum and     makes comparisons and
                          display text.           validation clearer. A
                                                  display conversion can
                                                  provide the text shown
                                                  in GTK.

  Numeric types           Keep current types; use Choose types based on
                          integer types for       the agreed input rules
                          whole-number values and and consistency with
                          `double` for            existing backend
                          calculations.           function signatures.
                                                  Avoid changing working
                                                  functions without a
                                                  clear reason.

  Course limit            Use the existing        Retain the current
                          `MAX_COURSES`; change   limit unless the team
                          it; use dynamic         identifies a concrete
                          allocation.             need to change it.

  Storage during          Fixed-size array;       A fixed-size array is a
  calculation             dynamically allocated   straightforward MVP
                          collection.             option if the agreed
                                                  course limit remains
                                                  fixed.

  Semester summary        Calculate totals from   Prefer a clear summary
                          course records;         result if it makes the
                          maintain a separate     interface/integration
                          summary structure.      contract easier to use.
                                                  Avoid storing duplicate
                                                  values without a
                                                  reason.
  -----------------------------------------------------------------------

### 2.5 One-course data flow

``` text
Course name + score + credit hours
              |
              v
       Validate UI input
              |
              v
     Existing calculation logic
       |        |         |
       v        v         v
     Grade   Grade value  Weighted points
              |
              v
     Build complete course result
              |
              v
       Store result for session
              |
              v
      Display course in GTK table
```

### 2.6 Questions the team should settle

-   What is the final structure name?
-   Which fields must be stored, and which can be derived when needed?
-   What types should each field use?
-   What is the course-name length limit?
-   Should the letter grade be represented internally as an enum, text,
    or both?
-   Do we retain the current fixed-size course array?
-   How should the semester totals and GPA be represented and returned
    to the interface?
-   Where should validation errors be represented so that an invalid
    course is not mistaken for a successfully calculated record?

**Expected outcome:** An agreed course-result structure and a clear
decision on how a collection of course results and the semester summary
will be represented in memory. No implementation should begin from the
illustrative structure until the team approves it.

------------------------------------------------------------------------

## 3. Backend function contracts and integration

### 3.1 What is already established

The CLI implementation gives us an existing calculation backend to build
on. We are not proposing to recreate the GPA calculation logic inside
GTK or to replace the CLI workflow unnecessarily.

The architecture remains:

``` text
+------------------------------+
|         GTK4 FRONTEND        |
| Course form • Actions        |
| Results table • GPA summary  |
+---------------+--------------+
                |
                | UI values / results
                v
+------------------------------+
| APPLICATION / INTEGRATION    |
| Validate • Coordinate calls |
| Prepare result data          |
+---------------+--------------+
                |
                | Function calls
                v
+------------------------------+
|      C CALCULATION BACKEND   |
| Grade conversion             |
| Weighted points • Totals     |
| Semester GPA                 |
+------------------------------+
```

The GTK4 frontend owns presentation and interaction. The integration
layer coordinates the flow. The C backend owns the calculation logic and
remains independently testable.

### 3.2 What still needs agreement

We should review the existing function declarations and implementations,
then agree on the interface that the GTK application will use. This is a
focused contract review---not a fresh design of the calculation rules.

  -------------------------------------------------------------------------
  Discussion point        Options                 Proposed direction
  ----------------------- ----------------------- -------------------------
  How GTK accesses        GTK callbacks call      Prefer an
  calculations            several backend         application/integration
                          functions directly; GTK function so GTK callbacks
                          calls a small           do not become responsible
                          application-level       for calculation
                          function that           sequences.
                          coordinates the         
                          backend.                

  What the integration    Individual values; a    Use the simplest input
  layer receives          course-input structure; representation that works
                          a collection of course  with the approved
                          inputs.                 course-result model and
                                                  existing backend.

  What it returns         Individual output       Return structured results
                          values; a completed     that the GTK layer can
                          course result; a        display without repeating
                          collection plus         GPA calculations.
                          semester summary.       

  Error reporting         Sentinel values;        Prefer explicit
                          printed messages;       status/error reporting.
                          status codes and output The GUI should decide how
                          parameters; an error    an error is presented;
                          structure.              the backend should not
                                                  print UI messages.

  Reuse of existing       Keep existing function  Preserve working
  functions               signatures; add a       functions where
                          wrapper/integration     practical. Add a wrapper
                          API; modify functions   if it provides a clean
                          where necessary.        GUI-facing contract.
  -------------------------------------------------------------------------

### 3.3 Contract review checklist

During the discussion, inspect the current headers and relevant function
declarations and confirm:

-   Which existing functions can be reused directly.
-   Which functions are terminal-input functions and must remain outside
    the GTK flow.
-   What input each reusable calculation function expects.
-   What output it returns and how errors are identified.
-   Whether the agreed course-result structure can be populated without
    duplicating calculation logic.
-   What single function or small set of functions the integration layer
    should expose to GTK.
-   Whether any focused backend change is necessary before integration.

**Important:** Do not reopen the ATU grade bands or the GPA formula
simply as part of this review. If the existing tests or source
inspection reveal a specific defect, record that issue separately and
address it with evidence.

**Expected outcome:** A documented GUI-facing backend/integration
contract, including inputs, outputs and error behaviour, with a clear
list of any required backend changes.

------------------------------------------------------------------------

## 4. GTK4 interface requirements

This is a major new area of work. The team has not yet agreed on the
actual screen layout and interaction details, so we should use this
discussion to compare practical options before implementation.

### 4.1 Main window layout

  -----------------------------------------------------------------------
  Option            Description       Advantages        Trade-offs
  ----------------- ----------------- ----------------- -----------------
  A. Single-page    Course-entry area User can enter    Window may become
  layout            at the top and    courses and see   long when many
                    results/summary   results in one    courses are
                    below it.         place;            entered.
                                      straightforward   
                                      navigation.       

  B. Separate pages One view for      More space for    User must switch
  or tabs           course entry and  each activity;    views to review
                    another for       clearer           or correct
                    results.          separation.       entries.

  C. Two-pane       Entry area on one Input and output  Can become
  layout            side and results  remain visible    cramped on
                    on the other.     together on       smaller windows.
                                      larger screens.   
  -----------------------------------------------------------------------

**Starting recommendation:** Consider Option A first because the MVP has
a focused workflow. The team should sketch the layout and assess it
against the maximum number of courses before deciding.

### 4.2 Course-entry interaction

  -----------------------------------------------------------------------
  Decision                Possible options        Starting recommendation
  ----------------------- ----------------------- -----------------------
  Initial course rows     Display all allowed     Start with one row and
                          rows immediately; start allow the user to add
                          with one row; start     rows.
                          with a small number of  
                          rows.                   

  Add course              Add button;             Use an explicit **Add
                          automatically create a  Course** button for
                          new row after the last  predictable behaviour.
                          row is completed.       

  Remove course           Remove button on each   Provide a remove action
                          row; select a row and   on each row.
                          remove it; no removal   
                          after entry.            

  Maximum courses         Enforce the existing    Enforce the existing
                          agreed limit; allow     project limit in the
                          unlimited rows.         UI.

  Data entry style        Separate labelled       Discuss a labelled row
                          fields; editable        containing course name,
                          table/grid; hybrid form score and credit hours.
                          and rows.               
  -----------------------------------------------------------------------

### 4.3 Calculation and editing actions

Discuss which actions should be available and how they should behave:

-   **Calculate GPA:** validates the entered course information and
    requests results from the integration layer.
-   **Add Course:** adds another course-entry row, subject to the agreed
    maximum.
-   **Remove Course:** removes the selected course row.
-   **Edit Course:** allows the user to correct an entry.
-   **Recalculate:** updates the displayed results after edits.
-   **Clear/Reset:** clears the current session's entries and results.
    Decide whether confirmation is required when data has already been
    entered.

**Starting recommendation:** Keep calculation explicit through a
Calculate button. Do not recalculate automatically after every keystroke
for the first version; explicit calculation makes the interaction easier
to reason about and test.

### 4.4 Results presentation

The results view should allow a user to inspect the calculation for each
course, not merely see the final GPA.

  -----------------------------------------------------------------------
  Result column / item                Why it matters
  ----------------------------------- -----------------------------------
  Course name                         Identifies the course.

  Score                               Shows the entered score used for
                                      conversion.

  Letter grade                        Shows the grade assigned by the ATU
                                      scale.

  Grade value                         Shows the numerical value used in
                                      the calculation.

  Credit hours                        Shows the course weighting.

  Weighted grade points               Shows the contribution of that
                                      course to the GPA.
  -----------------------------------------------------------------------

The semester summary should show:

-   Total credit hours.
-   Total weighted grade points.
-   Semester GPA.

**Discussion:** Should the summary appear above the results table, below
it, or in a visually distinct summary panel? Should the GPA be the most
visually prominent result? The team should agree on a hierarchy that
makes the final GPA easy to find without hiding the course-level
details.

### 4.5 Validation and feedback in the GUI

The backend's existing validation and CLI tests remain the foundation.
The GUI introduces a different question: how should the application
communicate a problem to the user?

  -----------------------------------------------------------------------
  Option                  Description             Trade-off
  ----------------------- ----------------------- -----------------------
  General message         Show one message        Simple, but may not
                          explaining that the     tell the user where the
                          input is invalid.       problem is.

  Inline feedback         Identify the field or   More helpful, but
                          course row with the     requires more UI
                          issue.                  handling.

  Combined feedback       Show a short summary    Clearer for multiple
                          and identify the        entries, but requires a
                          affected row/field.     little more
                                                  implementation.
  -----------------------------------------------------------------------

**Starting recommendation:** Use combined feedback where practical.
Preserve the user's entries when validation fails so that corrections do
not require re-entering the entire semester.

### 4.6 Window and usability behaviour

Discuss:

-   Should the window be resizable?
-   What minimum window size keeps the form and results readable?
-   If the results table is wider than the window, should it scroll
    horizontally, or should the layout adapt?
-   Should the results area remain hidden until the first successful
    calculation?
-   Should the user see a welcome/instruction message before entering
    courses?
-   What should the application display when no courses have been
    entered?
-   How should the interface behave when the maximum course count is
    reached?

**Starting recommendation:** Use a resizable window with a sensible
minimum size, clear labels and a readable results area. Keep the first
version functional and uncluttered; visual refinements can follow once
the workflow is working.

### 4.7 Proposed user flow

``` text
        OPEN APPLICATION
               |
               v
       ENTER COURSE DETAILS
     Name • Score • Credit hours
               |
        Add / Remove rows
               |
               v
          CALCULATE
               |
               v
       VALIDATION SUCCESS?
          /         \
        No           Yes
        |             |
        v             v
 Show useful       Call integration
 feedback          and backend
        |             |
        v             v
 Correct entry    Build course results
        |          and summary
        |             |
        +----<        v
                 DISPLAY RESULTS
             Course table + GPA summary
                       |
                       v
               EDIT / RECALCULATE
                  or CLEAR
```

**Expected outcome:** An agreed screen layout, course-entry interaction,
action set, results presentation and validation-feedback approach. A
simple sketch or wireframe should be produced before the GTK
implementation is divided into tasks.

------------------------------------------------------------------------

## 5. Testing: what is new for the GTK4 development?

### 5.1 What the existing tests already cover

The CLI backend has its own tests. Those tests are intended to protect
the calculation logic and should continue to be used. We should not
duplicate the entire backend test suite just because a GUI is being
added.

The new work introduces additional risks that CLI tests cannot fully
cover: widget behaviour, user actions, display updates, data transfer
between layers and the complete GUI workflow.

### 5.2 Proposed GUI and integration test coverage

  -----------------------------------------------------------------------
  Test area               Example checks          What success looks like
  ----------------------- ----------------------- -----------------------
  Initial window          Application launches;   No startup failure;
                          main window and         required controls are
                          expected controls       visible and usable.
                          appear.                 

  Course-row actions      Add a row; remove a     Rows are added/removed
                          row; reach the maximum; correctly and the limit
                          attempt to exceed it.   is respected.

  Field interaction       Enter course name,      Values are collected
                          score and credit hours; correctly and remain
                          edit an existing entry. available when an error
                                                  occurs.

  GUI validation feedback Submit incomplete or    The correct field/row
                          invalid entries.        is identified; the user
                                                  can correct the entry.

  Calculate action        Click Calculate with    The integration layer
                          valid entries.          receives the intended
                                                  values and returns
                                                  results.

  Results display         Check course name,      Displayed values match
                          score, grade, grade     the backend result
                          value, credit hours and data.
                          weighted points.        

  Semester summary        Check total credit      Summary matches the
                          hours, total weighted   values returned by the
                          points and GPA.         calculation layer.

  Recalculation           Change a score or       Old results are
                          credit hour and         replaced by the new
                          calculate again.        correct results; stale
                                                  values are not
                                                  retained.

  Reset behaviour         Clear entries; cancel a Entries and results are
                          confirmation if one     cleared only when the
                          exists.                 user confirms the
                                                  action.

  Error propagation       Cause the               The UI communicates the
                          integration/backend     error without crashing
                          call to report an       or displaying
                          error.                  misleading results.

  Window behaviour        Resize the window and   Important controls and
                          inspect the form/table. result fields remain
                                                  accessible.

  End-to-end workflow     Enter a realistic       The complete MVP user
                          semester, calculate,    journey works as
                          inspect results, edit   expected.
                          and recalculate.        
  -----------------------------------------------------------------------

### 5.3 How the existing and new tests fit together

``` text
EXISTING BACKEND TESTS
Grade conversion • Weighted points • Totals • GPA
                 |
                 v
       Protect calculation logic
                 |
                 v
NEW GUI / INTEGRATION TESTS
Widgets • User actions • Data flow • Display • Errors
                 |
                 v
       Protect application behaviour
                 |
                 v
       END-TO-END MVP ACCEPTANCE
```

### 5.4 Testing approach to decide

  -----------------------------------------------------------------------
  Option                  Description             Starting recommendation
  ----------------------- ----------------------- -----------------------
  Manual GUI testing      Team members follow a   Required for early UI
                          documented checklist.   development and
                                                  visual/usability
                                                  checks.

  Automated tests for     Test the                Recommended; keeps
  integration functions   application-level       data-flow and
                          functions without       error-handling logic
                          launching GTK where     testable.
                          possible.               

  Automated GTK tests     Exercise widgets and UI Consider where
                          behaviour through       practical; do not let
                          suitable GTK testing    test-framework setup
                          approaches.             delay the first working
                                                  interface.

  End-to-end acceptance   A teammate follows the  Required before MVP
  checklist               complete user journey   release.
                          on the built            
                          application.            
  -----------------------------------------------------------------------

**Expected outcome:** A clear test plan separating existing backend
coverage from new GUI, integration and end-to-end coverage. Each test
area should have an owner.

------------------------------------------------------------------------

## 6. Workstream responsibilities and shared ownership

### 6.1 How we will organise the work

We should divide the work by responsibility area, not assume that one
person must complete an entire feature alone.

Each workstream will have:

-   **Lead:** coordinates the workstream, keeps progress visible,
    ensures decisions are documented and presents blockers or completed
    deliverables to the team.
-   **Supporting members:** contribute implementation, research,
    reviews, testing and documentation. They should be involved in the
    work rather than waiting for the lead to finish it.
-   **Shared review:** important decisions and deliverables are reviewed
    by the relevant team members before being treated as complete.

The lead is accountable for coordination and completion tracking, not
expected to carry the whole workload.

### 6.2 Proposed workstreams

  ---------------------------------------------------------------------------------
  Workstream        Lead               Supporting members Example tasks and
                    responsibilities                      deliverables
  ----------------- ------------------ ------------------ -------------------------
  **1. Data model   Coordinate the     Review field       Approved course-result
  and API design**  course-result      types, naming,     structure;
                    structure and      memory approach    semester-summary
                    agree on the data  and function       representation;
                    exchanged between  contracts;         documented function
                    layers.            challenge design   inputs, outputs and
                                       choices.           errors.

  **2. Backend      Identify the       Review existing    GUI-facing calculation
  adaptation**      smallest changes   functions,         function or integration
                    or wrappers needed implement focused  API; backend changes, if
                    to expose the      changes, check     justified; updated
                    existing backend   compatibility and  backend tests where
                    to the GUI.        preserve working   needed.
                                       behaviour.         

  **3. GTK4         Coordinate the     Implement          Main window; course-entry
  frontend**        main window,       individual UI      rows; Add/Remove;
                    layout, widgets    components, review Calculate; Reset; results
                    and interaction    usability and test table; GPA summary.
                    design.            widget behaviour.  

  **4. Application  Coordinate data    Implement/review   Integration functions;
  integration**     flow between GTK   value collection,  UI-to-backend connection;
                    widgets and the    conversion, result correct population of
                    calculation        handling and error course results and
                    backend.           propagation.       semester summary.

  **5. Testing and  Maintain the test  Write test cases,  GUI test checklist;
  quality           plan and track     perform manual     integration tests;
  assurance**       whether the new    checks, automate   end-to-end test report;
                    GUI workflow is    suitable tests,    defect log.
                    verified.          reproduce and      
                                       retest defects.    

  **6.              Keep technical     Review setup       Updated
  Documentation and documentation and  instructions,      architecture/data-model
  release           build/run          document           notes; GUI usage notes;
  readiness**       instructions       decisions, capture README/setup updates; MVP
                    aligned with the   useful screenshots completion checklist.
                    delivered          and check release  
                    application.       requirements.      
  ---------------------------------------------------------------------------------

### 6.3 Suggested assignment sheet

  ---------------------------------------------------------------------------
  Workstream        Lead              Supporting        First deliverable
                                      members           
  ----------------- ----------------- ----------------- ---------------------
  Data model and    To be assigned    To be assigned    Approved data model
  API design                                            and interface
                                                        contract

  Backend           To be assigned    To be assigned    Reusable GUI-facing
  adaptation                                            backend/integration
                                                        entry point

  GTK4 frontend     To be assigned    To be assigned    Agreed wireframe and
                                                        initial
                                                        window/course-entry
                                                        interface

  Application       To be assigned    To be assigned    Working data flow
  integration                                           between UI and
                                                        backend

  Testing and       To be assigned    To be assigned    GUI/integration test
  quality assurance                                     plan and test
                                                        checklist

  Documentation and To be assigned    To be assigned    Updated project
  release readiness                                     documentation and
                                                        release checklist
  ---------------------------------------------------------------------------

### 6.4 How tasks should be shared

For each workstream, the lead should break the deliverable into smaller
tasks that supporting members can own. For example:

**GTK4 frontend** - Member A (Lead): coordinate the window layout and
review the overall implementation. - Member B: implement the
course-entry row and input widgets. - Member C: implement Add Course and
Remove Course behaviour. - Member D: implement the results table and GPA
summary. - Other members: review, test and help resolve issues.

This is an example only. The team should distribute tasks based on
interest, availability and current skills. Members may support more than
one workstream where workload allows.

**Working rule:** Every task should have a clear owner, a supporting
reviewer where useful, and an observable deliverable. Workstream leads
should report progress and blockers during team check-ins.

------------------------------------------------------------------------

## 7. Decision, research and action tracking

For every open topic, record one of the following outcomes:

  -----------------------------------------------------------------------
  Status                  Meaning                 What happens next
  ----------------------- ----------------------- -----------------------
  **AGREED**              The team accepts an     Record the exact
                          option or a documented  decision and use it
                          variation.              during implementation.

  **RESEARCH**            The team needs more     Assign a research
                          evidence before         owner, define the
                          choosing.               question and agree when
                                                  the findings will be
                                                  presented.

  **DEFERRED**            The topic is not        Record when or under
                          required to proceed or  what condition it
                          is outside the MVP.     should be revisited.
  -----------------------------------------------------------------------

### Decision and action log

  ----------------------------------------------------------------------------
  Topic            Status         Decision /     Owner          Review date
                                  research                      
                                  question                      
  ---------------- -------------- -------------- -------------- --------------
  Course-result    AGREE /                                      
  structure and    RESEARCH /                                   
  naming           DEFER                                        

  Field types and  AGREE /                                      
  string handling  RESEARCH /                                   
                   DEFER                                        

  Course           AGREE /                                      
  collection and   RESEARCH /                                   
  summary          DEFER                                        
  representation                                                

  GUI-facing       AGREE /                                      
  backend contract RESEARCH /                                   
                   DEFER                                        

  Error reporting  AGREE /                                      
  between layers   RESEARCH /                                   
                   DEFER                                        

  Main GTK4 window AGREE /                                      
  layout           RESEARCH /                                   
                   DEFER                                        

  Course-entry     AGREE /                                      
  interaction      RESEARCH /                                   
                   DEFER                                        

  Results and      AGREE /                                      
  summary          RESEARCH /                                   
  presentation     DEFER                                        

  GUI validation   AGREE /                                      
  feedback         RESEARCH /                                   
                   DEFER                                        

  GUI and          AGREE /                                      
  integration test RESEARCH /                                   
  approach         DEFER                                        

  Workstream leads AGREE /                                      
  and supporting   RESEARCH /                                   
  members          DEFER                                        
  ----------------------------------------------------------------------------

------------------------------------------------------------------------

## 8. What should we leave this meeting with?

By the end of the discussion, we should aim to have:

1.  **An approved course-result data model** --- structure name, fields,
    types, course collection and semester summary approach.
2.  **A clear integration contract** --- how GTK4 passes course
    information to the existing backend and receives course results,
    totals and GPA.
3.  **An agreed GTK4 interface direction** --- main layout, course-entry
    interaction, available actions, results presentation and error
    feedback.
4.  **A proposed screen sketch or wireframe** --- enough detail for the
    frontend workstream to begin without guessing the intended user
    experience.
5.  **A GUI and integration test plan** --- clearly separated from the
    existing CLI/backend tests.
6.  **Assigned workstream leads and supporting members** --- with
    initial tasks and deliverables.
7.  **A decision and research log** --- unresolved questions have owners
    and review dates.

> **The meeting is successful if the team leaves with enough agreement
> to begin the next implementation tasks without reopening settled
> project decisions or making assumptions about the data model and
> interface.**

------------------------------------------------------------------------

## 9. What happens after this discussion?

The following sequence is a practical guide. Some work can happen in
parallel once its dependencies are clear.

  -----------------------------------------------------------------------
  Order                   Next activity           Dependency / output
  ----------------------- ----------------------- -----------------------
  1                       Finalise and document   Team agreement from
                          the course-result data  this discussion.
                          model.                  

  2                       Agree and document the  Approved data model and
                          GUI-facing              review of existing
                          backend/integration     backend functions.
                          contract.               

  3                       Produce and approve a   Agreed interface
                          GTK4 wireframe or       requirements.
                          screen sketch.          

  4                       Begin GTK4 course-entry Wireframe and frontend
                          interface development.  task assignments.

  5                       Implement the           Agreed contract; can
                          integration layer and   proceed alongside
                          connect the existing    independent UI work
                          backend.                where practical.

  6                       Implement results table Agreed result structure
                          and GPA summary.        and UI design.

  7                       Run GUI, integration    Working interface and
                          and end-to-end tests.   connected backend.

  8                       Update README, setup    Verified build and
                          instructions and        application workflow.
                          project documentation.  
  -----------------------------------------------------------------------

------------------------------------------------------------------------

## 10. Closing discussion

The CLI implementation is the foundation for the graphical application,
not work that needs to be repeated. Our priority now is to agree on the
information the GUI needs, define a clean connection to the existing
backend, and design an interface that makes the semester GPA workflow
clear and reliable.

**Discuss together. Record decisions. Share the work. Build on what is
already working.**

# Data Model and API Design Workstream Lead Guide

**Purpose:** Help the lead and supporting members agree, document, and review the course-result data model and the interface between the GTK4 application and the existing C calculation backend before implementation depends on it.

> 🟩 **Target deliverable:** An approved course-result model, semester-summary representation, and GUI-facing function contract with inputs, outputs, and error behavior.
>
> 🟨 **Learning rule:** Start from the approved specification. Carry its agreed and inferred decisions into the implementation contract, preserving their status. Reopen one only when source review gives a concrete reason. The lead coordinates the work; the lead does not have to write every artifact.

## 1. Workstream at a glance

| Item | What the team does |
|---|---|
| Lead | Plans the sessions, assigns task owners, keeps the decision log current, coordinates reviews, and reports progress and blockers. |
| Supporting members | Inspect source and requirements, propose and challenge designs, draft parts of the contract, review edge cases, and help verify consistency. |
| First deliverable | Approved data model and interface contract. |
| Completion check | Team can explain what data moves between layers, who owns each responsibility, how failures are reported, and what implementation can safely begin. |
| Cross-workstream link | Invite the Backend adaptation lead to review compatibility with current functions and identify any focused wrapper or backend changes. This review informs this workstream; ownership of its decisions stays with this workstream and the team. |

## 2. Guardrails before the first session

- Build on the current C CLI and calculation functions; do not redesign the grade scale or GPA formula.
- Keep GTK widgets and GTK types out of the calculation backend.
- GTK callbacks should pass values through a small application/integration API, not coordinate a chain of calculation calls.
- Keep terminal input functions (`getnumcrs()`, `getcrs()`, `getch()`, `getscr()`) out of the GTK flow.
- Preserve existing backend functions where practical. Propose changes only when source inspection shows a concrete need.
- Keep MVP scope: one semester calculation and in-session course results. Persistence, CGPA, export, and analytics are deferred.
- Treat the approved specification's **agreed** and **inferred** choices as settled project direction. Do not schedule them for another team decision session; translate them into implementation-ready declarations and notes.

## 3. People and task ownership

At kickoff, fill this table with the actual team names. One person may support more than one workstream if the team agrees and workload allows.

| Role | Name | First responsibility |
|---|---|---|
| Workstream lead | To assign | Coordinate the steps below and present the deliverable for review. |
| Supporting member | To assign | Review data fields, types, naming, and memory approach. |
| Supporting member | To assign | Inspect backend headers/implementations and map reusable functions. |
| Backend adaptation reviewer | To assign | Check compatibility and identify the smallest justified backend changes. |
| Decision recorder/reviewer | To assign | Capture decisions, rationale, status, open questions, and review outcome. |

Names and meeting cadence are not specified in the source decisions; agree them at kickoff rather than assuming them in this guide.

## 4. Step-by-step execution

### Step 1 — Prepare the work

**Lead:**

1. Share this guide and the two source references below before the session, highlighting the specification's settled outcomes.
2. Confirm attendees, time, note-taker, and who can make or ratify team decisions.
3. Create a task list with one owner and a visible output for each task.
4. Ask members to inspect the current header and relevant backend functions so the team can map settled decisions onto the actual code and identify only genuine contract gaps.

**Supporting members:** Read the accepted data-model outcomes and the V2 discussion sections 2 and 3. Bring questions or evidence from source; avoid proposing a replacement formula.

**Sources:** [Approved requirements and decisions](../../../archive/GKGDev_Core5_Requirements_Decisions_and_Agreed_Specifications_Styled.md), sections 2 and 3; [V2 team discussion](../../../archive/Requirements_and_Data_Model_Team_Discussion_v2.md), sections 2 and 3.

### Step 2 — Map the current backend

Make a short inventory before designing the interface. Use the real declarations and definitions, not stale executables or assumptions.

| Inspect | Record |
|---|---|
| `include/gpa.h` and relevant `src/` functions | Parameters, return types, side effects, and current error conventions. |
| Grade conversion and calculation functions | Which calculations can be reused without GTK and in what order. |
| Terminal input functions | Mark as CLI-only; do not expose them to GTK callbacks. |
| Existing tests, where relevant | Which behavior is already protected and should remain stable. |

**Backend adaptation lead/member:** Review this inventory, confirm compatibility, and flag a specific source-level reason for each proposed change. Do not implement changes as part of this design step unless the team explicitly moves that task into implementation.

### Step 3 — Apply the settled course-result model

The model questions in Section 2 of the approved specification have outcomes; the section states that no item remains open. **Do not hold another vote on the structure name, fields, types, course limit, collection approach, or derived summary.** Draft the declarations and mapping notes using the recorded outcomes below. Preserve each outcome's status in the handover.

| Field | Meaning | Current project direction |
|---|---|---|
| `courseName` | Course label shown in results | Fixed 100-character buffer; input must be bounded and safely terminated. **Inferred.** |
| `score` | Entered score used for grade conversion | `int`, consistent with current input rules. **Inferred.** |
| `letterGrade` | Grade assigned by the ATU scale | Internal enum; convert to display text for GTK. **Inferred.** |
| `gradeValue` | Numeric value for the letter grade | Retain a floating-point calculation field consistent with current backend signatures. **Inferred.** |
| `creditHour` | Course credit hours | Retain the existing floating-point representation. **Inferred.** |
| `gradePoint` | Course weighted grade points | Keep the current name and use as the course contribution to totals. **Inferred.** |

`MAX_COURSES` remains 15 and storage remains a fixed-size collection for the MVP (**agreed/carried forward**). The summary is derived from course results and contains total credit hours, total weighted grade points, and semester GPA (**inferred**).

### Step 4 — Turn the agreed layer boundary into an API contract

The three-layer architecture and direction are agreed. Turn them into an implementable contract by documenting the exact function name, declarations, parameter types, result/error structures, and ownership rules that the specification leaves open. Do not ask the team to choose again whether GTK should call a small integration entry point, whether the backend stays GTK-independent, or whether errors are explicit: those directions are already recorded.

Use this agreed data flow as a constraint:

```text
GTK form values
      ↓
Application/integration function: validate and coordinate
      ↓
Existing C calculation functions: grade, weighted points, totals, GPA
      ↓
Structured course results + semester summary, or explicit error status
      ↓
GTK displays results or a user-facing validation/error message
```

For the GUI-facing integration entry point (one small function or a small set if source review justifies it), document:

| Contract part | Questions to answer |
|---|---|
| Name and owner | What exact name and declaration fit project conventions? The function belongs to the application/integration layer. |
| Inputs | Choose the simplest representation compatible with `CourseResult` and the backend. How is count passed and checked? |
| Outputs | Return structured course results and semester summary without making GTK repeat GPA calculations. Who owns the memory? |
| Status/errors | Define exact status/error types and details so invalid input cannot look like success. The reporting must be explicit; exact representation remains to be designed. |
| Side effects | Does the function print, read from the terminal, mutate global state, or allocate memory? Prefer none that surprise the caller. |
| Limits | How are `MAX_COURSES`, course-name capacity, score, and credit-hour rules enforced? |

**Example shape only — not an approved signature:**

```c
/* Illustrative only: agree names, exact types, and ownership as a team. */
typedef struct {
    CourseResult courses[MAX_COURSES];
    size_t courseCount;
    SemesterSummary summary;
} CalculationResult;

CalculationStatus calculate_semester(
    const CourseInput inputs[],
    size_t courseCount,
    CalculationResult *result,
    CalculationError *error);
```

The names and output/error structures above are prompts for discussion, not approved project declarations. The final contract must use the project’s naming conventions and existing calculation types. Do not let the GUI recompute GPA or infer success from ambiguous sentinels such as `0` or `-1.0`.

### Step 5 — Record only genuine open details or evidence-based exceptions

The approved specification marks the model outcomes agreed or inferred and leaves no model question open. Record those as carry-forward decisions; do not list them as questions for another vote. Use team discussion time only for exact implementation details the specification does not define, or for a proposed exception supported by source evidence. For each such item, record the evidence, options, outcome, rationale, status, owner, and date. If unresolved, assign an owner and return date and state what it blocks.

| Decision area | Review prompts |
|---|---|
| Contract detail | What exact declarations, parameter and output types fit the approved model and existing backend? |
| Validation mapping | Where is each accepted rule enforced, and how is the failed field/course identified? |
| Error representation | What exact status/error structure carries the explicit reporting required by the specification? |
| Compatibility | Which current calculation functions can be reused, and what source evidence justifies a wrapper or change? |
| Memory ownership | How will fixed-size course/result data be passed and returned safely without ambiguous pointer ownership? |
| Evidence-based exception | If proposing a change to an agreed/inferred outcome, what concrete defect or incompatibility demonstrates the need? |

Use the specification's status labels to describe the origin of each settled direction. They are not prompts to reopen the decisions:

- 🟩 **AGREED** — explicitly accepted by the team or carried-forward decision.
- 🔵 **INFERRED** — accepted starting recommendation; retain this label in documentation.
- 🟨 **PROPOSED** — a new option awaiting team review.
- 🟥 **OPEN** — unresolved; assign an owner and review date.

### Step 6 — Review the contract with connected workstreams

1. Walk through one valid course using the settled fields, from UI input to displayed course result.
2. Walk through a complete semester from the bounded course collection to totals and GPA.
3. Walk through invalid input and show how the status/error returns without printing UI text or producing misleading results.
4. Ask the Backend adaptation lead to verify compatibility with settled decisions and identify any justified change with source evidence.
5. Ask the Application integration lead (when assigned) to check whether the contract is implementable from the UI boundary.
6. Capture review comments, decide which are accepted, and update the contract before requesting team approval.

### Step 7 — Present progress and close the workstream

The lead presents a short update:

```text
Completed: [reviewed model / contract sections]
Decisions: [decision + status]
Open: [question, owner, return date, blocker]
Backend impact: [reusable functions / justified change candidates]
Next: [task, owner, observable output]
```

Close only when the team has reviewed and approved the deliverable, unresolved decisions have named owners and dates, and dependent leads know which contract version to use. Record implementation follow-ups as owned tasks; do not report design approval as completed implementation.

## 5. Suggested task board

| Task | Owner | Output / done when |
|---|---|---|
| Inspect current backend declarations and functions | Supporting member | Function inventory includes inputs, outputs, error conventions, and CLI-only functions. |
| Map settled model fields and limits into declarations | Supporting member | Draft matches the approved field meanings/types, fixed 15-course collection, and summary; statuses are preserved. |
| Draft course-result and semester-summary representation | Lead + member | Approved model is translated into declarations and integration-facing notes; derived totals are identified. |
| Draft GUI-facing API contract | Lead + backend reviewer | Exact inputs, outputs, ownership, validation, errors, and limits are explicit within agreed architecture. |
| Cross-review and decision log | Assigned reviewer | Comments resolved or tracked with owner/date; team review recorded. |

## 6. Completion checklist

- [ ] The agreed/inferred course-result fields, types, and capacity are translated into the proposed declarations with their status labels preserved; no settled model decision was reopened without evidence.
- [ ] The semester summary contains total credit hours, total weighted grade points, and GPA derived from course results.
- [ ] The course limit remains 15 unless a documented team decision changes it.
- [ ] The UI-facing contract defines inputs, outputs, memory ownership, validation, limits, and explicit status/error behavior.
- [ ] GTK stays out of the calculation backend; terminal input functions stay out of the GTK flow.
- [ ] Existing backend functions are reused where practical; every proposed change has a concrete reason.
- [ ] No design change redefines the ATU grade bands or GPA formula.
- [ ] Decisions distinguish agreed, inferred, proposed, and open items; open items have owners and review dates.
- [ ] Backend adaptation and application integration reviewers have checked the relevant boundary.
- [ ] The team has approved the first deliverable and received the lead’s progress summary.

## 7. What the lead hands over

The deliverable should be concise and implementation-ready:

1. **Course-result model** with field meanings and status labels.
2. **Semester-summary representation** and which values are derived.
3. **GUI-facing API contract** covering inputs, outputs, memory ownership, validation, and errors.
4. **Decision log** with rationale and unresolved questions, owners, and review dates.
5. **Backend impact notes** identifying reusable functions and any evidence-based change candidates.

The implementation team can then begin from one reviewed contract rather than separate assumptions. Record the approved version in the project documentation when the team completes this workstream.

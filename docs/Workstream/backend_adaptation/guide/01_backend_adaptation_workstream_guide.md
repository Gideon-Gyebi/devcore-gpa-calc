# Backend Adaptation Workstream Guide

**Purpose:** Prepare the existing C calculation backend to support the approved course-result/API contract while preserving the established ATU grading scale, GPA formula, and useful CLI behavior.

> **Scope boundary:** Backend adaptation changes or exposes calculation behavior. The separate **Application Integration** workstream implements the application-layer function that validates UI input, coordinates backend calls, assembles the response, and reports status. Data Model and API Design owns the contract design and handoff; it does not automatically own implementation of the integration layer.

## 1. What this workstream delivers

The backend adaptation workstream reviews the current implementation against the approved contract and makes the smallest justified backend changes so the contract can be implemented safely. Its deliverable is an adapted, independently usable calculation backend with focused verification and a clear handoff to Application Integration.

It does not implement GTK widgets or callbacks, and it does not take over the Application Integration workstream's orchestration function. If a narrowly scoped backend wrapper is needed, document its boundary and coordinate it with the integration owner before adding it.

## 2. How the three workstreams fit together

1. **Data Model and API Design (Workstream 1):** Owns the approved model and API contract, including its recorded field types, status/error behavior, and data flow. Its completed handoff is the implementation reference.
2. **Backend Adaptation (Workstream 2):** Makes the existing calculation functions compatible with that contract and records any evidence-based compatibility gaps.
3. **Application Integration (Workstream 4):** Implements the API declared by the contract, validates and coordinates inputs, calls the backend, fills structured outputs, and returns explicit status/error information. GTK calls this layer rather than coordinating backend calls itself.

Workstreams 2 and 4 can coordinate or proceed in parallel after the contract is available. Integration implementation belongs to Workstream 4, not to the Data Model/API design workstream. The team should assign its implementation owner when Application Integration is allocated; do not assume that the Workstream 1 lead or the Workstream 2 lead owns it solely because they reviewed the design.

## 3. Suggested task split for a lead and two supporting members

Fill in actual names at kickoff. The lead coordinates and tracks completion; supporting members own concrete changes and reviews rather than serving only as observers.

| Role | Suggested ownership | Observable output |
|---|---|---|
| Workstream lead | Coordinate the source-to-contract gap review; agree file ownership and sequencing; resolve cross-member conflicts; review the final behavior against the contract; coordinate handoff with the Application Integration lead. The lead may own a focused backend change if workload permits. | Gap/decision log, assigned task list, reviewed backend handoff, progress/blocker report. |
| Supporting Member A | Own score and grade conversion compatibility: inspect `scrconv()`/`lgconv()` and related declarations; implement only contract-required type or boundary changes while preserving ATU grade bands and conversion behavior. Coordinate any input-function impact with the lead. | Focused conversion changes and relevant verification evidence. |
| Supporting Member B | Own record/aggregate compatibility: inspect storage and total functions; adapt them to the approved course-result fields where needed; check the `savechgp.c` header case mismatch if that file remains in use; update directly affected fixtures/tests when requested by the team's test plan. | Focused storage/aggregate changes and relevant verification evidence. |

The lead can reassign these areas based on availability and actual code dependencies, but every change needs one named owner and a reviewer. Avoid overlapping edits to the same files without coordination.

## 4. Steps

### Step 1 — Read the approved handoff and inventory the source

- Read the approved contract in [Role 3: API Signatures and Data Flow — Gideon](../../data_model_and_api_esign/deliverable/role_3_api_signatures_and_data_flow_gideon.md) and the relevant sections of the [approved requirements and decisions](../../../archive/GKGDev_Core5_Requirements_Decisions_and_Agreed_Specifications_Styled.md).
- Inspect current headers, implementations, and relevant existing tests. Record what already works and where the source differs from the handoff.
- Do not wait for the pending Role 2 document if the approved Role 3 contract and current source are sufficient to begin this review. When Role 2 is uploaded, compare it for provenance or omitted context; only raise a discrepancy if it materially conflicts with the approved contract.
- Keep requirements marked **AGREED** distinct from decisions marked **INFERRED** in reports. The contract carries those recorded statuses forward.

### Step 2 — Agree the minimal backend changes

For each proposed change, record the contract clause, source evidence, file(s), owner, and expected behavior. Review at least:

- Score/grade conversion compatibility, including valid boundaries and preservation of the established ATU scale.
- Existing numeric types and any approved score representation; do not broaden or change input rules without evidence and a recorded decision.
- Weighted points, course result storage, totals, and semester GPA compatibility.
- Validation ownership: backend calculations must safely handle their own documented inputs; the integration API owns whole-request validation and explicit status/error reporting as specified.
- CLI callers that may need adaptation so existing functionality remains usable during the transition.
- Existing edge cases, naming, and the case-sensitive `GPA.h`/`gpa.h` include issue if the affected source remains active.

Do not introduce GTK headers, widget behavior, terminal prompting in GUI code paths, persistence, CGPA, or unrelated cleanup.

### Step 3 — Implement and review

- Make focused changes in the assigned backend files.
- Keep declarations and definitions consistent, initialize outputs, bound array/string access, and preserve established calculations.
- Keep the calculation backend independently compilable/testable without GTK where practical.
- Review each other's changes and check that integration can call the adapted functions without reproducing formulas or interpreting ambiguous sentinels as success.

### Step 4 — Handoff to Application Integration

Provide the integration owner with:

- The changed backend function signatures and their input/error behavior.
- A short mapping from each contract operation to the backend function(s) that implement it.
- Any remaining incompatibilities or explicitly deferred items.
- The exact focused verification performed and its outcome, or clearly marked outstanding verification.

The Application Integration owner then implements the contract's application-layer API. Coordinate on shared types and headers before either side changes them.

## 5. Expected deliverables

Store reviewed work products in the sibling `deliverables/` folder. This guide creates the folder; add files there as the workstream produces them.

- Backend-to-contract gap review with evidence and assigned owners.
- Focused backend source changes required by the approved contract.
- Relevant test/fixture updates and exact verification notes, where assigned and requested.
- Integration handoff describing usable backend calls, behavior, and remaining gaps.
- Updated project documentation only where implemented behavior or verified build/run instructions changed.

## 6. Completion checklist

- [ ] The approved API/data-model contract was used as the implementation reference.
- [ ] Each proposed backend change has a concrete contract or source-based reason.
- [ ] Established ATU grade bands and GPA formula are preserved.
- [ ] Backend responsibilities remain GTK-independent and do not call terminal input from GTK flows.
- [ ] Existing callers affected by changed declarations were identified and handled or documented.
- [ ] Focused verification was performed only as assigned/requested, with exact commands and outcomes recorded; no test is claimed from stale binaries.
- [ ] The Application Integration owner received the backend handoff and any shared-header coordination points.
- [ ] Remaining gaps, blockers, and unverified behavior are visible to the team.

## References

- [Approved requirements and decisions](../../../archive/GKGDev_Core5_Requirements_Decisions_and_Agreed_Specifications_Styled.md), especially sections 2, 3, and 6.
- [Project architecture note](../../../project/03_architecture_note.md).
- [MVP development checklist](../../../project/04_mvp_development_checklist.md).
- [Role 3 approved API handoff](../../data_model_and_api_esign/deliverable/role_3_api_signatures_and_data_flow_gideon.md).

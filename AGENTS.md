# AGENTS.md — GKGDev Core 5 GPA Calculator

Persistent development instructions for this repository. Keep this file maintainable; update it when the team approves significant architectural, workflow, or build changes. Link to detailed project references rather than copying them here.

## Project identity and objectives

- **Project:** GKGDev Core 5 — ATU GPA Calculator “C” Project
- **Institution:** Accra Technical University (ATU)
- **Repository:** `devcore-gpa-calc`
- **Language/UI direction:** C backend with a GTK4 desktop interface
- **Initial target:** Windows, MSYS2 MinGW64 and GCC
- **MVP:** Calculate semester GPA using the established ATU grading scale, retain per-course results, and present course results and semester totals through GTK4.
- **Deferred:** Persistent semester records, CGPA, export and analytics, unless the team approves a scope change.

Build on the existing CLI and calculation work. Do not restart the project or replace working behavior without evidence and a focused reason.

## Source of truth and references

Use approved project decisions together with the actual current source, tests and configuration. Check these repository references as relevant:

- [`docs/archive/GKGDev_Core5_Requirements_Decisions_and_Agreed_Specifications_Styled.md`](docs/archive/GKGDev_Core5_Requirements_Decisions_and_Agreed_Specifications_Styled.md) — formal requirements and recorded decisions.
- [`docs/archive/GKGDev_Core5_Requirements_Discussion_Notes_and_Meeting_Decisions.md`](docs/archive/GKGDev_Core5_Requirements_Discussion_Notes_and_Meeting_Decisions.md) — discussion outcomes and open matters.
- [`docs/project/02_project_governance_and_development_plan.md`](docs/project/02_project_governance_and_development_plan.md) — scope, priorities and working agreement.
- [`docs/project/03_architecture_note.md`](docs/project/03_architecture_note.md) — intended frontend, integration and backend responsibilities.
- [`docs/project/04_mvp_development_checklist.md`](docs/project/04_mvp_development_checklist.md) — implementation and verification checklist.
- [`docs/project/01_initial_repository_overview.md`](docs/project/01_initial_repository_overview.md) — historical assessment; verify it against current code.
- [`docs/setup.md`](docs/setup.md) — Windows/MSYS2/GTK4 setup notes; review and verify before relying on commands or assuming every contributor has a working GTK environment.
- [`docs/solutions/`](docs/solutions/) — implementation explanations and research notes.

The formal requirements record some data-model choices as inferred from accepted proposals. Preserve their status labels and do not present inferred details as independently explicit team statements. The meeting record notes that some original dictated details are unavailable.

## Repository map

- `main.c` — current CLI entry point and orchestration.
- `include/gpa.h` — shared `MAX_COURSES`, `GpaRecord` and function declarations.
- `src/` — terminal input, conversions, weighted points, storage, totals and GPA functions.
- `ui/gui.c` — GTK4 placeholder; empty in the assessed repository.
- `test/` — standalone C test programs and input fixtures.
- `docs/project/` — governance, architecture, checklist and baseline assessment.
- `docs/archive/` — requirements and team decision records.
- `docs/solutions/` — function explanations and research.
- `docs/flowcharts/` — function flowcharts.
- `docs/worksheet/` — team reference notes.
- `obj/` — ignored prebuilt executables; they may be stale and are not proof of a current build.
- `.vscode/` — editor IntelliSense configuration; currently references `C:\MinGW\bin\gcc.exe`, unlike the documented MSYS2 direction.

There is no Makefile or CMake configuration in the assessed repository.

## Architecture and current data flow

The implemented application is a CLI:

```text
main.c -> getnumcrs/getcrs/getch/getscr
       -> scrconv -> lgconv -> gpcalc -> savechgp
       -> tchcalc/tgpcalc -> gpacalc -> terminal output
```

The approved target architecture is:

```text
GTK4 frontend -> application/integration layer -> C calculation backend
```

- **GTK4 frontend:** widgets, input, navigation, validation feedback and result display.
- **Integration layer:** validate/convert UI values, coordinate backend calls, assemble structured results and report status/errors.
- **Backend:** grade conversion, weighted points, totals and GPA; must remain independent of GTK.

The repository currently has neither an integration module nor an implemented GTK interface. Do not describe planned behavior as implemented.

## Important functions and data

Declarations are in `include/gpa.h`:

- `getnumcrs()`, `getcrs()`, `getch()`, `getscr()` — terminal-only input functions.
- `scrconv(int score)` — score-to-letter conversion using the ATU scale.
- `lgconv(char *letterGrade)` — letter-to-grade-value conversion.
- `gpcalc(float gradeValue, float creditHours)` — weighted points (`gradeValue * creditHours`).
- `savechgp(...)` — stores credit hours and weighted points in `GpaRecord`.
- `tchcalc(...)`, `tgpcalc(...)` — total credit hours and weighted points.
- `gpacalc(float totalGradePoints, float totalCreditHours)` — semester GPA from totals.

Current `GpaRecord` contains only `creditHour` and `gradePoint`; it cannot supply all fields planned for the per-course results table. The formal project specification records a `CourseResult` model, fixed 100-character course-name buffer, internal letter-grade enum, `MAX_COURSES = 15`, and a derived semester summary. Follow the specification’s status labels; do not silently change these decisions or the established ATU scale/formula.

## Backend/frontend integration rules

- Never call terminal-oriented `get*()` input functions from GTK callbacks.
- GTK collects values from widgets and passes them to the integration layer.
- GTK must not duplicate GPA formulas or coordinate multiple backend calls directly when an integration API is available.
- Integration returns structured results and explicit status/error information. The GUI presents user-facing messages; calculation functions do not manipulate widgets or print UI messages.
- Keep backend functions independently testable without GTK where practical.
- Preserve existing backend functions where practical; add focused wrappers when needed.

## C conventions and safety

- Follow existing naming and formatting conventions; the editor configuration specifies C11 unless an approved change supersedes it.
- Keep `include/gpa.h` declarations consistent with definitions and keep modules focused.
- Initialize variables, handle failed input and `EOF`, and validate function inputs at the layer that owns the contract.
- Bound array and string access; never trust UI values or terminal validation alone for backend safety.
- Make error representations explicit. Existing `-1.0` and `0` conventions have ambiguities; do not expand them without documenting the contract.
- Keep GTK headers and types out of backend modules.

## GTK4 conventions

- Use GTK4 APIs and verify signatures against the installed GTK4 headers/documentation.
- Keep widget creation and signal wiring in the UI layer; calculations belong in the backend.
- Use callbacks to collect widget values and invoke the integration API. Consider widget ownership, callback lifetime and cleanup.
- Follow the approved three-page direction: course entry, results, and dedicated GPA summary. Calculate opens results; manual navigation remains available.
- Preserve agreed entry behavior: initial course count, Add Course, per-row Remove, 15-course maximum, Calculate/Recalculate state, and Reset with confirmation.
- Preserve entries on validation failure; show useful feedback. Follow agreed results fields, totals, resizing/minimum-size, and horizontal-scrolling requirements.
- Do not assume unresolved behavior. Whether Reset should show the first-launch welcome instructions again remains open.
- Before depending on GTK for team development, review `docs/setup.md` and verify that the setup instructions work for contributors across the team’s environments. Update the setup documentation only after confirming the required toolchain, GTK4, `pkg-config`, paths and build/run steps.

## Build environment and commands

The intended Windows environment is MSYS2 MinGW64 with GCC, GTK4 and `pkg-config`; see `docs/setup.md`.

**Build status:** There is no current build system, and README commands target an earlier converter. No complete command for the current CLI or GTK application was verified during onboarding. The setup document’s GTK pattern is only a template:

```bash
gcc <source-code.c> -o <app-name> `pkg-config --cflags --libs gtk4`
```

Do not present that template or stale README commands as verified project commands. Establish the source list and contributor environment, then run and document a concrete command before calling it verified. Treat generated binaries as file writes and avoid overwriting user data.

## Testing procedures

Tests are standalone programs under `test/`; there is no unified runner. Existing files cover conversions, calculations, aggregate functions, record storage and interactive inputs.

- Inspect test dependencies before compiling; link the tested implementation source.
- Interactive tests may require fixtures or manual input. Confirm working directory and redirection expectations.
- Do not infer passing tests from executables in `obj/`.
- Do not add or run tests unless requested or required by the active task. When run, report exact commands and outcomes.
- For relevant changes, add focused backend tests, integration tests that avoid GTK where practical, and manual GUI acceptance checks for visual/interaction behavior.
- Known test concerns: `test_gpcalc.c` has an `int` helper wrapping a `float` result; `test_tchcalc.c` uses a zero-length array. Address these when relevant, not as unrelated cleanup.

## Git workflow and branch safety

- The assessed working reference is `gideon`; the remote default branch is `main`. Check the actual branch and status before significant work.
- Preserve uncommitted and untracked work. Never reset, discard, stash, overwrite or rewrite history to simplify a task.
- Do not force-push or switch branches as part of ordinary implementation.
- Keep changes focused and inspect the final diff.
- Ignored binaries and old branch snapshots may not match current source.

## File modification and command safety

- Inspect relevant implementation, interfaces, tests and decisions before changing code.
- Make the smallest change that satisfies the approved request and architecture.
- Do not delete, move or rename files without explicit authorization.
- Do not replace established implementations, add dependencies, or make unrelated formatting changes without a concrete reason.
- Treat commands that generate or overwrite artifacts as writes. Explain material effects when approval is needed.
- Report exactly what changed and what verification was performed. Do not claim a build or test passed unless it actually did.

## Documentation requirements

- Keep documentation aligned with implemented behavior and approved decisions.
- Update README/setup instructions when the verified build, run or user workflow changes; do not duplicate full technical references here.
- Record significant architecture and data-contract decisions in the appropriate project document.
- Clearly distinguish implemented, planned, inferred, deferred and open items.
- Revisit this file after significant approved architecture or workflow changes.
- README is stale relative to the current repository; update it when a concrete build/run workflow is established, not during unrelated work.

## Known limitations and decisions

- The app is currently CLI-only; GTK4 UI and integration layer are not implemented.
- Course storage retains only credit hours and weighted points.
- There is no build system or verified end-to-end build command.
- `src/savechgp.c` includes `GPA.h`, while the tracked header is `gpa.h`; this case mismatch may fail on case-sensitive systems.
- Input code has failure paths where variables may remain uninitialized; handle carefully when changing it.
- `lgconv()` returns `0` for unknown grades, indistinguishable from a valid F grade value.
- Backend validation does not consistently enforce the CLI’s input ranges.
- Reset/welcome behavior and workstream assignments remain open in the decision records.
- Persistence, CGPA, export and analytics are deferred beyond the MVP.

## Guidance for extending the implementation

Before a change:

1. Check `git status` and the active branch.
2. Read relevant source, headers, tests and current decision documents.
3. Establish whether the behavior is implemented, approved, inferred, open or deferred.
4. Identify the smallest affected file set and preserve existing behavior.

For backend changes, keep GTK out and preserve independent testability. For UI changes, follow the approved flow and use an integration API. For data-model or error-contract changes, update declarations, implementation, tests and relevant documentation together. Afterward, summarize changed behavior, affected files, verification and remaining limitations.

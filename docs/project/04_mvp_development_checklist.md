# Semester GPA MVP — Development Checklist

## Requirements and decisions
- [ ] Confirm ATU grade scale and boundary behaviour.
- [ ] Confirm maximum courses and valid credit-hour values.
- [ ] Confirm handling of empty/duplicate course names.
- [ ] Agree on course-result structure.
- [ ] Agree on backend error conventions.
- [ ] Agree on GTK4 form and results-table requirements.

## Backend
- [ ] Review score-to-letter-grade conversion.
- [ ] Review grade-value conversion.
- [ ] Review weighted grade-point calculation.
- [ ] Review total credit-hour calculation.
- [ ] Review total grade-point calculation.
- [ ] Review semester GPA calculation.
- [ ] Ensure backend functions validate their own inputs.
- [ ] Keep backend independent of GTK4.

## Tests
- [ ] Test every grade boundary.
- [ ] Test scores below 0 and above 100.
- [ ] Test valid and invalid credit hours.
- [ ] Test weighted points and multi-course totals.
- [ ] Test GPA and zero-credit-hour handling.
- [ ] Correct test helper return types.
- [ ] Run tests and record results.

## GTK4 frontend
- [ ] Create main window.
- [ ] Add course-entry controls.
- [ ] Add/remove course rows within agreed limit.
- [ ] Add calculate action.
- [ ] Add clear/reset action if agreed.
- [ ] Display per-course result rows.
- [ ] Display total credit hours and weighted points.
- [ ] Display semester GPA.
- [ ] Show clear validation messages.

## Integration and release
- [ ] Connect GTK input to integration logic.
- [ ] Connect integration logic to C backend.
- [ ] Verify results against known calculations.
- [ ] Test realistic semester and invalid-input scenarios.
- [ ] Update README and setup instructions.
- [ ] Confirm MVP acceptance criteria.

## Deferred to Phase 2
- [ ] Choose semester-record storage format.
- [ ] Save and retrieve semester records.
- [ ] Calculate CGPA from stored semesters.
- [ ] Add export functionality.

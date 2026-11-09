# Architecture Note — GTK4 and C GPA Backend

## Objective
Keep the GTK4 interface independent from the GPA calculation engine so calculations can be tested without GTK and reused later.

## Dependency direction
```text
GTK4 widgets -> UI/application integration -> C calculation functions
```
The calculation layer must not include GTK headers or manipulate GTK widgets.

## GTK4 responsibilities
- Collect course name, score and credit hours.
- Add/remove course rows within the agreed limit.
- Validate obvious UI constraints and show useful errors.
- Trigger calculation and display per-course results and semester totals.

## Integration responsibilities
- Receive values from GTK.
- Validate and convert UI values into backend inputs.
- Call calculation functions.
- Assemble result records for display.

## Backend responsibilities
- Map score to ATU letter grade and grade value.
- Calculate weighted grade points.
- Sum credit hours and weighted points.
- Calculate semester GPA.
- Return clear errors for invalid input.

## Course result
Retain course name, numerical score, letter grade, grade value, credit hours and weighted grade points. The exact C structure and field types must be agreed before implementation.

## Testing
1. Score boundaries and invalid scores.
2. Grade conversion.
3. Weighted grade points.
4. Totals.
5. GPA, including zero total credit hours.
6. Integration function independent of GTK where practical.
7. Full GUI acceptance test.

## Deferred
Persistence, CGPA, export and analytics belong to later phases unless the team explicitly changes MVP scope.

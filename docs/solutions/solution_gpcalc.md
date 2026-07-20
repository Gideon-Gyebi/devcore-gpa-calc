# Algorithm
1. Create to two variables to store grade values and credit hours
2. Multiple the integer values stored in variables
3. Output the product to get the grade point

```
**Course**
↓
Score ✓
↓
Letter Grade ✓
↓
Grade Value ✓
↓
Credit Hours ✓
↓
Grade Point ✓
↓
**Total Grade Point**
↓
**Total Credit Hours**
```

``` C
float gpcalc(float gradeValue, float creditHours);
```

# Pseudocode
1. START
2. FUNCTION `gpcalc(gradeValue,creditHours)`
3. if `gradeValue < 0` OR `creditHours < 0`
4. `return -1.0`
5. `return gradeValue * creditHours`
6. END
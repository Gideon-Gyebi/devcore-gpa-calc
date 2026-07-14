# Algorithm
1. Get the corresponding scrconv for the gradeLetter(LG)
2. Store the gradeLetter
3. Create a conditional statement to determine which LG correspond to the Grade Value(NE)
4. Output the result

```
LG 
↓
convert LG
↓
GV

```

``` C 
float lgconv(char *letterGrade)
```
# Pseudocode
1. Start 
2. char *gradeLetter
3. Input gradeLetter
4. check gradeLetter
5. if gradeLetter = A+ {Output: 5.0}
6. elseif gradeLetter = A {Output: 4.5}
7. elseif gradeLetter = B+ {Output: 4.0}
8. elseif gradeLetter = B {Output: 3.5}
9. elseif gradeLetter = C+ {Output: 3.0}
10. elseif gradeLetter = C {Output: 2.5}
11. elseif gradeLetter = D+{Output: 2.0}
12. elseif gradeLetter = D {Output: 1.5}
13. elseif gradeLetter= F {Output:0}
14.Else Output "Invalid Grade"
15.End If
16.End
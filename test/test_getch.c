#include <stdio.h>
#include "gpa.h"


/*
 * test_getch.c
 * Test file for the getch function
 
 * 1       → lower boundary
 * 3       → upper boundary
 * 2       → normal valid value
 * 2.5     → valid floating-point input
 * 2abc    → valid number + invalid trailing characters
 * 0       → just below range
 * 4       → just above range
 * abc     → completely invalid input
 */


float test_getch(void)
 {
     float creditHours = getch();

     return creditHours;
 }


int main()
{
    float creditHours;

    printf("\n===================== GETCH Function Tests =====================\n\n");

    printf("Test Case 1: Valid input (1) Lower Boundary.\n");
    creditHours = test_getch();
    if (creditHours == 1.0f)
    {
        printf("\n[Credit Hours Entered: %.1f]\n", creditHours);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 2: Valid input (3) Upper Boundary.\n");
    creditHours = test_getch();
    if (creditHours == 3.0f)
    {
        printf("\n[Credit Hours Entered: %.1f]\n", creditHours);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 3: Valid input (2) Normal Value.\n");
    creditHours = test_getch();
    if (creditHours == 2.0f)
    {
        printf("\n[Credit Hours Entered: %.1f]\n", creditHours);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 4: Invalid input (2.5) Valid floating-point input.\n");
    creditHours = test_getch();
    if (creditHours == 2.5f)
    {
        printf("\n[Credit Hours Entered: %.1f]\n", creditHours);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }
    
    printf("----------------------------------------------------------------\n");
    
    printf("\nTest Case 5: Invalid input (2abc) Valid + Invalid Characters.\n");
    creditHours = test_getch();
    if (creditHours == 2.0f)
    {
        printf("\n[Credit Hours Entered: %.1f]\n", creditHours);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 6: Invalid input samples (0, 4, abc) Below Range,\nAbove Range and Completely Invalid.\n");
    test_getch();
    printf("\n[PASS] = Two range errors and one invalid input error.\n");
    printf("[FAIL] = If there are less than three error messages.\n");
    
    printf("\n=========================== Test End ===========================\n");
    
    return 0;
}
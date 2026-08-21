#include<stdio.h>
#include "gpa.h"


/*
 * test_tchcalc.c
 * Test file for the tchcalc function
 * 
 * 3 courses with credit hours 3.0, 1.5, 2.0 → valid input
 * 1 course with credit hour 3.0 → valid input
 * 0 courses → valid input (should return 0.0)
 */


float test_tchcalc(GpaRecord gpaStorage[], int numCourses)
{
    float totalCreditHours = tchcalc(gpaStorage, numCourses);

    return totalCreditHours;
}


int main()
{
    float totalCreditHours;
    int numCourses;

    printf("\n===================== TCHCALC Function Tests =====================\n\n");

    printf("Test Case 1: Valid Input (3 courses with credit hours 3.0, 1.5, 2.0) Normal Case.\n");
    GpaRecord gpaStorage[3] =
    {
        {.creditHour = 3.0f},
        {.creditHour = 1.5f},
        {.creditHour = 2.0f}
    };
    numCourses = 3;
    totalCreditHours = test_tchcalc(gpaStorage, numCourses);
    if (totalCreditHours == 6.5f)
    {
        printf("\n[Total Credit Hours Calculated: %.1f]\n", totalCreditHours);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n\n");

    
    printf("Test Case 2: Valid Input (1 course with credit hour 3.0) Single Course.\n");
    GpaRecord gpaStorage2[1] =
    {
        {.creditHour = 3.0f}
    };
    numCourses = 1;
    totalCreditHours = test_tchcalc(gpaStorage2, numCourses);
    if (totalCreditHours == 3.0f)
    {
        printf("\n[Total Credit Hours Calculated: %.1f]\n", totalCreditHours);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n\n");

    GpaRecord gpaStorage3[0]; // No courses
    numCourses = 0;
    totalCreditHours = test_tchcalc(gpaStorage3, numCourses);
    if (totalCreditHours == 0.0f)
    {
        printf("\n[Total Credit Hours Calculated: %.1f]\n", totalCreditHours);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("\n=========================== Test End ===========================\n");

    return 0;
}
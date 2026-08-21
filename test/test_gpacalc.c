#include<stdio.h>
#include "gpa.h"


/*
 * test_gpacalc.c
 * Test file for the gpacalc function
 * 
 * totalGradePoints, totalCreditHours
 * 90.0, 18.0 → valid input
 * 0.0, 9.0 → valid input
 * 52.5, 0.0 → invalid input (cannot divide by zero)
 * -52.0, 6.0 → invalid input (negative total grade points)
 * 43.0, -2.0 → invalid input (negative total credit hours)
 */


float test_gpacalc(float totalGradePoints, float totalCreditHours)
{
    float gpa = gpacalc(totalGradePoints, totalCreditHours);

    return gpa;
}


int main()
{
    float totalGradePoints;
    float totalCreditHours;
    float gpa;

    printf("\n===================== GPACALC Function Tests =====================\n\n");

    printf("Test Case 1: Valid Input (90.0, 18.0) Normal Case.\n");
    gpa = test_gpacalc(90.0f, 18.0f);
    if (gpa == 5.0f)
    {
        printf("\n[GPA Calculated: %.1f]\n", gpa);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n\n");

    printf("Test Case 2: Valid Input (0.0, 9.0) Edge Case.\n");
    gpa = test_gpacalc(0.0f, 9.0f);
    if (gpa == 0.0f)
    {
        printf("\n[GPA Calculated: %.1f]\n", gpa);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n\n");

    printf("Test Case 3: Invalid Input (52.5, 0.0) Error Case.\n");
    gpa = test_gpacalc(52.5f, 0.0f);
    if (gpa == -1.0f)
    {
        printf("\n[GPA Calculated: %.1f]\n", gpa);
        printf("Returned [-1.0] to indicate an error.\n");
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n\n");

    printf("Test Case 4: Invalid Input (-52.0, 6.0) Error Case.\n");
    gpa = test_gpacalc(-52.0f, 6.0f);
    if (gpa == -1.0f)
    {
        printf("\n[GPA Calculated: %.1f]\n", gpa);
        printf("Returned [-1.0] to indicate an error.\n");
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n\n");

    printf("Test Case 5: Invalid Input (43.0, -2.0) Error Case.\n");
    gpa = test_gpacalc(43.0f, -2.0f);
    if (gpa == -1.0f)
    {
        printf("\n[GPA Calculated: %.1f]\n", gpa);
        printf("Returned [-1.0] to indicate an error.\n");
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("\n=========================== Test End ===========================\n");

    return 0;
}

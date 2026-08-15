#include<stdio.h>
#include "gpa.h"


/*
 * test_gpcalc.c
 * Test file for the gpcalc function
 * 
 * gradeValue, creditHours
 * 5.0, 3.0 → valid input
 * 0.0, 2.5 → valid input
 * 4.5, 0.0 → valid input
 * -1.0, 2.0 → invalid input (negative grade value)
 * 4.0, -2.0 → invalid input (negative credit hours)
 */

 int test_gpcalc(float gradeValue, float creditHours)
 {
     float gradePoint = gpcalc(gradeValue, creditHours);

     return gradePoint;
 }


 int main()
 {
    float gradeValue;
    float creditHours;
    float gradePoint;

    printf("\n===================== GPCALC Function Tests =====================\n\n");

    printf("Test Case 1: Valid Input (5.0, 3.0) Normal Case.\n");
    gradePoint = test_gpcalc(5.0f, 3.0f);
    if (gradePoint == 15.0f)
    {
        printf("\n[Grade Point Calculated: %.1f]\n", gradePoint);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n\n");

    printf("Test Case 2: Valid Input (0.0, 2.5) Edge Case.\n");
    gradePoint = test_gpcalc(0.0f, 2.5f);
    if (gradePoint == 0.0f)
    {
        printf("\n[Grade Point Calculated: %.1f]\n", gradePoint);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n\n");

    printf("Test Case 3: Valid Input (4.5, 0.0) Edge Case.\n");
    gradePoint = test_gpcalc(4.5f, 0.0f);
    if (gradePoint == 0.0f)
    {
        printf("\n[Grade Point Calculated: %.1f]\n", gradePoint);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n\n");

    printf("Test Case 4: Invalid Input (-1.0, 2.0) Error Case.\n");
    gradePoint = test_gpcalc(-1.0f, 2.0f);
    if (gradePoint == -1.0f)
    {
        printf("\n[Grade Point Calculated: %.1f]\n", gradePoint);
        printf("Returned [-1.0] to indicate an error.\n");
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n\n");

    printf("Test Case 5: Invalid Input (4.0, -2.0) Error Case.\n");
    gradePoint = test_gpcalc(4.0f, -2.0f);
    if (gradePoint == -1.0f)
    {
        printf("\n[Grade Point Calculated: %.1f]\n", gradePoint);
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
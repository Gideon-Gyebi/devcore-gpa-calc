#include<stdio.h>
#include "gpa.h"


/*
 * test_gpcalc.c
 * Test file for the gpcalc function
 * 
 * gradeValue, creditHours
 * 5.0, 3.0 → valid input
 * 0.0, 3.0 → valid input
 * 4.5, 0.0 → valid input
 * -1.0, 3.0 → invalid input (negative grade value)
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

    printf("Test Case 1: Valid input (4.0, 3.0) Normal Case.\n");
    gradePoint = test_gpcalc(4.0f, 3.0f);
    if (gradePoint == 12.0f)
    {
        printf("\n[Grade Point Calculated: %.1f]\n", gradePoint);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    
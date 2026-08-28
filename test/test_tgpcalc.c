#include <stdio.h>
#include "gpa.h"

/*
*test_tgpcalc.c
*Test file for the tgpcalc function

*3 courses with gradepoints 12.0, 4.5, 6.0 → valid input
*1 course with gradepoint 12.0 → valid input
*0 courses → valid input (should return 0.0)
*/

float test_tgpcalc(GpaRecord gpaStorage[], int numCourses)
{
    float totalGradePoints = tgpcalc(gpaStorage, numCourses);

    return totalGradePoints;
}

int main()
{
    float totalGradePoints;
    int numCourses;

    printf("\n===================== TGPCALC Function Tests =====================\n\n");

    printf("Test Case 1: Valid Input (3 courses with gradepoints 12.0, 4.5, 6.0) Normal Case.\n");
    GpaRecord gpaStorage[3] =
        {
            {.gradePoint = 12.0f},
            {.gradePoint = 4.5f},
            {.gradePoint = 6.0f}};
    numCourses = 3;
    totalGradePoints = test_tgpcalc(gpaStorage, numCourses);
    if (totalGradePoints == 22.5f)
    {
        printf("\n[Total Grade Points Calculated: %.1f]\n", totalGradePoints);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }
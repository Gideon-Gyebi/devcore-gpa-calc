#include <stdio.h>
#include "gpa.h"

float tgpcalc(float gradePoint, float gradeValue)
{
    int score;
    char *letterGrade;
    float creditHours;
    char *selectedCourse;

    float totalGradePoints = 0.0;

    // 1. STOPS EXACTLY AT 8: The loop condition i <= 8 ensures it stops after the 8th course
    for (int i = 1; i <= 8; i++)
    {
        printf("\n--- COURSE %d OF 8 ---\n", i);

        selectedCourse = getcrs();

        // Handle validation for score
        score = getscr();
        while (score == -1)
        {
            printf("Invalid score. Please re-enter.\n");
            score = getscr();
        }

        // Handle validation for credit hours
        creditHours = getch();
        while (creditHours == -1)
        {
            printf("Invalid credit hours. Please re-enter.\n");
            creditHours = getch();
        }

        // 2. CALCULATE EACH INDIVIDUAL COURSE:
        letterGrade = scrconv(score);
        gradeValue = lgconv(letterGrade);
        gradePoint = gpcalc(gradeValue, creditHours); // Calculates GP for this specific course

        // Display individual result
        printf("Course: %s | Grade Point: %.1f\n", selectedCourse, gradePoint);

        // 3. ACCUMULATE TOTAL: Add current course point to the running total
        totalGradePoints += gradePoint;

        // 4. FIX INFINITE LOOP GLITCH: Clear the remaining enter key (\n) from input stream
        // If left uncleared, the next getcrs() menu will read the leftover '\n' and crash/loop forever.
        while (getchar() != '\n')
            ;
    }

    // 5. CANCELLING/EXITING OUTPUT: Once the loop hits i=9, it breaks automatically and comes here
    printf("\n==================================================\n");
    printf("All 8 courses completed! Exiting loop...\n");
    printf("Final Total Grade Points for all 8 courses: **%.1f**\n", totalGradePoints);
    printf("==================================================\n");
    return totalGradePoints;
}

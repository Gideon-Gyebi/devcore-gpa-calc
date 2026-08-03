#include <stdio.h> // Include the standard input/output library
#include "gpa.h"   // Include the header file for GPA conversion

// Main function to run the GPA conversion program
int main()
{

    // Create storage for GPA records
    GpaRecord gpaStorage[MAX_COURSES];

    // Declare variables for course information
    int score;
    char *letterGrade;
    float gradeValue;
    float creditHours;
    float gradePoint;
    char *selectedCourse;
    int numCourses;
    int index = 0; // Initialize index for storing GPA records
    float totalCreditHours;

    // Call the getnumcrs function to get the number of courses
    numCourses = getnumcrs();

    for (index = 0; index < numCourses; index++)
    {
        // Call the getcrs function to select a course
        selectedCourse = getcrs();

        // Call the getch function to read the credit hours
        creditHours = getch();

        // Prompt the user to enter a score and read the input
        score = getscr();

        // Call the scrconv function to convert the score to a letter grade
        letterGrade = scrconv(score);

        // Call the lgconv function to convert the letter grade to a grade value
        gradeValue = lgconv(letterGrade);

        // Call the gpcalc function to calculate the grade point
        gradePoint = gpcalc(gradeValue, creditHours);

        // Save course record
        savechgp(gpaStorage, index, creditHours, gradePoint);

        // Print the results to the console
        printf("\nSelected Course: %s\n", selectedCourse);
        printf("Grade Letter: %s\n", letterGrade);
        printf("Credit Hours: %.1f\n", creditHours);
        printf("Grade Value: %.1f\n", gradeValue);
        printf("Grade Point: %.1f\n", gradePoint);
    }

    // Call the tchcalc function to calculate the total credit hours
    totalCreditHours = tchcalc(gpaStorage, numCourses);
    printf("\nTotal Credit Hours: %.1f\n", totalCreditHours);

    /*
    // Call the getcrs function to select a course
    selectedCourse = getcrs();

    // Call the getch function to read the credit hours
    creditHours = getch();

    // Prompt the user to enter a score and read the input
    score = getscr();

    // Call the scrconv function to convert the score to a letter grade
    letterGrade = scrconv(score);

    // Call the lgconv function to convert the letter grade to a grade value
    gradeValue = lgconv(letterGrade);

    // Call the gpcalc function to calculate the grade point
    gradePoint = gpcalc(gradeValue, creditHours);

    // Save first course record
    savechgp(gpaStorage, 0, creditHours, gradePoint);

    // Print the results to the console
    // displayResults(letterGrade, creditHours, gradeValue, gradePoint);

    printf("\nSelected Course: %s\n", selectedCourse);
    printf("Grade Letter: %s\n", letterGrade);
    printf("Credit Hours: %.1f\n", creditHours);
    printf("Grade Value: %.1f\n", gradeValue);
    printf("Grade Point: %.1f\n", gradePoint);
    printf("Total Grade Point: %.1f\n", tgpcalc(gradePoint, gradeValue));
    */

    return 0;
}
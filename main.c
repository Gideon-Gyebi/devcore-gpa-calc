#include <stdio.h> // Include the standard input/output library
#include "gpa.h"   // Include the header file for GPA conversion

// Main function to run the GPA conversion program
int main()
{

    // Declare variables for the score and the resulting letter grade
    int score;
    char *letterGrade;
    float gradeValue;
    float creditHours;
    float gradePoint;
    char *selectedCourse;

    // Call the getcrs function to select a course
    selectedCourse = getcrs();

    // Prompt the user to enter a score and read the input
    score = getscr();

    // Call the getch function to read the credit hours
    creditHours = getch();

    // Call the scrconv function to convert the score to a letter grade
    letterGrade = scrconv(score);

    // Call the lgconv function to convert the letter grade to a grade value
    gradeValue = lgconv(letterGrade);

    // Call the gpcalc function to calculate the grade point
    gradePoint = gpcalc(gradeValue, creditHours);

    // Print the results to the console
    // displayResults(letterGrade, creditHours, gradeValue, gradePoint);

    printf("Selected Course: %s\n", selectedCourse);
    printf("Grade Letter: %s\n", letterGrade);
    printf("Credit Hours: %.1f\n", creditHours);
    printf("Grade Value: %.1f\n", gradeValue);
    printf("Grade Point: %.1f\n", gradePoint);

    return 0;
}
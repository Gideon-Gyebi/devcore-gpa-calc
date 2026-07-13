#include <stdio.h> // Include the standard input/output library
#include "gpa.h" // Include the header file for GPA conversion

// Main function to run the GPA conversion program
int main() {

    // Declare variables for the score and the resulting letter grade
    int score;
    char *letterGrade;
    float creditHours;
    // int gradePoint;

    // Prompt the user to enter a score and read the input
    printf("Enter a score: ");
    scanf("%d", &score);

    // Call the getch function to read the credit hours
    creditHours = getch();

    // Call the scrconv function to convert the score to a letter grade
    letterGrade = scrconv(score);

    // Call the gpcalc function to calculate the grade point
    // gradePoint = gpcalc(gradeValue, creditHours);

    // Print the results to the console
    printf("Grade Letter: %s\n", letterGrade);
    printf("Credit Hours: %.1f\n", creditHours);

    // printf("Grade Point: %.1f\n", gradePoint);

    return 0;
}
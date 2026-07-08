#include <stdio.h> // Include the standard input/output library
#include "gpa.h" // Include the header file for GPA conversion

// Main function to run the GPA conversion program
int main() {

    // Declare variables for the score and the resulting letter grade
    int score;
    char *gradeLetter;

    // Prompt the user to enter a score and read the input
    printf("Enter a score: ");
    scanf("%d", &score);

    // Call the scrconv function to convert the score to a letter grade
    gradeLetter = scrconv(score);

    // Print the resulting letter grade to the console
    printf("%s\n", gradeLetter);

    return 0;
}
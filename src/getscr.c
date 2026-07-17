#include <stdio.h>
#include "gpa.h" // Include the header file for GPA calculation

// Function to read the number of credit hours from the user
int getscr(void)
{
    int score;

    printf("Enter the score (e.g., 85 or 90): ");
    
    if (scanf("%d", &score) != 1) // Check if the input is valid
    {
        fprintf(stderr, "GETSCR_Error: Invalid input for score.\n"); // Print an error message to standard error
        return -1; // Return an error value
    }

    if (score < 0 || score > 100 ) // Check if the score is within the valid range (0 to 100)
    {
        fprintf(stderr, "GETSCR_Error: Score must be between 0 and 100.\n"); // Print an error message to standard error
        return -1; // Return an error value
    }

    while (getchar() != '\n'); // Clear the input buffer to remove any leftover characters

    return score;
}
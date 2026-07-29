#include <stdio.h>
#include "gpa.h" // Include the header file for GPA calculation

// Function to read the number of credit hours from the user
int getscr(void)
{
    int score;
    char clear; // Variable to clear the input buffer

    do
    {
        printf("Enter the score (e.g., 85 or 90): ");
        
        if (scanf("%d", &score) != 1) // Check if the input is valid
        {
            fprintf(stderr, "GETSCR_Error: Invalid input for score.\n"); // Print an error message to standard error
        
            while (getchar() != '\n'); // Clear the input buffer to remove any leftover characters
        }

        else if (score < 0 || score > 100) // Check if the score is within the valid range (0 to 100)
        {
            fprintf(stderr, "GETSCR_Error: Score must be between 0 and 100.\n"); // Print an error message to standard error
        
            while (getchar() != '\n'); // Clear the input buffer to remove any leftover characters
        }

        else if (scanf("%c", &clear) == 1 && clear != '\n') // Check if there are any leftover characters in the input buffer
        {
            fprintf(stderr, "GETSCR_Warning: Extra characters are not allowed.\n"); // Print an error message to standard error
            
            while (getchar() != '\n'); // Clear the input buffer to remove any leftover characters
        }
    } while (score < 0 || score > 100); // Repeat the prompt until a valid score is entered
    
    return score;
}
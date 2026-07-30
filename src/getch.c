#include <stdio.h>
#include "gpa.h" // Include the header file for GPA calculation

// Function to read the number of credit hours from the user
float getch(void)
{
    float creditHours;
    char clear; // Variable to clear the input buffer

    do
    {
        printf("Enter the number of credit hours (e.g., 3.0 or 3): ");

        if (scanf("%f", &creditHours) != 1) // Check if the input is valid
        {
            fprintf(stderr, "GETCH_Error: Invalid input for credit hours.\n"); // Print an error message to standard error
            while (getchar() != '\n')
                ; // Clear the input buffer to remove any leftover characters
        }

        else if (creditHours < 1 || creditHours > 3) // Check if the credit hours are within the valid range (1 to 3)
        {
            fprintf(stderr, "GETCH_Error: Credit hours should range from 1 and 3.\n"); // Print an error message to standard error
            while (getchar() != '\n')
                ; // Clear the input buffer to remove any leftover characters
        }

        else if (scanf("%c", &clear) == 1 && clear != '\n') // Check if there are any leftover characters in the input buffer
        {
            fprintf(stderr, "GETCH_Warning: Extra characters are not allowed.\n"); // Print an error message to standard error
            while (getchar() != '\n')
                ; // Clear the input buffer to remove any leftover characters
        }
    } while (creditHours < 1 || creditHours > 3); // Repeat the prompt until valid credit hours are entered

    return creditHours;
}
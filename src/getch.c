#include <stdio.h>
#include "gpa.h" // Include the header file for GPA calculation

// Function to read the number of credit hours from the user
float getch(void) 
{
    float creditHours;

    printf("Enter the number of credit hours (e.g., 3.0 or 3): ");
    if (scanf("%f", &creditHours) != 1) // Check if the input is valid
    {
        fprintf(stderr, "Error reading credit hours.\n"); // Print an error message to standard error
        return -1; // Return an error value
    }
    if (creditHours < 1 || creditHours > 3 ) // Check if the credit hours are within the valid range (1 to 3)
    {
        fprintf(stderr, "Credit hours must be between 1 and 3.\n"); // Print an error message to standard error
        return -1; // Return an error value
    }

    return creditHours;
}
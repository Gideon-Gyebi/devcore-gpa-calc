#include <stdio.h>
#include "gpa.h"

// Function to read the number of courses from the user
int getnumcrs(void)
{
    int numCourses;
    char clear; // Variable to check for extra characters in input

    do
    {
        printf("Enter the number of courses (1-%d): ", MAX_COURSES);

        // Check if the input is a valid integer
        if (scanf("%d", &numCourses) != 1)
        {
            fprintf(stderr, "GETNUMCRS_Error: Invalid input for number of courses.\n");

            while (getchar() != '\n'); // Clear invalid input
        }

        // Check if the number of courses is within the valid range
        else if (numCourses < 1 || numCourses > MAX_COURSES)
        {
            fprintf(stderr, "GETNUMCRS_Error: Number of courses should range from 1 to %d.\n", MAX_COURSES);

            while (getchar() != '\n'); // Clear remaining input
        }

        // Check for extra characters after the number
        else if (scanf("%c", &clear) == 1 && clear != '\n')
        {
            fprintf(stderr, "GETNUMCRS_Warning: Extra characters are not allowed.\n");

            while (getchar() != '\n'); // Clear extra characters
        }

    } while (numCourses < 1 || numCourses > MAX_COURSES);

    return numCourses;
}
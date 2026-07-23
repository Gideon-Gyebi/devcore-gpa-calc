#include <stdio.h>
#include "gpa.h" // Include the header file for GPA calculation

// Function to get the selected course
char *getcrs(void)
{
    char *course;

    // Display the list of available courses
    printf("\n AVAILABLE COURSES \n");
    printf("1. Programming Fundamentals\n");
    printf("2. Mathematics for computer Science\n");
    printf("3. Communication Skills\n");
    printf("4. Numeracy skills\n");
    printf("5. Computer system installation and maintenance\n");
    printf("6. Office productivity\n");
    printf("7. Fundamentals of computer science\n");

    // Prompt the user until a valid choice is entered
    do
    {
        printf("\nSelect a course (1-7): "); // Prompt the user to select a course
        scanf("%d", &course);                // Read the user's input for the course number

        if (course < 1 || course > 7) // Check if the input is within the valid range (1 to 7)
        {
            printf("GETCRS_Error: Course number should range from 1 to 7.\n"); // Display an error message if the input is invalid
        }

    } while (course < 1 || course > 7); // Repeat the prompt until a valid course number is entered

    // Return the selected course

    return course;
}
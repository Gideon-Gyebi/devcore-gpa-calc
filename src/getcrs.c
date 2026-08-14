#include <stdio.h>
#include "gpa.h" // Include the header file for GPA calculation

// Function to get the selected course
char *getcrs(void)
{
    static char course[100]; // Static array to store the course name
    int choice;
    char clear; // Variable to clear the input buffer

    // Display the list of available courses
    printf("\n AVAILABLE COURSES \n");
    printf("1. Programming Fundamentals\n");
    printf("2. Mathematics for Computer Science\n");
    printf("3. Communication Skills\n");
    printf("4. Numeracy Skills\n");
    printf("5. Computer System Installation and Maintenance\n");
    printf("6. Office Productivity\n");
    printf("7. Fundamentals of Computer Science\n");
    printf("8. Others [Enter the course name manually]\n"); // Prompt the user to select a course

    // Prompt the user until a valid choice is entered
    do
    {
        printf("\nSelect a course (1-8): "); // Prompt the user to select a course
        if (scanf("%d", &choice) != 1)       // Check if the input is valid . To read the user's input for the course number
        {
            fprintf(stderr, "GETSCR_Error: Invalid input; please enter a number.\n"); // Print an error message to standard error
            while (getchar() != '\n')
                ; // Clear the input buffer to remove any leftover characters
        }
        else if (choice < 1 || choice > 8) // Check if the input is within the valid range (1 to 8)
        {
            fprintf(stderr, "GETCRS_Error: Course number should range from 1 to 8.\n"); // Display an error message if the input is invalid
            while (getchar() != '\n')
                ;
            // Clear the input buffer to remove any leftover characters
        }
        else if (scanf("%c", &clear) == 1 && clear != '\n') // Check if there are any leftover characters in the input buffer
        {
            fprintf(stderr, "GETCRS_Warning: Extra characters are not allowed.\n"); // Print an error message to standard error
            while (getchar() != '\n')
                ; // Clear the input buffer to remove any leftover characters
        }
    } while (choice < 1 || choice > 8); // Repeat the prompt until a valid course number is entered

    // Return the selected course
    switch (choice)
    {
    case 1:
        return "Programming Fundamentals";
        break;
    case 2:
        return "Mathematics for Computer Science";
        break;
    case 3:
        return "Communication Skills";
        break;
    case 4:
        return "Numeracy Skills";
        break;
    case 5:
        return "Computer System Installation and Maintenance";
        break;
    case 6:
        return "Office Productivity";
        break;
    case 7:
        return "Fundamentals of Computer Science";
        break;
    case 8:
        printf("Enter the course name: "); // Prompt the user to enter the course name manually
        scanf("%99[^\n]", course);         // Read the course name from the user
        return course;
    }
}
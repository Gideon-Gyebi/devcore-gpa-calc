#include "gpa.h" // Include the header file for GPA calculation

// Function to calculate the grade point based on the grade value and credit hours
float gpcalc(float gradeValue, float creditHours)
{
    if (gradeValue < 0 || creditHours < 0) // Check for invalid input values
    {
        return -1.0;
    }
    
    // Calculate and return the grade point by multiplying grade value with credit hours
    return gradeValue * creditHours; 
}
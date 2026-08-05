#include "gpa.h"

// Function to calculate the GPA based on total grade points and total credit hours
float gpacalc(float totalGradePoints, float totalCreditHours)
{
    if (totalGradePoints < 0 || totalCreditHours <= 0) // Check for invalid input values
    {
        return -1.0; // Return -1.0 to indicate an error
    }
    // Calculate GPA by dividing total grade points by total credit hours
    return totalGradePoints / totalCreditHours;
}
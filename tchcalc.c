#include "gpa.h"

// Calculates the total credit hours of all stored courses
float tchcalc(GpaRecord gpaStorage[], int numCourses)
{
    float totalCreditHour = 0.0; // Initialize total credit hours to zero
    int index;
    
    // Sum the credit hours of all stored courses
    for (index = 0; index < numCourses; index++)
    {
        totalCreditHour += gpaStorage[index].creditHour;
    }

    return totalCreditHour;
}
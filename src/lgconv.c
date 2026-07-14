#include "gpa.h"

float lgconv(char *letterGrade) // Function to convert a lettergrade to a grade value
{
    // Determine the grade value based on its corresponding letter grade
    if (letterGrade = "A+")
    {
        return 5.0;
    }

    else if (letterGrade = "A")
    {
        return 4.5;
    }

    else if (letterGrade = "B+")
    {
        return 4.0;
    }

    else if (letterGrade = "B")
    {
        return 3.5;
    }

    else if (letterGrade = "C+")
    {
        return 3.0;
    }

    else if (letterGrade = "C")
    {
        return 2.5;
    }

    else if (letterGrade = "D+")
    {
        return 2.0;
    }

    else if (letterGrade = "D")
    {
        return 1.5;
    }

    else
    {
        return 0;
    }
}
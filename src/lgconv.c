#include "gpa.h"
#include <string.h>

float lgconv(char *letterGrade) // Function to convert a lettergrade to a grade value
{
    // Determine the grade value based on its corresponding letter grade
    // if (letterGrade = "A+")
    if (strcmp(letterGrade, "A+") == 0)
    {
        return 5.0;
    }

    else if (strcmp(letterGrade, "A") == 0)
    {
        return 4.5;
    }

    else if (strcmp(letterGrade, "B+") == 0)
    {
        return 4.0;
    }

    else if (strcmp(letterGrade, "B") == 0)
    {
        return 3.5;
    }

    else if (strcmp(letterGrade, "C+") == 0)
    {
        return 3.0;
    }

    else if (strcmp(letterGrade, "C") == 0)
    {
        return 2.5;
    }

    else if (strcmp(letterGrade, "D+") == 0)
    {
        return 2.0;
    }

    else if (strcmp(letterGrade, "D") == 0)
    {
        return 1.5;
    }

    else
    {
        return 0;
    }
}
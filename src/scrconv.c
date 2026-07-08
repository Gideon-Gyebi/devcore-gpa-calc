#include "gpa.h" // Include the header file for GPA conversion

char *scrconv(int score) // Function to convert a numerical score to a letter grade
{
    // Check if the score is within the valid range of 0 to 100
    if (score < 0 || score > 100)
    {
        return "INVALID";
    }

    // Determine the letter grade based on the score
    if (score >= 85)
    {
        return "A+";
    }
    else if (score >= 80)
    {
        return "A";
    }
    else if (score >= 75)
    {
        return "B+";
    }
    else if (score >= 70)
    {
        return "B";
    }
    else if (score >= 65)
    {
        return "C+";
    }
    else if (score >= 60)
    {
        return "C";
    }
    else if (score >= 55)
    {
        return "D+";
    }
    else if (score >= 50)
    {
        return "D";
    }
    else
    {
        return "F";
    }
}
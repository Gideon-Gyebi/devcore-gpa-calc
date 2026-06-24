#include <stdio.h>
#include "gpa.h"

int main() {
    int score;
    char *gradeLetter;

    printf("Enter a score: ");
    scanf("%d", &score);

    gradeLetter = gpconv(score);

    printf("%s\n", gradeLetter);

    return 0;
}
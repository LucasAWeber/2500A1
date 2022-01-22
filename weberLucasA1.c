#include "weberLucasA1.h"

FILE *openFileForReading(char *fileName)
{
    return fopen(fileName, "r");
}

int readMovies(FILE *file, char movieNames[NUMBER_MOVIES][MAX_STR])
{
    int i = 0;
    while (!feof(file))
    {
        fgets(movieNames[i], MAX_STR, file);
        i++;
    }
    return 1;
}

int readReviews(FILE *file, reviewStruct reviews[NUMBER_REVIEWERS])
{
    int i = 0;
    while (!feof(file))
    {
        
        i++;
    }
    return 1;
}
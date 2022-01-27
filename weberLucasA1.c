#include "weberLucasA1.h"

FILE *openFileForReading(char *fileName)
{
    return fopen(fileName, "r");
}

int readMovies(FILE *file, char movieNames[NUMBER_MOVIES][MAX_STR])
{
    if (file == NULL)
    {
        return 0;
    }
    int i = 0;
    while (!feof(file))
    {
        if (i == NUMBER_MOVIES)
        {
            return 0;
        }
        fgets(movieNames[i], MAX_STR, file);
        movieNames[i][strlen(movieNames) - 1] = '\0';
        i++;
    }
    if (i < NUMBER_MOVIES)
    {
        return 0;
    }
    return 1;
}

int readReviews(FILE *file, reviewStruct reviews[NUMBER_REVIEWERS])
{
    int i = 0;
    while (!feof(file))
    {
        fscanf(file, "%s", reviews[i].reviewer);
        i++;
    }
    return 1;
}
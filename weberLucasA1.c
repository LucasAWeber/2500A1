#include "weberLucasA1.h"

// opens passed in file in read mode
FILE *openFileForReading(char *fileName)
{
    return fopen(fileName, "r");
}

// reads movies from the passed in txt file to the passed in array with abnormal exits
int readMovies(FILE *file, char movieNames[NUMBER_MOVIES][MAX_STR])
{
    if (!file)
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
        if (movieNames[i][strlen(movieNames[i]) - 1] == '\n')
        {
            movieNames[i][strlen(movieNames[i]) - 1] = '\0';
        }
        i++;
    }
    if (i < NUMBER_MOVIES)
    {
        return 0;
    }
    return 1;
}

// reads reviews from the passed in txt file to the passed in array with abnormal exits
int readReviews(FILE *file, reviewStruct reviews[NUMBER_REVIEWERS])
{
    if (!file)
    {
        return 0;
    }
    int i = 0;
    char readFromFile[MAX_STR];
    char charRatings[NUMBER_MOVIES][MAX_STR];
    while (!feof(file))
    {
        if (i == NUMBER_REVIEWERS)
        {
            return 0;
        }
        fgets(readFromFile, MAX_STR, file);
        strcpy(reviews[i].reviewer, strtok(readFromFile, " "));
        for (int j = 0; j < 3; j++)
        {
            strcpy(charRatings[j], strtok(NULL, " "));
            if (charRatings[j][strlen(charRatings[j]) - 1] == '\n')
            {
                charRatings[j][strlen(charRatings[j]) - 1] = '\0';
            }
            if (charRatings[j][0] == 'Y' || charRatings[j][0] == 'y')
            {
                reviews[i].feedback[j] = 1;
            }
            else if (charRatings[j][0] == 'N' || charRatings[j][0] == 'n')
            {
                reviews[i].feedback[j] = 0;
            }
        }
        i++;
    }
    if (i < NUMBER_REVIEWERS)
    {
        return 0;
    }
    return 1;
}

// reads the feedback from reviewers from struct determining how many/who are the most critical reviewers
int getMostCriticalReviewers(reviewStruct reviews[NUMBER_REVIEWERS], char mostCriticalReviewers[NUMBER_REVIEWERS][MAX_STR])
{
    int mostNegReviews = 0;
    int currentNegReviews = 0;
    int numCriticalReviewers = 0;

    for (int i = 0; i < NUMBER_REVIEWERS; i++)
    {
        currentNegReviews = 0;
        for (int j = 0; j < NUMBER_MOVIES; j++)
        {
            if (reviews[i].feedback[j] == 0)
            {
                currentNegReviews += 1;
            }
        }
        if (currentNegReviews > mostNegReviews)
        {
            mostNegReviews = currentNegReviews;
        }
    }

    for (int i = 0; i < NUMBER_REVIEWERS; i++)
    {
        currentNegReviews = 0;
        for (int j = 0; j < NUMBER_MOVIES; j++)
        {
            if (reviews[i].feedback[j] == 0)
            {
                currentNegReviews += 1;
            }
        }
        if (currentNegReviews == mostNegReviews)
        {
            strcpy(mostCriticalReviewers[numCriticalReviewers], reviews[i].reviewer);
            numCriticalReviewers += 1;
        }
    }
    return numCriticalReviewers;
}

int getMostRecommendedMovies(const char movieNames[NUMBER_MOVIES][MAX_STR], const reviewStruct reviews[NUMBER_REVIEWERS], char mostRecommendedMovies[NUMBER_MOVIES][MAX_STR])
{
    int intMostRecommendedMovies = 0;
    int currentMovieRecommendations = 0;
    int numMostRecommendedMovies = 0;

    for (int i = 0; i < NUMBER_MOVIES; i++)
    {
        currentMovieRecommendations = 0;
        for (int j = 0; j < NUMBER_REVIEWERS; j++)
        {
            if (reviews[j].feedback[i] == 0)
            {
                currentMovieRecommendations += 1;
            }
        }
        if (currentMovieRecommendations > intMostRecommendedMovies)
        {
            intMostRecommendedMovies = currentMovieRecommendations;
        }
    }

    for (int i = 0; i < NUMBER_MOVIES; i++)
    {
        currentMovieRecommendations = 0;
        for (int j = 0; j < NUMBER_REVIEWERS; j++)
        {
            if (reviews[j].feedback[i] == 0)
            {
                currentMovieRecommendations += 1;
            }
        }
        if (currentMovieRecommendations == intMostRecommendedMovies)
        {
            strcpy(mostRecommendedMovies[numMostRecommendedMovies], movieNames[i]);
            numMostRecommendedMovies += 1;
        }
    }
    return numMostRecommendedMovies;
}
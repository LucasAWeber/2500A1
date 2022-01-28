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
int readReviews(FILE *file, struct reviewStruct reviews[NUMBER_REVIEWERS])
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
int getMostCriticalReviewers(struct reviewStruct reviews[NUMBER_REVIEWERS], char mostCriticalReviewers[NUMBER_REVIEWERS][MAX_STR])
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

// reads the reviews for each movie determining the most recommended movies and how many of them there are
int getMostRecommendedMovies(const char movieNames[NUMBER_MOVIES][MAX_STR], const struct reviewStruct reviews[NUMBER_REVIEWERS], char mostRecommendedMovies[NUMBER_MOVIES][MAX_STR])
{
    int intMostRecommendedMovies = 0;
    int currentMovie = 0;
    int numMostRecommended = 0;

    for (int i = 0; i < NUMBER_MOVIES; i++)
    {
        currentMovie = 0;
        for (int j = 0; j < NUMBER_REVIEWERS; j++)
        {
            if (reviews[j].feedback[i] == 1)
            {
                currentMovie += 1;
            }
        }
        if (currentMovie > intMostRecommendedMovies)
        {
            intMostRecommendedMovies = currentMovie;
        }
    }

    for (int i = 0; i < NUMBER_MOVIES; i++)
    {
        currentMovie = 0;
        for (int j = 0; j < NUMBER_REVIEWERS; j++)
        {
            if (reviews[j].feedback[i] == 1)
            {
                currentMovie += 1;
            }
        }
        if (currentMovie == intMostRecommendedMovies)
        {
            strcpy(mostRecommendedMovies[numMostRecommended], movieNames[i]);
            numMostRecommended += 1;
        }
    }
    return numMostRecommended;
}

// predicts the performance of a movie based on the title (number of words, characters, etc)
int predictMovie(const char movie[MAX_STR])
{
    int numWords = 1;
    int sales = 0;
    int j;
    int evenNumChars = 0;
    int numLetters = 0;
    int sameLetters;
    for (int i = 0; i < strlen(movie) - 1; i++)
    {
        if(movie[i] == ' ' && movie[i+1] != ' ')
        {
            numWords++;
        }
    }

    if (numWords > 2)
    {
        sales--;
    }
    else if (numWords == 1)
    {
        sales -= 2;
    }

    if (numWords > 1)
    {
        for (int i = 0; i < numWords; i++)
        {
            j = 0;
            while (movie[j] != ' ' && movie[j] != '\0')
            {
                j++;
            }
            if (j % 2 == 0)
            {
                evenNumChars++;
            }
        }
        if (evenNumChars >= 2)
        {
            sales++;
        }
    }

    j = -1;
    for (int i = 0; i < numWords; i++)
    {
        j++;
        while (movie[j] != ' ' && movie[j] != '\0')
        {
            j++;
        }
        if (i == 0)
        {
            sameLetters = 1;
            numLetters = j;
        }
        else if (j - (i * (numLetters + 1)) != numLetters)
        {
            sameLetters = 0;
        }
    }
    if (sameLetters == 1)
    {
        sales += 2;
    }

    if (sales > 2)
    {
        sales = 2;
    }
    else if (sales < -2)
    {
        sales = -2;
    }
    return sales;
}

int enumerateMovie(const char movie[MAX_STR], int charCounts[MAX_WORDS])
{
    int numWords = 1;
    int j = -1;
    for (int i = 0; i < strlen(movie) - 1; i++)
    {
        if(movie[i] == ' ' && movie[i+1] != ' ')
        {
            numWords++;
        }
    }

    for (int i = 0; i < numWords; i++)
    {
        j++;
        while (movie[j] != ' ' && movie[j] != '\0')
        {
            j++;
        }
        if (i == 0)
        {
            charCounts[i] = j;
        }
        else
        {
            charCounts[i] = j;
            for (int k = 0; k < i; k++)
            {
                charCounts[i] -= charCounts[k] + 1;
            }
        }
    }
    for (int i = 0; i < numWords; i++)
    {
        printf("number of characters in the %dth term: %d\n", i, charCounts[i]);
    }

    return numWords;
}
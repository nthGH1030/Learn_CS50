#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if(score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    // take the argument, break it down to char
    char *s = word;
    // Go through all the char ,compare the char with the list of array, find the score
    int i = 0;
    int y = 0;
    int totalScore = 0;
    int lowerLetterScore = 0;
    int UpperLetterScore = 0;
    int index = 0;
    //Lowerletter
    while((s[i] != '\0') )
    {
        // Get the index of points array using relationship of char with ASCII printable character
        if(s[i] > 96 && s[i] < 123)
        {
            index = s[i] - 97;
            lowerLetterScore += POINTS[index];
            i++;
        }
        else if (s[i] > 64 && s[i] < 91)
        {
            index = s[i] - 65;
            UpperLetterScore += POINTS[index];
            i++;
        }
        else
        {
            i++;
            continue;
        }
        //printf("Lower score: %i\n", lowerLetterScore);
    }

    totalScore = lowerLetterScore + UpperLetterScore;
    return totalScore;

}
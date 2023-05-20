#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentence(string text);

int main(void)
{
    //promt input
    string input = get_string("Text: ");
    //print out the string;
    printf("%s\n", input);
    //Call count_letters(string text)
    int letter = count_letters(input);
    int word = count_words(input);
    int sentence = count_sentence(input);
    printf("%i letters \n", letter);
    printf("%i words \n", word);
    printf("%i sentences \n", sentence);

    float L = (float)letter / (float)word * 100;

    float S = (float)sentence / (float)word * 100;


    //Coleman-Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int rindex = round(index);
    printf("%f\n",index);

    if(rindex < 16 && rindex > 0)
    {
        printf("Grade %i\n", rindex);
    }
    else if(rindex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(rindex >= 16)
    {
        printf("Grade 16+\n");
    }


}

int count_letters(string text)
{
    int letterCount = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        if(isalpha(text[i]) != 0)
        {
            letterCount++;
        }
    }
    return letterCount;
}

int count_words(string text)
{
    int wordCount = 1;
    for(int i = 0; i < strlen(text); i++)
    {
        if(text[i] == 32)
        {
            wordCount++;
        }
    }
    return wordCount;
}

int count_sentence(string text)
{
    int sentenceCount = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        if(text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sentenceCount++;
        }
    }
    return sentenceCount;
}
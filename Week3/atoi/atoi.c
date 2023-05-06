#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);
int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    //Get the array length
    int length = strlen(input);
    //base case
    if (length == 0)
    {
        return 0;
    }
    else
    {
        //Convert this char into its numeric value. Can you subtract some char to do this?
        // if length is 1, ASCII 1 is 49, ASCII 0 is 48, 1 - 0 = 1(integer)
        int totalValue = input[length-1] - '0';
        //Remove the last char from the string by moving the null terminator one position to the left.
        input[length-1] = '\0';
        //Return converted string as digit
        return totalValue  + 10 * convert(input);
    }
}
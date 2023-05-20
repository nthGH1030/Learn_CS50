// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
string replace(string words);

int main(int argc, string argv[])
{
    //Use the replace function on the command line arguement and print out the answer
    string output;
    output = replace(argv[1]);
    printf("%s\n", output);

    //If program is executed without command-line argument, propmt error
    if(argc != 1)
    {
        printf("invald input");
        return 1;
    }
}


string replace(string words)
{
    int i = 0;
    char *s = words;
    while (s[i] != '\0')
    {
        if(s[i] == 'a')
        {
            s[i] = '6';
        }
        else if(s[i] == 'e')
        {
            s[i] = '3';
        }
        else if(s[i] == 'i')
        {
            s[i] = '1';
        }
        else if(s[i] == 'o')
        {
            s[i] = '0';
        }
        i++;
    }
    return s;
}
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

char * encryption(string plaintext, string key);
char Checkkey(string key1);

int main(int argc, string argv[])
{
    string inputKey = argv[1];


    //print out the encryted message
    if (argc == 2)
        {
            if(Checkkey(inputKey) == 'c')
            {
                //Promt user input
                string inputPlaintext = get_string("plaintext: ");
                string output = encryption(inputPlaintext, inputKey);
                printf("ciphertext: %s\n", output);
            }
            else if(Checkkey(inputKey) == 'a')
            {
                printf("Key contains invalid character\n");
                return 1;
            }
            else if(Checkkey(inputKey) == 'b')
            {
                printf("Invalid key Length\n");
                return 1;
            }
            else if(Checkkey(inputKey) == 'd')
            {
                printf("There are duplicate characters in key\n");
                return 1;
            }

        }

    else if (argc != 2)
    {
        printf("Please input a valid key\n");
        return 1;
    }
    else
    {
        return 1;
    }

}

char * encryption(string plaintext, string key)
{
    //implement function to encrypt a message
    int i = 0;
    char *s = plaintext;
    char *k = key;

    //encrypt the array
    while(s[i] != '\0')
    {
        //If the array is lowercase
        if(s[i] > 96 && s[i] < 123)
        {
            s[i] = tolower(k[(s[i]-97)]);
            i++;
        }
        //If the array is uppercase
        else if (s[i] > 64 && s[i] < 91)
        {
            s[i] = toupper(k[(s[i]-65)]);
            i++;
        }
        //Remain unchange for all other outcome
        else
        {
            i++;
        }
    }
    return s;

}

char Checkkey(string key1)
{
    char message;
    int y = 0;
    char *k1 = key1;
    while(k1[y] != '\0')
    {
        // if the key include an non alphabetic character
        if((k1[y] > 0 && k1[y] < 65) || (k1[y] > 90 && k1[y] < 97) || (k1[y]> 122 && k1[y] < 127))
        {
            message = 'a';
            break;
        }
        //If each key does not appear exactly once
        for(int x = 0; x < y ; x++)
        {
            if(k1[x] == k1[y])
            {
                message = 'd';
                goto end;
            }
        }
        //If the character is not exactly 26
        if (y != 25)
        {
            message = 'b';
        }
        else
        {
            message = 'c';
        }
        y++;
    }
    end:
    return message;
}
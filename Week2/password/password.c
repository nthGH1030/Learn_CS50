// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int i = 0;
    char *s = password;
    bool symbol = false;
    bool lowercase = false;
    bool uppercase = false;
    bool number = false;
    while(s[i] != '\0')
    {

        if((s[i] > 32 && s[i] < 48) || (s[i] > 57 && s[i] < 65) ||
        (s[i] > 90 && s[i] < 97) || (s[i] > 122 && s[i] < 127))
        {
            //if it is a symbol
            symbol = true;
        }
        else if(s[i] > 96 && s[i] < 123 )
        {
            //if it is a lowercase
            lowercase = true;
        }
        else if(s[i] > 64 && s[i] < 91 )
        {
            //if it is a uppercase
            uppercase = true;
        }
        else if(s[i] > 47 && s[i] < 58 )
        {
            //if it is a number
            number = true;
        }

        i++;
    }

    if (symbol == true && lowercase == true && uppercase == true && number == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

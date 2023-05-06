#include <cs50.h>
#include <stdio.h>

#include <stdio.h>

int main(void)
{
    //promt user to input card number
    long int cardNumber;

    cardNumber = get_long("Credit Card Number: ");
    long int n = cardNumber;
    //check how many digits a card has
    int count = 0;
    long int i = cardNumber;
    long int cardNumber2 = cardNumber;
    while(i > 0)
    {
        i = i / 10;
        count++;
    }

    //Use Luhn's algorithm to check if the card number is valid

    long int digit;
    long int remainder;
    long int product;
    long int product1;
    long int product2;
    long int sum = 0;
    if (count == 16)
    {
        for(int y = 0; y < (count/2); y ++)
        {
            //use the remainder method to get the second last digit
            remainder = cardNumber % 100;
            remainder = remainder / 10;
            //move 2 digit ahead
            cardNumber = cardNumber / 100;
            //each digit * 2
            product = remainder * 2;
            // add up the digits
            if (product > 9)
            {
                //first digit of the product
                product1 = product % 10;
                //Second digit of the product
                product2 = product /10;
                sum = sum + product1 + product2 ;
            }
            else
            {
                sum = sum + product;
            }

            //printf("%li\n", sum);
        }

    long int remainder2;
    long int sum1=0;

        for(int y = 0; y < (count/2); y ++)
        {
            //use the remainder method to get the last digit
            remainder2 = cardNumber2 % 10;
            //move 2 digit ahead
            cardNumber2 = cardNumber2 / 100;
            // add up the digits
            sum1 = sum1 + remainder2;

            //printf("%li\n", sum1);
        }

    long int sum3;
    sum3 = sum1 + sum;
    printf("%li\n", sum3);
    //*10 to the division number, check if its VISa or mastercard
    if(sum3 % 10 == 0 && n / 1000000000000000 == 4)
    {
        printf("VISA\n");
    }
    else if (sum3 % 10 == 0 && n / 100000000000000 > 50 && n / 100000000000000 < 56)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
    }

// for 15 digit case
    else if (count == 15)
    {
        for(int y = 0; y < 7; y ++)
        {
            //use the remainder method to get the second last digit
            remainder = cardNumber % 100;
            remainder = remainder / 10;
            //move 2 digit ahead
            cardNumber = cardNumber / 100;
            //each digit * 2
            product = remainder * 2;
            // add up the digits
            if (product > 9)
            {
                //first digit of the product
                product1 = product % 10;
                //Second digit of the product
                product2 = product /10;
                sum = sum + product1 + product2 ;
            }
            else
            {
                sum = sum + product;
            }

            //printf("%li\n", sum);
        }

    long int remainder2;
    long int sum1=0;

        for(int y = 0; y < 8; y ++)
        {
            //use the remainder method to get the last digit
            remainder2 = cardNumber2 % 10;
            //move 2 digit ahead
            cardNumber2 = cardNumber2 / 100;
            // add up the digits
            sum1 = sum1 + remainder2;

            //printf("%li\n", sum1);
        }

    long int sum3;
    sum3 = sum1 + sum;
    //*10 to the division number, check if its amex or invalid
    if(sum3 % 10 == 0 && n / 10000000000000 == 34)
    {
        printf("AMEX\n");
    }
    else if(sum3 % 10 == 0 &&  n / 10000000000000 == 37)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }

    }

// for 13 digit case
    else if (count == 13)
    {
        for(int y = 0; y < 6; y ++)
        {
            //use the remainder method to get the second last digit
            remainder = cardNumber % 100;
            remainder = remainder / 10;
            //move 2 digit ahead
            cardNumber = cardNumber / 100;
            //each digit * 2
            product = remainder * 2;
            // add up the digits
            if (product > 9)
            {
                //first digit of the product
                product1 = product % 10;
                //Second digit of the product
                product2 = product /10;
                sum = sum + product1 + product2 ;
            }
            else
            {
                sum = sum + product;
            }

            //printf("%li\n", sum);
        }

    long int remainder2;
    long int sum1=0;

        for(int y = 0; y < 7; y ++)
        {
            //use the remainder method to get the last digit
            remainder2 = cardNumber2 % 10;
            //move 2 digit ahead
            cardNumber2 = cardNumber2 / 100;
            // add up the digits
            sum1 = sum1 + remainder2;

            //printf("%li\n", sum1);
        }

    long int sum3;
    sum3 = sum1 + sum;
    //*10 to the division number, check if its VISa or mastercard
    if(sum3 % 10 == 0 && n / 1000000000000 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    }
    else
    {
        printf("INVALID\n");
    }



}
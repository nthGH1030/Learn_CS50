#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    //promt user to input height
    do
    {
        height = get_int("Height: ");
    }
    while(height > 8 || height < 1);
    // Generate number of space to print
        int spaceCount = height - 1;
    // Generate number of # to print
        int hashCount = height - spaceCount;

    //Generate the triangle
    for(int j = 0; j < height; j++ )
    {

        for(int i = 0; i < spaceCount; i++)
        {
            printf(" ");
        }

        for(int y = 0; y < hashCount; y++)
        {
            printf("#");
        }

        printf("  ");

        for(int z = 0; z < hashCount; z++)
        {
            printf("#");
        }

        printf("\n");

        spaceCount--;
        hashCount++;

    }



















    // write a space bar vertical row

    //write a loop to generate an inverted angle triangle
}
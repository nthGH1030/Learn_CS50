#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startSize;
    int endSize;

    do
    {
        startSize = get_int("What is the start size: ");
    }
    while (startSize < 9);


    // TODO: Prompt for end size
    do
    {
        endSize = get_int("What is the end size: ");
    }
    while(endSize < startSize);

    // TODO: Calculate number of years until we reach threshold
    // year 1 , llamas amount += startsize / 3 - statsize / 4
    // check if llama amount reach end size
    // year 2, llamas amount += totalllamas / 3 - totallamas / 4
    // check if llama amount reach end size
    int year = 0;
    int totalLlamas = startSize;
    while(totalLlamas < endSize)
    {
        totalLlamas += (totalLlamas / 3) - (totalLlamas / 4);
        year++;
        //printf("Llamas: %i\n", totalLlamas );

    }
    // TODO: Print number of years
    printf("Years: %i", year );
}

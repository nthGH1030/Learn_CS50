// Practice writing a function to find a max value
// Using Nested for loop

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    //Loop the first index(n) of the array that serve as the first comparison figure
    for(int i = 0; i < n; i++)
    {
        int minPosition = i;
        //Loop the n+1 index of the array that serve as the second comparision figure.
        for(int j = i + 1; j < n ;  j++)
        {
            //If n is smaller than n+1
            if(array[minPosition] < array[j])
            {
                // Get the index that you need to swap
                minPosition = j;
            }
        }
            // swap
            // set up temp variable
            int tempArray = array[i];
            //Set the n+1 figure to the n location;
            array[i] = array[minPosition];
            //Set the n figure to the n+1 location;
            array[minPosition] = tempArray;

    }
    //Since the array is sorted in descending order, the first index is the max value
    return array[0];
}
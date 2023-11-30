#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void swap(candidate* a, candidate* b);
bool compareByVotes(candidate* a, candidate* b);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    //int size = sizeof(candidates);
    //printf("size is %i.\n", size);

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");
        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    //loop through candidate and check if the name exists
    //if no, return false
    //if true, canidadate[i].vote += 1
    for (int i = 0; i < candidate_count; i++)
    {
        //printf("canidadtes[i] %s.\n",candidates[i].name);
        //printf("name: %s.\n",name);
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            //printf("votes of candidates[i]: %d.\n",candidates[i].votes);
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    string winner = NULL;
        for (int i = 0; i < candidate_count - 1; i++)
    {
        for(int j = 0; j < candidate_count - i - 1; j++)
        {
            if (compareByVotes(&candidates[j], &candidates[j+1]))
            {
                swap(&candidates[j], &candidates[j+1]);
            }
        }
    }
    for(int i = 0; i < candidate_count; i++)
    {
        //printf("%s\n", candidates[i].name);
        //printf("%d\n", candidates[i].votes);
    }

    int max_votes = candidates[candidate_count - 1].votes;
    //printf("Max votes is %d\n", max_votes);

    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes == max_votes)
        {
            winner = candidates[i].name;
            printf("%s\n", winner);
        }
    }
}

// helper function to swap
void swap(candidate* a, candidate* b) {
    candidate temp = *a;
    *a = *b;
    *b = temp;
}

//helper function to compare
bool compareByVotes(candidate* a, candidate* b) {
    return a->votes > b->votes;
}

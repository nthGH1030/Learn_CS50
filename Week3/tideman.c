#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] stores the voter's preference
int preferences[MAX][MAX];

// locked[i][j] means locking in the largest win to avoid cycle
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool cycle(int winner, int loser);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO (Checked)
    // check if name match for the candidate name
    for(int i = 0; i < candidate_count; i++ )
    {
        if(strcmp(name, candidates[i]) == 0)
        {
            // update ranks array to indicate rank preference
            ranks[rank] = i;

            return true;
        }
    }
    return false;

}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // update global preference by ranks[]
    for(int i = 0; i < candidate_count; i++)
    {
        int rank = i;
        for(int j = 0; j < candidate_count; j++)
        {
            if(rank == j)
            {
                preferences[i][j] = 0;
            }
            if(rank < j)
            {
                preferences[ranks[rank]][ranks[j]]++;
            }

            //printf("%i\n", preferences[i][j]);
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    // TODO
    // add when the preference of a candidate exceed another candidate preference to himself
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if(preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                //printf("%i\n", pairs[pair_count].winner);
                pair_count++;

            }
        }
    }
    //printf("%i\n", pair_count);
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // sort the pairs in descending order
		// Outer = outer loop, innter = inner loop
    for(int iOuter = 0; iOuter < candidate_count; iOuter++)
    {
        for(int jOuter = 0; jOuter < candidate_count; jOuter++)
        {
			// vMax = the value that is being compared to others
			int vMax = preferences[iOuter][jOuter];
			int iMax = iOuter;
			int jMax = jOuter;
			for(int jInner = jOuter + 1; jInner < candidate_count; jInner++)
            {
				//Loop through the current row
				if (preferences[iOuter][jInner] > vMax)
		        {
	            // set iMax and jMax to store the value
				iMax = iOuter;
				jMax = jInner;
				// save the value for the pairs
				vMax = preferences[iOuter][jInner];
		        }
			}
			//loop through other row and column
			for(int iInner = iOuter + 1; iInner < candidate_count; iInner++)
			{
				for(int jInner = 0; jInner < candidate_count; jInner++)
				{
                    if(preferences[iInner][jInner] > vMax)
                    {
                        iMax = iInner;
                        jMax = jInner;
                        vMax = preferences[iInner][jInner];
                    }
				}
			}
            // after getting the preference [i][j], loop through pairs to find the corresponding
            // winner & loser value same to the preference [i][j], and implement swapping
            for(int i = 0; i < pair_count; i++)
            {
                for(int j = 0; j < pair_count; j++)
                {
                    if(pairs[i].winner == iMax && pairs[i].loser == jMax)
                    {
                        if(pairs[j].winner == iOuter && pairs[j].loser == jOuter)
                        {
                             //sawp the pairs with the outer
                            int tempW = pairs[i].winner;
                            int tempL = pairs[i].loser;

                            pairs[i].winner = pairs[j].winner;
                            pairs[i].loser = pairs[j].loser;

                            pairs[j].winner = tempW;
                            pairs[j].loser = tempL;
                        }
                    }
                }
                //printf("[%i]\n",  pairs[i].winner);
                //printf("(%i)\n",  pairs[i].loser);
            }

        }

    }


}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // Lock in the pairs to avoid cycles
    // loop through all the pairs
    for (int i = 0 ; i < pair_count; i++)
    {
        // if a cycle is not formed
        if(cycle(pairs[i].winner, pairs[i].loser) != true)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }

     return;
}

bool cycle(int winner, int loser)
{
    //if a cycle is form, return true and break the recursion
    if(winner == loser)
    {
        return true;
    }
    //iterate through the locked pairs
    for(int i = 0 ; i < candidate_count; i++)
    {
        //check if the loser win against any winner in a locked pair
        if(locked[loser][i] == true)
        {
            // check if the loser of this pair win against another locked pair
            //keep passing in the original winner to check if winner == loser
            // change to loser pass in each time if it is winner in another pair
            // if a cycle is formed, it will return true
            if(cycle(winner, i) == true)
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // true winner is the one which column in adjacency matrix would all be false value;
    for(int i = 0 ; i < candidate_count; i++)
    {
        int falseCount = 0;
        for(int j = 0; j < candidate_count; j++)
        {
            //if an entire column is false value
            if(locked[j][i] == false)
            {
                falseCount++;
                //if the count = candidate count, it means all 3 column are false;
                if(falseCount == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}

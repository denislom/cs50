#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // // TO DELETE: print preference table
    // for (int i = 0; i < voter_count; i++) {
    //     // Loop through each candidate
    //     for (int j = 0; j < candidate_count; j++) {
    //         printf("%d ", preferences[i][j]);
    //     }
    //     // Print a new line after each row
    //     printf("\n");
    // }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
// preferences[MAX_VOTERS][MAX_CANDIDATES];
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
// void tabulate(void)
// {
//     for (int i = 0; i < voter_count; i++)
//     {
//         for (int j = 0; j < candidate_count; j++)
//         {
//             if (candidates[i].eliminated == false)
//             {
//                 candidates[preferences[i][j]].votes++;
//                 break;
//             }
//         }
//     }
//     return;
// }
void tabulate(void)
{
    int i = 0;
    int j = 0;
    while (i < voter_count)
    {
        while (j < candidate_count)
        {
            if (!candidates[preferences[i][j]].eliminated)
            {
                    candidates[preferences[i][j]].votes++;
                    break;
            }
            j++;
        }
        i++;
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for(int i = 0; i < candidate_count; i++)
    {  
        char    *winner = candidates[i].name ;
        if (candidates[i].votes > voter_count / 2)
        { 
            printf("winner %s\n",winner);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
// int find_min(void)
// {
//     int minvotes = voter_count;
    
//     for(int i = 0; i < candidate_count; i++)
//     {
//         if (candidates[i].eliminated == false && candidates[i].votes > minvotes)
//         {
//             minvotes = candidates[i].votes;
//         }
//     }
//     return 0;
// }
int find_min(void)
{
    int min = candidates[0].votes;
    int i = 1;
    while (i < candidate_count)
    {
        if (candidates[i].eliminated == false)
        {
            if (min > candidates[i].votes)
            {
                min = candidates[i].votes;
            }
        }
        i++;
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for(int i=0;i<candidate_count;i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes != min)
        {
        return false;
        }
    }
    return true; 
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for(int i=0;i<candidate_count;i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}

// void eliminate(int min)
// {
//     int i = 0;
//     while (i < candidate_count)
//     {
//         if (candidates[i].votes == min)
//             candidates[i].eliminated = true;
//         else
//             candidates[i].eliminated = false;
//         i++;
//     }
//     return;
// }
// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = (LENGTH +1) * 'Z';

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Lookup the hash table, check if there is a same word in it
    // Use hash function to find the index of hash table that might contain the word
        int index = hash(word);
    // Go through the link list of the hash table at the given index
    // set the current node
        node* current = table[index];
        while(current != NULL)
        {
            //check if a same word can be found
            if(strcasecmp(word, current->word) == 0)
            {
                return true;
            }
            //move on to next node in the link list
            current = current->next;
        }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int index = 0;
    //give a unique index for each unique word
    for(int i = 0; i < strlen(word); i++)
    {
        index += toupper(word[i]);
    }
    return index;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    //open file
    FILE *file = fopen(dictionary,"r");
    if(file != NULL)
    {
        char buffer[LENGTH + 1];
        while(fscanf(file, "%s", buffer) != EOF)
        {
            //declare head pointer
            node *current = NULL;
            //allocate memory for new node
            node *n = malloc(sizeof(node));
            //cater for scenrio of failure to allocate memory
            if(n == NULL)
            {
                return false;
            }
            //Update "word" of the node by copying the string in buffer
            strcpy(n->word, buffer);
            //Update value of next and set to null as its the last node;
            n->next = current;
            //calculate the index of hash table to point the list into
            int index = hash(n->word);
            //reset the head of pointer to hash table node, it is not pointing to anything yet
            current = table[index];

            //Append new node
            //if there is not a node in the table[index]
            if(current == NULL)
            {
                //point the hash table node to the new node
                table[index] = n;
            }
            else
            {
                //if there is already a node in the hash table node, point the new node to the existing node first
                n->next = table[index];
                //then point the hash table head to the new node
                table[index] = n;
            }
        }
        fclose(file);
        return true;
    }
    else
    {
        unload();
        return false;
    }

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // iterate entire hash table , when found a word, count ++
    int wordCount = 0;
    //loop to iterate the hash table
    for(int i = 0; i < N ; i++)
    {
        node* current = table[i];
        //loop to update wordCount
        while(current != NULL)
        {
            //update count
            wordCount++;
            //point to the next node
            current = current->next;
        }
    }
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // iterate through the hash table
        //use a temp variabe to point to the ->next one you want to free
        //call free()
    for(int i = 0; i < N ; i++)
    {
        // set header pointer
        node* current = table[i];
        //loop to free all node
        while(current != NULL)
        {
            //set the temp to the next of the header
            node* ptr = current-> next;
            //free the header
            free(current);
            //set the header to the temp pointer
            current = ptr;
        }
    }
    return true;
}

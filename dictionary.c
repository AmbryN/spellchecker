// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

#define ALPHABET_SIZE 27

typedef struct node
{
    bool is_word;
    struct node *children[ALPHABET_SIZE];
}
node;

node *root;
FILE *file;
unsigned int dictionarySize = 0;

// Returns the index of the character in the children array
int hashFunction(char character)
{
    return character == '\'' ? ALPHABET_SIZE - 1 : tolower(character) - 'a';
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *trav = root;
    // go through all characters in the string
    for (int i = 0; i < strlen(word); i++)
    {
        // use only lowercase characters
        int characterIndex = hashFunction(word[i]);

        // if a NULL pointer is hit, return not found
        if (trav->children[characterIndex] == NULL)
        {
            return false;
        }
        // if end of the string
        else if (i == strlen(word) - 1)
        {
            // if flag is_word is set return found, else not found
            return trav->children[characterIndex]->is_word ? true : false;
        }
        // else go down a level
        else
        {
            trav = trav->children[characterIndex];
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    // Initialize the root node
    root = calloc(1, sizeof(node));
    // Create a buffer for the words read in the dictionary
    char word[LENGTH] = "";
    while (fscanf(file, "%s", word) != EOF)
    {
        node *trav = root;
        // go through all characters in the string
        for (int i = 0; i < strlen(word); i++)
        {
            int characterIndex = hashFunction(word[i]);

            // if node is null, create a new node
            if (!trav->children[characterIndex])
            {
                trav->children[characterIndex] = calloc(1, sizeof(node));
            }
            // go down a level
            trav = trav->children[characterIndex];
        }
        // end of string is reached, set the is_word flag
        trav->is_word = true;
        dictionarySize++;
    }
    // close file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictionarySize;
}

// Frees up all nodes recursively
void free_node(node *trav)
{
    // for all pointers in the children array of trav
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        // if its child is not NULL
        if (trav->children[i])
        {
            // recurse
            free_node(trav->children[i]);
        }
    }
    // reached the end, free up the pointer
    free(trav);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *trav = root;
    // for all pointers in the children array of trav
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        // if its child is not NULL
        if (trav->children[i])
        {
            // call free node recursively
            free_node(trav->children[i]);
        }
        //else free up the pointer
        else
        {
            free(trav->children[i]);
        }
    }
    // free the root of the trie
    free(root);
    return true;
}



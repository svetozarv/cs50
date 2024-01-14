// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

node *create_new_node(void);
void free_a_node(node *node);

node *root;

unsigned int num_of_words;
bool loaded;


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = create_new_node();

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];
    int index;
    node *curr_node;

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        curr_node = root;

        for (int i = 0, strlen_word = strlen(word); i < strlen_word; i++)
        {
            // decide where to put the symbol
            if (word[i] == '\'')
            {
                index = N - 1;
            }
            else
            {
                index = (toupper(word[i]) - 64) - 1;
            }
            
            // check for existence of needed node
            if (curr_node->children[index] == NULL)
            {
                curr_node->children[index] = create_new_node();
            }

            // move to next one(or just created)
            curr_node = curr_node->children[index];
        }
        
        curr_node->is_word = true;
        num_of_words++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    loaded = true;
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (!loaded)
    {
        return 0;
    }
    
    return num_of_words;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *curr_node = root;
    int index;
    for (int i = 0, strlen_word = strlen(word); i < strlen_word; i++)
    {
        // check for incoming symbol
        if (word[i] == '\'')
        {
            index = N - 1;
        }
        else
        {
            index = (toupper(word[i]) - 64) - 1;
        }
        
        // check if the node exists
        if (curr_node->children[index] == NULL)
        {
            return false;
        }
        curr_node = curr_node->children[index];
    }

    // check if end of the word
    if (!curr_node->is_word)
    {
        return false;
    }
    
    return true;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    free_a_node(root);
    
    free(root);
    
    return true;
}


// local functions
void free_a_node(node *node)
{
    for (int i = 0; i < N; i++)
    {
        if (node->children[i] != NULL)
        {
            free_a_node(node->children[i]);
        }
        free(node->children[i]);
    }
}


node *create_new_node(void)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        unload();
        printf("Couldn't create a new node\n");
        return false;
    }
    new_node->is_word = false;
    for (int i = 0; i < N; i++)
    {
        new_node->children[i] = NULL;
    }

    return new_node;
}
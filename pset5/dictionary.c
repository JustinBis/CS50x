/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 * Additional Programming by Justin Bisignano, Spring 2013
 ***************************************************************************/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

#define ARRAY_LEN 27

// Use a trie. Lots of RAM, but simple (in theory at least)
typedef struct trie_node{
    bool isWord;
    struct trie_node* next[ARRAY_LEN];
}
node;

// Define the deallocate function
void deallocate(node* trie_pointer);

// Global variable to store the pointer to the first node
node* first;
// Store the size of the dictonary and initilize it to 0
unsigned int dictSize = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // Make sure that the dictionary has been loaded and that first is initilized
    if(first == NULL){
        printf("Error checking word \"%s\" because the dictionary has not been properly loaded. The first pointer is still NULL.\n", word);
        return false;
    }
    
    node* current = first;
    
    for(int i = 0, l = strlen(word); i<l; i++){
        // Change the current character into a lowecase letter and then find its appropriate index
        int c = tolower(word[i]);
        
        if(c == '\'')
            c = 26;
        else
            c = c-'a';
        
        // Move through the nodes for this letter, making sure it isn't a NULL poiner
        if(current->next[c] == NULL)
            return false;
        else
            current = current->next[c];
    }
    
    // Only return true if current points to the end of a word
    if(current->isWord)
        return true;
    else
        return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{

    // Allocate the first node
    first = malloc(sizeof(node));
    
    // I need to somehow allocate all the necessary space for the trie. Can I just allocate the arrays to known words by looping through the dictionary, word by word, allocating the next array letter by letter, skipping the allocation and just following the pointer if its already allocated? Then mark the end. Like a trie, but not everything has to be fully allocated.
    
    // Open the dictionary file
    FILE* in = fopen(dictionary, "r");
    if (in == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    // Pointer to keep track of the current position
    node* current = first;
    
    // Loop through the dictionary, reading character by character
    for (int c = fgetc(in); c != EOF; c = fgetc(in))
        // Make sure the character is a letter and then move the pointer along the nodes, allocating new ones as necessary.
        if (isalpha(c) || (c == '\''))
        {
            // Convert the character c to it's proper array index
            if(c == '\'')
                c = 26;
            else
                c = c-'a';

            // If the next pointer for the letter isn't allocated, make a new node for it
            if(current->next[c] == NULL){
                current->next[c] = malloc(sizeof(node));  
            }
            
            // Move on to the next node
            current = current->next[c];
        }
        // If it's a newline character, mark the current node as the endpoint of a word
        else if (c == '\n'){
            current->isWord = true;
            // Reset the pointer so we can start over on a new word
            current = first;
            // Increase the size of the dictionary by 1 for the newly added word
            dictSize++;
        }
    
    // Close the file
    fclose(in);
    
    return true;
}



/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // Call the recursive deallocate function, and it'll do the rest
    deallocate(first);
    
    // If the deallocate function worked, first will be NULL
    //if(first == NULL)
        return true;
    //else
    //    return false;
}

void deallocate(node* trie_pointer){
    // return if trie_pointer is NULL
    //if(trie_pointer == NULL)
    //    return;
    
    // Loop through each index in the array, recursively freeing each
    for(int i=0; i<ARRAY_LEN; i++){
        // Only bother with pointers that have been initilized
        if(trie_pointer->next[i] != NULL)
            deallocate(trie_pointer->next[i]);
    }
    free(trie_pointer);
}

/*
 * Vigenere Cipher
 * Justin Bisignano
 * CS50x Fall 2012
 */
 
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    // Make sure that we got exactly 1 extra command line arguement
    if (argc != 2)
    {
        printf("Y u no listen? Enter just one command line arguement!\n");
        return 1;
    }
    
    // Assign the arguemnt to a string
    string key = argv[1];
    
    // Check that the arguement is only alphabetic 
    for (int i=0, n = strlen(key); i<n; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("The key can only be alphabetic characters!\n");
            return 1;
        }
    }

    // Get user input
    string input = GetString();
    
    // Initilize output string
    string output = input;
    
    // Set up some variables to index the key
    int index = 0;
    int keylen = strlen(key);
    
    // Base number to subtract from the ascii value of a char
    int inputbase = 0, keybase = 0;
    
    // Loop through the input string
    for (int i=0, n = strlen(input); i<n; i++)
    {
        if (isupper(input[i]))
            inputbase = 'A';
        else if (islower(input[i]))
            inputbase = 'a';
        else
            inputbase = 0;
            
        if (isupper(key[index]))
            keybase = 'A';
        else if (islower(key[index]))
            keybase = 'a';
        else
            keybase = 0;
        
        if (inputbase != 0 && keybase !=0)
        {
        output[i] = ((input[i]-inputbase + key[index]-keybase)%26 + inputbase);
        index = (index+1)%keylen; // Keeps the key index looping
        }
    }
    
    // Print output
    printf("%s\n", output);
    
    // Completed successfully, return 0
    return 0;
}

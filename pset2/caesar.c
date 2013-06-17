/*
 * Caesar's Cipher
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
        printf("Y u no listen? Enter just one non-negative integer command line arguement!\n");
        return 1;
    }
   
    // Make the command line arguement an integer
    int k = atoi(argv[1]);
    // Check that the int is non-negative 
    if (k <= 0)
    {
        printf("Y u no listen? I need a positive integer as the arguement!\n");
        return 1;
    }
    
    // Mod k so it is between 0 and 25
    k = k%26;
    
    // Get user input
    string input = GetString();
    
    // Initilize output string
    string output = input;
    
    // Loop through the input string
    for (int i=0, n = strlen(input); i<n; i++)
    {
        if (isupper(input[i]))
        output[i] = ((input[i]-'A' + k)%26 + 'A');
        else if (islower(input[i]))
        output[i] = ((input[i]-'a' + k)%26 + 'a');
    }
    
    // Print output
    printf("%s\n", output);
    
    // Completed successfully, return 0
    return 0;
}

/*
 * pset2 Hacker Edition - Password Cracker
 * Justin Bisignano
 * CS50x Fall 2012
 */
 
#define _XOPEN_SOURCE
 
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, string argv[])
{
    // Make sure that we got exactly 1 extra command line arguement
    if (argc != 2)
    {
        printf("Incorrect number of command line arguements (expected 1).\n");
        return 1;
    }
    
    // Assign the arguemnt to a string
    string encryptedpass = argv[1];

    // The first two characters of the encrypted password is the salt
    char salt[2];
    salt[0] = encryptedpass[0];
    salt[1] = encryptedpass[1];
    
    // Initilize the key character array, with a maximum of 8 characters.
    char key[9] = "a\0\0\0\0\0\0\0\0"; // Will init to "z" for first undercase testing and eventually "126"(~) for full brute force

    // Now we loop through every password possibility (brute force)
    while(true)
    {
            // Increment the first letter by one on each loop
            key[0]++;
            
            for(int i=0; i<8; i++) // Increment for each character in the array (string)
            {
                // If we've incremented past null, change it to 32 to skip all the characters that can't be typed usually.
                if(key[i] == 1)
                    key[i] = 'a'; //lowercase test, would change to 32 to start at 'SPC'
                
                // If we've incremented all the way to the last character we're checking, reset it to 'a' and then begin incrementing the next character.
                if(key[i] > 'z') //lowecase test, would change to the last possible character, ~ (126)
                {
                    key[i] = 'a'; // lowercase test, would change to 32 to start at 'SPC'
                    key[i+1]++;
                }
            }
        //}
        
        // Encrypt the key and see if it matches the given ciphertext. If it does, break.
        if(strcmp(encryptedpass, crypt(key, salt)) == 0)
            break;
        
        // For testing
        printf("Test: %s\n", key);
    }
    
    // If we hit the last possibility, something failed, so return an error
    if(strcmp(key, "~~~~~~~~") == 0)
        return 2;
    
    // Print output
    printf("%s\n", key);
    
    // Completed successfully, return 0
    return 0;
}

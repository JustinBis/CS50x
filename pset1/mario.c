#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = -1;
    printf("Please enter a height between 0 and 23.\n");
    
    // Reprompt user until height is between 1 and 23
    while (height>23||height<0)
    {
        height = GetInt();
        if (height>23||height<0)
            printf("That isn't a valid height. Try again.\n");
    }
    
    // Loop through the building of the pyramid, starting with i=2 for two blocks
    for (int i=2; i<=height+1; i++)
    {        
        // Print spaces
        for (int j=0; j<height+1 - i; j++)
            printf(" ");
        
        // Print #'s
        for (int k=0; k<i; k++)
            printf("#");
        
        // Go to a new line after each pass of the loop
        printf("\n");
    }
    
    return 0;
}

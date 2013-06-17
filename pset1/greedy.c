#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change = -1;
    printf("Hey there! How much change is owed?.\n");
    
    // Reprompt user until change is positive
    while (change<0)
    {
        change = GetFloat();
        if (change<0)
            printf("No, really, how much change is owed?\n");
    }
    
    // Convert from dollars to rounded cents
    change = change*100;
    int cents = (int) round(change);

    int coins=0;
    
    // Find the number of quarters
    coins = coins + cents/25;
    
    // Set cents to the remainder
    cents = cents%25;
    
    // Repeat for dimes
    coins = coins + cents/10;
    cents = cents%10;
    
    // Now for nickels
    coins = coins + cents/5;
    cents = cents%5;
    
    // And finally, pennies. No need to devide or find remainder.
    coins = coins + cents;
    
    // Print final output
    printf("%d\n", coins);
        
    return 0;
}

#include <stdio.h>
#include <cs50.h>

int main(void){
    printf("Please enter a temperature in Celsius\n");
    float c = GetInt();
    printf("%.1f in Fahrenheit is %.1f in Celsius\n", c, c*9/5+32);
}

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) {

    int coins = 0; 
    int value = 0;
    
    // receive a value
    float dollars;
    do {
        dollars = get_float("Change owed: ");
    } while (dollars < 0);
    
    value = round(dollars * 100);

    // counting coins
    while (value != 0) {
        if (value >= 25) {
            coins++;
            value -= 25;
        } else if (10 <= value && value < 25) {
            coins++;
            value -= 10;
        } else if (5 <= value && value < 10) {
            coins++;
            value -= 5;
        } else if (1 <= value && value < 5) {
            coins++;
            value -= 1;
        }
    }
    printf("%i\n", coins);
}

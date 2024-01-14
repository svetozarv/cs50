#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int mario;

    do
    {
        mario = get_int("Height: ");
    }
    while (mario < 1 || mario > 8);

    for (int i = 0; i < mario; i++)
    {

        // print spaces
        int num_of_spaces = mario - (i + 1);
        for (int y = 0; y < num_of_spaces; y++)
        {
            printf(" ");
        }

        // print #
        int j = -1;
        do
        {
            printf("#");
            j++;
        }
        while (j != i);

        printf("  ");

        // print #
        int k = -1;
        do
        {
            printf("#");
            k++;
        }
        while (k != i);

        printf("\n");
    }
}

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int mario, j, num_of_spaces;

    do
    {
        mario = get_int("Height: ");
    }
    while (mario < 1 || mario > 8);

    for (int i = 0; i < mario; i++)
    {
        num_of_spaces = mario - (i + 1);
        for (int y = 0; y < num_of_spaces; y++)
        {
            printf(" ");
        }

        j = -1;
        do
        {
            printf("#");
            j++;
        }
        while (j != i);
        printf("\n");
    }
}

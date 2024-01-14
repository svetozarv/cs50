#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    unsigned long int a = 100;
    unsigned long int b = 10;
    unsigned long int c = 1000000000000;
    unsigned int the_two_first_numbers;
    int sum = 0;
    int num_x2 = 0;

    // receive a number
    unsigned long int card_number = get_long("Number: ");

    // getting a sum of doubled even digits(part 1)
    for (int i = 0; i < 16; i++)
    {
        num_x2 = (card_number % a / b) * 2;
        sum += num_x2 % 10;
        sum += num_x2 / 10;
        a *= 100;
        b *= 100;
    }

    // getting the others(part 2)
    a = 10;
    b = 1;
    for (int i = 0; i < 16; i++)
    {
        sum += card_number % a / b;
        a *= 100;
        b *= 100;
    }

    //getting the two first ones
    do
    {
        the_two_first_numbers = card_number / c;
        if (the_two_first_numbers / 100 != 0)
        {
            c *= 10;
            the_two_first_numbers = card_number / c;
        }
        c *= 10;
    }
    while (the_two_first_numbers % 100 != the_two_first_numbers % 1000);


    // validation(part 3)
    if (sum % 10 == 0)
    {
        if (the_two_first_numbers == 34 || the_two_first_numbers == 37)
        {
            printf("AMEX\n");
        }
        else if (51 <= the_two_first_numbers && the_two_first_numbers <= 55)
        {
            printf("MASTERCARD\n");
        }
        else if (the_two_first_numbers / 10 == 4 || the_two_first_numbers == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

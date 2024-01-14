#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>
#include <cs50.h>
#include <time.h>

void add_1(char a[], int i);
void expand_the_pass(char pass[], int strlen_pass);
char* compare_hashes(char pass[], char hash[], char salt[]);


int main(int argc, char *argv[])
{
    // check for input
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    // time tracking
    time_t time_begin = time(NULL);
    double time_spent = 0.0;
    clock_t clock_begin = clock();

    // store salt
    char salt[2];
    for (int i = 0; i < 2; i++)
    {
        salt[i] = argv[1][i];
    }

    // store hash
    char hash[15];
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        hash[i] = argv[1][i];
    }


    char pass[6] = "A";         // starting symbol
    int strlen_pass;
    char password[15];
    int counter = 0;

    while (true)
    {
        strlen_pass = strlen(pass);
        if (strlen_pass >= 6)
        {
            return 1;
        }

        *password = *compare_hashes(pass, hash, salt);
        if (*password != '\0')
        {
            printf("password found: %s\nSteps taken: %i\n", pass, counter);

            // time info
            time_t time_end = time(NULL);
            printf("The real time is %ld seconds\n", (time_end - time_begin));

            clock_t clock_end = clock();
            time_spent += (double)(clock_end - clock_begin) / CLOCKS_PER_SEC;
            printf("The running time is %f seconds\n", time_spent);

            break;
        }

        add_1(pass, strlen_pass - 1);
        counter++;
        if (counter % 99999 == 0)
        {
            printf("in process: %s\n", pass);
        }
    }
}


void add_1(char a[], int i)
{
    if (i == -1)
    {
        expand_the_pass(a, strlen(a));
    }
    else
    {
        if (a[i] != 'z')        // ending symbol
        {
            // range
            // skip
            if (a[i] == 'Z')        // start-skiping symbol
            {
                a[i] = '`';         // end-skiping symbol
            }
            a[i] += 1;
        }
        else
        {
            add_1(a, i-1);
            a[i] = 'A';         // starting symbol
        }
    }
}


void expand_the_pass(char pass[], int strlen_pass)
{
    strlen_pass++;
    for (int i = 0; i < strlen_pass; i++)
    {
        pass[i] = 'A';      // starting symbol
    }
}


char* compare_hashes(char pass[], char hash[], char salt[])
{
    // crypting the password
    char *crypted_pass = crypt(pass, salt);

    // comparing
    for (int j = 0; j < strlen(crypted_pass); j++)
    {
        if (crypted_pass[j] != hash[j])
        {
            return "\0";
            break;
        }
    }
    return crypted_pass;
}

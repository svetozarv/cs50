#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>
#include "cs50.h"

int main(int argc, string argv[])
{
    // check for input
    if (argc != 2) {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    char salt[] = {'3', '9'};

    string crypted_password = crypt(argv[1], salt);
    printf("%s\n", crypted_password);

}

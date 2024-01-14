#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int shift(char c);

int main(int argc, string argv[])
{
    // cheking the input
    if (argc != 2) {
        printf("Usage: ./vigenere key\n");
        return 1;
    }
    for (int i = 0; i<strlen(argv[1]); i++) {
        if (isdigit(argv[1][i])) {
            printf("Usage: ./vigenere key\n");
            return 1;
        }
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    int key;
    for (int i = 0, j = 0; i<strlen(plaintext); i++, j++) {
        if (isupper(plaintext[i]) || islower(plaintext[i])) {
            key = shift(argv[1][j % strlen(argv[1])]);
        } else {
            j--;
        }
        if (isupper(plaintext[i])) {
            printf("%c", ((plaintext[i]-65 + key) % 26) + 65);
        } else if (islower(plaintext[i])) {
            printf("%c", ((plaintext[i]-97 + key) % 26) + 97);
        } else {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}


int shift(char c) {
   if (isupper(c)) {
       return c - 65;
   } else if (islower(c)) {
       return c - 97;
   } else {
       return 0;
   }
}

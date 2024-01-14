#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char string[20];
    printf("Enter the text: ");
    scanf("%s", &string);

    for (int i = 0, strlen_string = strlen(string); i < strlen_string; i++)
    {
        printf("%i ", toupper(string[i]) - 64);
    }
}

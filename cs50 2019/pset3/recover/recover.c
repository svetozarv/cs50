#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // check for input
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover [file]\n");
        return 1;
    }

    // open card file
    FILE *card_file = fopen(argv[1], "r");
    if (card_file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    int already_found_a_jpg = 0;
    FILE *image = NULL;
    char filename[7];
    int num_of_pic = 0;
    uint8_t buffer[512];

    while (fread(&buffer, 1, 512, card_file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 &&
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (already_found_a_jpg)
            {
                // close the previous one
                fclose(image);
            }

            // making a .jpg
            sprintf(filename, "%03i.jpg", num_of_pic);

            image = fopen(filename, "w");
            if (image == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                return 2;
            }

            fwrite(&buffer, 1, 512, image);

            already_found_a_jpg = 1;
            num_of_pic++;
        }
        else
        {
            if (already_found_a_jpg)
            {
                fwrite(&buffer, 1, 512, image);
            }
        }
    }

    fclose(image);
    fclose(card_file);
    printf("Files closed. Success\n");

    return 0;
}

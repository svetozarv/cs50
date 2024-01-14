#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize n infile outfile\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            fprintf(stderr, "Usage: resize n infile outfile\n");
            return 1;
        }
    }

    // getting the n multiplier as int
    int n = atoi(argv[1]);
    if (0 < n && n > 100)
    {
        fprintf(stderr, "Usage: resize n infile outfile\n");
        return 1;
    }


    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER and BITMAPINFOHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    bf.bfSize *= n*n;
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // store width & height
    int infile_biWidth = bi.biWidth;
    int infile_biHeight = bi.biHeight;
    
    // write outfile's BITMAPINFOHEADER
    bi.biWidth *= n;
    bi.biHeight *= n;
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding and offset for scanlines
    int infile_padding = (4 - (infile_biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("%i\n", infile_padding);

    int outfile_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("%i\n", outfile_padding);

    // num of pixels we need to move back for copying a pixel-line again
    long int offset = -infile_biWidth*3 + infile_padding;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(infile_biHeight); i < biHeight; i++)
    {
        for (int n_lines = 0; n_lines < n; n_lines++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < infile_biWidth; j++)
            {
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int n_pixels = 0; n_pixels < n; n_pixels++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, infile_padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < outfile_padding; k++)
            {
                fputc(0x00, outptr);
            }
            fseek(inptr, offset, SEEK_CUR);
        }
    }

    // closing files
    fclose(inptr);
    fclose(outptr);

    // success
    return 0;
}

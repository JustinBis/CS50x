/****************************************************************************
 * resize.c
 * Modified from copy.c
 * By Justin Bisignano
 * CS50x, Fall 2012
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP file
 * 
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: copy infile outfile\n");
        return 1;
    }

    // remember n and filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    // make sure the resize factor isn't insane
    if(n<1 || n>100)
    {
        printf("Please use a resize factor between 1 and 100, inclusive");
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
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
    
    // determine padding for scanlines
    int origPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // Store the original height and width, then update biHight and biWidth
    int origHeight = bi.biHeight;
    int origWidth = bi.biWidth;
    bi.biHeight *= n;
    bi.biWidth *= n;
    
    // determine resized padding (in bytes) for scanlines
    int resizedPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update biSizeImage, which is the number of bytes in the actual bitmap itself, which is height*width*bytes_per_pixel + any space taken by padding.
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth) * sizeof(RGBTRIPLE) + abs(bi.biHeight) * resizedPadding;
    
    // update bfSize by finding out the size (in bytes) of the just the bitmap's pixels, then multiplying that by n squared, and adding it to the size of the header.
    bf.bfSize = bf.bfOffBits + bi.biSizeImage;
    //printf("%d\n", bf.bfSize);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // create a file position object to store the position
    fpos_t tempPosition;
    
    // iterate over infile's scanlines
    for (int i = 0, height = abs(origHeight); i < height; i++)
    {
        // temporarily store the offset of the input pointer at this scanline so we can reset it later
        fgetpos(inptr, &tempPosition);
        
        // duplicate the scanline n times to resize it.
        for (int yResizeCount = 0; yResizeCount < n; yResizeCount++)
        {
            // reset the input pointer to the start of the scanline
            fsetpos(inptr, &tempPosition);
            
            // iterate over pixels in scanline
            for (int j = 0; j < origWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile, multiple times according to n to resize horizontally.
                for(int xResizeCount = 0; xResizeCount < n; xResizeCount++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over input padding, if any
            fseek(inptr, origPadding, SEEK_CUR);

            // then add the new padding (if necessary) to the output
            for (int k = 0; k < resizedPadding; k++)
                fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

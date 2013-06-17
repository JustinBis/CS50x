/****************************************************************************
 * recover.c
 * By Justin Bisignano
 * CS50x, Fall 2012
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image (card.raw)
 ***************************************************************************/
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 #include <string.h>
 
 #define BLOCKSIZE 512
 
 // FOR FUTURE REFERENCE: byte 5120 is the first jpeg signature in the file
 
 int main(void)
 {
    // open input file 
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("Could not open the file \"card.raw\".\n");
        return 1;
    }
    
    // create a variable to track the number of recovered jpegs
    int jpegNumber = 0;
    
    // create a variable to track the input file's offset so we can back it up later
    
    // iterate through the file, stopping when we set off the end of file flag
    while(!feof(inptr))
    {
        // if we found a jpeg on a previous iteration of the loop, we need to seek one block backwards to begin reading the next jpeg in.
        if(jpegNumber != 0)
            fseek(inptr, -BLOCKSIZE, SEEK_CUR);
        
        // create a buffer the size of each FAT block and read the file into it
        char* buffer = malloc(BLOCKSIZE);
        fread(buffer, BLOCKSIZE, 1, inptr);
        
        // create a 4 byte (32bit) variable
        uint32_t firstFour;
        
        // copy the first four bytes of buffer into firstFour
        memcpy(&firstFour, buffer, 4);
        
        // look for jpeg signatures at the beginning of each block. Note that the bytes are reversed and represented in little-endian format 
        if(firstFour == 0xe0ffd8ff || firstFour == 0xe1ffd8ff)
        {
            // We probably found a jpeg, start recovering it!
            
            // create the output filename string
            char outName[8];
            sprintf(outName, "%03d.jpg", jpegNumber);            
            
            // open up a file to write the recovered jpeg to
            FILE* outptr = fopen(outName, "w");
            if (outptr == NULL)
            {
                printf("Could not create the file %s. You may be out of space\n", outName);
                return 2;
            }
            
            // loop through the file and across subsequent blocks until a new jpeg is found or the file ends
            while(!feof(inptr))
            {
                // write the recovered jpeg contents to the output file
                fwrite(buffer, BLOCKSIZE, 1, outptr);
                
                // load the next block in to the buffer
                fread(buffer, BLOCKSIZE, 1, inptr);
                
                // copy the first four bytes of buffer into firstFour
                memcpy(&firstFour, buffer, 4);
                
                // check if the next block begins a new jpeg, and break if it does
                if(firstFour == 0xe0ffd8ff || firstFour == 0xe1ffd8ff)
                    break;
            }
            
            jpegNumber++;
            fclose(outptr);
        }
        
        // Free buffer, since we aren't using it anymore
        free(buffer);
    }
    
    // close the input file
    fclose(inptr);
    
    // All good, no more to be done.
    return 0;
 }

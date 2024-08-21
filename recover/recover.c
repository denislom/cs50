#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
#define BLOCK_SIZE 512

/*
        Theory notes:
    TODO: open memory card, look fo beginning of a JPEG, open a new JPEG file, 
        write 512 bytes until a new JPEG is found,
        stop at end of file.
    Open memory card:
        FILE *f = fopen(filename, "r");
    Look for beginning of a JPEG
        JPEG header:
            first three bytes: 0xff, 0xd8, 0xff,
            last byte: 0xe0, 0xe1, ..., 0xef
        JPEGs start with distinct header,
        JPEGs stored back-to-back in memory card
        Each block is 512 bytes

    Read Files
        fread(data, size, number, inptr);
            data: pointer to where to store data you're reading,
            size: size of each element to read,
            number: number of elements to read,
            inptr: FILE * to read from.
    
    buffer[3] == 0xe0 || buffer [3] == 0xe1 || ...
    -> bitwise arithmetic
        (buffer[3] & 0xf0) == 0xe0

    Making a new JPEG
        Filenames: ###.jpg, starting 000.jpg

        sprintf(filname, "%03i.jpg", i);
        FILE *img = fopen(filname, "w");
        
        fwrite(data, size, number, outptr);
        data: pointer to bytes that will be written to file,
        size: size of each element to write,
        number: number of elements to write,
        ouptr; FILE * to write to

    End of the file:
        fread return number of items of size size were read,
        it will return 512 and if end of file, less than 512.

    Pseudocode:
        Open memory card
        Repeat until end of card
            Read 512 bytes into a buffer
            If start of new JPEG
                If first JPEG
                    ...
                Else
                    ....
        Close any remaining files
*/
 
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("expected input: ./recover card.raw\n");
        return (1);
    }
    BYTE buffer[BLOCK_SIZE];
    // Open the memory card
    FILE *f = fopen(argv[1], "r");
    int count = 0;
    char filename[8];
    FILE *recovered_img_i = NULL;
    if (f == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }
    // While there's still data left to read from the memory card
    // JPEG, first three bytes: 0xff, 0xd8, 0xff,
            // last byte 0xe0, 0xe1, ..., 0xef
        // each block is 512 bytes
    while (fread(buffer, sizeof(BYTE) * BLOCK_SIZE, 1, f) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if ((buffer[3] & 0xf0) == 0xe0)
            {
                if (recovered_img_i)
                    fclose(recovered_img_i);
                sprintf(filename, "%03i.jpg", count);
                count++;
                recovered_img_i = fopen(filename, "w");
            }
        }
        if (recovered_img_i)
            fwrite(buffer, sizeof(BYTE) * BLOCK_SIZE, 1, recovered_img_i);
    }
    if (recovered_img_i)
        fclose(recovered_img_i);
    if (f)
        fclose(f);
    return (0);
}
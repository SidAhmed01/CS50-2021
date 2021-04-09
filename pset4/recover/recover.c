#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./copy infile\n");
        return 1;
    }
    char *infile = argv[1];
    FILE *card = fopen(infile, "r");
    if (card == NULL)
    {
        fprintf(stderr, "Couldn't open %s!\n", infile);
        return 2;
    }

    FILE *img = NULL;

    int counter = 0;
    char image[8]; 

    BYTE data[BLOCK];
    //checking if the end of the card is reached
    while (fread(&data, sizeof(BLOCK), 1, card) != 0)
    {
        //checking if it's a new jpeg
        if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && (data[3] & 0xf0)==0xe0)
        {
            //if it's not the first new jpeg, close the previous 
            if (img != NULL)
            {
                fclose(img);
            }

            sprintf(image, "%03i.jpg", counter);
            img = fopen(image, "w");
            if (img == NULL)
            {
                fprintf(stderr, "Couldn't open %s!\n", image);
                fclose(card);
                return 3;
            }
            counter++;

        }
        if (img != NULL)
        {
            fwrite(&data, sizeof(BLOCK), 1, img);
        }
    } 

    fclose(img);
    fclose(card);

    return 0;
}
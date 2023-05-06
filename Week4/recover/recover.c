#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //Open memory card with Fopen
    //use a loop to read 512 bytes chunks inside the memory card ,put it in a buffer (an array of bytes)
    //use if statement to check for jpeg header in the 512 chunk, if not found, use continue to restart the loop
    //If a jpeg is found, make a new jpeg and copy it into the new jpeg file
    //to make a new jpeg, you need a counter which also serve as filename of the jpeg, use sprintf() to set filename
    //open the new file created with fopen in write mode
    //use fwrite to write the data into the new file
    //check the return value of fread to see if it has reached the end of a file

    /* Open memory card
    Repeat until end of card with a loop:
        Read 512 bytes into a buffer
        If a JPEG header is found
            If it is the first JPEG
                write the jpeg
            else
                close the file you are writing and start a new one
        Else
            If already found JPEG
                Keep writing the JPEG
    At end of file (End of loop), close any remaining files
    */

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: incorrect input\n");
        return 1;
    }
    //Open memory card, take a command line argument
    char *filename = argv[1];
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Could not open %s.\n", filename);
        return 1;
    }
    //create a variable for storing BYTES
    typedef uint8_t BYTE;
    BYTE buffer[512];

    FILE *img = NULL;
    char writeFile[8];
    int jpgCount = 0;
    //loop to check fo end of line
    while(fread(buffer, sizeof(BYTE), 512, f) == 512)
    {
        //check fo JPEG header
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //check if it is the first JPEG
            if(jpgCount == 0)
            {
                //Create a new file name
                sprintf(writeFile, "%03i.jpg", jpgCount);
                //Open a new file with the new file name
                img = fopen(writeFile, "w");
                //write the kpg into the new file
                fwrite(buffer, sizeof(BYTE), 512, img);
                jpgCount++;
            }
            else
            {
                //close the file you are writing and start a new one
                fclose(img);
                sprintf(writeFile, "%03i.jpg", jpgCount);
                //Open a new file with the new file name
                img = fopen(writeFile, "w");
                //write the kpg into the new file
                fwrite(buffer, sizeof(BYTE), 512, img);
                jpgCount++;
            }
        }
        //if you already found a JPEG
        else if(jpgCount > 0)
        {
            //keep writing the JPEG block
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
    }
    //close remaining file
    fclose(img);
    fclose(f);
}
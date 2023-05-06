#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //iterate all the pixel
            //for each iteration change the RGB figure of the BMP
            if(image[i][j].rgbtBlue == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtRed == 0)
            {
                image[i][j].rgbtBlue = 10;
                image[i][j].rgbtGreen = 50;
                image[i][j].rgbtRed = 150;
            }

        }
    }
}

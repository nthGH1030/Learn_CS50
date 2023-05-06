#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average = 0;
    int roundAverage = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            average = ((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed)/3;
            roundAverage = round(average);
            image[i][j].rgbtBlue = roundAverage;
            image[i][j].rgbtGreen = roundAverage;
            image[i][j].rgbtRed = roundAverage;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temprgbtBlue = 0;
    int temprgbtGreen = 0;
    int temprgbtRed = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < (width/2); j++)
        {
            if(image[i][j].rgbtBlue != image[i][(width-1-j)].rgbtBlue || image[i][j].rgbtGreen != image[i][(width-1-j)].rgbtGreen || image[i][j].rgbtRed != image[i][(width-1-j)].rgbtRed)
            {
                //swap color
                temprgbtBlue = image[i][j].rgbtBlue;
                temprgbtGreen = image[i][j].rgbtGreen;
                temprgbtRed = image[i][j].rgbtRed;

                image[i][j].rgbtBlue = image[i][(width-1-j)].rgbtBlue;
                image[i][j].rgbtGreen = image[i][(width-1-j)].rgbtGreen;
                image[i][j].rgbtRed = image[i][(width-1-j)].rgbtRed;

                image[i][(width-1-j)].rgbtBlue = temprgbtBlue;
                image[i][(width-1-j)].rgbtGreen = temprgbtGreen;
                image[i][(width-1-j)].rgbtRed = temprgbtRed;
            }
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE imgcpy[height][width];
    //Save the original pixel value
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            imgcpy[i][j] = image[i][j];

        }
    }

    for(int i = 0; i < height ; i++)
    {
        for(int j = 0; j < width ; j++)
        {
            float redTotal = 0;
            float greenTotal = 0;
            float blueTotal = 0 ;
            float edgeCount = 0;
            float redAvg = 0;
            float greenAvg = 0;
            float blueAvg = 0;
            int topOffset = 0;
            int bottomOffset = 0;
            int leftOffset = 0;
            int rightOffset = 0;
            // if top row
            if(i == 0 &&  j != 0 && j != width -1)
            {
                edgeCount = 3;
                topOffset = 1;
            }
            // if bottom row
            else if(i == height -1 && j != 0 && j != width -1)
            {
                edgeCount = 3;
                bottomOffset = -1;
            }
            // if left column
            else if(j == 0 && i != 0 && i != height -1)
            {
                edgeCount = 3;
                leftOffset = 1;
            }
            //if right column
            else if(j == width -1 && i != 0 && i != height -1)
            {
                edgeCount = 3;
                rightOffset = -1;
            }
            //top left corner
            else if(i == 0 && j == 0)
            {
                edgeCount = 5;
                topOffset = 1;
                leftOffset = 1;
            }
            //bottom left corner
            else if(i == height - 1 && j == 0)
            {
                edgeCount = 5;
                bottomOffset = -1;
                leftOffset = 1;
            }
            //top right corner
            else if(j == width - 1 && i == 0)
            {
                edgeCount = 5;
                topOffset = 1;
                rightOffset = -1;
            }
            //bottom right corner
            else if(j == width - 1 && i == height - 1)
            {
                edgeCount = 5;
                bottomOffset = -1;
                rightOffset = -1;
            }

            //Get the average RGB value of the grid
            for(int r = i - 1 + topOffset ; r <= i + 1 + bottomOffset ; r++)
            {
                for(int c = j - 1 + leftOffset ; c <= j + 1 + rightOffset ; c++)
                {
                    redTotal += imgcpy[r][c].rgbtRed;
                    greenTotal += imgcpy[r][c].rgbtGreen;
                    blueTotal += imgcpy[r][c].rgbtBlue;
                }
            }
                redAvg = redTotal/(9-edgeCount);
                greenAvg = greenTotal/(9-edgeCount);
                blueAvg = blueTotal/(9-edgeCount);

                redAvg = round(redAvg);
                greenAvg = round(greenAvg);
                blueAvg = round(blueAvg);

                image[i][j].rgbtRed = redAvg;
                image[i][j].rgbtGreen = greenAvg;
                image[i][j].rgbtBlue = blueAvg;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1 , 0 , 1}, {-2, 0 , 2}, {-1 , 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1 , 2, 1}};
    RGBTRIPLE imgcpy[height][width];
    //Save the original pixel value
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            imgcpy[i][j] = image[i][j];

        }
    }
    //Go through each of the pixel
    for(int i = 0; i < height ; i++)
    {
        for(int j = 0; j < width ; j++)
        {
            int redGx = 0;
            int greenGx = 0;
            int blueGx = 0;
            int redGy = 0;
            int greenGy = 0;
            int blueGy = 0;
            int redChannel = 0;
            int greenChannel = 0;
            int blueChannel = 0;
            for(int r = -1; r < 2; r++)
            {
                for(int c = -1; c < 2; c++)
                {
                    //if top or bottom edge case, ignore
                    if(r + i < 0 || r + i > height - 1)
                    {
                        continue;
                    }
                    //if left or right edge case, ignore
                    if(c + j < 0 || c + j > width - 1)
                    {
                        continue;
                    }
                    //logic for getting Gx & Gy
                    redGx += imgcpy[r + i][c + j].rgbtRed * gx[r + 1][c + 1];
                    greenGx += imgcpy[r + i][c + j].rgbtGreen * gx[r + 1][c + 1];
                    blueGx += imgcpy[r + i][c + j].rgbtBlue * gx[r + 1][c + 1];
                    redGy += imgcpy[r + i][c + j].rgbtRed * gy[r + 1][c + 1];
                    greenGy += imgcpy[r + i][c + j].rgbtGreen * gy[r + 1][c + 1];
                    blueGy += imgcpy[r + i][c + j].rgbtBlue * gy[r + 1][c + 1];
                }
            }
            //Gx^2 + Gy^2
            redChannel = round(sqrt(pow(redGx,2) + pow(redGy,2)));
            greenChannel = round(sqrt(pow(greenGx,2) + pow(greenGy,2)));
            blueChannel =  round(sqrt(pow(blueGx,2) + pow(blueGy,2)));
            if(redChannel > 255)
            {
                redChannel = 255;
            }
            if(greenChannel > 255)
            {
                greenChannel = 255;
            }
            if(blueChannel > 255)
            {
                blueChannel = 255;
            }

            image[i][j].rgbtRed = redChannel;
            image[i][j].rgbtGreen = greenChannel;
            image[i][j].rgbtBlue = blueChannel;

        }
    }
    return;
}

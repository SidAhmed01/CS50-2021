#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int average = round((pixel.rgbtBlue + pixel.rgbtRed + pixel.rgbtGreen) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            float originalRed = pixel.rgbtRed;
            // Apply formulas to the pixel
            int sepiaRed = round(.393 * pixel.rgbtRed + .769 * pixel.rgbtGreen + .189 * pixel.rgbtBlue);
            int sepiaGreen = round(.349 * pixel.rgbtRed + .686 * pixel.rgbtGreen + .168 * pixel.rgbtBlue);
            int sepiaBlue = round(.272 * pixel.rgbtRed + .534 * pixel.rgbtGreen + .131 * pixel.rgbtBlue);
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    //Transformations to temp
    //1 2 3 4 -> _ _ _ _
    //        j  cP
    //4 5 6 7 ->

    //Copy to final image
    for(int i = 0; i < height; i++)
    {
        int curPos = 0;
        for(int j = width - 1; j >= 0; j--, curPos++)
        {
            temp[i][curPos] = image[i][j];
        }
    }
    //Copy to final image
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

     RGBTRIPLE temp[height][width];
     /*
     for each row
     for each col
         set count to 0
         for every neighboring pixel within the radius m in the x diretion
             for every neighboring pixel within the radius m in the y direction
               add the color to the total
               count++
         final_color = total/count
         setpixel(current x, current y, final_color)
     */
    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            int count = 0;
            int rowCoords[] = { row-1, row, row+1 };
            int colCoords[] = { col-1, col, col+1 };
            float totalR = 0, totalG = 0, totalB = 0;
            for(int r = 0; r < 3; r++)
            {
                for(int c = 0; c < 3; c++)
                {
                    int curRow = rowCoords[r];
                    int curCol = rowCoords[c];
                    if (curRow >= 0 && curRow < height && curCol >=0 && curCol < width)
                    {
                        RGBTRIPLE pixel = image [curRow][curCol];
                        totalR += pixel.rgbtRed;
                        totalG += pixel.rgbtGreen;
                        totalB += pixel.rgbtBlue;
                        count++;
                        
                    }
                    
                }
            }
            // I have examind all the neightboring cells
            image[row][col].rgbtRed = round(totalR / count);
            image[row][col].rgbtGreen = round(totalG / count);
            image[row][col].rgbtBlue = round(totalB / count);
        }
    } 

     //Copy to final image
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

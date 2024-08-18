#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale - convert to black and white
/*
    xxyyzz: when x == y == z -> shades of gray, higher values -> lighter
    we will take the average of r, g and b
*/
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // take average of red, grenn and blue
            avg = round(((float) image[i][j].rgbtRed + (float) image[i][j].rgbtGreen +
                         (float) image[i][j].rgbtBlue) /
                        3.0);
            // update pixel values
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            sepiaRed = round(.393 * (float)image[i][j].rgbtRed + .769 * (float)image[i][j].rgbtGreen + .189 * (float)image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * (float)image[i][j].rgbtRed + .686 * (float)image[i][j].rgbtGreen + .168 * (float)image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * (float)image[i][j].rgbtRed + .534 * (float)image[i][j].rgbtGreen + .131 * (float)image[i][j].rgbtBlue);
            // Update pixel with sepia values
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
        }
    }
    return;
}

void free_img_temp(int height, int width, RGBTRIPLE **image_temp)
{
    int i = 0;
    while (i < height)
    {
        free(image_temp[i]);
        i++;
    }
    free(image_temp);
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // // free memory after using image_temp
    // free_2d_array(height, width, image_temp);

    // Loop over all pixels
    int h;
    int w;
    int width_temp;
    // Allocate memory for an array of height pointers
    RGBTRIPLE **image_temp = (RGBTRIPLE **) malloc(height * sizeof(RGBTRIPLE *));
    // Allocate memory for each row
    for (int p = 0; p < height; p++)
        image_temp[p] = (RGBTRIPLE *) malloc(width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_temp[i][j] = image[i][j]; 
        }
    }
    for (h = 0; h < height; h++)
    {
        for (w = 0, width_temp = width; width_temp > 0; w++, width_temp--)
        {
            image[h][w] = image_temp[h][width_temp - 1];
        }
    }
    // free memory after using image_temp
    free_img_temp(height, width, image_temp);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
                float red = 0, green = 0, blue = 0, average = 0;
                for (int y = -1; y < 2; y++)
                {
                    for (int x = -1; x < 2; x++)
                    {
                        if (i + y < 0 || i + y > height - 1 || j + x < 0 || j + x > width - 1)
                        {
                            continue;
                        }
                        blue += image[i + y][j + x].rgbtBlue;
                        green += image[i + y][j + x].rgbtGreen;
                        red += image[i + y][j + x].rgbtRed;
                        average++;
                    }
                }
                copy[i][j].rgbtBlue = round(blue / average);
                copy[i][j].rgbtGreen = round(green / average);
                copy[i][j].rgbtRed = round(red / average);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }
    return;
}

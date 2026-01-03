#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = 0;
    while (n <= 0)
    {
        n = get_int("Height: ");
    }
    int leftAir = n - 1;
    int leftBrick = 1;
    int rightAir = n - 1;
    int rightBrick = 1;

    for (int row = 0; row < n; row++)
    {
        // Printing left air
        for (int i = leftAir; i > 0; i--)
        {
            printf(" ");
        }
        // Printing left side of pyramide
        for (int i = leftBrick; i > 0; i--)
        {
            printf("#");
        }
        leftAir -= 1;
        leftBrick += 1;
        printf("  ");
        // Printing right side of pyramide
        for (int i = rightBrick; i > 0; i--)
        {
            printf("#");
        }
        printf("\n");
        rightAir += 1;
        rightBrick += 1;
    }
    return (0);
}
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

int main(void)
{
    int i;
    int height;
    int space;
    int hash;
    i = 0;
    space = 0;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);
    while (i < height)
    {
        while (space < (height - i))
        {
            if (space != 0)
                printf(" ");
            space++;
        }
        while (space <= (height))
        {
            printf("#");
            space++;
        }
        printf("\n");
        i++;
        space = 0;
    }
    return (0);
}
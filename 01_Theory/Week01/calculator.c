#include <cs50.h>
#include <stdio.h>
// cc calculator.c -o calculator -lcs50

int main(void)
{
    long dollars = 1;
    while (true)
    {
        char c = get_char("Here's $%li. Double it and give to next person? ", dollars);
        if (c == 'y')
        {
            dollars *= 2;
        }
        else break;
    }
    return (0);
}
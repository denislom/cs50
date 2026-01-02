#include <cs50.h>
#include <stdio.h>
// cc cat.c -o cat -lcs50

// Prototype
void    meow(int n);

int main(void)
{
    int n = get_int("What's n? ");
    meow(n);
}

void    meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}
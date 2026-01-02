#include <cs50.h>
#include <stdio.h>
// cc cat.c -o cat -lcs50

// Prototype
void    meow(int n);
int get_n(void);

int main(void)
{
    int n = get_n();
    meow(n);
}

int get_n(void)
{
    int n;
    do
    {
        n = get_int("What's n? ");
    }
    while (n < 0);
    return n;
}

void    meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}
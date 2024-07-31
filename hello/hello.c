#include <cs50.h>
#include <stdio.h>

// https://cs50.harvard.edu/x/2023/psets/1/hello/
// https://manual.cs50.io/
/*
check50 cs50/problems/2023/x/hello
style50 hello.c
submit50 cs50/problems/2023/x/hello
*/
int main(void)
{
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
    return (0);
}
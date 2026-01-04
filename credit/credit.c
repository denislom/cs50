#include <cs50.h>
#include <stdio.h>

/*
    American Express:   15 digits, starts with 34 or 37
    MasterCard:         16 digits, starts with 51, 52, 53, 54 or 55
    Visa:               13 or 16 digits, starts with 4
*/

int main(void)
{
    long number = get_long("Number: ");

    // Count digits
    long temp = number;
    int digits = 0;
    while (temp > 0)
    {
        digits++;
        temp /= 10;
    }

    // Luhn’s algorithm
    int sum1 = 0; // sum of digits of products (*2)
    int sum2 = 0; // sum of other digits
    temp = number;
    int position = 0;

    while (temp > 0)
    {
        int digit = temp % 10;

        if (position % 2 == 0)
        {
            sum2 += digit;
        }
        else
        {
            int product = digit * 2;
            sum1 += (product / 10) + (product % 10);
        }

        temp /= 10;
        position++;
    }

    int total = sum1 + sum2;

    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Check provider rules
    if (digits == 15 && (number / 10000000000000LL == 34 || number / 10000000000000LL == 37))
    {
        printf("AMEX\n");
    }
    else if (digits == 16 && (number / 100000000000000LL >= 51 && number / 100000000000000LL <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((digits == 13 || digits == 16) &&
             (number / 1000000000000000LL == 4 || (digits == 13 && number / 1000000000000LL == 4)))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    return (0);
}

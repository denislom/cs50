// clang -lcs50 substitution.c

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i = 0;
	int	j = 1;

	if (argc != 2)
		return (printf("Usage: ./substitution key\n"), 1);
	else
	{
		while (argv[1][i] != '\0')
		{
			// Check for non-alphabetic characters
			if (isalpha(argv[1][i]) == 0)
				return (printf("Key must contain only alphabetical characters\n"), 1);
			// Check for repeated characters (case-insensitive)
			while (argv[1][j])
			{
				if (argv[1][i] == tolower(argv[1][j]) || argv[1][i] == toupper(argv[1][j]))
					return (printf("The characters in the input can't be repeated\n"), 1);
				j++;
			}
			i++;
			j = i +1;
		}
		// Check for key length
		if (i != 26)
			return (printf("Key must contain 26 characters\n"), 1);
		else
		{
			char *str = get_string("plaintext: ");
			printf("ciphertext: ");
			i = 0;
			j = 0;
			char	c;
			while (str[i])
			{
				if (str[i] >= 'A' && str[i] <= 'Z')
				{
					j = str[i] - 'A';
					c = toupper(argv[1][j]);
					printf("%c", c);
					i++;
				}
				else if (str[i] >= 'a' && str[i] <= 'z')
				{
					j = str[i] - 'a';
					c = tolower(argv[1][j]);
					printf("%c", c);
					i++;
				}
				else
				{
					write(1, &str[i], 1);
					i++;
				}
			}
			printf("\n");
		}
	}
	return (0);
}
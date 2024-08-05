// index = 0.0588 * L - 0.296 * S - 15.8
// L: average number of letter per 100 words in the text
// S: average number of sentences per 100 words in the text

// clang -lcs50 readability.c

#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int	count_words(char *str);
int	count_letters(char *str);
int	count_sentences(char *str);


int	main(void)
{
	// Prompt the user for some text
	char *str = get_string("Text: ");
	int	letters = 0;
	int	words = 0;
	int	sentences = 0;
	int	i = 0;
	// int	index;

	// Count the number of letters, words, and sentences in the text
	letters = count_letters(str);
	words = count_words(str);
	sentences = count_sentences(str);

	// Compute the Coleman-Liau index
	float	S = 0;
	float	L = 0;
	S = ((float)sentences / (float)words) * 100;
	L = ((float)letters / (float)words) * 100;
	float	index = (0.0588 * L) - (0.296 * S) - 15.8;

	// Print the grade level
	if (index < 1)
		printf("Before Grade 1\n");
	else if (index >= 16)
		printf("Grade 16+\n");
	else
		printf("Grade %d\n", (int) round(index));
}

int	count_words(char *str)
{
	int	i = 0;
	int	words = 1;

	while (str[i])
	{
		if (str[i + 1] == ' ')
			words++;
		i++;
	}
	return (words);
}

int	count_letters(char *str)
{
	int	i = 0;
	int	letters = 0;

	while (str[i])
	{
		if(isalpha(str[i]))
			letters++;
		i++;
	}
	return (letters);
}

int	count_sentences(char *str)
{
	int	i = 0;
	int sentences = 0;

	while (str[i])
	{
		if (str[i] == '.' || str[i] == '?' || str[i] == '!')
			sentences++;
		i++;
	}
	return (sentences);
}

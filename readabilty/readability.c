#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// int L_avg_nr_letters(char *s);
// int S_avg_nr_sentences(char *s);
int count_words(char *s);
int count_sentences(char *s);
int count_letters(char *s);

// index = 0.0588 * L - 0.296 * S - 15.8
int main(void)
{
    int words;
    char *text;
    int sentences;
    int letters;
    float L;
    float S;
    int index;

    text = get_string("Text: ");
    words = count_words(text);
    sentences = count_sentences(text);
    letters = count_letters(text);
    // printf("Obtained text is: \n%s\nCount of words: %i\nCount of sentences: %i\nCount of letters: %i\n",text, words, sentences, letters);
    L = ((float)letters / (float)words / 100);
    S = ((float)sentences / (float)words / 100);
    index = 0.0588 * L - 0.296 * S - 15.8;
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    return (0);
}

int count_words(char *s)
{
    int words;
    int i;

    words = 0;
    i = 0;
    while(s[i] != '\0')
    {
        if (s[i] == ' ')
            words++;
        i++;
    }
    words++;
    return (words);
}

int count_sentences(char *s)
{
    int i;
    int sentences;

    i = 0;
    sentences = 0;
    while(s[i] == ' ')
        i++;
    while(s[i] != '\0')
    {
        if(s[i] == '!' || s[i] == '?' || s[i] == '.')
            sentences++;
        i++;
    }
    return (sentences);
}

int count_letters(char *s)
{
    int i;
    int letters;

    i = 0;
    letters = 0;
    while(s[i] != '\0')
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            letters++;
        i++;
    }
    return (letters);
}
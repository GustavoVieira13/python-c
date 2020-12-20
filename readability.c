//Programa que recomenda idade mínima para leitura de devido texto baseado em fragmento do mesmo
//Gustavo Vieira

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int letter(int length_l, char array_l[]);
int word(int length_w, char array_w[]);
int sentence(int length_s, char array_s[]);

int main()
{
    string text = get_string("Input: ");        //fill each space of the text[] (array) with each letter
    printf("Text: ");
    
    int n = strlen(text);                       //strlen assignes the length of the string to n
    for (int i = 0; i < n; i++)                
    {
        printf("%c", text[i]);                  //outputs the text
    }
    printf("\n");
    
    //printf("%d letter(s)\n", letter(n, text));
    //printf("%d word(s)\n", word(n, text));
    //printf("%d sentence(s)\n", sentence(n, text));
    
    float l_avg = (float) letter(n, text) * 100 / (float) word(n, text);    //avarage of letters per 100 words
    float s_avg = (float) sentence(n, text) * 100 / (float) word(n, text);  //avarages of sentences per 100 words
    float index = round(0.0588 * l_avg - 0.296 * s_avg - 15.8);             //Coleman-Liau index formulae
    
    //printf("%f\n", l_avg);
    //printf("%f\n", s_avg);
    //printf("%f\n", index);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index == 1)
    {
        printf("Grade 1\n");
    }
    else if (index == 2)
    {
        printf("Grade 2\n");
    }
    else if (index == 3)
    {
        printf("Grade 3\n");
    }
    else if (index == 4)
    {
        printf("Grade 4\n");
    }
    else if (index == 5)
    {
        printf("Grade 5\n");
    }
    else if (index == 6)
    {
        printf("Grade 6\n");
    }
    else if (index == 7)
    {
        printf("Grade 7\n");
    }
    else if (index == 8)
    {
        printf("Grade 8\n");
    }
    else if (index == 9)
    {
        printf("Grade 9\n");
    }
    else if (index == 10)
    {
        printf("Grade 10\n");
    }
    else if (index == 11)
    {
        printf("Grade 11\n");
    }
    else if (index == 12)
    {
        printf("Grade 12\n");
    }
    else if (index == 13)
    {
        printf("Grade 13\n");
    }
    else if (index == 14)
    {
        printf("Grade 14\n");
    }
    else if (index == 15)
    {
        printf("Grade 15\n");
    }
    else if (index == 16)
    {
        printf("Grade 16\n");
    }
    else //if (index > 16)
    {
        printf("Grade 16+\n");
    }
    
}


int letter(int length_l, char array_l[])                       //function gets number of letters from the text
{
    int sum_letters = 0;    //store the summation of letters
    for (int i = 0; i < length_l; i++)
    {
        if (isalpha(array_l[i]))
        {
            sum_letters += 1;
        }
    }
    return sum_letters;
}


int word(int length_w, char array_w[])                        //function gets number of words from the text
{
    int sum_words = 0;
    for (int i = 0; i < length_w; i++)
    {
        if (i == 0 || (isspace(array_w[i]) && isalpha(array_w[i + 1])) || (ispunct(array_w[i]) && (array_w[i] != '-') 
                && ((int) array_w[i] != 39) && isalpha(array_w[i + 1])))  //attention to the first condition
        {
            sum_words += 1;
        }
    }
    return sum_words;
}


int sentence(int length_s, char array_s[])                  //function gets number of senteces from the text
{
    int sum_sentences = 0;
    for (int i = 0; i < length_s; i++)
    {
        if (isalpha(array_s[i]) && ((array_s[i + 1] == '.' || (array_s[i + 1] == '?' || (array_s[i + 1] == '!')))))
        {
            sum_sentences += 1;
        }
    }
    return sum_sentences;
}

//Programa imprime uma pirâmide de altura determinada pelo usuário
//Gustavo Vieira

#include <stdio.h>
#include <cs50.h>

int main()
{
    int n; //number of rows
    int i; //current row
    int j; //columns
    
    do
    {
        n = get_int("What is the height of the pyramid?\n");
    }
    while (n < 1 || n > 8);

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n - i; j++) //number of dots = n - i
        { 
            printf(" ");
        }
        for (j = 1; j <= i; j++) //number of hashes proportional to current row
        { 
            printf("#");
        }
        printf("\n"); 
    }
    return 0;
}

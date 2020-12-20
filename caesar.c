//Programa de criptografia basilar no qual as letras do alfabeto são deslocadas baseada na chave imputada
//Gustavo Vieira

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    string key = argv[1];  //assembles the key value stored in argv[1] to the string key
    
    if (argc == 2)  //checks if the command-line has only 2 arguments
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)  //loops each character of the key in order to check if it is valid
        {
            if (!isdigit(key[i]))  //if the key is not composed only by digits it is invalid
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    else  //if the command-line has more than two arguments it prompts an usage message
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    int k = atoi(key);  //converts the digits from string characters into integers
    string plain = get_string("plaintext: ");
    printf("ciphertext: ");
    
    for (int j = 0, m = strlen(plain); j < m; j++) //loops each character of the input message
    {
        if (plain[j] >= 'a' && plain[j] <= 'z')  //checks if the character is a lowercase letter
        {
            printf("%c", (((plain[j] - 'a') + k) % 26) + 'a');  //prints ciphered lowercase character
        }
        else if (plain[j] >= 'A' && plain[j] <= 'Z')  //checks if the character is a uppercase letter
        {
            printf("%c", (((plain[j] - 'A') + k) % 26) + 'A');  //prints ciphered uppercase character
        }
        else
        {
            printf("%c", plain[j]);  //prints the same input character if it is not an alphanumeric character
        }
    }
    printf("\n");
}

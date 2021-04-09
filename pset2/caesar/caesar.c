//pset caesar

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>




int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar k");
        return 1;
    }
    //loops
    for (int k = 0; k < strlen(argv[1]); k++)
    {
        if (isalpha(argv[1][k]))
        {
            printf("Usage: ./caesar key \n");
            return 1;
        }
    }
    //variable
    int k = atoi(argv[1]) % 26; //if k is > 26, stor the division remainder
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (!isalpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
            continue;
        }
        
        int ascii_offset = isupper(plaintext[i]) ? 65 : 97;
        int pi = plaintext[i] - ascii_offset;
        int ci = (pi + k) % 26; 
        printf("%c", ci + ascii_offset);
    }
        
    printf("\n");
    return 0;

}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* encrypt(char* string, char* password, char* table, int length)
{
    int password_length = (int)strlen(password);
    char* cipher = (char*)malloc(length);
    int idk;
    for(int i = 0, j = 0; i < length; i++, j++)
    {
        if(j == password_length)
            j = 0;
        idk = (string[i] + password[j] + password_length) % 256;
        cipher[i] = table[idk];
        printf("%u ", (unsigned int)(string[i] + password[j]) % 256);
    }
    return cipher;
}

char* decrypt(char* string, char* password, char* table, int length)
{
    int password_length = (int)strlen(password);
    char* deciphered = (char*)malloc(length);
    for(int i = 0, j = 0; i < length; i++, j++)
    {
        if(j == password_length)
            j = 0;
        deciphered[i] = table[(string[i] - password[j] + 256 - password_length) % 256];
        printf("%c", deciphered[i]);
    }
    return deciphered;
}

char* generateTable()
{
    char* table = (char*)malloc(65536);
    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            table[i * 256 + j]  = (char)((i + j) % 256);
        }
    }
    return table;
}

int main()
{

    FILE * input = fopen("test.txt", "rb");
    fseek(input, 0L, SEEK_END);
    int length = ftell(input);
    fseek(input, 0L, SEEK_SET);

    FILE* tmp = fopen("temp.txt", "wb");
    FILE *deciphered_temp = fopen("dec_tmp.txt", "wb");

    printf("Enter Your Password:");
    char* password = " ";


    char* buffer = (char*)malloc(length);

    fread(buffer, 1, length, input);
    char* table = generateTable();
    char* cipher = encrypt(buffer, password, table, length);
    fwrite(cipher, sizeof(char), length, tmp);
    char* deciphered = decrypt(cipher, password, table, length);
    fwrite(deciphered, sizeof(char), length, deciphered_temp);

    fclose(input);
    fclose(tmp);
    fclose(deciphered_temp);
    return 0;
}

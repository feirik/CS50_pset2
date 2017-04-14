#include <stdio.h>
#include <cs50.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>

#define _XOPEN_SOURCE

#define ALPHABET_LEN 26

// clang -ggdb3 -O0 -std=c11 -Wall -Werror -Wshadow crack.c -lcrypt -lcs50 -lm -o crack

void copySalt(char hashInput[], char salt[]);
void copyKey(char hashInput[], char salt[], int inputLen);
void crackPassword(char search[], char salt[], char key[]);

int main(int argc, string argv[])
{
    // Verifying command line input is 1 argument, else exit with an error
    if(argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    int inputLen = strlen(argv[1]);
    
    char salt[2];
    char key[inputLen];
    
    copySalt(argv[1], salt);
    copyKey(argv[1], key, inputLen);
    
    char search[5] = {'A','\0','\0','\0','\0'};
    
    crackPassword(search, salt, key);
    
    return 0;
}

// Input of a search char array, salt char array and key char array
// Generates all possible combinations of 4 letter words
// Hashes the generated word and comparison checks the hash
// with the hash input in "key",
// If hashes match, prints the cracked password implicit in key. 
// Else prints an error message with a blank password.

void crackPassword(char search[], char salt[], char key[])
{
    string hashSearch;
    
    // One letter search
    // Char 'A' in search array initialized in main
    for(int i = 0; i < (2*ALPHABET_LEN); i++)
    {
        // If done with uppercase alphabet, begin lower case 'a'
        if(search[0] == ('Z' + 1))
        {
            search[0] = 'a';
        }
        // Encrypt the search string, creating hash search
        hashSearch = crypt(search, salt);
        
        // Compare the hash search with the key, if true
        // Go to end and print the found password
        if(strcmp(key, hashSearch) == 0)
        {
            goto label;
        }
        // Increments char
        search[0] += 1;
    }
    
    // Two letter search
    for(int i = 0; i < (2*ALPHABET_LEN); i++)
    {
        // Initializes search array[1] from '\0' to 'A'
        if(i == 0)
        {
            search[0] = 'A';
        }
        if(search[0] == ('Z' + 1))
        {
            search[0] = 'a';
        }
        
        for(int j = 0; j < (2*ALPHABET_LEN); j++)
        {
            if(j == 0)
            {
                search[1] = 'A';
            }
            if(search[1] == ('Z' + 1))
            {
                search[1] = 'a';
            }
            
            hashSearch = crypt(search, salt);
            if(strcmp(key, hashSearch) == 0)
            {
                goto label;
            }
            search[1] += 1;
        }
        
        search[0] += 1;
    }
    
    // Three letter search
    for(int i = 0; i < (2*ALPHABET_LEN); i++)
    {
        if(i == 0)
        {
            search[0] = 'A';
        }
        if(search[0] == ('Z' + 1))
        {
            search[0] = 'a';
        }
        
        for(int j = 0; j < (2*ALPHABET_LEN); j++)
        {
            if(j == 0)
            {
                search[1] = 'A';
            }
            if(search[1] == ('Z' + 1))
            {
                search[1] = 'a';
            }
            
            for(int k = 0; k < (2*ALPHABET_LEN); k++)
            {
                if(k == 0)
                {
                    search[2] = 'A';
                }
                if(search[2] == ('Z' + 1))
                {
                    search[2] = 'a';
                }
                
                hashSearch = crypt(search, salt);
                if(strcmp(key, hashSearch) == 0)
                {
                    goto label;
                }
                search[2] += 1;
            }
            
            search[1] += 1;
        }
        
        search[0] += 1;
    }
    
    // Four letter search
    for(int i = 0; i < (2*ALPHABET_LEN); i++)
    {
        if(i == 0)
        {
            search[0] = 'A';
        }
        if(search[0] == ('Z' + 1))
        {
            search[0] = 'a';
        }
        
        for(int j = 0; j < (2*ALPHABET_LEN); j++)
        {
            if(j == 0)
            {
                search[1] = 'A';
            }
            if(search[1] == ('Z' + 1))
            {
                search[1] = 'a';
            }
            
            for(int k = 0; k < (2*ALPHABET_LEN); k++)
            {
                if(k == 0)
                {
                    search[2] = 'A';
                }
                if(search[2] == ('Z' + 1))
                {
                    search[2] = 'a';
                }
                
                for(int l = 0; l < (2*ALPHABET_LEN); l++)
                {
                    if(l == 0)
                    {
                        search[3] = 'A';
                    }
                    if(search[3] == ('Z' + 1))
                    {
                        search[3] = 'a';
                    }
                    
                    hashSearch = crypt(search, salt);
                    if(strcmp(key, hashSearch) == 0)
                    {
                        goto label;
                    }
                    search[3] += 1;
                }
                
                search[2] += 1;
            }
            
            search[1] += 1;
        }
        
        search[0] += 1;
    }
    
    printf("ERROR if printed, pw not found: \n");
    
    label: printf("%s\n", search);
}

// Input of a char array hash input and char array salt
// Copies the 2 first elements in the hash into salt array
void copySalt(char hashInput[], char salt[])
{
    for(int i = 0; i < 2; i++)
    {
        salt[i] = hashInput[i];
    }
}

// Input of a char array hash input, char array key, int input length
// Copies the hash array to the key array
void copyKey(char hashInput[], char key[], int inputLen)
{
    for(int i = 0; i < inputLen; i++)
    {
        key[i] = hashInput[i];
    }   
}
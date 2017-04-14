#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string getPlaintext(void);
void makeKeyArray(int *keyArray, string key, int keyLength);
void updateCypherText(string plaintext, int *cypherText, int *key, int keyLength);
void printCypherText(int *cypherText, int cypherLength);

int main(int argc, string argv[])
{
    // Checking if command line input of 1 argument, else exit with an error
    if(argc != 2)
    {
        printf("Exit 1 number of argument error\n");
        return 1;
    }
    // Checking if the command line input is of all alphabetical letters, else exit with an error
    for(int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if(!isalpha(argv[1][i]))
        {
            printf("Exit 1 number of integer input argument error\n");
            return 1;
        }
    }

    int keyLength = strlen(argv[1]);
    int key[keyLength];
    
    makeKeyArray(key, argv[1], keyLength);
    
    string plaintext = getPlaintext();
    
    int inputLen = strlen(plaintext);
    int cypherText[inputLen];
    
    updateCypherText(plaintext, cypherText, key, keyLength);
    
    printCypherText(cypherText, inputLen);
    
    return 0;
}

// Input of an int array, length of the array
// Prints the ints of the array as characters, ending with \n
void printCypherText(int *cypherText, int cypherLen)
{
    printf("ciphertext: ");
    for(int i = 0; i < cypherLen; i++)
    {
        printf("%c", cypherText[i]);
    }
    printf("\n");
    
}

// Input of a string plaintext, int array cyphertext, int array key, int key length
// updates the cyphertext array 
// with the plaintext char int values manipulated by the key array vaules
// by Vigenere`s formula
void updateCypherText(string plaintext, int *cypherText, int *key, int keyLength)
{
    int k = 0;
    int j = 0;
    // Iterating through chars until end of string
    while(plaintext[j] != '\0')
    {
        // If the char is capitalized
        if(isupper(plaintext[j]) != 0)
        {
            // Checking if plaintext + key value needs to wrap around alphabet
            if((int)plaintext[j] + key[k] > 'Z')
            {
                // Reduce by size of alphabet
                cypherText[j] = (int)plaintext[j] + key[k] - 26;
            }
            else
            {
                cypherText[j] = (int)plaintext[j] + key[k];
            }
            
            k++;
            // If key count at end of key, wrap around the key array
            if(k == keyLength)
            {
                k = 0;
            }
        }
        // If the char is not capitalized
        if(islower(plaintext[j]) != 0)
        {
            if((int)plaintext[j] + key[k] > 'z')
            {
                cypherText[j] = (int)plaintext[j] + key[k] - 26;
            }
            else
            {
                cypherText[j] = (int)plaintext[j] + key[k];
            }
            
            k++;
            if(k == keyLength)
            {
                k = 0;
            }
        }
        // If char is not an alphabetical letter, copy
        if(isalpha(plaintext[j]) == 0)
        {
            cypherText[j] = (plaintext[j]);
        }
        j++;
    }
}

// Input of an int array, a string keyword, int length of keyword
// Updates the array elements with numbers a/A = 0, b/B = 1... z/Z = 25
// for each char in string keyword
void makeKeyArray(int *keyArray, string key, int keyLength)
{
    for(int i = 0; i < keyLength; i++)
    {
        keyArray[i] = toupper(key[i])-65;
    }
}

// Prompts user for a string
// Returns the string
string getPlaintext(void)
{
    printf("plaintext: ");
    string s = get_string();
    
    return s;
}
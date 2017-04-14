#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string getName(void);
int getInitialsInfo(string name, char initials[]);
void printInitials(char initials[], int initialsCount);

int main(void)
{
    string name = getName();
    
    char initials[64];
    int initialsCount = 0;
    
    initialsCount = getInitialsInfo(name, initials);
    printInitials(initials, initialsCount);
    
    return 0;
}

// Prompts user for a name
// Returns the name as a string
string getName(void)
{
    //printf("What is your full name?\n");
    string s = get_string();
    
    return s;
}

// Input of a full name as a string, char array to store initials
// Updates the char array with found chars
// Returns the number of initials found
int getInitialsInfo(string name, char initials[])
{
    int i = 0;
    int j = 0;
    
    // Looping until end of string
    while(name[i] != '\0')
    {
        // If first element in string is not a space, store as an initial
        if((name[i] != ' ') && i == 0)
        {
            initials[j] = name[i];
            // Iterates to next empty slot in array pluss counts the number of initials
            j++;
        }
        // If past first element in string
        // If previous element was a space and current element not a space, store as an initial
        if((i > 0) && (name[i-1] == ' ') && (name[i] != ' '))
        {
            initials[j] = name[i];
            j++;
        }
        i++;
    }
    // Returns count of initials that was found
    return j;
}


// Input of a char array of initials and a count of how many initials in array
// Capitalizes the chars and prints the initials, ending with a new line
void printInitials(char initials[], int initialsCount)
{
    for(int k = 0; k < initialsCount; k++)
    {
        printf("%c",toupper(initials[k]));
    }
    printf("\n");
}
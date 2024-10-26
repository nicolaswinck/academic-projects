#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"


// UI functions.

void clearInputBuffer(void)
{
    while (getchar() != '\n')
    {
        ;
    }
}


void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


// Input functions.

// Validates the input of an integer number by the user.
int inputInt(void)
{
    char userNewLine;
    int userInt, inputOk = 0;

    do {
        scanf("%d%c", &userInt, &userNewLine);

        // Validating newline character (ENTER key) input from user.
        if (userNewLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        else
        {
            inputOk = 1;
        }

    } while (inputOk == 0);

    return userInt;
}

// Validates the input of a positive integer number by the user.
int inputIntPositive(void)
{
    int userInt, inputOk = 0;

    do {
        // Validating an integer input from user.
        userInt = inputInt();

        // Validating the integer as a positive number.
        if (userInt < 1)
        {
            printf("ERROR! Value must be > 0: ");
        }
        else
        {
            inputOk = 1;
        }

    } while (inputOk == 0);

    return userInt;
}

// Validates the input of an integer number in a range between two values.
int inputIntRange(int lowerBound, int upperBound)
{
    int userInt, inputOk = 0;

    do {
        // Validating an integer input from user.
        userInt = inputInt();

        // Validating the min and max boundaries for the integer range.
        if (userInt < lowerBound || userInt > upperBound)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ",
                lowerBound, upperBound);
        }
        else
        {
            inputOk = 1;
        }

    } while (inputOk == 0);

    return userInt;
}

// Matches the entered characters with the input string.
char inputCharOption(const char validationStr[])
{
    char userInput[50], userChar;
    char* found;
    int inputOk = 0;

    do {
        // Getting a string from user input.
        scanf("%[^\n]", userInput);

        // Fetching only the first character.
        userChar = userInput[0];

        // Looking for the first occurrence of the character in the string.
        found = strchr(validationStr, userChar);

        // Checking for a match into the given string.
        if (found != NULL && strlen(userInput) == 1)
        {
            inputOk = 1;
        }

        // Returning error for no matches and displaying the validation string.
        else
        {
            clearInputBuffer();
            printf("ERROR: Character must be one of [%s]: ", validationStr);
        }

    } while (inputOk == 0);

    // Clearing buffer and returning the matching user character.
    clearInputBuffer();
    return userChar;
}

// Stores the user input string and checks for the character range of that string.
void inputCString(char* str, int min, int max)
{
    // Setting up a large string array and assigning it to a safe memory space.
    char value[50 + 1] = { 0 };
    int i, len, inputOk = 0, digitCount;

    do {
        // Getting user input preventing buffer overflow.
        scanf("%[^\n]", value);

        // Getting string length.
        len = strlen(value);

        // Copying the entered string to the 1st argument str.
        if (len >= min && len <= max)
        {
            strcpy(str, value);
        }

        // Checking for phone number strings (all digits).
        for (i = 0, digitCount = 0; i < len; i++)
        {
            if (isdigit(value[i]))
            {
                digitCount++;
            }
        }

        // Checking for equal min and max values.
        if (min == max)
        {
            // Displaying error message for standard non-digit string.
            if (len != max && digitCount != len)
            {
                clearInputBuffer();
                printf("ERROR: String length must be exactly %d chars: ", min);
            }
            // Displaying error message for telephone number string.
            else if (len != max && digitCount == len)
            {
                clearInputBuffer();
                printf("Invalid %d-digit number! Number: ", min);
            }
            else
            {
                inputOk = 1;
            }
        }
        // Checking for different min and max values.
        else
        {
            // Clearing buffer and giving the error messages to invalid values.
            if (len < min)
            {
                clearInputBuffer();
                printf("ERROR: String length must be between %d and %d chars: ", min, max);
            }
            else if (len > max)
            {
                clearInputBuffer();
                printf("ERROR: String length must be no more than %d chars: ", max);
            }
            else
            {
                inputOk = 1;
            }
        }

    } while (inputOk == 0);

    // Clearing input buffer.
    clearInputBuffer();
}


// Utility functions.

// Displays the formatted 10-character array for the input phone number.
void displayFormattedPhone(const char* strPhone)
{
    /* Declaring and assigning a variable, storing the default display for
    empty/invalid phone input. */
    char phoneFormat[13 + 1] = "(___)___-____";
    int i, len, notDigitFound = 0, isNull = 0;

    // Assigning validation flag for NULL string.
    if (strPhone == NULL)
    {
        isNull = 1;
    }

    // Cases for NULL and not NULL.
    switch (isNull)
    {
    case 1:
        break;
    case 0:

        // Getting the string length.

        len = strlen(strPhone);

        if (len > 0)
        {
            for (i = 0; i < len && !(notDigitFound); i++)
            {
                if (!(isdigit(strPhone[i])))
                {
                    notDigitFound = 1;
                }
            }

            // Validating the 10-digit phone.
            // Inserting numbers into the phone template format.
            if (len == 10 && notDigitFound == 0)
            {
                for (i = 0; i < strlen(phoneFormat); i++)
                {
                    if (i > 0 && i < 4)
                    {
                        phoneFormat[i] = strPhone[i - 1];
                    }

                    if (i > 4 && i < 8)
                    {
                        phoneFormat[i] = strPhone[i - 2];
                    }

                    if (i > 8)
                    {
                        phoneFormat[i] = strPhone[i - 3];
                    }
                }
            }
        }
        else
        {
            break;
        }
    }

    // Displaying the phone/empty template.
    printf("%s", phoneFormat);
}
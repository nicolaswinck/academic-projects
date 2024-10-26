#ifndef UTILS_H
#define UTILS_H


// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


// Validates the input of an integer number by the user.
int inputInt(void);

// Validates the input of a positive integer number by the user.
int inputIntPositive(void);

// Validates the input of an integer number in a range between two values.
int inputIntRange(int lowerBound, int upperBound);

// Matches the entered characters with the input string.
char inputCharOption(const char validationStr[]);

// Stores the user input string and checks for the character range of that string.
void inputCString(char* str, int min, int max);


// Displays the formatted 10-character array for the input phone number.
void displayFormattedPhone(const char* strPhone);



#endif // !UTILS_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include "File.h"
#include "Report.h"
using namespace std;

PostalRecord* records = { 0 };
int noOfPostalCodes = 0, noOfPopRecords = 0;
char userInput[4] = { '\0' };


bool startsWith(const char* cstring, const char* subString)
{
    return strstr(cstring, subString) == cstring;
}

// This function was adapted from the function provided in part 1.
void sort()
{
    PostalRecord temp;
    int i, j;
    for (i = noOfPostalCodes - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (records[j].population > records[j + 1].population)
            {
                temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
}

bool getPostalCode(char* postal_code_prefix)
{
    int result = false;

    // Printing out prompt to user.
    cout << "Population Report" << endl;
    cout << "-----------------" << endl;
    cout << "Enter postal code:" << endl;
    cout << "> ";

    // Getting entered value.
    cin >> postal_code_prefix;

    // Validating for end character ('!').
    if (!strcmp("!", postal_code_prefix))
    {
        result = false;
    }
    else
    {
        result = true;
        // Assigning the value through a copy if the result is true.
        // Getting input out of the scope of this function.
        strcpy(userInput, postal_code_prefix);
    }

    return result;
}

bool load(PostalRecord& records)
{
    // Creating char with the desired record size.
    char recordLine[7] = { '\0' };
    bool ok = false;

    // Calling two overloaded read() functions and setting the attributes.
    if (read(recordLine) == 1 &&
        read(records.population) == 1)
    {
        records.prefix = new char[7 + 1];
        strcpy(records.prefix, recordLine);

        ok = true;
    }

    return ok;
}

bool load(const char* filename, const char* partial_postal_code_prefix)
{
    bool isOpen = openFile(filename), ok = false;
    int rec, num;


    // Testing file opening.
    if (isOpen)
    {
        // Getting the number of records.
        noOfPostalCodes = noOfRecords();
        // Creating dynamically allocated array.
        records = new PostalRecord[noOfPostalCodes];

        // Loading each record from the file to the array elements.
        for (rec = 0, num = 0; num < noOfPostalCodes; num++)
        {
            rec += load(records[num]);
        }

        if (rec != noOfPostalCodes)
        {
            cout << "Error: incorrect number of records read; the data is possibly corrupted." << endl;
        }
        else
        {
            ok = true;
        }

        // Closing the file.
        closeFile();
    }
    else
    {
        cout << "Could not open data file:" << filename << endl;
    }

    return ok;
}

void display(const PostalRecord& records)
{
    // Printing the information in the correct format.
    cout << records.prefix << ":  "
        << records.population << endl;
}

void display()
{
    int rec, num;

    // Restarting the population count variable.
    noOfPopRecords = 0;

    // Printing header.
    cout << "Postal Code: population" << endl;
    cout << "-------------------------" << endl;

    // Sorting the population number (ascending).
    sort();

    // Printing each corresponding postal code.
    for (rec = 0, num = 0; num < noOfPostalCodes; num++)
    {
        // Displaying result for specific prefix match.
        if (startsWith(records[num].prefix, userInput))
        {
            cout << rec + 1 << "- "; // Adjusting from the index number.
            display(records[num]);
            noOfPopRecords += records[num].population;
            rec++; // Incrementing counter for records display number.
        }
        // Displaying all records read.
        else if (!strcmp(userInput, "all"))
        {
            cout << rec + 1 << "- ";
            display(records[num]);
            noOfPopRecords += records[num].population;
            rec++;
        }
        else
        {
            ; // Do nothing.
        }
    }

    // Printing the corresponding query result with total number of 
    // population displayed.
    cout << "-------------------------" << endl;
    cout << "Population of the listed areas: " << noOfPopRecords << endl;
    cout << '\n';
}

void deallocateMemory()
{
    for (int i = 0; i < noOfPostalCodes; i++)
    {
        // Deleting each record.
        delete[] records[i].prefix;
        records[i].prefix = nullptr;
    }

    // Deleting the array pointer.
    delete[] records;
    records = nullptr;
}
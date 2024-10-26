#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "File.h"

FILE* fptr;
bool openFile(const char filename[])
{
    fptr = fopen(filename, "r");
    return fptr != NULL;
}

int noOfRecords()
{
    int noOfRecs = 0;
    char ch;
    while (fscanf(fptr, "%c", &ch) == 1)
    {
        noOfRecs += (ch == '\n');
    }
    rewind(fptr);
    return noOfRecs;
}

bool read(char* pref)
{
    bool ok = false;

    if (fscanf(fptr, "%[^,],", pref) == 1)
    {
        ok = true;
    }

    return ok;
}

bool read(int& pop)
{
    bool ok = false;

    if (fscanf(fptr, "%d\n", &pop) == 1)
    {
        ok = true;
    }

    return ok;
}

void closeFile()
{
    if (fptr) fclose(fptr);
}
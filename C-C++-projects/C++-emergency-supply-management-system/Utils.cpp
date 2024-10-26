#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <string.h>
#include "Utils.h"

using namespace std;

Utils ut;
void Utils::testMode(bool testmode) {
    m_testMode = testmode;
}

// Function to dynamically allocate a string and copy to destination.
void Utils::alocpy(char*& destination, const char* source)
{
    destination = nullptr;

    if (source != nullptr)
    {
        destination = new char[strlen(source) + 1];
        strcpy(destination, source);
    }
}

// Get integer from istream.
int Utils::getInt()
{
    int num;
    bool done = false;

    do {
        cin >> num;

        if (cin.fail())
        {
            cerr << "Invalid Integer, retry: ";
            cin.clear();
        }
        else
        {
            done = true;
        }

        cin.ignore(100000, '\n');

    } while (!done);

    return num;
}

// Get integer (foolproof).
int Utils::getInt(int min, int max)
{
    int num;
    bool done = false;

    do
    {
        num = getInt();

        if (num < min || num > max)
        {
            cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
        }
        else
        {
            done = true;
        }

    } while (!done);

    return num;
}

// Get double from istream.
double Utils::getDouble()
{
    double num;
    bool done = false;

    do {
        cin >> num;

        if (cin.fail())
        {
            cerr << "Invalid number, retry: ";
            cin.clear();
        }
        else
        {
            done = true;
        }

        cin.ignore(100000, '\n');

    } while (!done);

    return num;
}

// Get double (foolproof).
double Utils::getDouble(double min, double max)
{
    double num;
    bool done = false;

    do
    {
        num = getDouble();

        if (num < min || num > max)
        {
            cout << "Value out of range [";
            cout.setf(ios::fixed);
            cout.precision(2);
            cout << min << "<=val<=" << max << "]: ";
        }
        else
        {
            done = true;
        }

    } while (!done);

    return num;
}

void Utils::getSystemDate(int* year, int* mon, int* day) {
    if (m_testMode) {
        if (day) *day = sdds_testDay;
        if (mon) *mon = sdds_testMon;
        if (year) *year = sdds_testYear;
    }
    else {
        time_t t = std::time(NULL);
        tm lt = *localtime(&t);
        if (day) *day = lt.tm_mday;
        if (mon) *mon = lt.tm_mon + 1;
        if (year) *year = lt.tm_year + 1900;
    }
}

int Utils::daysOfMon(int month, int year)const {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
    return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}
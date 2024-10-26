#ifndef UTILS_H
#define UTILS_H

const int sdds_testYear = 2023;
const int sdds_testMon = 12;
const int sdds_testDay = 9;
class Utils {
    bool m_testMode = false;
public:
    void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
    int daysOfMon(int mon, int year)const;
    void testMode(bool testmode = true);
    // Safely allocates memory in the destination and copies source into it.
    void alocpy(char*& destination, const char* source);
    /*Two functions to get an integer as input (foolproof).
    Those functions were designed by prof. Fardad,
    and were found in his notes from ZAA/08-Oct02,
    in the file m-foolproofEntry.cpp.*/
    int getInt();
    int getInt(int min, int max);
    // The two functions below are adapted from the ones above.
    double getDouble();
    double getDouble(double min, double max);
};
extern Utils ut;

#endif // !UTILS_H
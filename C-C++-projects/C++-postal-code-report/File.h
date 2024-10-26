#ifndef FILE_H_
#define FILE_H_

bool openFile(const char filename[]);

// Gets the number of records read.
// returns an integer that is the number of records in the file.
int noOfRecords();

// Reads from the file the record prefix and stores it in the parameter.
// @param pref - Address to a string with the postal code prefix.
// returns true if read was succcessful and false otherwise.
bool read(char* pref);

// Reads from the file the record population and stores it in the parameter.
// @param pop - Address to an int with the population amount.
// returns true if read was succcessful and false otherwise.
bool read(int& pop);

void closeFile();

#endif // !FILE_H_
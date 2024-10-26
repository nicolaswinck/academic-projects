#ifndef REPORT_H_
#define REPORT_H_

struct PostalRecord
{
    char* prefix;
    int population;
};

bool startsWith(const char* cString, const char* subString);
void sort();
bool getPostalCode(char* postal_code_prefix);
bool load(PostalRecord& records);
bool load(const char* filename, const char* partial_postal_code_prefix);
void display(const PostalRecord& records);
void display();
void deallocateMemory();

#endif // !REPORT_H_
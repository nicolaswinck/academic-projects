#ifndef GRADUATE_H
#define GRADUATE_H
#include <iostream>
#include "Student.h"

class Graduate : public Student
{
	char* m_supervisor{};
	char* m_thesisTitle{};

public:
	Graduate();
	Graduate(const char* name, int age, const char* thesisTitle, const char* supervisor);
	Graduate(const Graduate& gr);
	Graduate& operator=(const Graduate& gr);
	~Graduate();
	void display();
};

#endif // !GRADUATE_H
#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>

class Student
{
	char* m_name{};
	int m_age;

public:
	Student();
	Student(const char* name, int age);
	Student(const Student& st);
	Student& operator=(const Student& st);
	virtual ~Student();
	void display();
};

#endif // !STUDENT_H
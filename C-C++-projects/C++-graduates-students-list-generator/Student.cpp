#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <string>
#include "Student.h"

using namespace std;

Student::Student()
{
	m_age = 0;
}

Student::Student(const char* name, int age)
{
	// Assigning the argument age to the attribute age.
	m_age = age;

	if (name != nullptr)
	{
		// Deallocating memory.
		delete[] m_name;
		m_name = nullptr;

		// Dynamically assigning argument name to attribute name.
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}
	else
	{
		m_name = nullptr;
	}
}

Student::Student(const Student& st)
{
	// Assigning right hand age to attribute age.
	m_age = st.m_age;

	if (st.m_name != nullptr)
	{
		delete[] m_name;
		m_name = nullptr;

		// Dynamically assigning right hand name to attribute name.
		m_name = new char[strlen(st.m_name) + 1];
		strcpy(m_name, st.m_name);
	}
	else
	{
		m_name = nullptr;
	}
}

Student& Student::operator=(const Student& st)
{
	// Checking for self-assignment.
	if (this != &st)
	{
		delete[] m_name;

		m_age = st.m_age;

		if (st.m_name != nullptr)
		{
			m_name = new char[strlen(st.m_name) + 1];
			strcpy(m_name, st.m_name);
		}
		else
		{
			m_name = nullptr;
		}
	}

	return *this;
}

Student::~Student()
{
	delete[] m_name;
}

void Student::display()
{
	// Printing out name and age.
	cout << "Name: " << m_name << endl;
	cout << "Age: " << m_age << endl;
}
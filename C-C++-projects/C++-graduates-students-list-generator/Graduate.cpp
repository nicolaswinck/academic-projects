#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <string>
#include "Graduate.h"

using namespace std;

Graduate::Graduate()
{
	m_supervisor = nullptr;
	m_thesisTitle = nullptr;
}

// Getting the two arguments from the base class.
// Using base constructor to initialize name and age.
Graduate::Graduate(const char* name, int age,
	const char* thesisTitle, const char* supervisor) : Student(name, age)
{
	if (supervisor != nullptr)
	{
		m_supervisor = new char[strlen(supervisor) + 1];
		strcpy(m_supervisor, supervisor);
	}
	else
	{
		m_supervisor = nullptr;
	}

	if (thesisTitle != nullptr)
	{
		m_thesisTitle = new char[strlen(thesisTitle) + 1];
		strcpy(m_thesisTitle, thesisTitle);
	}
	else
	{
		m_thesisTitle = nullptr;
	}
}

Graduate::Graduate(const Graduate& gr) : Student(gr)
{
	if (gr.m_supervisor != nullptr)
	{
		m_supervisor = new char[strlen(gr.m_supervisor) + 1];
		strcpy(m_supervisor, gr.m_supervisor);
	}
	else
	{
		m_supervisor = nullptr;
	}


	if (gr.m_thesisTitle != nullptr)
	{
		m_thesisTitle = new char[strlen(gr.m_thesisTitle) + 1];
		strcpy(m_thesisTitle, gr.m_thesisTitle);
	}
	else
	{
		m_thesisTitle = nullptr;
	}
}

Graduate& Graduate::operator=(const Graduate& gr)
{
	if (this != &gr)
	{
		// Calling the assignment operator from the base class.
		Student::operator=(gr);

		delete[] m_supervisor;
		delete[] m_thesisTitle;

		if (gr.m_supervisor != nullptr)
		{
			m_supervisor = new char[strlen(gr.m_supervisor) + 1];
			strcpy(m_supervisor, gr.m_supervisor);
		}
		else
		{
			m_supervisor = nullptr;
		}

		if (gr.m_thesisTitle != nullptr)
		{
			m_thesisTitle = new char[strlen(gr.m_thesisTitle) + 1];
			strcpy(m_thesisTitle, gr.m_thesisTitle);
		}
		else
		{
			m_thesisTitle = nullptr;
		}
	}

	return *this;
}

Graduate::~Graduate()
{
	delete[] m_supervisor;
	m_supervisor = nullptr;
	delete[] m_thesisTitle;
	m_thesisTitle = nullptr;
}

void Graduate::display()
{
	// Calling the display function from the base class.
	Student::display();

	if (m_thesisTitle != nullptr && m_supervisor != nullptr)
	{
		cout << "Thesis Title: " << m_thesisTitle << endl;
		cout << "Supervisor: " << m_supervisor << endl;
	}

	cout << "---------------------------------------------" << endl;
}
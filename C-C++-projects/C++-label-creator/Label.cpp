#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <iomanip>
#include "Label.h"

using namespace std;

Label::Label()
{
	// Creating empty label.
	m_content = nullptr;
	// Assigning default frame.
	strcpy(m_frame, defaultFrame);
}

Label::Label(const char* frameArg)
{
	// Creating empty label.
	m_content = nullptr;

	if (frameArg != nullptr && strlen(frameArg))
	{
		// Setting frameArg as the frame.
		strcpy(m_frame, frameArg);
	}
	else
	{
		// Assigning the default frame (nullptr case).
		strcpy(m_frame, defaultFrame);
	}
}

Label::Label(const char* frameArg, const char* content)
{
	// Setting frameArg as the frame.
	strcpy(m_frame, frameArg);

	if (content != nullptr && strlen(content) < 71)
	{
		// Dynamically assigning content to the label.
		text(content);
	}
}

Label::~Label()
{
	delete[] m_content;
	m_content = nullptr;
}

std::istream& Label::readLabel()
{
	char content[71];

	// Input limited to 70 chars + null byte.
	cin.get(content, 71);
	// Cleaning buffer for each input as it was did in main().
	cin.ignore(10000, '\n');

	// Dynamically storing the content within the label up to 70 chars.
	text(content);

	return cin;
}

std::ostream& Label::printLabel() const
{
	if (m_content != nullptr)
	{
		// Storing the label size.
		int lenTotal = strlen(m_content) + 1;

		// TOP FRAME (#1)
		// Left up corner char.
		cout << m_frame[0];
		// Filling char.
		cout.fill(m_frame[1]);
		// Word size + 2 spaces + 1 null byte.
		cout.width(lenTotal + 2);
		// Right up corner char.
		cout << m_frame[2] << endl;

		// BLANK LINE (#2)
		// Left side char.
		cout << m_frame[7];
		// Filling (nothing).
		cout.fill(' ');
		// Word size + 2 spaces + 1 null byte.
		cout.width(lenTotal + 2);
		// Right side char.
		cout << m_frame[3] << endl;

		// LABEL LINE (#3)
		// Left side char.
		cout << m_frame[7];
		// Word size + 1 null byte (accomodating the label).
		cout.width(lenTotal);
		// Displaying the label + Right filling char.
		cout << m_content << ' ' << m_frame[3] << endl;

		// BLANK LINE (#4)
		// Left side char.
		cout << m_frame[7];
		// Filling (nothing).
		cout.fill(' ');
		// Word size + 2 spaces + 1 null byte.
		cout.width(lenTotal + 2);
		// Right side char.
		cout << m_frame[3] << endl;

		// BOTTOM FRAME (#5)
		// Left bottom corner char.
		cout << m_frame[6];
		// Filling char.
		cout.fill(m_frame[5]);
		// Word size + 2 spaces + 1 null byte.
		cout.width(lenTotal + 2);
		// Right bottom corner char.
		cout << m_frame[4];
	}

	return cout;
}

Label& Label::text(const char* content)
{
	// Clearing memory space.
	delete[] m_content;
	m_content = nullptr;
	// dynamically assigning the content to the label.
	m_content = new char[70 + 1];
	strcpy(m_content, content);
	// Returning current object.
	return *this;
}
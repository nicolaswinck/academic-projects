#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <string>
#include "LabelShape.h"

using namespace std;

const char* LblShape::label() const
{
	return m_label;
}

LblShape::LblShape()
{
	if (m_label != nullptr)
	{
		m_label = nullptr;
	}
}

LblShape::LblShape(const char* label)
{
	// Deallocating memory.
	delete[] m_label;
	m_label = nullptr;

	if (label != nullptr && label)
	{
		// Dynamically allocating memory for the label.
		m_label = new char[strlen(label) + 1];
		strcpy(m_label, label);
	}
}

LblShape::~LblShape()
{
	if (m_label)
	{
		delete[] m_label;
		m_label = nullptr;
	}
}

void LblShape::getSpecs(std::istream& istr)
{
	// Setting a string with a safe size (macro) compared to the frame.
	char label[LABEL_SIZE + 1];
	// Deallocating memory.
	delete[] m_label;
	m_label = nullptr;

	istr.get(label, LABEL_SIZE + 1, ',');
	istr.ignore();
	// Dynamically allocating memory for the label.
	m_label = new char[strlen(label) + 1];
	strcpy(m_label, label);
}
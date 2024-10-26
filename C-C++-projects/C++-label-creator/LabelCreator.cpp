#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <iomanip>
#include "LabelCreator.h"

using namespace std;

LabelMaker::LabelMaker()
{
	m_listOfLabels = { 0 };
	m_limitLabels = 0;
}

LabelMaker::LabelMaker(int noOfLabels)
{
	// Validating a positive value from client code.
	if (noOfLabels > 0)
	{
		// Assigning number of labels (dynamically).
		m_limitLabels = noOfLabels;
		m_listOfLabels = new Label[noOfLabels];
	}
	else
	{
		noOfLabels = 0;
	}
}

void LabelMaker::readLabels()
{
	// Validating for positive limit labels.
	if (m_limitLabels > 0)
	{
		// Printing out the user prompt.
		cout << "Enter " << m_limitLabels << " labels:" << endl;

		// Iterating the array.
		for (int i = 0; i < m_limitLabels; i++)
		{
			// Calling the input function.
			cout << "Enter label number " << i + 1 << endl << "> ";
			m_listOfLabels[i].readLabel();
		}
	}
}

void LabelMaker::printLabels()
{
	// Iterating the array to print each label.
	for (int i = 0; i < m_limitLabels; i++)
	{
		m_listOfLabels[i].printLabel();
		// Adding newline betwen labels.
		cout << endl;
	}
}

LabelMaker::~LabelMaker()
{
	delete[] m_listOfLabels;
	m_listOfLabels = nullptr;
}
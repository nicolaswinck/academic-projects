#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <string.h>
#include <iostream>
#include "Menu.h"
#include "Utils.h"

using namespace std;

Menu::Menu(const char* content)
{
	// Using unsigned int for comparing.
	unsigned int i;
	m_numOptions = 0;
	// Considering a content entered.
	if (content)
	{
		// Counting the number of items by the separator (<TAB>).
		for (i = 0; i < strlen(content); i++)
		{
			if (content[i] == '\t')
			{
				m_numOptions++;
			}
		}
	}
	// No content entered.
	// Validating.
	if (content == nullptr || m_numOptions > 15 || m_numOptions == 0)
	{
		m_content = nullptr;
	}
	else
	{
		// Assigning the attribute with content entered.
		ut.alocpy(m_content, content);
	}
}

Menu::~Menu()
{
	delete[] m_content;
}

unsigned int Menu::run()
{
	char* temp;
	char* item;
	unsigned int i;
	int itemCount{};
	unsigned int input{};
	unsigned int validValue = 0;
	int validLen = 0;

	// Making a copy in a temporary string.
	ut.alocpy(temp, m_content);
	// Checking for valid menu.
	if (m_content != nullptr && m_numOptions < 16)
	{
		// Getting the length without the separators.
		// (Avoiding only \t strings.)
		for (i = 0; i < strlen(m_content); i++)
		{
			if (m_content[i] != '\t')
			{
				validLen++;
			}
		}

		if (validLen)
		{
			// Assigning number of items (starting from 1).
			itemCount = 1;

			/* Using the standard tokenize function into the copied string.
			Grabbing the items separated by <TAB>.
			Professor, I've made a lot of research to get to this. Before
			knowing this resource, I had nested loops to print each character
			at a time, but it was becoming hard to pass the information to
			the other class to print it. However, if you'd like to see that,
			I have it in my computer, in a text file.*/
			item = strtok(const_cast<char*>(temp), "\t");
			// Checking the tokens.
			while (item != nullptr)
			{
				// Printing the number of the item + the name of the task.
				std::cout << itemCount << "- " << item << std::endl;
				// Tokenizing again.
				item = strtok(nullptr, "\t");
				// Incrementing the item number.
				itemCount++;
			}
			// Printing the standard Exit option.
			std::cout << "---------------------------------" << endl;
			std::cout << "0- Exit" << endl;
			std::cout << "> ";
			// Getting the input and validating the number.
			// The validation with the errors are in the getInt overloads.
			input = ut.getInt(0, m_numOptions + 1);
			// Assign valid value.
			validValue = input;
		}
	}
	else
	{
		std::cout << "Invalid Menu!" << endl;
		// Assigning zero for invalid menu.
		validValue = 0;
	}
	// Deallocating memory for the temporary string.
	delete[] temp;

	return validValue;
}
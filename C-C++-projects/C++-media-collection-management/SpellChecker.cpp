#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "SpellChecker.h"

using namespace std;

SpellChecker::SpellChecker(const char* filename)
{
	std::ifstream file(filename);

	// File missing (not open).
	if (!file.is_open())
	{
		throw "Bad file name!";
	}
	else
	{
		string line;
		size_t idx = 0u;

		// Lambda function to optimize the process (save lines of code).
		// This cleans the lines and properly tokenizes the words.
		auto clean = [&](size_t i, string& str, string arr[])
			{
				// Assigning character to be found (space).
				char ch = ' ';

				// Erasing spaces between the two words.
				str.erase(0, str.find_first_not_of(ch));
				idx = str.find(ch);

				// Tokenizing.
				if (idx > 0)
				{
					arr[i] = str.substr(0, idx);
					str.erase(0, idx);
				}
				else
				{
					arr[i] = str;
				}
			};
		// Applying the lambda in the two arrays.
		for (size_t i = 0; i < SIZE && getline(file, line); i++)
		{
			clean(i, line, m_badWords);
			clean(i, line, m_goodWords);
		}
	}
}

void SpellChecker::operator()(std::string& text)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		// Using npos to avoid stopping in the first "bad word".
		while (text.find(m_badWords[i]) != string::npos)
		{
			// Replacing and updating.
			text.replace(text.find(m_badWords[i]), m_badWords[i].size(), m_goodWords[i]);
			m_replacemCount[i]++;
		}
	}
}

void SpellChecker::showStatistics(std::ostream& out) const
{
	out << "Spellchecker Statistics" << endl;

	for (size_t i = 0u; i < SIZE; i++)
	{
		out << setw(15) << right << m_badWords[i] << ": " << m_replacemCount[i] << " replacements" << endl;
	}
}
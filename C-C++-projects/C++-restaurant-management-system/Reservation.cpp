#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include <string>
#include "Reservation.h"

using namespace std;

Reservation::Reservation()
{
	m_id = "";
	m_name = "";
	m_email = "";
	m_numOfPeople = 0;
	m_day = 0;
	m_hour = 0;
}

Reservation::Reservation(const std::string& res) : Reservation()
{
	// Temp string to hold data.
	string tempStr = res;

	// Defining first separator (colon).
	size_t sep1 = tempStr.find(':');
	// Getting ID and updating main str.
	m_id = trim(tempStr.substr(0, sep1));
	tempStr.erase(0, sep1 + 1);

	// Defining second separator (comma).
	size_t sep2 = tempStr.find(',');
	// Getting name and updating main str.
	m_name = trim(tempStr.substr(0, sep2));
	tempStr.erase(0, sep2 + 1);

	sep2 = tempStr.find(',');
	// Getting email and updating main str.
	m_email = trim(tempStr.substr(0, sep2));
	tempStr.erase(0, sep2 + 1);

	sep2 = tempStr.find(',');
	// Getting size and updating main str.
	m_numOfPeople = stoi(trim(tempStr.substr(0, sep2)));
	tempStr.erase(0, sep2 + 1);

	sep2 = tempStr.find(',');
	// Getting day and updating main str.
	m_day = stoi(trim(tempStr.substr(0, sep2)));
	tempStr.erase(0, sep2 + 1);

	sep2 = tempStr.find(',');
	// Getting time and updating main str.
	m_hour = stoi(trim(tempStr.substr(0, sep2)));
	tempStr.erase(0, sep2 + 1);
}

void Reservation::update(int day, int time)
{
	m_day = day;
	m_hour = time;
}

std::string Reservation::trim(std::string str)
{
	// Defining the character to be trimmed.
	char space = ' ';
	// Getting the first and the last non-whitespace characters on string.
	size_t start = str.find_first_not_of(space);
	size_t end = str.find_last_not_of(space);

	// Returning the string without the spaces at the edges.
	return str.substr(start, (end - start) + 1);
}

std::ostream& operator<<(std::ostream& os, const Reservation& res)
{
	// Temp strings for displaying meal and number of people.
	string mealType = "";
	string partySize = "";

	// Picking the meal type according to time (as per documentation).
	if (res.m_hour > 5 && res.m_hour < 10)
	{
		mealType = "Breakfast";
	}
	else if (res.m_hour > 10 && res.m_hour < 16)
	{
		mealType = "Lunch";
	}
	else if (res.m_hour > 16 && res.m_hour < 22)
	{
		mealType = "Dinner";
	}
	else
	{
		mealType = "Drinks";
	}

	// Picking the right word for the party size.
	// Obs.: I was practicing ternary operators here.
	res.m_numOfPeople > 1 ? partySize = " people." : partySize = " person.";

	// Formatting according to the sample output.
	os << "Reservation ";
	os << setw(10) << right << res.m_id << ": ";
	os << setw(20) << right << res.m_name << "  ";
	os << setw(20) << left << '<' + res.m_email + '>' << "    ";
	os << mealType + " on day " << res.m_day;
	os << " @ " << res.m_hour << ":00 for " << res.m_numOfPeople << partySize << endl;

	return os;
}
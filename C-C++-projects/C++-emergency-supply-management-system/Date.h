#ifndef DATE_H
#define DATE_H

#include <iostream>
#include "Status.h"

const int maxYear = 2030;

class Date
{
	int m_year;
	int m_month;
	int m_day;
	Status m_state;
	bool m_formatted;

public:
	bool validate();
	int uniqueDateValue(int year, int mon, int day);
	Date(int year = 0, int month = 0, int day = 0);
	bool operator==(const Date& rightDate) const;
	bool operator!=(const Date& rightDate) const;
	bool operator<(const Date& rightDate) const;
	bool operator>(const Date& rightDate) const;
	bool operator<=(const Date& rightDate) const;
	bool operator>=(const Date& rightDate) const;
	const Status& state() const;
	Date& formatted(bool format);
	operator bool() const;
	std::ostream& write(std::ostream& ostr = std::cout) const;
	std::istream& read(std::istream& istr = std::cin);
};

std::ostream& operator<<(std::ostream& ostr, const Date& date);
std::istream& operator>>(std::istream& istr, Date& date);

#endif // !DATE_H
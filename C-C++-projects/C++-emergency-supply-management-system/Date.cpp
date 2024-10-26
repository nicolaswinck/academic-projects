#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>
#include "Date.h"
#include "Status.h"
#include "Utils.h"

using namespace std;

// Constant value for current year.
const int currentYear = 2023;

Date::Date(int year, int month, int day)
{
    // Checking for three arguments.
    if (year && month && day)
    {
        // Assigning.
        m_year = year;
        m_month = month;
        m_day = day;

        validate();
    }
    else
    {
        // Getting system date.
        ut.getSystemDate(&m_year, &m_month, &m_day);
    }
    // Initializing m_state and m_formatted.
    m_state = Status();
    m_formatted = true;
}

bool Date::validate()
{
    // Set to true, so, whenever finds false, gets out of validation.
    bool result = true;
    // Validation for year, month and day.
    if (m_year < currentYear || m_year > maxYear)
    {
        m_state = "Invalid year in date";
        m_state = 1;

        result = false;
    }

    else if (m_month < 1 || m_month > 12)
    {
        m_state = "Invalid month in date";
        m_state = 2;

        result = false;
    }

    else if (m_day < 1 || m_day > ut.daysOfMon(m_month, m_year))
    {
        m_state = "Invalid day in date";
        m_state = 3;

        result = false;
    }
    // Clearing for true state.
    if (result)
    {
        m_state.clear();
    }

    return result;
}

int Date::uniqueDateValue(int year, int mon, int day)
{
    // Calculating the unique value (given by documentation).
    return year * 372 + mon * 31 + day;
}

bool Date::operator==(const Date& rightDate) const
{
    // Temporary objects to assign left values and compare with right values.
    Date temp;

    return temp.uniqueDateValue(m_year, m_month, m_day) ==
        temp.uniqueDateValue(rightDate.m_year, rightDate.m_month, rightDate.m_day);
}

bool Date::operator!=(const Date& rightDate) const
{
    Date temp;

    return temp.uniqueDateValue(m_year, m_month, m_day) !=
        temp.uniqueDateValue(rightDate.m_year, rightDate.m_month, rightDate.m_day);
}

bool Date::operator<(const Date& rightDate) const
{
    Date temp;

    return temp.uniqueDateValue(m_year, m_month, m_day) <
        temp.uniqueDateValue(rightDate.m_year, rightDate.m_month, rightDate.m_day);
}

bool Date::operator>(const Date& rightDate) const
{
    Date temp;

    return temp.uniqueDateValue(m_year, m_month, m_day) >
        temp.uniqueDateValue(rightDate.m_year, rightDate.m_month, rightDate.m_day);
}

bool Date::operator<=(const Date& rightDate) const
{
    Date temp;

    return temp.uniqueDateValue(m_year, m_month, m_day) <=
        temp.uniqueDateValue(rightDate.m_year, rightDate.m_month, rightDate.m_day);
}

bool Date::operator>=(const Date& rightDate) const
{
    Date temp;

    return temp.uniqueDateValue(m_year, m_month, m_day) >=
        temp.uniqueDateValue(rightDate.m_year, rightDate.m_month, rightDate.m_day);
}

const Status& Date::state() const
{
    return m_state;
}

Date& Date::formatted(bool format)
{
    m_formatted = format;

    return *this;
}

Date::operator bool() const
{
    return bool(m_state);
}

std::ostream& Date::write(std::ostream& ostr) const
{
    if (m_formatted)
    {
        // Formatting date output.
        ostr << m_year << "/";
        // Adding padding zeros with a condition.
        if (m_month < 10)
        {
            ostr << "0";
        }

        ostr << m_month << "/";

        if (m_day < 10)
        {
            ostr << "0";
        }

        ostr << m_day;
    }
    else
    {
        // Unformatted date output.
        ostr << m_year % 100;

        if (m_month < 10)
        {
            ostr << "0";
        }

        ostr << m_month;

        if (m_day < 10)
        {
            ostr << "0";
        }

        ostr << m_day;
    }

    return ostr;
}

std::istream& Date::read(std::istream& istr)
{
    int value;
    // Getting input value.
    istr >> value;
    // Fail case for non-integer inputs.
    if (istr.fail())
    {
        m_state = "Invalid date value";
        istr.setstate(std::ios::failbit);
    }
    // Case for four-digit inputs.
    else if (value > 999 && value < 10000)
    {
        // Setting current year as default.
        m_year = currentYear;
        // Isolating digits with calculation.
        m_month = value / 100;
        m_day = value % 100;

        if (!validate())
        {
            istr.setstate(std::ios::badbit);
        }
    }
    // Case for six-digit inputs.
    else if (value > 99999 && value < 1000000)
    {
        // Adding 2000 to match the YYYY format.
        m_year = (value / 10000) + 2000;
        m_month = (value % 10000) / 100;
        m_day = value % 100;

        if (!validate())
        {
            istr.setstate(std::ios::badbit);
        }
    }
    // Case for one or two digits.
    else if (value < 100)
    {
        // Setting current year as default.
        m_year = currentYear;
        // Assuming no month.
        m_month = 0;
        // Assuming the input as the day value.
        m_day = value;

        if (!validate())
        {
            istr.setstate(std::ios::badbit);
        }
    }
    // Ignoring characters until newline (flushing buffer).
    istr.ignore(1000, '\n');

    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const Date& date)
{
    return date.write(ostr);
}

std::istream& operator>>(std::istream& istr, Date& date)
{
    return date.read(istr);
}
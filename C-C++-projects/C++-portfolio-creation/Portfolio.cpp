#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include "Portfolio.h"

using namespace std;


Portfolio::Portfolio() {
    emptyPortfolio();
}

void Portfolio::emptyPortfolio()
{
    m_value = 0;
    m_stock[0] = 0;
    m_type = 'E';
}

Portfolio::Portfolio(double value, const char* stock, char type) {
    emptyPortfolio();
    if (value >= 0 && (type == 'V' || type == 'G' || type == 'I')) {
        m_value = value;
        m_type = type;
        strcpy(m_stock, stock);
    }
}

void Portfolio::dispPortfolio() const {
    cout << " ";
    cout.width(10);
    cout << (const char*)(*this);
    cout << " | ";
    cout << "Value: ";
    cout.width(10);
    cout << double(*this);
    cout << " | ";
    cout << " Type: ";
    cout << char(*this);
}

std::ostream& Portfolio::display() const {

    if (~*this) {
        cout << " Portfolio  |  Bad-NG |";
        dispPortfolio();
    }
    else if (*this) {
        cout << " Portfolio  |  Active |";
        dispPortfolio();

    }
    else {
        cout << " Portfolio  |  EMPTY  |";
        dispPortfolio();
    }
    return cout;
}

Portfolio::operator double() const
{
    return m_value;
}

Portfolio::operator const char* () const
{
    return m_stock;
}

Portfolio::operator char() const
{
    return m_type;
}

Portfolio::operator bool() const
{
    bool result = false;
    // Checking the type of investiment.
    if (m_type == 'G' || m_type == 'V' || m_type == 'I')
    {
        result = true;
    }

    return result;
}

Portfolio& Portfolio::operator+=(double value)
{
    // Validating true object and positive double.
    if (*this && value > 0.0)
    {
        // Accumulating a double value to this value.
        this->m_value += value;
    }

    return *this;
}

Portfolio& Portfolio::operator-=(double value)
{
    // Validating true object and positive double.
    if (*this && value > 0.0)
    {
        // Subtracting a double value of this value.
        this->m_value -= value;
    }

    return *this;
}

bool Portfolio::operator~() const
{
    // Validating for negative value.
    return m_value < 0;
}

Portfolio& Portfolio::operator<<(Portfolio& rightPortfolio)
{
    // Checking for self-assignment and true objects (left and right).
    if (this != &rightPortfolio && *this && rightPortfolio)
    {
        // Accumulating both values from both objects (right to left).
        this->m_value += rightPortfolio.m_value;
        // Setting the object to empty values.
        rightPortfolio.emptyPortfolio();
    }

    return *this;
}

Portfolio& Portfolio::operator>>(Portfolio& rightPortfolio)
{
    if (this != &rightPortfolio && this && rightPortfolio)
    {
        // Accumulating both values from both objects (left to right).
        rightPortfolio.m_value += this->m_value;
        this->emptyPortfolio();
    }

    return *this;
}

double operator+(const Portfolio& leftPortfolio, const Portfolio& rightPortfolio)
{
    double value = 0.0;
    // Validating for true objects.
    if (leftPortfolio && rightPortfolio)
    {
        // Adding both values (left and right).
        value = leftPortfolio.m_value + rightPortfolio.m_value;
    }
    // Returning the whole sum.
    return value;
}

double operator+=(double& leftOperand, const Portfolio& rightPortfolio)
{
    // Accumulating left and right values to a new double value.
    double value = leftOperand += rightPortfolio.m_value;
    // Returning new value.
    return value;
}
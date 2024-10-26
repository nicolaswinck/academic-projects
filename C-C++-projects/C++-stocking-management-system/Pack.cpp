#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string.h>
#include "Pack.h"

using namespace std;

Pack::Pack(const char* content, int size, int unitSize, int numUnits) :
    // Initializing the Container class to the correct specifications.
    Container(content, (size* unitSize), (numUnits* unitSize))
{
    if (unitSize <= 0)
    {
        // Emptying for invalid unit size.
        setEmpty();
    }
    else
    {
        // Assigning a valid value.
        m_unitSize = unitSize;
    }
}

int Pack::operator+=(int rhNumUnits)
{
    // Variable which will hold the added value.
    int added;
    // Assigning it with the Container += operator.
    added = Container::operator+=(rhNumUnits * m_unitSize);
    // Returning the calculated amount.
    return added / m_unitSize;
}

int Pack::operator-=(int rhNumUnits)
{
    // Variable which will hold the reduced value.
    int reduced;
    // Assigning it with the Container -= operator.
    reduced = Container::operator-=(rhNumUnits * m_unitSize);
    // Returning the calculated amount.
    return reduced / m_unitSize;
}

int Pack::unit() const
{
    return m_unitSize;
}

int Pack::noOfUnits() const
{
    return Container::volume() / m_unitSize;
}

int Pack::size() const
{
    return Container::capacity() / m_unitSize;
}

void Pack::clear(int packSize, int unitSize, const char* content)
{
    // Clearing container with packs.
    if (unitSize > 0)
    {
        Container::clear(packSize * unitSize, content);
        m_unitSize = unitSize;
    }
}

std::ostream& Pack::print(std::ostream& ostr) const
{
    Container::print(ostr);
    // Displaying status for valid container with packs.
    if (*this)
    {
        ostr << ", " << noOfUnits() << " in a pack of " << size();
    }

    return ostr;
}

std::istream& Pack::read(std::istream& istr)
{
    bool inputOk = false;
    int value{};
    int added{};

    if (!*this)
    {
        // Invalid container input (newline).
        while (!inputOk)
        {
            std::cerr << "Broken Container, adding aborted! Press <ENTER> to continue....";
            char c = istr.get();

            if (c == '\n')
            {
                inputOk = true;
            }
        }
    }
    else
    {
        // Validating number of units.
        if (noOfUnits() < size())
        {
            // Printing the pack and getting value input.
            std::cout << "Add to ";
            print(std::cout) << endl;
            std::cout << "> ";
            istr >> value;
            // Validating the size.
            while (value < 1 || value > size() - noOfUnits())
            {
                // Fail and large value scenarios.
                if (istr.fail())
                {
                    std::cerr << "Invalid Integer, retry: ";
                }
                else
                {
                    std::cerr << "Value out of range [1<=val<=" << size() - noOfUnits() << "]: ";
                }

                istr >> value;

                istr.clear();
                istr.ignore(10000, '\n');
            }
            // Assigning the added amount.
            added = *this += value;
            // Printing the cans/bottles added.
            std::cout << "Added " << added << std::endl;
        }
        else
        {
            // Full pack warning (wait for user to input <newline>).
            std::cerr << "Pack is full!, press <ENTER> to continue...";
            char c = istr.get();

            if (c == '\n')
            {
                inputOk = true;
            }
        }
    }

    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const Pack& pk)
{
    return pk.print(ostr);
}

std::istream& operator>>(std::istream& istr, Pack& pk)
{
    return pk.read(istr);
}
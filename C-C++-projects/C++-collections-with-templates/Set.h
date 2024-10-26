#ifndef SET_H
#define SET_H

#include <iostream>
#include <cmath>
#include "Collection.h"

template <typename T>
class Set : public Collection<T, 100>
{

public:
    bool add(const T& item) override
    {
        // Flag for the presence of a duplicate (compared to the argument item).
        bool exists = false;
        // Checking for duplicates item-by-item.
        for (int i = 0; i < this->size() && !exists; i++)
        {
            if ((*this)[i] == item)
            {
                // Item found!
                exists = true;
            }
        }
        // Adding item if a duplicate does not exist.
        if (!exists)
        {
            Collection<T, 100>::add(item);
        }

        return !exists;
    }
};

// Specialization of the add() function for T = double.
template <>
class Set<double> : public Collection<double, 100>
{
public:
    bool add(const double& item) override
    {
        bool exists = false;

        for (int i = 0; i < this->size() && !exists; i++)
        {
            // Claculating absolute value of the difference.
            if (std::fabs((*this)[i] - item) <= 0.01)
            {
                // Item found!
                exists = true;
            }
        }

        if (!exists)
        {
            Collection<double, 100>::add(item);
        }

        return !exists;
    }
};

#endif
#ifndef COLLECTION_H
#define COLLECTION_H

#include <iostream>
#include "Pair.h"

template <typename T, int CAPACITY>
class Collection
{
	T m_collection[CAPACITY];
	int m_len;
	T m_dummy;

public:
	// Default constructor.
	Collection() : m_collection{}, m_len(0)
	{
		m_dummy = T{};
	}

	// Empty body virtual destructor.
	virtual ~Collection() {}

	int size() const
	{
		return m_len;
	}

	void display(std::ostream& ostr = std::cout) const
	{
		// Formatting output according to the sample.
		ostr << "----------------------" << std::endl;
		ostr << "| Collection Content |" << std::endl;
		ostr << "----------------------" << std::endl;
		// Printing each element of the collection.
		for (int i = 0; i < m_len; i++)
		{
			ostr << m_collection[i] << std::endl;
		}

		ostr << "----------------------" << std::endl;
	}

	virtual bool add(const T& item)
	{
		// Flag to yield the return value.
		bool result;
		// Collection is not full.
		if (m_len < CAPACITY)
		{
			// Assigning the argument item to the collection.
			m_collection[m_len] = item;
			// Updating the size of the array.
			m_len++;

			result = true;
		}
		// Collection is full.
		else
		{
			result = false;
		}

		return result;
	}

	T operator[](int idx) const
	{
		// Flag to yield the return value.
		T returnedObject;
		// Array is out of bounds (index not valid).
		if (idx < 0 || idx > m_len)
		{
			returnedObject = m_dummy;
		}
		// Array in bounds (valid index).
		else
		{
			returnedObject = m_collection[idx];
		}

		return returnedObject;
	}
};

// Specialization of the dummy object for T = Pair and CAPACITY = 100.
template <>
class Collection<Pair, 100>
{
	Pair m_collection[100];
	int m_len;
	Pair m_dummy;

public:
	Collection() : m_collection{}, m_len(0)
	{
		m_dummy = Pair("No Key", "No Value");
	}

	virtual ~Collection() {}

	int size() const
	{
		return m_len;
	}

	void display(std::ostream& ostr = std::cout) const
	{
		ostr << "----------------------" << std::endl;
		ostr << "| Collection Content |" << std::endl;
		ostr << "----------------------" << std::endl;

		for (int i = 0; i < m_len; i++)
		{
			ostr << m_collection[i] << std::endl;
		}

		ostr << "----------------------" << std::endl;
	}

	virtual bool add(const Pair& item)
	{
		bool result;

		if (m_len < 100)
		{
			m_collection[m_len] = item;
			m_len++;

			result = true;
		}
		else
		{
			result = false;
		}

		return result;
	}

	Pair operator[](int idx) const
	{
		Pair returnedObject;

		if (idx < 0 || idx > m_len)
		{
			returnedObject = m_dummy;
		}
		else
		{
			returnedObject = m_collection[idx];
		}

		return returnedObject;
	}
};
#endif
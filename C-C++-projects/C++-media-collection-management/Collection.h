#ifndef COLLECTION_H
#define COLLECTION_H

#include <string>
#include <iostream>
#include <stdexcept>

template <typename T>
class Collection
{
	// Initializing attributes and member functions (since there's no .cpp file).
	std::string m_name = {};
	T* m_items = nullptr;
	size_t m_size = 0u;
	void (*c_observer) (const Collection<T>&, const T&) = nullptr;

public:
	Collection(const std::string& name) : m_name(name) {}
	// Deleting copying operations (constructor + assignment operator).
	Collection(const Collection&) = delete;
	Collection& operator=(const Collection&) = delete;
	~Collection()
	{
		if (m_items)
		{
			delete[] m_items;
			m_items = nullptr;
		}
	}

	const std::string& name() const
	{
		return m_name;
	}

	size_t size() const
	{
		return m_size;
	}

	void setObserver(void (*observer)(const Collection<T>&, const T&))
	{
		c_observer = observer;
	}

	Collection<T>& operator+=(const T& item)
	{
		// Flag to identify repeated items.
		bool found = false;

		for (size_t i = 0u; i < m_size; i++)
		{
			// Comparing objects' elements (titles).
			if (m_items[i].title() == item.title())
			{
				found = true;
			}
		}
		// No matching title.
		if (!found)
		{
			// +1 to accomodate new item.
			T* tempItems = new T[m_size + 1];

			// Assigning new item.
			for (size_t i = 0; i < m_size; i++)
			{
				tempItems[i] = m_items[i];
			}

			tempItems[m_size] = item;

			// Deallocating.
			delete[] m_items;
			m_items = nullptr;

			m_items = tempItems;
			m_size++;

			if (c_observer)
			{
				c_observer(*this, item);
			}
		}

		return *this;
	}

	T& operator[](size_t idx) const
	{
		// Index is out of bounds.
		if (idx >= size())
		{
			throw std::out_of_range("Bad index [" + std::to_string(idx) +
				"]. Collection has [" + std::to_string(m_size) + "] items.");
		}
		else
		{
			return m_items[idx];
		}
	}

	T* operator[](const std::string& title) const
	{
		// Holding result as null.
		T* result = nullptr;

		for (size_t i = 0; i < m_size; i++)
		{
			// Title matches.
			if (m_items[i].title() == title)
			{
				result = &m_items[i];
			}
		}

		return result;
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& ostr, const Collection<T>& collection)
{
	for (size_t i = 0; i < collection.size(); i++)
	{
		ostr << collection[i];
	}

	return ostr;
}

#endif
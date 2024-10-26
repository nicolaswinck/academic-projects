#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <numeric>
#include "Bakery.h"

using namespace std;

Bakery::Bakery(std::string filename)
{
	// Opening file.
	ifstream file(filename);
	// Temp strings to hold data before passing to the struct.
	string line, typeStr, descStr, lifeStr, stockStr, priceStr;

	if (!file.is_open())
	{
		throw std::runtime_error("Invalid filename.");
	}

	// File is open (getting lines).
	while (getline(file, line))
	{
		// Custom lambda expression to tokenize each piece of data.
		// This avoids some unnecessary repetition.
		auto tokenize = [&](int size)
			{
				string target = trim(line.substr(0, size));
				line.erase(0, size);

				return target;
			};

		// Getting information to strings with suggested sizes.
		typeStr = tokenize(8);
		descStr = tokenize(20);
		lifeStr = tokenize(14);
		stockStr = tokenize(8);
		priceStr = tokenize(6);

		// Creating temp object to hold data.
		BakedGood b;

		// Converting/passing data to the struct.
		b.descr = descStr;
		b.life = stoi(lifeStr);
		b.price = stod(priceStr);
		b.stock = stoi(stockStr);

		// Switching between bread and pastry type.
		if (typeStr == "Bread")
		{
			b.type = BakedType::BREAD;
		}
		else if (typeStr == "Pastry")
		{
			b.type = BakedType::PASTERY;
		}

		// Inserting struct into BakedGoods collection.
		m_collection.push_back(b);
	}

	file.close();
}

void Bakery::showGoods(std::ostream& os) const
{
	// Printing out the collection using iterator (not a loop).
	for (auto& c : m_collection)
	{
		os << c << endl;
	}

	// (Part 2) Accumulating stock and price, then displaying it.
	int stockSum = accumulate(m_collection.begin(), m_collection.end(), 0, [](int sum, const BakedGood& b)
		{
			return sum + b.stock;
		});

	double totalPrice = accumulate(m_collection.begin(), m_collection.end(), 0.0, [](double sum, const BakedGood& b)
		{
			return sum + b.price;
		});

	os << "Total Stock: " << stockSum << endl;
	os << "Total Price: " << totalPrice << endl;
}

std::string Bakery::trim(std::string token)
{
	// Defining the character to be trimmed.
	char space = ' ';
	// Getting the first and the last non-whitespace characters on string.
	size_t start = token.find_first_not_of(space);
	size_t end = token.find_last_not_of(space);

	// Returning the string without the spaces at the edges.
	return token.substr(start, (end - start) + 1);
}

void Bakery::sortBakery(std::string field)
{
	// Switching between fields and sorting accordingly.
	if (field == "Description")
	{
		sort(m_collection.begin(), m_collection.end(), [](const BakedGood& b1, const BakedGood& b2)
			{
				return b1.descr < b2.descr;
			});
	}
	if (field == "Shelf")
	{
		sort(m_collection.begin(), m_collection.end(), [](const BakedGood& b1, const BakedGood& b2)
			{
				return b1.life < b2.life;
			});
	}
	if (field == "Stock")
	{
		sort(m_collection.begin(), m_collection.end(), [](const BakedGood& b1, const BakedGood& b2)
			{
				return b1.stock < b2.stock;
			});
	}
	if (field == "Price")
	{
		sort(m_collection.begin(), m_collection.end(), [](const BakedGood& b1, const BakedGood& b2)
			{
				return b1.price < b2.price;
			});
	}
}

std::vector<BakedGood> Bakery::combine(Bakery& b)
{
	// Creating vector to hold result (adjusting size to fit collections).
	vector<BakedGood> result(m_collection.size() + b.m_collection.size());

	// Sorting each collection by price using custom method.
	sortBakery("Price");
	b.sortBakery("Price");

	// Merging collections and sorting again (this part was provided by the professor).
	merge(m_collection.begin(), m_collection.end(), b.m_collection.begin(), b.m_collection.end(),
		result.begin(), [](const BakedGood& b1, const BakedGood& b2)
		{
			return b1.price < b2.price;
		});

	return result;
}

bool Bakery::inStock(std::string desc, BakedType bt) const
{
	// Counting data with condition (capture flag to get the parameters).
	bool result = count_if(m_collection.begin(), m_collection.end(), [&](const BakedGood& b)
		{
			// Matching type, description and positive value for stock.
			return b.type == bt && b.descr == desc && b.stock > 0;
		});

	return result;
}

std::list<BakedGood> Bakery::outOfStock(BakedType bt) const
{
	// Temp vector to hold the result.
	list<BakedGood> result;

	// Copying elements from the collection with condition.
	copy_if(m_collection.begin(), m_collection.end(), back_inserter(result), [&](const BakedGood& b)
		{
			// Matching type and empty stock.
			return b.type == bt && b.stock == 0;
		});

	// Sorting the result by price.
	result.sort([](const BakedGood& b1, const BakedGood& b2)
		{
			return b1.price < b2.price;
		});

	return result;
}

std::ostream& operator<<(std::ostream& out, const BakedGood& b)
{
	// Temp string to hold type info.
	string type;

	// Switching to get type info.
	if (b.type == BakedType::BREAD)
	{
		type = "Bread";
	}
	else
	{
		type = "Pastry";
	}

	// Formatting the line accordingly (with type already as a str).
	out << left << "* " << setw(10) << type;
	out << " * " << setw(20) << b.descr;
	out << " * " << setw(5) << b.life;
	out << " * " << setw(5) << b.stock;
	out << " * " << right << setw(8) << fixed << setprecision(2) << b.price << " * ";

	return out;
}
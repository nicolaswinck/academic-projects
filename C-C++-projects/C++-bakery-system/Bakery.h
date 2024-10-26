#ifndef BAKERY_H
#define BAKERY_H

#include <iostream>
#include <vector>
#include <list>

enum class BakedType
{
	BREAD, PASTERY
};

// Structure with initialized data members.
struct BakedGood
{
	BakedType type{};
	std::string descr{ "" };
	int life{ 0 };
	int stock{ 0 };
	double price{ 0.0 };
};

class Bakery
{
	std::vector<BakedGood> m_collection;

public:
	Bakery(std::string filename);
	void showGoods(std::ostream& os) const;
	// Custom trim function I made for previous workshops.
	std::string trim(std::string token);
	void sortBakery(std::string field);
	std::vector<BakedGood> combine(Bakery& b);
	bool inStock(std::string desc, BakedType bt) const;
	std::list<BakedGood> outOfStock(BakedType bt) const;
};

// Free helper: insertion operator.
std::ostream& operator<<(std::ostream& out, const BakedGood& b);

#endif
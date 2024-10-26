#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include <iostream>
#include "Station.h"

struct Item
{
	std::string s_itemName;
	size_t s_serialNumber{ 0 };
	bool s_isFilled{ false };

	Item(const std::string& src) : s_itemName(src) {};
};

class CustomerOrder
{
	std::string m_name;
	std::string m_product;
	size_t m_cntItem;
	Item** m_lstItem;

public:
	// Class variable.
	static size_t m_widthField;

	// Constructors (default and custom).
	CustomerOrder() = default;
	CustomerOrder(const std::string& line);
	// Copy operations (assignment deleted).
	CustomerOrder(CustomerOrder& rhOrd);
	CustomerOrder& operator=(const CustomerOrder& rhOrd) = delete;
	// Move operations.
	CustomerOrder(CustomerOrder&& rhOrd) noexcept;
	CustomerOrder& operator=(CustomerOrder&& rhOrd) noexcept;
	~CustomerOrder();

	bool isOrderFilled() const;
	bool isItemFilled(const std::string& itemName) const;
	void fillItem(Station& station, std::ostream& os);
	void display(std::ostream& os) const;
};

#endif
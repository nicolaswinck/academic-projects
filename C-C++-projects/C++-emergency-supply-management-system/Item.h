#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <fstream>
#include "iProduct.h"
#include "Status.h"

class Item : public iProduct
{
	double m_price;
	int m_qty;
	int m_qtyNeeded;
	char* m_description;
	bool m_linear;

protected:
	Status m_state;
	int m_sku;
	// Protected query method.
	bool linear() const;

public:
	Item();
	// Rule of three.
	Item(const Item& it);
	Item& operator=(const Item& it);
	~Item();
	// Virtual public query overrides.
	int qtyNeeded() const override;
	int qty() const override;
	operator double() const override;
	operator bool() const override;
	// Virtual public modifier overrides.
	int operator-=(int rhQty) override;
	int operator+=(int rhQty) override;
	void linear(bool linear) override;
	// Public modifier.
	void clear();
	// Virtual operators overrides.
	bool operator==(int rhSku) const override;
	bool operator==(const char* rhDesc) const override;
	// Virtual input/output method overrides.
	std::ofstream& save(std::ofstream& ofstr) const override;
	std::ifstream& load(std::ifstream& ifstr) override;
	std::ostream& display(std::ostream& ostr) const override;
	int readSku(std::istream& istr) override;
	std::istream& read(std::istream& istr) override;
};

#endif // !ITEM_H
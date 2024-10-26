#ifndef PERISHABLE_H
#define PERISHABLE_H

#include "Item.h"
#include "Date.h"

class Perishable : public Item
{
	Date m_expDate;
	char* m_instructions;

public:
	Perishable();
	Perishable(const Perishable& per);
	Perishable& operator=(const Perishable& per);
	~Perishable();
	const Date& expiry() const;
	virtual int readSku(std::istream& istr) override;
	virtual std::ofstream& save(std::ofstream& ofstr) const override;
	virtual std::ifstream& load(std::ifstream& ifstr) override;
	virtual std::ostream& display(std::ostream& ostr) const override;
	virtual std::istream& read(std::istream& istr) override;
};

#endif // !PERISHABLE_H
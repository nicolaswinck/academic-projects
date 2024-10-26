#ifndef IPRODUCT_H
#define IPRODUCT_H
#include <iostream>

class iProduct
{
public:
	// Functions copied from the documentation and converted
	// into pure virtual functions.
	virtual int readSku(std::istream& istr) = 0;
	virtual int operator-=(int rhQty) = 0;
	virtual int operator+=(int rhQty) = 0;
	virtual operator double()const = 0;
	virtual operator bool()const = 0;
	virtual int qtyNeeded()const = 0;
	virtual int qty()const = 0;
	virtual void linear(bool isLinear) = 0;
	virtual std::ofstream& save(std::ofstream& ofstr)const = 0;
	virtual std::ifstream& load(std::ifstream& ifstr) = 0;
	virtual std::ostream& display(std::ostream& ostr)const = 0;
	virtual std::istream& read(std::istream& istr) = 0;
	virtual bool operator==(int sku)const = 0;
	virtual bool operator==(const char* description)const = 0;
	// Destructor.
	virtual ~iProduct() = default;
};

// Insertion and extraction operator overloads.
std::ostream& operator<<(std::ostream& ostr, const iProduct& prod);
std::istream& operator>>(std::istream& istr, iProduct& prod);

#endif // !IPRODUCT_H
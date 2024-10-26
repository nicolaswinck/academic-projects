#ifndef CARSYSTEM_H
#define CARSYSTEM_H

class CarInventory
{
	// Private data members.
	char* m_type;
	char* m_brand;
	char* m_model;
	int m_year;
	int m_code;
	double m_price;

	// Private member function.
	void resetInfo();

public:
	CarInventory();
	~CarInventory();
	CarInventory(const char* type, const char* brand,
		const char* model);
	CarInventory(const char* type, const char* brand,
		const char* model, int year, int code, double price);
	CarInventory& setInfo(const char* type, const char* brand,
		const char* model, int year, int code, double price);
	void printInfo() const;
	bool isValid() const;
	bool isSimilarTo(const CarInventory& car) const;
};

// Global function.
int find_similar(CarInventory car[], const int num_cars);

#endif // !CARSYSTEM_H
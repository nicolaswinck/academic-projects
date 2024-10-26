#ifndef STATUS_H
#define STATUS_H

#include <iostream>

class Status
{
	char* m_status{};
	int m_code;

public:
	Status(const char* status = nullptr);
	Status& clear();
	Status(const Status& st);
	Status& operator=(const Status& st);
	Status& operator=(const char* status);
	Status& operator=(int code);
	~Status();
	operator int() const;
	operator const char* () const;
	operator bool() const;

	friend std::ostream& operator<<(std::ostream& ostr, const Status& status);
};

#endif // !STATUS_H
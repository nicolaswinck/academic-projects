#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

// Fixing the maximum keys/values for maintainability.
const int MAX = 20;

enum class Err_Status
{
	Err_Success,
	Err_NotFound,
	Err_OutOfMemory,
};

template<typename T>
class Database
{
	int m_entriesNum{ 0 };
	std::string m_keys[MAX];
	T m_values[MAX];
	std::string m_filename{ "" };
	static std::shared_ptr<Database> m_address;

	// Private constructor.
	Database(const std::string& filename)
	{
		// Printing the address of the instance + constructor prototype.
		std::cout << '[' << this << "] " << "Database(const std::string&)" << std::endl;

		// Opening file.
		std::ifstream file(filename);
		// Temp strings for extracting/editing data.
		std::string line, tempKey;

		// Assigning filename.
		m_filename = filename;

		// Assuming that the file exists and is correct (as per instructions).
		// File is open (getting lines).
		while (std::getline(file, line))
		{
			// Space character is the delimiter.
			size_t delimiter = line.find(' ');

			// Trimming, tokenizing and switching underscore.
			tempKey = trim(line.substr(0, delimiter));
			size_t underScore = tempKey.find('_');
			tempKey[underScore] = ' ';
			// Assigning key.
			m_keys[m_entriesNum] = tempKey;

			// Using sstream to assign the value (because of type T).
			std::istringstream iss(line.substr(delimiter + 1));
			// Assigning the value.
			iss >> m_values[m_entriesNum];
			// Decrypting value.
			encryptDecrypt(m_values[m_entriesNum]);

			++m_entriesNum;
		}

		file.close();
	}

	// Empty body function for specializing.
	void encryptDecrypt(T& value) {}

public:
	static std::shared_ptr<Database> getInstance(const std::string& filename)
	{
		// The class has not been instantiated.
		if (m_address == nullptr)
		{
			// Creating new instance of Database.
			m_address = std::shared_ptr<Database>(new Database(filename));
		}

		return m_address;
	}

	Err_Status GetValue(const std::string& key, T& value) const
	{
		// Temp Err_Status to hold the result (assuming not found).
		Err_Status result = Err_Status::Err_NotFound;

		for (size_t i = 0u; i < m_keys->size(); i++)
		{
			// The key is found (match).
			if (m_keys[i] == key)
			{
				// Storing the value and returning success.
				value = m_values[i];
				result = Err_Status::Err_Success;
			}
		}

		return result;
	}

	Err_Status SetValue(const std::string& key, const T& value)
	{
		// Temp Err_Status to hold the result (one exit).
		Err_Status result = Err_Status();

		// There is space in the database (max has not been reached).
		if (m_entriesNum < MAX)
		{
			// Adding pair.
			m_keys[m_entriesNum] = key;
			m_values[m_entriesNum] = value;
			// Incrementing space.
			++m_entriesNum;

			result = Err_Status::Err_Success;
		}
		// There is no space left.
		else
		{
			result = Err_Status::Err_OutOfMemory;
		}

		return result;
	}

	std::string trim(std::string token)
	{
		// Defining the character to be trimmed.
		char space = ' ';
		// Getting the first and the last non-whitespace characters on string.
		size_t start = token.find_first_not_of(space);
		size_t end = token.find_last_not_of(space);

		// Returning the string without the spaces at the edges.
		return token.substr(start, (end - start) + 1);
	}

	~Database()
	{
		// Printing the address of the current object + prototype.
		std::cout << '[' << this << "] " << "~Database()" << std::endl;

		// Creating backup file (suffix appended to filename).
		std::string filename = m_filename + ".bkp.txt";
		std::ofstream backupFile(filename);

		if (backupFile.is_open())
		{
			// Iterating over the database and copying the lines.
			for (int i = 0u; i < m_entriesNum; i++)
			{
				// Encrypting values for backup (part 2).
				encryptDecrypt(m_values[i]);

				backupFile << std::left << std::setw(25) << m_keys[i];
				backupFile << " -> " << m_values[i] << std::endl;
			}
		}

		backupFile.close();
	}
};

// String type specialization.
template<>
void Database<std::string>::encryptDecrypt(std::string& value)
{
	// Line provided by documentation.
	const char secret[]{ "secret encryption key" };

	for (char& C : value)
	{
		for (const char& K : secret)
		{
			C = C ^ K;
		}
	}
}

// Long long type specialization.
template<>
void Database<long long>::encryptDecrypt(long long& value)
{
	// Line provided by documentation.
	const char secret[]{ "super secret encryption key" };
	// Accessing each byte by a pointer.
	// Casting as recommended by the documentation.
	char* byte = reinterpret_cast<char*>(&value);

	for (size_t i = 0; i < sizeof(long long); i++)
	{
		for (const char& K : secret)
		{
			byte[i] = byte[i] ^ K;
		}
	}
}

template<typename T>
std::shared_ptr<Database<T>> Database<T>::m_address = nullptr;

#endif 
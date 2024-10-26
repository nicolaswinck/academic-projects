#ifndef Portfolio_H_
#define Portfolio_H_

#include <ostream>


class Portfolio {
    double m_value = 0;
    char m_stock[16];
    char m_type;

public:
    Portfolio();
    void emptyPortfolio();
    Portfolio(double value, const char* stock, char type);
    void dispPortfolio() const;
    std::ostream& display() const;
    // Type conversion operators.
    operator double() const;
    operator const char* () const;
    operator char() const;
    operator bool() const;
    // Binary operators.
    Portfolio& operator+=(double value);
    Portfolio& operator-=(double value);
    // Unary operator.
    bool operator~() const;
    // Binary operators.
    Portfolio& operator<<(Portfolio& rightPortfolio);
    Portfolio& operator>>(Portfolio& rightPortfolio);
    // Binary helper operators.
    friend double operator+(const Portfolio& leftPortfolio, const Portfolio& rightPortfolio);
    friend double operator+=(double& leftOperand, const Portfolio& rightPortfolio);
};

#endif // !PORTFOLIO_H_
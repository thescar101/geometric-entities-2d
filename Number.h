#ifndef NUMBER_H
#define NUMBER_H
#include <string>

class Number
{
public:
    // Constructors/Deconstructor
    Number(); // Default Constructor: Initialized to 0
    Number(std::string s); // String Constructor "xxx.xxx"
    Number(const Number& n); // Copy Constructor
    Number(Number&& n); // Move Constructor
    ~Number();

    // Arithmetic Operators
    Number operator+(const Number& n) const;
    Number operator-(const Number& n) const;
    Number operator*(const Number& n) const;
    Number operator/(const Number& n) const;

    // Comparison Operators
    bool operator<(const Number& n) const;
    bool operator>(const Number& n) const;
    bool operator==(const Number& n) const;
    bool operator!=(const Number& n) const;
    bool operator>=(const Number& n) const;
    bool operator<=(const Number& n) const;

    // Assignment Operators
	Number& operator=(std::string s);
    Number& operator=(Number&& n);
    Number& operator=(const Number& n);
    Number& operator+=(const Number& n);
    Number& operator-=(const Number& n);
    Number& operator*=(const Number& n);
    Number& operator/=(const Number& n);

    // Input Operator
    friend std::istream& operator>>(std::istream& is, Number& n);

    // Output Operator
    friend std::ostream& operator<<(std::ostream& os, const Number& n);

    friend Number sqrt(const Number& n);

    private:
        struct Impl;
        Impl* pimpl;

};



#endif // NUMBER_H
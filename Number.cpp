#include <gmpxx.h>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <regex>
#include "Number.h"


void input_string(mpz_class& a, mpz_class& b, std::string c);
std::string output_string(mpq_class value);

struct Number::Impl 
{
    mpq_class value;
};

// Constructors/Deconstructor
Number::Number() : pimpl( new Impl()) 
{
}
Number::Number(std::string s) : pimpl( new Impl())
{
    input_string(this->pimpl->value.get_num(), this->pimpl->value.get_den(), s);
    this->pimpl->value.canonicalize();
}
Number::Number(const Number& n) : pimpl( new Impl())
{
    this->pimpl->value = n.pimpl->value;
}
Number::Number(Number&& n)
{
    this->pimpl = n.pimpl;
    n.pimpl = nullptr;
}
Number::~Number()
{
    delete pimpl;
}

// Arithmetic Operators
Number Number::operator+(const Number& n) const
{
    Number sum;
    sum.pimpl->value = this->pimpl->value + n.pimpl->value;
    return sum;
}
Number Number::operator-(const Number& n) const
{
    Number diff;
    diff.pimpl->value = this->pimpl->value - n.pimpl->value;
    return diff;
}
Number Number::operator*(const Number& n) const
{
    Number product;
    product.pimpl->value = this->pimpl->value * n.pimpl->value;
    return product;
}
Number Number::operator/(const Number& n) const
{
    Number quotient;  // Currently zero, 0/1
    if (quotient == n) // Is the denominator 0?
        throw std::runtime_error("Error: Division by Zero\n");
    quotient.pimpl->value = this->pimpl->value / n.pimpl->value;
    return quotient;
}

// Comparison Operators
bool Number::operator<(const Number& n) const
{
    if (cmp(this->pimpl->value, n.pimpl->value) < 0) // negative if less than
        return true;
    else
        return false;
}
bool Number::operator>(const Number& n) const
{
    if (cmp(this->pimpl->value, n.pimpl->value) > 0) // positive if greater than
        return true;
    else
        return false;
}
bool Number::operator==(const Number& n) const
{
    if (cmp(this->pimpl->value, n.pimpl->value) == 0) // 0 if equal to
        return true;
    else
        return false;
}
bool Number::operator!=(const Number& n) const
{
    return !(*this == n);
}
bool Number::operator>=(const Number& n) const
{
    return !(*this < n);
}
bool Number::operator<=(const Number& n) const
{
    return !(*this > n);
}

// Assignment Operators
Number& Number::operator=(std::string s)
{
    input_string(this->pimpl->value.get_num(), this->pimpl->value.get_den(), s);
    this->pimpl->value.canonicalize();
	return *this;
}
Number& Number::operator=(Number&& n)
{
    this->pimpl = n.pimpl;
    n.pimpl = nullptr;
    return *this;
}
Number& Number::operator=(const Number& n)
{
    this->pimpl->value = n.pimpl->value;
	return *this;
}
Number& Number::operator+=(const Number& n)
{
    *this = *this + n;
    return *this;
}
Number& Number::operator-=(const Number& n)
{
    *this = *this - n;
    return *this;
}
Number& Number::operator*=(const Number& n)
{
    *this = *this * n;
    return *this;
}
Number& Number::operator/=(const Number& n)
{
    *this = *this / n;
    return *this;
}

// Input Operator
std::istream& operator>>(std::istream& is, Number& n)
{
    std::string input;
    is >> input;
    n = input;
    return is;
}

// Output Operator
std::ostream& operator<<(std::ostream& os, const Number& n)
{
    if (n.pimpl != nullptr)
        os << output_string(n.pimpl->value);
    return os;
}

void input_string(mpz_class& a, mpz_class& b, std::string c)
{
    std::regex numberFormat("^[-]?[0-9]*[.]?[0-9]*$"); // Regular Expression for a number
    std::smatch isFormated;

    if (!regex_search(c, isFormated, numberFormat))
        throw std::runtime_error("Error: Invalid Number Input Format\n");
    
    int powTen;
    while(c.front() == '0')
    {
        c.erase(c.begin());        // Pop off zeros in the front
    }
    int indexP = c.find('.');
    if (indexP == std::string::npos) // Case 1: No decimal point
    {
        powTen = 0;
        b = 1;
        a = c;
    }
    else                            // Case 2: There is a decimal point
    {
        while(c.back() == '0')
        {
            c.pop_back();        // Pop off zeros at the back
        }

        powTen = (c.length() - 1) - indexP;  // How many decimal places to move
        b = pow(10, powTen);
        c.erase(indexP, 1);
        a = c;
    }
}
std::string output_string(mpq_class value)
{
    mpz_class numer = value.get_num();
    mpz_class denom = value.get_den();
    int m = 0;
    int n = 0;

    while (denom % 2 == 0)
    {
        denom /= 2;
        m++;
    }
    while (denom % 5 == 0)
    {
        denom /= 5;
        n++;
    }

    int maxPower = std::max(m, n);
    numer *= pow(2, maxPower - m) * pow(5, maxPower - n);

    std::string stringN = numer.get_str();
    int index = stringN.length() - maxPower;
    while (index  <= 0)
    {
        stringN.insert(0, "0");
        index++;
    }
    if (maxPower != 0)  // The number is not a standalone integer
        stringN.insert(index, ".");

    return stringN;
}


Number sqrt(const Number& n)
{
     Number squareRoot;

    // Basically I create 3 floats to store the data I need: 
    // the sqrt(numerator), sqrt(denominator), and the old denominator
    mpf_class numer = n.pimpl->value.get_num();
    mpf_class denom = n.pimpl->value.get_den();
    mpf_class oldDenom = denom;

    if (sgn(numer) != sgn(denom))
        throw std::runtime_error("Error: Negative Number Under Square Root\n");

    numer = sqrt(numer);
    denom  = sqrt(denom);

    // Here i set the numerator to sqrt(numer) * sqrt(denom), 
    // and I set the denominator to oldDenom
    // This way the new value is squrt(numer) * sqrt(denom) / denom 
    // to preserve the precision of the denominator
    squareRoot.pimpl->value.get_num() = numer * denom;
    squareRoot.pimpl->value.get_den() = oldDenom;
    
    return squareRoot;
}
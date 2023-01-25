#include "Number.h"

// Constructors/Deconstructor
Number::Number()
{
    mpq_init(this->number); // Initialize to 0 to avoid core dump
}
Number::Number(const double& d)
{
    mpq_init(this->number);
    mpq_set_d(this->number, d);
    mpq_canonicalize(this->number);
}
Number::Number(const Number& n)
{
    mpq_init(this->number);
    mpq_set(this->number, n.number);
    mpq_canonicalize(this->number);
}
Number::~Number()
{
    mpq_clear(this->number);
}

// Arithmetic Operators
Number Number::operator+(const Number& n) const
{
    Number sum;
    mpq_add(sum.number, this->number, n.number);
    return sum;
}
Number Number::operator-(const Number& n) const
{
    Number diff;
    mpq_sub(diff.number, this->number, n.number);
    return diff;
}
Number Number::operator*(const Number& n) const
{
    Number product;
    mpq_mul(product.number, this->number, n.number);
    return product;
}
Number Number::operator/(const Number& n) const
{
    Number quotient;  // Currently zero, 0/1
    if (quotient == n) // Is the denominator 0?
        throw runtime_error("Error: Division by Zero\n");
    mpq_div(quotient.number, this->number, n.number);
    return quotient;
}

// Comparison Operators
bool Number::operator<(const Number& n) const
{
    if (mpq_cmp(this->number, n.number) < 0) // negative if less than
        return true;
    else
        return false;
}
bool Number::operator>(const Number& n) const
{
    if (mpq_cmp(this->number, n.number) > 0) // positive if greater than
        return true;
    else
        return false;
}
bool Number::operator==(const Number& n) const
{
    if (mpq_cmp(this->number, n.number) == 0) // 0 if equal to
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
Number& Number::operator=(const double& d)
{
    //mpq_clear(this->number);
	//mpq_init(this->number);
    mpq_set_d(this->number, d);
    mpq_canonicalize(this->number);
	return *this;
}
Number& Number::operator=(const Number& n)
{
    //mpq_clear(this->number);
	//mpq_init(this->number);
    mpq_set(this->number, n.number);
    mpq_canonicalize(this->number);
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

// Extraction Operator
ostream& operator<<(ostream& os, const Number& n)
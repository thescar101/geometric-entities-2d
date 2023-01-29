#include "Number.h"

struct Number::Impl {

    Impl();
    Impl(const double& d);
    Impl(const Number& n);
    ~Impl();

    mpq_class value;
};

// Impl Constructors/Deconstructor
Number::Impl::Impl()
{
    // Initialize to 0/1
}
Number::Impl::Impl(const double& d)
{
    this->value = d;
    this->value.canonicalize();
}
Number::Impl::Impl(const Number &n)
{
    this->value = n.pimpl->value;
}
Number::Impl::~Impl()
{
    
}

// Constructors/Deconstructor
Number::Number() : pimpl( new Impl()) 
{
    cout << "Default Constructor" << endl;
}
Number::Number(const double& d) : pimpl( new Impl(d))
{
    cout << "Double Constructor for " << d << endl;
}
Number::Number(const Number& n) : pimpl( new Impl(n))
{
    cout << "Copy Constructor for " << n << endl;
}
Number::Number(Number&& n) : pimpl(move(n.pimpl))
{
    cout << "Move Constructor for " << n << endl;
}
Number::~Number()
{
    if (this->pimpl != nullptr)
        cout << "Deconstructing " << *this << endl;
    else
        cout << "Deconstructing nullptr" << endl;
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
        throw runtime_error("Error: Division by Zero\n");
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
Number& Number::operator=(const double& d)
{
    this->pimpl->value = d;
    this->pimpl->value.canonicalize();
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

// Extraction Operator
ostream& operator<<(ostream& os, const Number& n)
{
    if (n.pimpl != nullptr)
        os << n.pimpl->value;
    return os;
}
#pragma once
#include <gmp.h>
#include <iostream>
#include <stdexcept>
using namespace std;

class Number{
	mpq_t number;

public:
    // Constructors/Deconstructor
    Number();
    Number(const double& d);
    Number(const Number& n);
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
	Number& operator=(const double& d);
    Number& operator=(const Number& n);
    Number& operator+=(const Number& n);
    Number& operator-=(const Number& n);
    Number& operator*=(const Number& n);
    Number& operator/=(const Number& n);

    // Extraction Operator
    friend ostream& operator<<(ostream& os, const Number& n);

};
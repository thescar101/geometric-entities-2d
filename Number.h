#pragma once
#include <stdio.h>
#include <gmpxx.h>
#include <iostream>
#include <stdexcept>
#include <memory>
using namespace std;

class Number{

public:
    // Constructors/Deconstructor
    Number(); // Default Constructor: Initialized to 0
    Number(const double& d); // String Constructor "xxx.xxx"
    Number(const Number& n);
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
	Number& operator=(const double& d);
    Number& operator=(const Number& n);
    Number& operator+=(const Number& n);
    Number& operator-=(const Number& n);
    Number& operator*=(const Number& n);
    Number& operator/=(const Number& n);

    // Extraction Operator
    friend ostream& operator<<(ostream& os, const Number& n);

    private:

    class Impl;

    unique_ptr<Impl> pimpl;

};
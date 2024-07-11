//207723198
// yair852258@gmail.com

#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>

using namespace std;

class Complex
{
public:

    // Constructor. Also works as a conversion from double and
    // also as a default ctor.
    Complex (const double& re = 0.0, const double& im = 0.0): real(re), imag(im) {}

    // Getters
    double get_real() const {return real;}

    double get_imag() const {return imag;}


    // OPERATORS

    // Unary operators
    bool operator!() const
    {
        return real==0 && imag==0;
    }

    Complex& operator-()
    {
        real = -real;
        imag = -imag;
        return *this;
    }


    // Binary operators

    Complex operator+(const Complex& other) const
    {
        Complex complex = Complex(real + other.real, imag + other.imag);
        return complex;
    }

    Complex& operator+=(const Complex& other)
    {
        real+= other.real;
        imag+= other.imag;
        return *this;
    }

    Complex operator-(const Complex& other) const
    {
        Complex complex = Complex(real - other.real, imag - other.imag);
        return complex;
    }

    Complex& operator-=(const Complex& other)
    {
        real-= other.real;
        imag-= other.imag;
        return *this;
    }

    Complex operator*(const Complex& other) const
    {
        Complex complex = Complex (real * other.real - imag * other.imag,
                           real * other.imag + imag * other.real);
        return complex;
    }

    Complex& operator*=(const Complex& other)
    {
        double new_real = real*other.real - imag*other.imag;
        double new_imag = real*other.imag + imag*other.real;
        real = new_real;
        imag = new_imag;
        return *this;
    }


    // Prefix increment:
    Complex& operator++()
    {
        real++;
        return *this;
    }

    // Postfix increment:
    Complex operator++(int)
    {
        Complex copy = *this;
        real++;
        return copy;
    }


    // Comparison operators

    bool operator==(const Complex& other) const
    {
        return real == other.real && imag == other.imag;
    }

    bool operator!=(const Complex& other) const
    {
        return !(*this == other);
    }

    bool operator<(const Complex& other) const
    {
        return sqrt(real * real + imag * imag) < sqrt(other.real * other.real + other.imag * other.imag);
    }

    bool operator>(const Complex& other) const
    {
        return other < *this;
    }

    bool operator<=(const Complex& other) const
    {
        return *this < other || *this == other;
    }

    bool operator>=(const Complex& other) const
    {
        return other <= *this;
    }


    // Print operator
    friend ostream &operator<<(ostream &output, const Complex &c) {
        output << c.real << "+" << c.imag << "i";
        return output;
    }
private:

    double real;
    double imag;

};

#endif
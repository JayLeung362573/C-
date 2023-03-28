//
// Created by Jiawei Liang on 2023-02-03.
//

#ifndef LAB5_VECTOR_H
#define LAB5_VECTOR_H

#endif //LAB5_VECTOR_H
#include <iostream>
using namespace std;

class Vector
{
private:
    double* list;
    unsigned int size;
    void allocateMemory();
    void deallocateMemory();
public:
    Vector();
    Vector(unsigned int);
    Vector(double*, unsigned int);
    Vector(const Vector&);
// Move Constructor
    Vector(Vector&&);
    ~Vector();
    friend const Vector operator+ (const Vector&, const Vector&);
    friend const Vector operator- (const Vector&, const Vector&);
    friend const Vector operator- (const Vector&);
    friend double operator* (const Vector&, const Vector&);
    friend const Vector& operator+=(Vector&, const Vector&);
    friend const Vector& operator-=(Vector&, const Vector&);
    Vector& operator= (const Vector&);
// Move Assignment Operator
    Vector& operator=(Vector&&);
    friend ostream& operator <<(ostream&, const Vector&);
    friend istream& operator >>(istream&, Vector&);
    friend const bool operator==(const Vector&, const Vector&);
    double& operator[](const int index); /// getter
    const double& operator[](const int index) const; /// setter
    friend double getMagnitude(const Vector&);
// removes the last element and returns it.
    double pop();
// pushes a new value to the end.
    void push(double);
// returns the current size.
    unsigned int getSize() const;
};
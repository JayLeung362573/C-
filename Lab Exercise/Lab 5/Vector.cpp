//
// Created by Jiawei Liang on 2023-02-10.
//

#include "Vector.h"
using namespace std;
#include <iostream>
#include <cmath>

Vector::Vector(): size(0)
{
    cout << "Default constructor called" << endl;
    this->allocateMemory();
}


void Vector::allocateMemory()
{
    if(size == 0)
    {
        list = nullptr;
    }
    else
    {
        list = new double[size];
        for(unsigned int i = 0; i < size; i ++)
        {
            list[i] = 0.0;
        }
    }
}


void Vector::deallocateMemory()
{
    delete[] list;
}


Vector::Vector(unsigned int s): size(s)
{
    cout << "One-arg constructor called." << endl;
    this->allocateMemory();
}


Vector::~Vector()
{
    cout << "Destructor called for Vector with " << size << " elements" << endl;
    this->deallocateMemory();
}


Vector::Vector(double *input_value, unsigned int input_size): size(input_size)
{
    cout << "Two-arg constructor called." << endl;
    this->allocateMemory();
    for(unsigned int count = 0; count < size; count ++)
    {
        (*this)[count] = input_value[count];
    }
}


Vector::Vector(const Vector &v)
{
    cout << "Copy constructor called" << endl;
    this->size = v.size;
    this->allocateMemory();
    for(unsigned int count = 0; count < size; count ++)
    {
        (*this)[count] = v[count];
    }
}


const Vector operator+ (const Vector& v1, const Vector& v2)
{
    Vector result(v1.size);
    if(v1.size == v2.size)
    {
        for(unsigned int count = 0; count < v1.size; count ++)
        {
            result[count] = v1[count] + v2[count];
        }
    }
    else
    {
        cout << "ERROR: cannot add two factors of different lengths" << endl;
    }
    return result;
}


const Vector operator- (const Vector& v1, const Vector& v2)
{
    Vector result(v1.size);
    if(v1.size == v2.size)
    {
        for(unsigned int count = 0; count < v1.size; count ++)
        {
            result[count] = v1[count] - v2[count];
        }
    }
    else
    {
        cout << "ERROR: cannot subtract two factors of different lengths" << endl;
    }
    return result;
}


const Vector operator-(const Vector &v)
{
    Vector result(v.size);
    for (unsigned int i = 0; i < v.size; i++) {
        result[i] = -v[i];
    }
    return result;
}


double operator* (const Vector& v1, const Vector& v2)
{
    double result = 0.0;
    for(unsigned int i = 0; i < v1.size; i ++)
    {
        result += v1[i] + v2[i];
    }
    return result;
}


const Vector& operator+=(Vector& v1, const Vector& v2)
{
    cout << "Assignment operator called" << endl;
    if(v1.size == v2.size)
    {
        for(unsigned int count = 0; count < v1.size; count ++)
        {
            v1[count] += v2[count];
        }
    }
    else
    {
        cout << "ERROR: cannot add two factors of different lengths" << endl;
    }
    return v1;
}


const Vector& operator-=(Vector& v1, const Vector& v2)
{
    cout << "Assignment operator called" << endl;
    if(v1.size == v2.size)
    {
        for(unsigned int count = 0; count < v1.size; count ++)
        {
            v1[count] -= v2[count];
        }
    }
    else
    {
        cout << "ERROR: cannot add two factors of different lengths" << endl;
    }
    return v1;
}


Vector& Vector::operator= (const Vector& v)
{
    cout << "Assignment operator called" << endl;
    if(this != &v)
    {
        if(this->list != nullptr)
        {
            this->deallocateMemory();
        }
        this->size = v.size;
        this->allocateMemory();
        for(unsigned int count = 0; count < size; count ++)
        {
            (*this)[count] = v[count];
        }
    }
    return *this;
}


Vector::Vector(Vector&& v)
{
    cout << "Move Constructor called" << endl;
    this->size = v.size;
    this->list = v.list;
    v.list = nullptr;
    v.size = 0;
}


Vector& Vector::operator=(Vector&& v)
{
    cout << "Move Assignment operator called" << endl;
    if(this != &v)
    {
        swap(this->list, v.list);
        swap(this->size, v.size);
    }
    return *this;

}


ostream& operator <<(std::ostream& os, const Vector& v)
{
    os << "[";
    for (unsigned int i = 0; i < v.size; i ++)
    {
        if (i != (v.size - 1))
        {
            os << v[i] << ", ";
        }
        else
        {
            os << v[i];
        }
    }
    os << "]";
    return os;
}


istream& operator >>(istream& is, Vector& v)
{
    for (unsigned int count = 0; count < v.size; count ++)
    {
        cout << "Please enter a number for component " << count << ":" << endl;
        is >> v[count];
        while (!is.good())
        {
            cout << "ERROR! Invalid number." << endl;
            cout << "Please enter a number for component " << count << ":" << endl;
            is.clear();
            is.ignore(80, '\n');
            is >> v[count];
        }
    }
    return is;
}


const bool operator==(const Vector& v1, const Vector& v2)
{
    bool result = true;
    if(v1.size == v2.size)
    {
        for(unsigned int i = 0; i < v1.size; i++)
        {
            result = result && (v1[i] == v2[i]);
        }
    }
    else
    {
        cout << "ERROR: cannot compare two vectors of different lengths." << endl;
    }
    return result;
}


double& Vector::operator[](const int index)
{
    if(index < 0 or index >= size)
    {
        cout << "ERROR! Index out of bound. Program terminating..." << endl;
        exit(1);
    }
        return list[index];
}


const double& Vector::operator[](const int index) const
{
    if (index < 0 or index >= size)
    {
        cout << "ERROR! Index out of bound. Program terminating..." << endl;
        exit(1);
    }
    return list[index];
}


double getMagnitude(const Vector& v)
{
    double result;
    for(unsigned int count = 0; count < v.size; count ++)
    {
        result += v[count] * v[count];
    }
    return sqrt(result);
}


double Vector::pop()
{
//    if(size == 0)
//    {
//        cout << "ERROR" << endl;
//    }
//
//    size --;
//    double poppedValue = list[size];
//
//    // reallocate new memory to match the new size
//    double *newList = new double[size];
//    for (unsigned int i = 0; i < size; i++)
//    {
//        newList[i] = list[i];
//    }
//    deallocateMemory();
//    list = newList;
//
//    return poppedValue;

    double val = (*this)[size - 1];
    Vector* temp = new Vector(*this);

    this->deallocateMemory();
    size --;

    this->allocateMemory();
    for(unsigned int i = 0; i < size; i ++)
    {
        (*this)[i] = (*temp)[i];
    }

    delete temp;

    return val;
}


void Vector::push(double value)
{
//    double *newList = new double[size + 1];
//    for(unsigned int i = 0; i < size + 1; i ++)
//    {
//        newList[i] = list[i];
//    }
//    newList[size] = value;
//    deallocateMemory();
//
//    // set the list pointer to the new array
//    list = newList;
//    size ++;

    Vector* temp = new Vector(*this);

    this->deallocateMemory();
    size ++;

    this->allocateMemory();
    for(unsigned int i = 0; i < size; i ++)
    {
        (*this)[i] = (*temp)[i];
        (*this)[size - 1] = value;
    }

    delete temp;
}


unsigned int Vector::getSize() const
{
    return size;
}





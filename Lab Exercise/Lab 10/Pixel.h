//
// Created by Jiawei Liang on 2023-03-22.
//

#include <fstream>
#include <iostream>

using namespace std;
#ifndef LAB10_PIXEL_H
#define LAB10_PIXEL_H


class Pixel {
private:
    unsigned int red;
    unsigned int green;
    unsigned int blue;
public:
    ~Pixel();

    const unsigned int &operator[](const char *) const;

    Pixel();

    Pixel(const Pixel &);

    Pixel(unsigned int, unsigned int, unsigned int);

    friend ostream &operator<<(ostream&, const Pixel&);
};

#endif //LAB10_PIXEL_H

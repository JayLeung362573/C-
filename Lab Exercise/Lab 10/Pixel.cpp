//
// Created by Jiawei Liang on 2023-03-22.
//

#include "Pixel.h"
#include <algorithm>

using namespace std;

Pixel::~Pixel() {

}


const unsigned int &Pixel::operator[](const char *inputString) const {
    if (strcmp(inputString, "red") == 0) {
        return red;
    } else if (strcmp(inputString, "green") == 0) {
        return green;
    } else if (strcmp(inputString, "blue") == 0) {
        return blue;
    } else {
        throw "Invalid input";
    }
}


Pixel::Pixel() {
    red = 0;
    green = 0;
    blue = 0;
}

Pixel::Pixel(const Pixel &p) {
    red = p.red;
    green = p.green;
    blue = p.blue;
}

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b) :
        red(r),  green(g), blue(b){
}

ostream &operator<<(ostream &os, const Pixel &p) {
    try {
        os << p["red"] << " " << p["green"] << " " << p["blue"] << " ";
    }
    catch (const char *msg) {
        cerr << msg << endl;
        exit(1);
    }
    return os;
}

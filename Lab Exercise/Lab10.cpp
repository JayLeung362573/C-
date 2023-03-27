#include <iostream>
#include "Pixel.h"
#include <vector>
using namespace std;

void rotatePPM(ifstream& infile) {
    if (infile.is_open()) {
        string magic;
        getline(infile, magic);
        cout << magic << endl;

        if (magic != "P3") {
            throw "Input file is not a PPM image";
        }

        string comment;
        getline(infile, comment);
        cout << comment;

        int width, height, max;
        infile >> width >> height >> max;

        vector<Pixel> Pixels;

        int r, g, b;
        for (int i = 0; i < width * height; i++) {
            infile >> r >> g >> b;
            Pixels.emplace_back(r, g, b);
        }

        unsigned int numRotated;
        numRotated = height / 10;

        for (int i = 0; i < numRotated; i++) {
            string fileName = "frame_" + to_string(i) + ".ppm";

            ofstream outfile(fileName);
            if (!outfile.is_open()) {
                throw "Error opening output file";
            }
            cout << "Created output file: " << fileName << endl;

            outfile << "P3" << endl
            << comment << endl
            << width << " " << height << endl
            << max << endl;

            rotate(Pixels.begin(), Pixels.begin() + (10 * width), Pixels.end());

            for (const auto &element: Pixels) {
                outfile << element << " ";
            }

            outfile.close();
        }
    }
    else
    {
        throw "Error opening input file";
    }
}


int main()
{
    ifstream infile("batman.ppm");
    try
    {
        rotatePPM(infile);
    }
    catch (const char* s)
    {
        cout << s;
    }
    infile.close();
    return 0;
}

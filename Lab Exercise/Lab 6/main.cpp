#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void applyGrayScale(ifstream &infile, ofstream &outfile) {
    if (infile && outfile) {
        cout << "Applying the grayscale filter to image..." << endl;
        cout << "Header information from file: " << endl;
        int row = 0, col = 0, numrows = 0, numcols = 0, max = 0;
        int rgb[3] = {0, 0, 0}, g = 0;
        const int MAX = 80;
        char buffer[MAX];


        /// read the magic number and display it on the console
        infile.getline(buffer, MAX);
        cout << "> Version: " << buffer << endl;
        outfile << buffer << endl;


        /// read the comment and print it onto the console
        infile.getline(buffer, MAX);
        cout << "> Comment: " << buffer << endl;
        outfile << buffer << endl;


        /// read the width and height and print both onto the console
        infile >> numcols >> numrows;
        cout << "> Image has " << numcols << "columns and " << numrows << "rows" << endl;
        outfile << numcols << " " << numrows << endl;


        /// read the max number and print it onto the console
        infile >> max;
        cout << "> Max color: " << max << endl;
        outfile << max << endl;


        for (row = 0; row < numrows; ++row) {

            for (col = 0; col < numcols; ++col) {

                infile >> rgb[0] >> rgb[1] >> rgb[2];

                g = ((0.3 * rgb[0]) + (0.59 * rgb[1]) + (0.11 * rgb[2]));

                outfile << g << " " << g << " " << g << " ";
            }
            outfile << endl;
        }
        cout << "Finished processing image..." << endl;
    } else if (!infile && outfile) {
        throw "> Error reading the input file.\n";
    } else if (!infile && !outfile) {
        throw "> Error creating the output file.\n";
    } else
        throw "> Error reading the input file and creating the output file.\n";
}

    int main()
    {
        ifstream infile("Ferrari.ppm");
        ofstream outfile("Ferrari_GS.ppm");

        try{
            applyGrayScale(infile, outfile);
        }
        catch(const char *s){
            cout << s;
        }

        infile.close();
        outfile.close();

        return 0;
    }
























//    string version, comment;
//    int columns, rows, maxColor;
//
//    input >> version;
//    /// remove any leading whitespace characters from the input stream before
//    /// reading the input line into the comment string variable
//    getline(input >> ws, comment);
//
//    input >> columns;
//    input >> rows;
//    input >> maxColor;
//
//    if (!input.is_open())
//    {
//        throw runtime_error("Error opening input file.");
//    }
//
//    if (!output.is_open())
//    {
//        throw runtime_error("Error opening output file.");
//    }
//
//    if (version != "P3")
//    {
//        throw runtime_error("Incorrect image format, expected P3.");
//    }
//
//    if (columns <= 0 || rows <= 0 || maxColor <= 0 || maxColor > 255)
//    {
//        throw runtime_error("Invalid header values.");
//    }
//
//
//    output << version << endl;
//    output << comment << endl;
//    output << columns << " " << rows << endl;
//    output << maxColor << endl;
//
//
//
//    cout << "Version : " << version << endl;
//    cout << "Comment : " << comment << endl;
//    cout << "rows : " << rows << endl;
//    cout << "Image has " << columns << " columnss and " << rows << " rowss." << endl;
//    cout << "Max Color : " << maxColor << endl;
//
//    int red, green, blue, gray;
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < columns; j++) {
//            input >> red >> green >> blue;
//
//            // Calculate the grayscale value
//            gray = 0.3 * red + 0.59 * green + 0.11 * blue;
//
//            // Write the grayscale value to the output file
//            output << gray << " " << gray << " " << gray << " ";
//        }
//        output << endl;
//    }


//int main() {
//    ifstream input("Ferrari.ppm");
//    ofstream output("Ferrari_GS.ppm");
//
//    try {
//        cout << "Applying the grayscale filter to image..." << endl;
//        cout << "Header information from file: " << endl;
//        applyGrayScale(input, output);
//        cout << "Finished processing image..." << endl;
//    }
//
//    catch (const exception &ex) {
//        /// returns the error message associated with the exception that was thrown. In the code I provided
//        cerr << "Error: " << ex.what() << endl;
//    }
//
//    input.close();
//    return 0;
//}

#include <iostream>
#include <fstream>
using namespace std;

class PGM
{
protected:
    int** board;
    int numrows;
    int numcols;
    int max;
    string magic;
    string comment;

    void readInput(ifstream& infile)
    {
        if(infile)
        {
            getline(infile, magic);
            getline(infile, comment);
            infile >> numcols >> numrows;
            infile >> max;

            board = new int* [numrows];
            for(int i = 0; i < numrows; i ++)
            {
                board[i] = new int[numcols];
            }

            for(int row = 0; row < numrows; ++ row)
            {
                for(int col = 0; col < numcols; ++ col)
                {
                    infile >> board[row][col];
                }
            }
        }
        else
        {
            throw exceptionClass("> ERROR!: input file could not be opened.");
        }
    }

public:
    class exceptionClass
    {
    private:
        const char* errorMessage;
    public:
        exceptionClass(const char* c): errorMessage(c){};
        const char* returnError()
        {
            return errorMessage;
        }
    };

    PGM() : board(nullptr), numrows(0), numcols(0), max(0), magic(""), comment("")
    {
        cout << "> No-arg PGM constructor called..." << endl;
    }

    PGM(ifstream& infile): board(nullptr), numrows(0), numcols(0), max(0), magic(""), comment("")
    {
        cout << "> One-arg PGM constructor called..." << endl;

        try
        {
            readInput(infile);
        }
        catch(exceptionClass e)
        {
            throw e;
        }
    }

    virtual ~PGM()
    {
        cout << "> Destroying PGM object..." << endl;
        for(int i = 0; i < numrows; i++)
        {
            delete[] board[i];
        }
        delete[] board;
    }

    virtual PGM& operator<<(int deg) = 0;

    friend void saveToPGM(const PGM& f, const char* fn);
};


class DarkenPGM: public PGM
{
public:
    DarkenPGM(): PGM()
    {
        cout << "> No-arg DarkenPGM constructor called..." << endl;
    }

    DarkenPGM(ifstream& infile): PGM(infile)
    {
        cout << "> One-arg DarkenPGM constructor called..." << endl;
    }

    virtual ~DarkenPGM()
    {
        cout << "> DarkenPGM destructor called..." << endl;
    }

    virtual PGM& operator<< (int deg)
    {
        for(int row = 0; row < numrows; ++row)
        {
            for(int col = 0; col < numcols; ++col)
            {
                board[row][col] -= deg;
                if (board[row][col] - deg < 0)
                {
                    board[row][col] = 0;
                }
            }
        }
        return *this;
    }

};

class TshirtPGM: public PGM
{
public:
    TshirtPGM(): PGM()
    {
        cout << "> No-arg TshirtPGM constructor called..." << endl;
    }

    TshirtPGM(ifstream& infile): PGM(infile)
    {
        cout << "> One-arg TshirtPGM constructor called..." << endl;
    }

    virtual ~TshirtPGM()
    {
        cout << "> TshirtPGM destructor called..." << endl;
    }

    virtual PGM& operator<<(int deg)
    {
        int row = 0; int col = 0;

        for(row = 0; row < numrows; ++row)
        {
            for(col = 0; col < numcols; ++col)
            {
                if( board[row][col] < int(max / deg))
                    board[row][col] = 0;
                else
                    board[row][col] = max;
            }
        }
        return *this;
    }
};


void saveToPGM(const PGM& f, const char* fn)
{
    cout << "> Saving PGM object to ASCII file..." << endl;
    if(f.board != nullptr)
    {
        ofstream outfile(fn);
        outfile << f.magic << endl;
        outfile << f.comment << endl;
        outfile << f.numcols << " " << f.numrows << endl;
        outfile << f.max << endl;

        for(int row = 0; row < f.numrows; ++row)
        {
            for(int col = 0; col < f.numcols; ++col)
            {
                outfile << f.board[row][col] << " ";
            }
            outfile << endl;
        }

        outfile.close();
    }

    else
    {
        cout << "> ERROR!: PGM object is uninitialized." << endl;
    }
}





int main() {
// Open the two input image files
    ifstream file1("image1.pgm", ios::in);
    ifstream file2("image2.pgm", ios::in);
// Instantiate objects of the derived classes
    try {
        DarkenPGM image1(file1);
        TshirtPGM image2(file2);
// Close the two input image files
        file1.close();
        file2.close();
// Declare an integer array for the amount of change
        int degree[2] = {10, 3};
// Declare an array of pointers to the objects
        PGM *ptrToPGM[2] = {&image1, &image2};
// Use overridden virtual function for each object
        for (int i = 0; i < 2; i++)
            (*(ptrToPGM[i])) << degree[i];
// Save modified images to file.
        saveToPGM(image1, "image1_mod.pgm");
        saveToPGM(image2, "image2_mod.pgm");
    }
    catch (PGM::exceptionClass e) {
        cout << e.returnError() << endl;
        return 0;
    }
    return 0;
}



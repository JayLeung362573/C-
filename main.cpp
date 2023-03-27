#include <iostream>
#include <fstream>
using namespace std;


template <class T>
class PGM
{
protected:
    T** board;
    T numrows;
    T numcols;
    T max;
    string magic;
    string comment;
    void readInput(ifstream&);
    void allocateMemory();
    void deallocateMemory();
public:
// for file exceptions
    class exceptionClass;
// default constructor
    PGM();
// one-arg constructor
    PGM(ifstream&);
// destructor
    ~PGM();
// overloaded subtraction operator
    PGM<T> operator-(const PGM<T>&);
// copy constructor
    PGM<T>(const PGM<T>&);
// move constructor
    PGM<T>(PGM<T>&&);
// overloaded assignment operator
    PGM<T>& operator=(const PGM<T>&);
// move assignment operator
    PGM<T>& operator=(PGM<T>&&);
// template friend function for saving PGM object
// file
    template <class U>
    friend void saveToPGM(const PGM<U>&, const char*);
};

////////////////////////////////////////////////////////////
template<class T>
void PGM<T>::readInput(ifstream& infile)
{
    if(infile)
    {
        getline(infile, magic);
        getline(infile, comment);
        infile >> numcols >> numrows;
        infile >> max;

        allocateMemory();

        for(int row = 0; row < numrows; row++)
        {
            for(int col = 0; col < numcols; col++)
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

template<class T>
void PGM<T>::allocateMemory()
{
    board = new T*[numrows];
    for(int i = 0; i < numrows; i++)
    {
        board[i] = new T[numcols];
    }
}

template<class T>
void PGM<T>::deallocateMemory()
{
    for(int i = 0; i < numrows; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}

/// For file exceptions
template<class T>
class PGM<T>::exceptionClass
{
private:
    const char* errorMessage;
public:
    exceptionClass(const char* c): errorMessage(c)
    {

    };
    const char* returnError()
    {
        return errorMessage;
    }
};

/// Default Constructor
template<class T>
PGM<T>::PGM(): board(nullptr), numrows(0), numcols(0), max(0), magic(""), comment("")
{

}

/// One-arg constructor
template<class T>
PGM<T>::PGM(ifstream &infile): board(nullptr), numrows(0), numcols(0), max(0), magic(""), comment("")
{
    try
    {
        readInput(infile);
    }
    catch(exceptionClass e)
    {
        throw e;
    }
}

/// Destructor
template<class T>
PGM<T>::~PGM()
{
    deallocateMemory();
}

/// Overloaded subtraction operator
template<class T>
        PGM<T> PGM<T>::operator-(const PGM<T> &other)
{
    if(numrows != other.numrows || numcols != other.numcols)
    {
        throw exceptionClass("> ERROR!: input PGM dimension do not match");
    }

    /// Instantiate a PGM<T> object
    PGM<T> result(*this);

    for(int row = 0; row < numrows; ++row)
    {
        for(int col = 0; col < numcols; ++col)
        {
            /// the absolute value of
            ///the differences in pixel values between the input and the calling objects
            result.board[row][col] = abs(board[row][col] - other.board[row][col]);
        }
    }

    return result;
}

/// Copy constructor
template<class T>
PGM<T>::PGM(const PGM<T> &other)
{
    magic = other.magic;
    comment = other.comment;
    numcols = other.numcols;
    numrows = other.numrows;
    max = other.max;

    allocateMemory();

    for(int row = 0; row < numrows; row++)
    {
        for(int col = 0; col < numcols; col++)
        {
            board[row][col] = other.board[row][col];
        }
    }
}

/// Move constructor
template<class T>
PGM<T>::PGM(PGM<T>&& p): board(p.board), max(p.max), numcols(p.numcols), numrows(p.numrows),
magic(p.magic), comment(p.comment)
{
    p.board = nullptr;
    p.numrows = 0;
    p.numcols = 0;
}

/// Overloaded assignment operator
template<class T>
PGM<T> &PGM<T>::operator=(const PGM<T> &other)
{
    if(this != &other)
    {
        if(board != nullptr)
            this->deallocateMemory();

        magic = other.magic;
        comment = other.comment;
        numcols = other.numcols;
        numrows = other.numrows;
        max = other.max;

        this->allocateMemory();

        for(int row = 0; row < numrows; row++)
        {
            for(int col = 0; col < numcols; col++)
            {
                board[row][col] = other.board[row][col];
            }
        }
    }
    return *this;
}

/// Move assignment operator
template<class T>
PGM<T> &PGM<T>::operator=(PGM<T> &&other)
{
    if(this != &other)
    {
        cout << "> Move assignment operator called..." << endl;
        swap(numrows, other.numrows);
        swap(numcols, other.numcols);
        swap(max, other.max);
        swap(magic, other.magic);
        swap(comment, other.comment);
        swap(board, other.board);
    }
    return *this;
}

/// template friend function for saving PGM object
/// file
template<class U>
void saveToPGM(const PGM<U>& f, const char* fn)
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





int main()
{
    ifstream file1("frame1.pgm", ios::in);
    ifstream file2("frame2.pgm", ios::in);
    PGM<short>* ptr1 = nullptr;
    PGM<short>* ptr2 = nullptr;
    PGM<short>* ptr3 = nullptr;
    try
    {
        ptr1 = new PGM<short>(file1);
        ptr2 = new PGM<short>(file2);
        ptr3 = new PGM<short>(*ptr1 - *ptr2);
    }
    catch (PGM<short>::exceptionClass& e)
    {
        cout << e.returnError() << endl;
        return 0;
    }
    saveToPGM(*ptr3, "result.pgm");
    file1.close();
    file2.close();
    delete ptr1;
    ptr1 = nullptr;
    delete ptr2;
    ptr2 = nullptr;
    delete ptr3;
    ptr3 = nullptr;

}









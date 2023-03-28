#include <iostream>
#include "Vector.h"
#include <iomanip>

using namespace std;

Vector makeVector(double* l, unsigned int s)
{
    Vector temp(l, s);
    return temp;
}

int main()
{
    double arr[] = {3.0, 4.0, 5.0};
    Vector a(3), b(arr, 3), c(b), d;
    cout << a << endl;
    /// [0, 0, 0]
    cout << b << endl;
    /// [3, 4, 5]
    cout << c << endl;
    /// [3, 4, 5]
    cout << d << endl;
    /// []
    cin >> a;
    d = a + b;
    cout << d << endl;
    d += a;
    cout << d << endl;
    a[0] = 11.0;
    a[1] = -15.0;
    a[2] = 3.0;
    d = a - b;
    cout << d << endl;
    d -= b;
    cout << d << endl;
    double dotProduct = a * b;
    cout << dotProduct << endl;
    d = -a;
    cout << d << endl;
    cout << d << endl;
    d = a = b;
    cout << d << endl;
    if (a == b)
        cout << "a and b are equal!" << endl;
    else
        cout << "a and b are NOT equal!" << endl;
    a[0] = 11.0;
    a[1] = -15.0;
    a[2] = 3.0;
    b[0] = 11.0;
    b[1] = 15.0;
    b[2] = 3.0;
    if (a == b)
        cout << "a and b are equal!" << endl;
    else
        cout << "a and b are NOT equal!" << endl;
    cout << setprecision(4) << "Magnitude of a is equal to "
         << getMagnitude(a) << endl;
    cout << "Magnitude of b is equal to "
         << getMagnitude(b) << endl;
    double arr2[] = {12.0, -13.0, 1.0, 16.0};
    Vector V1 = makeVector(arr2, 4);
    Vector V2;
    V2 = makeVector(arr2, 4);
    cout << "The current size of V1 is " << V1.getSize() << endl;
    cout << V1.pop() << endl;
    cout << "The current size of V1 is " << V1.getSize() << endl;
    V2.push(100);
    cout << V2 << endl;
    cout << "The current size of V2 is " << V2.getSize() << endl;
    return 0;
}
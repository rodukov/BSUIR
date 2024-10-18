#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double x, y, r, z, min, max;

    cout << "X: " << endl;
    cin >> x;

    cout << "Y: " << endl;
    cin >> y;

    cout << "Z: " << endl;
    cin >> z;
 
    if (x > 0 && y > 0) {
        if (y < z) {
            min = y;
        }
        else {
            min = z;
        }
        cout << min + exp(0.9 * x) << endl;
    }
    else if (x < 0) {
        cout << sqrt(pow(x, 2) + pow(y, 2)) + exp(y - x) << endl;

    }
    r = (x > 0 && y > 0) ? ((y < z ? y : z)+exp(0.9*x)) : (x < 0) ? sqrt(pow(x,2) + pow(y, 2))+exp(y-x) : pow(sin(y), 2) > pow(cos(y), 2) ? pow(sin(y), 2) : pow(cos(y), 2);

    cout << r << endl;

}


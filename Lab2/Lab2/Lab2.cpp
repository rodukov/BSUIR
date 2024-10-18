#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    const double pi = 3.1415926535897932;
    double x, y, fx;
    int k;

    cout << "X: " << endl;
    cin >> x;

    cout << "Y: " << endl;
    cin >> y;

    cout << "select function(1,2,3): " << endl;
    cin >> k;

    switch (k) {
        case 1: fx = sinh(x); break;
        case 2: fx = pow(x, 2); break;
        case 3: fx = exp(x); break;
        default: cout << "No function selected" << endl; return 1;
    }

    if (x > y) {
        if (y == pi / 2 || y == (3 * pi) / 2) {
            cout << "Net reshenia" << endl;      
        }
        else {
            cout << pow(abs(fx + x), 1. / 3) - tan(y)<<endl;
        }
        
    }
   /* else*/ if (x == y) {
        cout << pow((y - fx), 3) + sin(y);
    }
    else {
        if (fx < 0) {
            cout << "net reshenia" << endl;
        }
        else {
            cout << y + pow(x, 3) - sqrt(fx);
        }
        
    }
}

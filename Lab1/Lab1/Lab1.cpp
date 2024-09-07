#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    double s, x, y, z;

    cout << "X: " << endl;
    cin >> x;

    cout << "Y: " << endl;
    cin >> y;

    cout << "Z: " << endl;
    cin >> z;

    /* x = 0.4 * pow(10, 4);
    y = -0.875;
    z = -0.475 * pow(10, -3);*/

    s = pow(abs(cos(x) - cos(y)), 1 + 2 * pow(sin(y), 2))
        *
        (1 + z + pow(z, 2) / 2 + pow(z, 3) / 3 + pow(z, 4) / 4);

    std::cout << s;
}

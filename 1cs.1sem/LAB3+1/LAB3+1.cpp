#include <iostream>
#include <cmath>

# define M_PI           3.14159265358979323846  /* pi */

using namespace std;

int main()
{
    double a, b, sx, yx, h, res, n, cosv;

    a = 0.1;
    b = 1;
    n = 80;
    h = 0.1;

    for (double x = a; x < (b + h / 2); x += h) {
        yx = exp(x * cos(M_PI / 4.0)) * cos(x * sin(M_PI / 4.0));

        res = 1;
        sx = res;

        for (int k = 1; k < n; k++) {

            cosv = cos((k * M_PI) / 4.0);
            
            res *= (1.0 / k) * x;
            sx += res * cosv; // * cosv
        }
        
        cout << "x " << x << "   " << "y(x) " << yx << "   " << "s(x) " << sx << endl;



    }

}


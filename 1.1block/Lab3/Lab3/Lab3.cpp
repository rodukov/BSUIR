#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a, b, k, sx, yx, h, res;

    a = 0.1;
    b = 1;
    k = 80;
    h = (b - a) / 10;

    for (double x = a; x < (b + h / 2); x += h) {
        yx = cos(x);


        res = -1*(x*x)/2;
        sx = 1 + res;
        for (int n = 2; n < k; n++) {
            res *= -1 * (x * x)/((n*2)*(n*2-1));

            sx += res;
        }
       
        cout << "x " << x << "   " << "y(x) " << yx << "   " << "s(x) " << sx << endl;



    }

}



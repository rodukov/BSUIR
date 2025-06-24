#include <iostream>
#include <cmath>

using namespace std;

double yx(double &x) {
	return x * atan(x);
}

double sx(double& x, double eps) {

	double c, sum, n;
	c = sum = n = 0;

	while (fabs(c) < eps) {
		c = (pow(-1, n) * pow(x, 2 * n + 2)) / (1 + 2 * n);
		sum += c;
		n++;
	}

	return sum;
}

int main() {
	double eps = pow(10, -4);
	double a = 1;
	double b = 3;
	double h = (b - a) / 10;
	for (double x = a; x < b + h / 2; x += h) {
		cout << yx(x) << " ";
		cout << sx(x, eps) << endl;

	}

}

#include <iostream>
#include <complex>
#include <cmath>

using namespace std;


int Task1(double w, double u, double f, double r1, double l, double c, double rk) {
	double xl, xc;

	xl = w * l * pow(10, -3);
	xc = 1 / (w * c * pow(10, -6));
	cout << "Xl = " << xl << endl << "Xc = " << xc << endl;

	complex<double> ucompl(u, 0); cout << "Ucomp = " << ucompl.real() << " " << ucompl.imag() << "i" << endl;
	complex<double> z1(r1, 0); cout << "Z1 = " << z1.real() << " " << z1.imag() << "i" << endl;
	complex<double> zc(0, -xc); cout << "Zc = " << zc.real() << " " << zc.imag() << "i" << endl;
	complex<double> zl(0, xl); cout << "Zl = " << zl.real() << " " << zl.imag() << "i" << endl;
	complex<double> zrk(rk, 0); cout << "Zrk = " << zrk.real() << " " << zrk.imag() << "i" << endl;
	complex<double> zall = z1 + zc + zl + zrk; cout << "Zп = " << zall.real() << " " << zall.imag() << "i" << endl;
	complex<double> i = ucompl / zall;
	complex<double> z12 = zl + zrk; cout << "Z12 = " << z12.real() << " " << z12.imag() << "i" << endl;
	complex<double> uk = i * z12;
	complex<double> uc = i * zc;
	complex<double> u1 = i * z1;
	cout << "I = " << i.real() * pow(10, 3) << " " << i.imag() * pow(10, 3) << "i" << endl << "Uk = " << uk.real() << " " << uk.imag() << "i" << endl << "Uc = " << uc.real() << " " << uc.imag() << "i" << endl << "U1 = " << u1.real() << " " << u1.imag() << "i" << endl;
	return 1;
}



int Task2(double u, double r1, double w, double c, double l, double rk) {
	double xl, xc;

	xl = w * l * pow(10, -3);
	xc = 1 / (w * c * pow(10, -6));
	cout << "Xl = " << xl << endl << "Xc = " << xc << endl;

	complex<double> ucompl(u, 0); cout << "Ucomp = " << ucompl.real() << " " << ucompl.imag() << "i" << endl;
	complex<double> zc(0, -xc); cout << "Zc = " << zc.real() << " " << zc.imag() << "i" << endl;
	complex<double> zl(0, xl); cout << "Zl = " << zl.real() << " " << zl.imag() << "i" << endl;
	complex<double> z1(r1, 0); cout << "Z1 = " << z1.real() << " " << z1.imag() << "i" << endl;
	complex<double> zrk(rk, 0); cout << "Zrk = " << zrk.real() << " " << zrk.imag() << "i" << endl;
	complex<double> i1 = ucompl / z1; cout << "I1 = " << i1.real() * pow(10, 3) << " " << i1.imag() * pow(10, 3) << "i" << endl;
	complex<double> i2 = ucompl / zc; cout << "I2 = " << i2.real() * pow(10, 3) << " " << i2.imag() * pow(10, 3) << "i" << endl;
	complex<double> i3 = ucompl / (zl + zrk); cout << "I3 = " << i3.real() * pow(10, 3) << " " << i3.imag() * pow(10, 3) << "i" << endl;
	complex<double> i = i1 + i2 + i3; cout << "I = " << i.real() * pow(10, 3) << " " << i.imag() * pow(10, 3) << "i" << endl;
	return 1;
}


int Task3(double u, double r1, double w, double c, double l, double rk, double r2, double r3) {
	double xl, xc;

	xl = w * l * pow(10, -3);
	xc = 1 / (w * c * pow(10, -6));
	cout << "Xl = " << xl << endl << "Xc = " << xc << endl;

	complex<double> ucompl(u, 0); cout << "Ucomp = " << ucompl.real() << " " << ucompl.imag() << "i" << endl;
	complex<double> zc(0, -xc); cout << "Zc = " << zc.real() << " " << zc.imag() << "i" << endl;
	complex<double> zl(0, xl); cout << "Zl = " << zl.real() << " " << zl.imag() << "i" << endl;
	complex<double> z1(r1, 0); cout << "Z1 = " << z1.real() << " " << z1.imag() << "i" << endl;
	complex<double> zrk(rk, 0); cout << "Zrk = " << zrk.real() << " " << zrk.imag() << "i" << endl;
	complex<double> z2 = zl + zrk + r2; cout << "Z2 = " << z2.real() << " " << z2.imag() << "i" << endl;
	complex<double> z3(r3, 0); cout << "Z3 = " << z3.real() << " " << z3.imag() << "i" << endl;
	complex<double> z23 = (z2 * z3) / (z2 + z3); cout << "Z23 = " << z23.real() << " " << z23.imag() << "i" << endl;
	complex<double> zall = z1 + z23; cout << "Zп = " << zall.real() << " " << zall.imag() << "i" << endl;
	complex<double> i1 = ucompl / zall; cout << "I1 = " << i1.real() * pow(10, 3) << " " << i1.imag() * pow(10, 3) << "i" << endl;
	complex<double> u1 = i1 * z1; cout << "U1 = " << u1.real() << " " << u1.imag() << "i" << endl;
	complex<double> i2 = i1 * (z3 / (z3 + z2)); cout << "I2 = " << i2.real() * pow(10, 3) << " " << i2.imag() * pow(10, 3) << "i" << endl;
	complex<double> i3 = i1 * (z2 / (z3 + z2)); cout << "I3 = " << i3.real() * pow(10, 3) << " " << i3.imag() * pow(10, 3) << "i" << endl;
	complex<double> u2 = i2 * r2; cout << "U2 = " << u2.real() << " " << u2.imag() << "i" << endl;
	complex<double> u3 = i3 * z3; cout << "U3= " << u3.real() << " " << u3.imag() << "i" << endl;

	cout << "БАЛАНС МОЩНОСТЕЙ: " << endl;
	complex<double> s = ucompl * conj(i1); cout << "S = " << s.real() << " " << s.imag() << "i" << endl;
	double p = pow(abs(i1), 2) * r1 + pow(abs(i2), 2) * (r2 + rk) + pow(abs(i3), 2) * r3;
	cout << "Pпотр = " << p << endl;
	complex<double> q = pow(abs(i2), 2) * zl; cout << "Q = " << q.real() << " " << q.imag() << "i" << endl;
	cout << "Если действительная часть числа S +- равна Рпотр и мнимая часть числа S +- равна Q, то задача решена верно" << endl;


	return 1;
}




int main()
{
	setlocale(LC_ALL, "rus");

	double u, f, r1, r2, r3, l, rk, c;
	cout << "ИСХОДНЫЕ ДАННЫЕ: " << endl;
	cout << "U (В) = "; cin >> u;
	cout << endl << "f (Гн) = "; cin >> f;
	cout << endl << "R1 (Ом) = "; cin >> r1;
	cout << endl << "R2 (Ом) = "; cin >> r2;
	cout << endl << "R3 (Ом) = "; cin >> r3;
	cout << endl << "L (Гн) = "; cin >> l;
	cout << endl << "rk (Ом) = "; cin >> rk;
	cout << endl << "C (Ф) = "; cin >> c;
	double w = 2 * 3.14 * f;


	int k;

	bool m = true;
	while (m) {

		cout << "НОМЕР ЗАДАНИЯ: ";

		cin >> k;

		switch (k)
		{
		case 1: {
			Task1(w, u, f, r1, l, c, rk);
			system("pause");
			system("cls");
		} break;
		case 2: {
			Task2(u, r1, w, c, l, rk);
			system("pause");
			system("cls");
		} break;
		case 3: {
			Task3(u, r1, w, c, l, rk, r2, r3);
			system("pause");
			system("cls");
		} break;
		default:
			m = false;
			break;
		}
	}


	return 0;
}


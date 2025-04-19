#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

// Функция f(x)
double f(double x) {
    return exp(x) / pow(x, 3) - pow(sin(x), 3);
}

// Метод средних прямоугольников
double midpointRule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double x = a + (i + 0.5) * h;
        sum += f(x);
    }
    return sum * h;
}

// Метод Гаусса (2-узловая квадратурная формула)
double gaussQuadrature1(double a, double b) {
    // Узлы и веса для n=2
    double x1 = -1.0 / sqrt(3), x2 = 1.0 / sqrt(3);
    double w1 = 1.0, w2 = 1.0;

    // Переводим узлы с [-1, 1] на [a, b]
    double c1 = (b - a) / 2 * x1 + (a + b) / 2;
    double c2 = (b - a) / 2 * x2 + (a + b) / 2;

    return (b - a) / 2 * (w1 * f(c1) + w2 * f(c2));
}

// Метод Гаусса с разбиением интервала на n частей
double gaussQuadrature(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    // Узлы и веса для 2-точечной формулы Гаусса
    double x1 = -1.0 / sqrt(3), x2 = 1.0 / sqrt(3);
    double w1 = 1.0, w2 = 1.0;

    for (int i = 0; i < n; ++i) {
        double left = a + i * h;
        double right = left + h;

        // Переводим узлы с [-1, 1] на [left, right]
        double c1 = (right - left) / 2 * x1 + (left + right) / 2;
        double c2 = (right - left) / 2 * x2 + (left + right) / 2;

        // Добавляем вклад текущего подотрезка
        sum += (right - left) / 2 * (w1 * f(c1) + w2 * f(c2));
    }

    return sum;
}


// Адаптивный метод Симпсона
double adaptiveSimpson(double a, double b, double eps) {
    function<double(double, double, double)> simpson = [&](double a, double b, double eps) {
        double c = (a + b) / 2; // seredina
        double S1 = (b - a) / 6 * (f(a) + 4 * f(c) + f(b));
        double d = (a + c) / 2, e = (c + b) / 2; // seredina levoy i pravoy
        double S2 = (b - a) / 12 * (f(a) + 4 * f(d) + 2 * f(c) + 4 * f(e) + f(b));
        if (fabs(S2 - S1) < 15 * eps) return S2 + (S2 - S1) / 15;
        return simpson(a, c, eps / 2) + simpson(c, b, eps / 2);
        };
    return simpson(a, b, eps);
}

int main() {
    double a = 4, b = 7;
    int n = 1000; // Количество разбиений для метода средних
    double eps = 1e-6; // Точность для адаптивного Симпсона

    cout << "Midpoint Rule: " << midpointRule(a, b, n) << endl;
    cout << "Gauss Quadrature: " << gaussQuadrature(a, b, n) << endl;
    cout << "Adaptive Simpson: " << adaptiveSimpson(a, b, eps) << endl;

    return 0;
}
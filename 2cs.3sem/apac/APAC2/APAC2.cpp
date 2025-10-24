#include <iomanip>
#include <iostream>
void gen(double[], double, double);
double* solve_matrix(double**, double*, int);
using namespace std;
int main()
{
    setlocale(LC_ALL, "rus");
    double e2, e4, r[6], g_vetv[6], g_uz[4], i[6];
    cout << "Введите 1 для использования значений по умолчанию\n";
    string ch;
    cin >> ch;
    if (ch == "1")
    {
        e2 = 15, e4 = 30, r[0] = 2000, r[1] = 1000,
            r[2] = 3900, r[3] = 1500, r[4] = 3900, r[5] = 1500;
    }
    else {
        cout << "Введите E2, E4\n";
        cin >> e2 >> e4;

        for (int i = 0; i < 6; i++) {
            cout << "Введите R" << i + 1 << endl;
            cin >> r[i];
            g_vetv[i] = 1 / r[i];
        }
    }


    for (int i = 0; i < 6; i++) {
        g_vetv[i] = 1 / r[i];
        cout << "G ветви №" << i + 1 << " = " << g_vetv[i] << endl;
    }

    g_uz[0] = g_vetv[0] + g_vetv[1] + g_vetv[2];
    g_uz[1] = g_vetv[0] + g_vetv[5] + g_vetv[4];
    g_uz[2] = g_vetv[2] + g_vetv[3] + g_vetv[4];
    g_uz[3] = g_vetv[1] + g_vetv[3] + g_vetv[5];

    for (int i = 0; i < 4; i++) {
        cout << "G узла №" << i + 1 << " = " << g_uz[i] << endl;
    }

    double** koeff = new double* [3];
    for (int i = 0; i < 3; i++) {
        koeff[i] = new double[3];
    }
    double* ans = new double[3];
    ans[0] = 0;
    ans[1] = e4 * g_vetv[3];
    ans[2] = -1 * e2 * g_vetv[1] - e4 * g_vetv[3];
    for (int i = 0; i < 3; i++) {
        koeff[i][i] = g_uz[i + 1];
    }
    koeff[0][1] = -g_vetv[4];
    koeff[0][2] = -g_vetv[5];
    koeff[1][0] = -g_vetv[4];
    koeff[1][2] = -g_vetv[3];
    koeff[2][0] = -g_vetv[5];
    koeff[2][1] = -g_vetv[3];
    double* y = solve_matrix(koeff, ans, 3);
    i[0] = -y[0] * g_vetv[0];
    i[1] = (y[2] + e2) * g_vetv[1];
    i[2] = y[1] * g_vetv[2];
    i[3] = (y[2] - y[1] + e4) * g_vetv[3];
    i[4] = (y[1] - y[0]) * g_vetv[4];
    i[5] = (y[0] - y[2]) * g_vetv[5];
    for (int ind = 0; ind < 6; ind++) {
        cout << "Ток " << ind + 1 << " = " << i[ind] * 1000 << " mA" << endl;
    }
    cout << "Баланс мощностей:\n";
    double tmp = 0;
    for (int ind = 0; ind < 6; ind++) {
        tmp += pow(i[ind], 2) * r[ind];
    }
    double tmp2 = e2 * i[1] + e4 * i[3];
    cout << "Левая часть: " << tmp << " Правая часть: " << tmp2 << endl;
    if (abs(tmp - tmp2) < 0.01)cout << "Баланс мощностей сошелся\n";
    else cout << "Баланс не сошелся\n";
    gen(r, e2, e4);

}
void gen(double r[], double e2, double e4) {
    double u34 = (e4 / r[3] + e2 / (r[1] + r[2])) / (1 / (r[1] + r[2]) + 1 / r[3] + 1 / (r[4] + r[5]));
    double i30 = (u34 - e2) / (r[1] + r[2]);
    double i50 = u34 / (r[4] + r[5]);
    double u_hol = e2 + i30 * r[1] - i50 * r[5];
    double r46 = (r[3] * r[5]) / (r[3] + r[4] + r[5]), r45 = (r[3] * r[4]) / (r[3] + r[4] + r[5]), r56 = r45;
    double r_gen = ((r46 + r[1]) * (r45 + r[2])) / (r45 + r[2] + r46 + r[1]) + r56;
    double i1_gen = u_hol / (r_gen + r[0]);
    cout << "Ток I1, вычисленный методом эквивалентоного генератора равен: " << i1_gen * 1000 << " mA";
}
double* solve_matrix(double** koeff, double* ans, int n) {
    int m = n + 1;                  //Расширенная матрица
    double** A = new double* [n + 1]; //Выделяем память под строки
    for (int i = 1; i < n + 1; i++)
        A[i] = new double[m + 1];    //Под столбцы
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            A[i][j] = koeff[i - 1][j - 1];
        }
    }
    for (int i = 1; i < n + 1; i++) {
        A[i][m] = ans[i - 1];
    }
    double tmp;
    double* x = new double[n + 1];
    for (int k = 1; k < n; k++) {
        for (int i = k + 1; i <= n; i++) {
            tmp = A[i][k] / A[k][k];
            for (int j = m; j >= k; j--) //Считаем от последнего эл-та в строке, т.е. базиса
                A[i][j] -= tmp * A[k][j]; //

        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (abs(A[i][j]) < 0.000001) A[i][j] = 0;
    x[n] = A[n][m] / A[n][n];
    for (int i = n - 1; i >= 1; i--) {
        x[i] = A[i][m];
        for (int j = i + 1; j <= n; j++)
            x[i] -= A[i][j] * x[j];
        x[i] = x[i] / A[i][i];
    }

    for (int i = 1; i <= n; i++)
        if (abs(x[i]) < 0.00000001) x[i] = 0;
    double* otv = new double[3];
    for (int i = 0; i < 3; i++) {
        otv[i] = x[i + 1];
        cout << "U" << i + 2 << "1=" << setw(8) << otv[i] << endl;
    }
    delete[] A;
    delete[]x;
    return otv;
}

#include <iostream>

using namespace std;
// Matrix calculator

int main() {


    /*
    1 - сложить матрицы
    2 - вычесть матрицы
    3 - умножить на число матрицу
    4 - перемножить матрицы
    */
    int k;
    cout << "select function(1,2,3,4): " << endl;
    cin >> k;

    int n, m;
    cout << "Enter size (stroki): "; // вниз
    cin >> n;
    cout << "Enter size (stolbcy): "; // вправо
    cin >> m;

    // first matrxi
    int** s1 = new int* [n];
    for (int i = 0; i < n; i++) s1[i] = new int[m];

    // ee vvod
    for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
    {
    cout << "Vvedite s1[" << i << "][" << j << "]: ";
    cin >> s1[i][j];
    }

    // res matrix initializ
    int** s = new int* [n];
    for (int i = 0; i < n; i++) s[i] = new int[m];


    if (k == 1 || k == 2 || k == 4) {
        // vtoraya matrix
        int** s2 = new int* [n];
        for (int i = 0; i < n; i++) s2[i] = new int[m];

        //vvod ee
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                cout << "Vvedite s2[" << i << "][" << j << "]: ";
                cin >> s2[i][j];
            }
        // slozhenie matrix
        if (k == 1) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++) {
                    s[i][j] = s1[i][j] + s2[i][j];
                }
        }
        // vychitanie matrix
        if (k == 2) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++) {
                    s[i][j] = s1[i][j] - s2[i][j];
                }
        }
        // peremnozhenie matrix
        if (k == 4) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    s[i][j] = 0;
                    for (int k = 0; k < m; k++) {
                        s[i][j] += s1[i][k] * s2[k][j];
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            delete[] s2[i];
        }
        delete []s2;
    }




    // umnozhenie matrix
    if (k == 3) {
        int conf;
        cout << "vvedi const: ";
        cin >> conf;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                s[i][j] = s1[i][j] * conf;
            }
    }

    // vivod matrix
    for (int i = 0; i < n; i++) {
    cout << endl;
        for (int j = 0; j < m; j++)
        {
            cout << s[i][j] << " ";
        }
    }

    for (int i = 0; i < n; i++) {
       delete[] s[i];
       delete[] s1[i];
    } 
    delete[] s;
    delete[] s1;




}

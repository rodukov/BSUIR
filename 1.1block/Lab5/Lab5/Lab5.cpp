#include <iostream>

using namespace std;

/*
Ввести с клавиатуры количество строк и столбцов массива, выделить
необходимый объем памяти для хранения элементов массива и ввести исходные данные.
Выполнить задание, результат вывести на экран.

Задана матрица размером N×M. Получить одномерный массив, занося
в ячейку значение 0, если строка матрицы с таким же номером содержит хотя
бы один нулевой элемент, и 1 в противном случае.

*/

int main() {
    int n, m;
    bool fnd;
    cout << "Enter size (stroki): "; // вниз
    cin >> n;
    cout << "Enter size (stolbcy): "; // вправо
    cin >> m;

    int* arr = new int[n];
    int** s = new int* [n];
    for (int i = 0; i < n; i++) s[i] = new int[m];
    

    for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        {
            cout << "Vvedite s[" << i << "][" << j << "]: ";
            cin >> s[i][j];
        }

    for (int i = 0; i < n; i++) {
        fnd = false;
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 0) {
                fnd = true;
                break;
            }
        }
        if (fnd) {
            arr[i] = 0;
        }
        else {
            arr[i] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    delete []arr;
    delete []s;


}

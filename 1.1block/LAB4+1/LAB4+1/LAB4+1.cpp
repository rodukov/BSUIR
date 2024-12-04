#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;

    int* arr1 = new int[n];
    int* arr2 = new int[n];

    cout << "Enter elements of arr1:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr1[i];
    }
    cout << "Enter elements of arr2:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr2[i];
    }

    int* arr3 = new int[n * 2];
    int i = 0, j = 0, k = 0;

    // Слияние массивов
    while (i < n && j < n) {
        if (arr1[i] < arr2[j]) {
            arr3[k] = arr1[i];
            i++;
        }
        else {
            arr3[k] = arr2[j];// если arr2 меньше или равен
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы из arr1, если есть
    while (i < n) {
        arr3[k] = arr1[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы из arr2, если есть
    while (j < n) {
        arr3[k] = arr2[j];
        j++;
        k++;
    }

    // Вывод объединенного массива
    cout << "Merged array: ";
    for (int m = 0; m < n * 2; m++) {
        cout << arr3[m] << " ";
    }
    cout << endl;

    // Освобождение памяти
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

}

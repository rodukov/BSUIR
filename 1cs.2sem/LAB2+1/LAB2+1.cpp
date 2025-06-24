#include <iostream>
using namespace std;

int maxRecursive(int arr[], int size) {
    if (size == 1) return arr[0]; 

    int maxOfRest = maxRecursive(arr, size - 1);

    // Текущий элемент и максимальный оставшегося
    if (arr[size - 1] >  maxOfRest) {
        return arr[size - 1];
    }
    else {
        return maxOfRest;+
    }
}


int main() {
    int size;

    cout << "Size: ";
    cin >> size;

    int* arr = new int[size];
    cout << "Array Elements: ";
    for (int i = 0; i < size; i++) cin >> arr[i];

    int result = maxRecursive(arr, size);
    cout << "Max Element: " << result << endl;

    delete[] arr;
    return 0;
}
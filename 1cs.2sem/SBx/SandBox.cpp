#include <iostream>

// Структура элемента массива
struct Item {
    int key;
};

const int n = 8;
Item a[n] = { {6}, {4}, {8}, {5}, {3}, {6}, {5}, {4} };
Item c[n]; // Вспомогательный массив для слияния

// Функция слияния двух отсортированных частей массива a[left..m] и a[m+1..right]
void slip(int left, int m, int right)
{
    int i = left;     // начало левого подмассива
    int j = m + 1;    // начало правого подмассива
    int k = 0;        // индекс для массива c[]
    while (i <= m && j <= right)
    {
        if (a[i].key < a[j].key) { c[k] = a[i]; i++; }
        else { c[k] = a[j]; j++; }
        k++;
    }

    while (i <= m) c[k] = a[i];i++;k++;
    while (j <= right) c[k] = a[j];j++;k++;
    

    for (k = 0, i = left; i <= right; i++, k++) a[i] = c[k];
    
}

// Рекурсивная функция сортировки слиянием
void s_sl(int left, int right) {
    if (left < right){
        int m = (left + right) / 2;
        s_sl(left, m);
        s_sl(m + 1, right);
        slip(left, m, right);
    }
}

// Вывод массива
void print_array()
{
    for (int i = 0; i < n; i++)
        std::cout << a[i].key << " ";
    std::cout << "\n";
}

int main()
{
    std::cout << "Original array:\n";
    print_array();

    s_sl(0, n - 1);

    std::cout << "Sorted array:\n";
    print_array();

    return 0;
}

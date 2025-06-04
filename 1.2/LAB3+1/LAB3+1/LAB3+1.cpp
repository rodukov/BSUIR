#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

struct Car {
    char brand[50];     // фактически записываем только 30 байт
    int year;
    float engine;
    int max_speed;
};

// Быстрая сортировка (нерекурсивная)
void quickSortNonRecursive(Car a[], int n) {
    struct { int l, r; } stack[20];
    int s = 0, i, j, left, right;
    Car t, x;
    stack[s].l = 0;
    stack[s].r = n - 1;

    while (s != -1) {
        left = stack[s].l;
        right = stack[s].r;
        s--;
        while (left < right) {
            i = left;
            j = right;
            x = a[(left + right) / 2];
            while (i <= j) {
                while (a[i].year < x.year) i++;
                while (a[j].year > x.year) j--;
                if (i <= j) {
                    t = a[i];
                    a[i] = a[j];
                    a[j] = t;
                    i++;
                    j--;
                }
            }
            if ((j - left) < (right - i)) {
                if (i < right) { s++; stack[s].l = i; stack[s].r = right; }
                right = j;
            }
            else {
                if (left < j) { s++; stack[s].l = left; stack[s].r = j; }
                left = i;
            }
        }
    }
}

// Сортировка выбором
void selectionSort(Car cars[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (cars[j].year < cars[minIndex].year) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Car temp = cars[i];
            cars[i] = cars[minIndex];
            cars[minIndex] = temp;
        }
    }
}

int main() {
    FILE* file = fopen("cars.bin", "rb");
    if (file == NULL) {
        cerr << "Ошибка открытия файла 'cars.bin'\n";
        return 1;
    }

    Car cars[100];
    int car_count = 0;

    while (true) {
        char brand_buf[30] = {};
        short year, max_speed;
        float engine;

        size_t read_brand = fread(brand_buf, sizeof(char), 30, file);
        size_t read_year = fread(&year, sizeof(short), 1, file);
        size_t read_engine = fread(&engine, sizeof(float), 1, file);
        size_t read_speed = fread(&max_speed, sizeof(short), 1, file);

        // Если что-то не прочиталось полностью — значит конец файла или ошибка
        if (read_brand != 30 || read_year != 1 || read_engine != 1 || read_speed != 1)
            break;

        // Сохраняем в структуру
        strncpy(cars[car_count].brand, brand_buf, 30);
        cars[car_count].brand[30] = '\0'; // защита от переполнения
        cars[car_count].year = year;
        cars[car_count].engine = engine;
        cars[car_count].max_speed = max_speed;
        car_count++;
    }

    fclose(file);

    // Быстрая сортировка
    ..quickSortNonRecursive(cars, car_count);
    cout << "Sorted QuickSort:\n";
    for (int i = 0; i < car_count; i++) {
        cout << cars[i].brand << " " << cars[i].year << " " << cars[i].engine << " " << cars[i].max_speed << "\n";
    }

    // Сортировка выбором
    selectionSort(cars, car_count);
    cout << "\nSorted Selection Sort:\n";
    for (int i = 0; i < car_count; i++) {
        cout << cars[i].brand << " " << cars[i].year << " " << cars[i].engine << " " << cars[i].max_speed << "\n";
    }

    return 0;
}

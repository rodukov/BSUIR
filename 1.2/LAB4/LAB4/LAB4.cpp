#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_N = 100;

struct Car {
    char brand[20];
    int year;
    double volume;
    int speed;
};

// Линейный поиск с барьером
int linearSearchWithBarrier(Car arr[], int n, int key) {
    Car temp;
    strcpy(temp.brand, "TEMP");
    temp.year = key;
    temp.volume = 0;
    temp.speed = 0;

    arr[n] = temp; // Барьер

    int i = 0;
    while (arr[i].year != key) {
        i++;
    }

    if (i == n)
        return -1;
    return i;
}

// Сравнение для сортировки по году
void sortByYear(Car arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].year > arr[j].year) {
                Car tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

// Двоичный поиск
int binarySearch(Car arr[], int n, int key) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid].year == key)
            return mid;
        else if (arr[mid].year < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main() {
    Car cars[MAX_N + 1]; // +1 для барьера
    int n = 0;

    FILE* f = fopen("index.txt", "r");
    if (!f) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    while (fscanf(f, "%s %d %lf %d", cars[n].brand, &cars[n].year, &cars[n].volume, &cars[n].speed) == 4) {
        n++;
    }
    fclose(f);

    int keyYear = 1996;

    // --- Линейный поиск с барьером ---
    int index1 = linearSearchWithBarrier(cars, n, keyYear);
    if (index1 != -1) {
        printf("Linear barrier: %s %d %.1lf %d km/h\n",
            cars[index1].brand, cars[index1].year, cars[index1].volume, cars[index1].speed);
    }
    else {
        printf("Linear barrier not found\n");
    }

    // --- Двоичный поиск ---
    sortByYear(cars, n); // Сортируем перед бинарным поиском
    int index2 = binarySearch(cars, n, keyYear);
    if (index2 != -1) {
        printf("Binary search: %s %d %.1lf %d km/h\n",
            cars[index2].brand, cars[index2].year, cars[index2].volume, cars[index2].speed);
    }
    else {
        printf("Binary search not found\n");
    }

    return 0;
}

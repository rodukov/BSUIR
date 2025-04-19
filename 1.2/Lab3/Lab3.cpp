#include <iostream>
#include <cstring>

using namespace std;

struct Car {
    char brand[50];
    int year;
    float engine;
    int max_speed;
};

void quickSortNonRecursive(Car cars[], int n) {
    int stack[100];
    int top = -1;
    stack[++top] = 0;
    stack[++top] = n - 1;

    while (top >= 0) {
        int high = stack[top--];
        int low = stack[top--];

        int pivot = cars[high].year; // опорный элемент
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (cars[j].year <= pivot) {
                i++;

                Car temp = cars[i];
                cars[i] = cars[j];
                cars[j] = temp;
            }
        }

        Car temp = cars[i + 1];
        cars[i + 1] = cars[high];
        cars[high] = temp;
        int pi = i + 1; // новая позиция

        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
}

void selectionSort(Car cars[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) { // Ищем минимальный элемент в оставшейся части массива
            if (cars[j].year < cars[minIndex].year) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            // меняем местами
            Car temp = cars[i];
            cars[i] = cars[minIndex];
            cars[minIndex] = temp;
        }
    }
}

int main() {
    FILE* file = fopen("index.txt", "r");
    if (file == NULL) {
        cerr << "Error opening file.\n";
        return 1;
    }

    Car cars[100];
    int car_count = 0;
    char line[200];

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %d %f %d", cars[car_count].brand, &cars[car_count].year, &cars[car_count].engine, &cars[car_count].max_speed);
        car_count++;
    }

    fclose(file);

    // Сортировка методом QuickSort (нерекурсивный)
    quickSortNonRecursive(cars, car_count);
    cout << "Sorted by Non-Recursive QuickSort:\n";
    for (int i = 0; i < car_count; i++) {
        cout << cars[i].brand << " " << cars[i].year << " " << cars[i].engine << " " << cars[i].max_speed << "\n";
    }

    // Сортировка методом Selection Sort
    selectionSort(cars, car_count);
    cout << "\nSorted by Selection Sort:\n";
    for (int i = 0; i < car_count; i++) {
        cout << cars[i].brand << " " << cars[i].year << " " << cars[i].engine << " " << cars[i].max_speed << "\n";
    }

    return 0;
}

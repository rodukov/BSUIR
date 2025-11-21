#include <iostream>
#include <cstring>

using namespace std;

struct Car {
    char brand[50];
    int year;
    float engine;
    int max_speed;
};

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

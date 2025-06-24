#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct Car {
    char brand[50];
    int year;
    float engine;
    int max_speed;
};

void createBinaryFile(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == nullptr) {
        cout << "Error creating file!" << endl;
        return;
    }
    cout << "FILE IS CREATED!" << endl;
    fclose(file);
}

void writeDataToFile(const char* filename, Car* cars, int n) {
    FILE* file = fopen(filename, "wb");
    if (file == nullptr) {
        cout << "Error opening file!" << endl;
        return;
    }
    fwrite(cars, sizeof(Car), n, file);
    fclose(file);
}

void readDataFromFile(const char* filename, Car* cars, int& n) {
    FILE* file = fopen(filename, "rb");
    if (file == nullptr) {
        cout << "Error opening file!" << endl;
        return;
    }
    n = 0;
    while (fread(&cars[n], sizeof(Car), 1, file) == 1) {
        ++n;
    }
    fclose(file);
}

void displayCars(Car* cars, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (cars[j].max_speed < cars[j + 1].max_speed) {
                Car temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (cars[i].year > 2005) {
            cout << "{ " << cars[i].brand << ", ";
            cout << cars[i].year << ", ";
            cout << cars[i].engine << ", ";
            cout << cars[i].max_speed << " }" << endl;
        }
    }

    // for (int i = 0; i < n; ++i) {
    //     cout << "{ " << cars[i].brand << ", " << cars[i].year << ", "
    //         << cars[i].engine << "L, " << cars[i].max_speed << " km/h }" << endl;
    // }
}

void writeResultsToTextFile(const char* textFilename, Car* cars, int n) {
    FILE* file = fopen(textFilename, "w");
    if (file == nullptr) {
        cout << "Error opening file!" << endl;
        return;
    }
    for (int i = 0; i < n; ++i) {
        fprintf(file, "{ %s, %d, %.1fL, %d km/h }\n", cars[i].brand, cars[i].year, cars[i].engine, cars[i].max_speed);
    }
    fclose(file);
}

void menu() {
    const char* binaryFilename = "cars.dat";
    const char* textFilename = "cars.txt";
    Car cars[100];
    int n = 0;
    int choice;



    do {
        cout << "Menu:\n";
        cout << "1. Create binary file\n";
        cout << "2. Write data to file\n";
        cout << "3. Read data from file\n";
        cout << "4. Display cars\n";
        cout << "5. Write results to text file\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createBinaryFile(binaryFilename);
            break;
        case 2:
            cout << "Enter number of cars: ";
            cin >> n;
            for (int i = 0; i < n; ++i) {
                cout << "Enter brand, year, engine capacity and max speed for car " << i + 1 << ":\n";
                cin >> cars[i].brand >> cars[i].year >> cars[i].engine >> cars[i].max_speed;
            }
            writeDataToFile(binaryFilename, cars, n);
            break;
        case 3:
            readDataFromFile(binaryFilename, cars, n);
            break;
        case 4:
            displayCars(cars, n);
            break;
        case 5:
            writeResultsToTextFile(textFilename, cars, n);
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}

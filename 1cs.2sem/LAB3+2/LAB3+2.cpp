#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main() {
    FILE* file = fopen("cars.bin", "wb");
    if (!file) {
        cerr << "error\n";
        return 1;
    }

    // Структура для хранения временных данных
    struct {
        const char* brand;
        short year;
        float engine;
        short max_speed;
    } cars[] = {
        {"BMW", 1996, 3.4f, 240},
        {"Toyota", 1996, 2.1f, 270},
        {"Lada", 2020, 3.1f, 210},
        {"Volvo", 2011, 4.5f, 320}
    };

    int car_count = sizeof(cars) / sizeof(cars[0]);

    for (int i = 0; i < car_count; i++) {
        char brand_buf[30] = {};  // 30 байт
        strncpy(brand_buf, cars[i].brand, 29); // Копируем название марки
        fwrite(brand_buf, sizeof(char), 30, file);
        fwrite(&cars[i].year, sizeof(short), 1, file);
        fwrite(&cars[i].engine, sizeof(float), 1, file);
        fwrite(&cars[i].max_speed, sizeof(short), 1, file);
    }

    fclose(file);
    cout << "created 'cars.bin'\n";

    return 0;
}
 
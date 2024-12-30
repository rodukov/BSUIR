#include <iostream>
#include <cstring>

using namespace std;

/*

Имеется список автомобилей. Каждый элемент списка содержит сле-
дующую информацию: марка, год выпуска, объем двигателя и максимальная
скорость. Вывести информацию об автомобилях, выпущенных после 2005 года
в порядке убывания их максимальной скорости.

*/
struct Car {
    char brand[50];
    int year;
    float engine;
    int max_speed;
};

int main() {
    cout << sizeof(Car) << endl;
    int n;
    cout << "Enter the number of cars: ";
    cin >> n;

    Car* cars = new Car[n];

    for (int i = 0; i < n; ++i) {
        cout << "Enter brand, year, engine capacity, and max speed for car " << i + 1 << ":\n";
        cin >> cars[i].brand >> cars[i].year >> cars[i].engine >> cars[i].max_speed;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (cars[i].max_speed < cars[j].max_speed) {
                Car temp = cars[i];
                cars[i] = cars[j];
                cars[j ] = temp;
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

    delete[] cars;

    return 0;
}

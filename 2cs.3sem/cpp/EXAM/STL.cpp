#include <iostream>              // Подключаем библиотеку ввода-вывода
#include <vector>                // Подключаем контейнер vector
#include <map>                   // Подключаем контейнер map
#include <algorithm>             // Подключаем алгоритмы STL (sort)
using namespace std;             // Используем стандартное пространство имён

// ===== ФУНКЦИЯ РАБОТЫ С VECTOR =====
void workWithVector()
{
    vector<int> numbers = {3, 5, 7};         // Создаём контейнер vector для целых чисел

    numbers.push_back(5);        // Добавляем элементы в vector
    numbers.push_back(1);
    numbers.push_back(4);
    numbers.push_back(2);
    numbers.push_back(3);

    cout << "Vector before sort: "; // Вывод текста
    for (int x : numbers)        // Перебор элементов vector
    {
        cout << x << " ";        // Вывод каждого элемента
    }
    cout << endl;

    sort(numbers.begin(),        // ИТЕРАТОР на начало
        numbers.end());          // Конец диапазона

    cout << "Vector after sort: "; // Вывод текста
    for (int x : numbers)        // range-based for loop
    {
        cout << x << " ";
    }
    cout << endl << endl;
}

// ===== ФУНКЦИЯ РАБОТЫ С MAP =====
void workWithMap()
{
    map<string, int> students;   // Создаём map: ключ — строка, значение — int

    students["Ivan"] = 5;        // Добавляем элементы в map
    students["Anna"] = 4;
    students["Petr"] = 3;

    cout << "Students map:" << endl; // Заголовок вывода

    for (auto it = students.begin(); // Итератор на начало map
        it != students.end();       // Пока не конец контейнера
        it++)                        // Переход к следующему элементу
    {
        cout << it->first            // Вывод ключа
            << " : "
            << it->second           // Вывод значения
            << endl;
    }

    cout << endl;
}

// ===== ГЛАВНАЯ ФУНКЦИЯ =====
int main()
{
    workWithVector();             // Вызов функции работы с vector и sort
    workWithMap();                // Вызов функции работы с map

    return 0;                     // Завершение программы
}

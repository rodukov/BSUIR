/*

Создайте std::set<int> и заполните его уникальными целыми числами.
Реализуйте функцию, которая принимает значение в качестве аргумента
и использует итераторы для определения наличия этого значения в наборе.
Если значение существует, верните итератор, указывающий на него;
в противном случае верните итератор на конец набора.
Создайте новый список по аналогии и определите общие элементы
(если есть) в обоих списках.

*/

#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

// --- Функция поиска элемента с помощью итератора ---
std::set<int>::iterator findValue(std::set<int>& s, int value) {
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (*it == value)         // Разыменовываем итератор и сравниваем
            return it;            // Если нашли — возвращаем итератор
    }
    return s.end();               // Если не нашли — возвращаем end()
}

int main() {
    setlocale(LC_ALL, "russian");
    // 1. Создаём множество и заполняем уникальными числами
    std::set<int> first = { 1, 3, 5, 7, 9 };

    // 2. Поиск элемента
    int target = 5;
    auto it = findValue(first, target);
    if (it != first.end())
        std::cout << "Элемент " << target << " найден в множестве.\n";
    else
        std::cout << "Элемент " << target << " не найден.\n";

    // 3. Создаём второе множество
    std::set<int> second = { 2, 3, 5, 8, 9 };

    // 4. Находим общие элементы (пересечение)
    std::set<int> common;
    std::set_intersection(
        first.begin(), first.end(),
        second.begin(), second.end(),
        std::inserter(common, common.begin())
    );

    // 5. Вывод общих элементов
    std::cout << "Общие элементы в обоих множествах: ";
    for (auto x : common)
        std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}

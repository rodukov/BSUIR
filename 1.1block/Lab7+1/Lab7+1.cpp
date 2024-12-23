#include <stdio.h>
#include <cstring>
#include <iostream>

using namespace std;

/* ПОМЕНЯТЬ ДВА СЛОВА В СТРОКЕ, ВВЕДЕННОЙ ПОЛЬЗОВАТЕЛЕМ, ПРИ УСЛОВИИ ЕСЛИ СЛОВА ЕСТЬ В СТРОКЕ */

int main() {
    char str[256];
    char word1[32];
    char word2[32];

    cout << "Enter stroka: " << endl;
    gets_s(str);
    cout << "Enter word1: " << endl;
    gets_s(word1);
    cout << "Enter word2: " << endl;
    gets_s(word2);

    int len = strlen(str);
    int len1 = strlen(word1);
    int len2 = strlen(word2);

    // Найдем позиции слов
    char* s1 = strstr(str, word1);
    int pos1 = static_cast<int>(s1 - str);

    char* s2 = strstr(str, word2);
    int pos2 = static_cast<int>(s2 - str);

    // Проверка наличия обоих слов в строке
    if (!s1 || !s2) {
        if (!s1) {
            cout << "Word \"" << word1 << "\" not found in the string!" << endl;
        }
        if (!s2) {
            cout << "Word \"" << word2 << "\" not found in the string!" << endl;
        }
        return 1;
    }

    // Выводим начальные позиции
    cout << pos1 << "  " << pos2 << endl;

    char temp[256];
    int i = 0;

    // Копируем часть строки до первого слова
    for (; i < pos1; i++) {
        temp[i] = str[i];
    }

    // Копируем второе слово на место первого
    for (int j = 0; j < len2; j++, i++) {
        temp[i] = word2[j];
    }

    // Копируем часть строки между словами
    for (int j = pos1 + len1; j < pos2; j++, i++) {
        temp[i] = str[j];
    }

    // Копируем первое слово на место второго
    for (int j = 0; j < len1; j++, i++) {
        temp[i] = word1[j];
    }

    // Копируем оставшуюся часть строки после второго слова
    for (int j = pos2 + len2; j <= len; j++, i++) {
        temp[i] = str[j];
    }

    // Заканчиваем строку
    temp[i] = '\0';

    // Выводим результирующую строку
    cout << "Modified string: " << temp << endl;

    return 0;
}

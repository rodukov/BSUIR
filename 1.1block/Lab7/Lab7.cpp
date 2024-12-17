#include <iostream>
#include <cstring>

using namespace std;

/*
ПОМЕНЯТЬ МЕСТАМИ ДВА СЛОВА ВВЕДЕННЫЕ ПОЛЬЗОВАТЕЛЕМ ПРИ УСЛОВИИ ЕСЛИ ОНИ ЕСТЬ В СТРОКЕ
*/
int main() {
    char str[256];

    puts("Enter:  ");
    gets_s(str);

    int counter = 0;
    for (int i = 0; i < 256; i++) {
        if (str[i] == '\0') {
            break;
        }
        else {
            counter += 1;
        }
    }
    cout << counter;
    //int length = strlen(str);

    // for (int i = 0; i < length; i++) {
    //     if ((str[i] == 'C' && str[i + 1] == 'i') && (str[i+2] == ' ' || (str[i + 2] == '\0'))) {
    //         for (int j = length; j > i + 1; j--) {
    //             str[j + 1] = str[j];
    //         }
    //         str[i + 1] = '+';
    //         str[i + 2] = '+';
    //         length += 2;
    //         i += 2;
    //     }
    // }
    // str[length + 1] = '\0';

    // puts( str );
}
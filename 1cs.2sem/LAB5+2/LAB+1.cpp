#include <iostream>
#include <cstring>

using namespace std;

void removeShortWords(char* input, int& removedCount) {
    removedCount = 0;
    char* write = input;
    char* token = strtok(input, " ");
    bool first = true;

    while (token) {
        if (strlen(token) >= 3) {
            if (!first) *write++ = ' ';
            for (char* p = token; *p; ++p, ++write) {
                *write = *p;
            }
            *write = '\0';
            first = false;
        }
        else {
            removedCount++;
        }
        token = strtok(nullptr, " ");
    }
}

int main() {
    char input[256];

    cout << "Vvedity stroky: ";
    cin.getline(input, 256);

    int count;
    removeShortWords(input, count);

    cout << "Novaya stroka: " << input << endl;
    cout << "Udaleno slov: " << count << endl;

    return 0;
}

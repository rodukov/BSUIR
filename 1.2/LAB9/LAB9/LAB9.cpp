#include <iostream>
#include <cstring>

using namespace std;

const int M = 10; // размер хеш-таблицы

struct Entry {
    char surname[30];
    int phone;
    char address[50];
    Entry* next;
};

// Инициализация таблицы
void initTable(Entry* table[]) {
    for (int i = 0; i < M; ++i)
        table[i] = NULL;
}

// Хеш-функция: остаток от деления номера на M
int hashFunction(int key) {
    return key % M;
}

// Вставка элемента в хеш-таблицу (в начало цепочки)
void insert(Entry* table[], const Entry& value) {
    int index = hashFunction(value.phone);
    Entry* node = new Entry;
    *node = value; // заполняем пустышку нужной структурой
    node->next = table[index]; // в ней же ставим указатель на текущий элемент в хэш таблице
    table[index] = node; // потом заменяем этот текущий элемент на её
}

void printTable(Entry* table[]) {
    for (int i = 0; i < M; ++i) {
        cout << "H[" << i << "] → ";
        Entry* current = table[i];
        while (current) {
            cout << "[" << current->surname << ", " << current->phone << ", " << current->address << "] → ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
}


// Вывод исходного массива
void printArray(const Entry arr[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i].surname << ", " << arr[i].phone << ", " << arr[i].address << endl;
    }
}

// Поиск всех записей по номеру телефона
void findAll(Entry* table[], int key) {
    int index = hashFunction(key);
    Entry* current = table[index];
    bool found = false;

    while (current) {
        if (current->phone == key) {
            cout << "Found: " << current->surname << ", " << current->phone << ", " << current->address << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found)
        cout << "Not found." << endl;
}

int main() {
    const int N = 9;
    Entry data[N] = {
        {"Ivanov",    3752911, "Minsk"},
        {"Petrov",    3752933, "Gomel"},
        {"Sidorov",   3752944, "Mogilev"},
        {"Smirnov",   3752912, "Brest"},
        {"Kuznetsov", 3752955, "Vitebsk"},
        {"Popov",     3752977, "Grodno"},
        {"Sokolov",   3752900, "Minsk"},
        {"Lebedev",   3752922, "Orsha"},
        {"Kozlov",    3752922, "Bobruisk"} // Повторный номер для проверки цепочки
    };

    Entry* hashTable[M];
    initTable(hashTable);

    for (int i = 0; i < N; ++i)
        insert(hashTable, data[i]);

    cout << "Ishod:\n";
    printArray(data, N);

    cout << "\nhash:\n";
    printTable(hashTable);

    int searchKey;
    cout << "\nEnter: ";
    cin >> searchKey;

    findAll(hashTable, searchKey);

    return 0;
}

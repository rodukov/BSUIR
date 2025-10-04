#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <numeric> // для accumulate

using namespace std;

// структура песни
struct Song {
    int id;                 // уникальный идентификатор
    string title;           // название песни
    vector<double> rates;   // список оценок
};

// --- глобальные контейнеры ---
vector<Song> songs;              // список песен
map<int, Song> songMap;          // быстрый доступ по id

// --- функции ---
void addSong() {
    Song s;
    cout << "Введите ID: ";
    cin >> s.id;
    cin.ignore(); // очищаем буфер после ввода числа

    if (songMap.find(s.id) != songMap.end()) {
        cout << "Ошибка: песня с таким ID уже существует!\n";
        return;
    }

    cout << "Введите название песни: ";
    getline(cin, s.title);

    int count;
    cout << "Сколько рейтингов добавить? ";
    cin >> count;

    for (int i = 0; i < count; i++) {
        double r;
        cout << "Оценка #" << i + 1 << ": ";
        cin >> r;
        s.rates.push_back(r);
    }


    songs.push_back(s);
    songMap[s.id] = s;

    cout << "Песня добавлена!\n";
}

void showAllSongs() {
    if (songs.empty()) {
        cout << "Список песен пуст.\n";
        return;
    }
    for (auto& s : songs) {
        cout << "ID: " << s.id << " | Название: " << s.title << " | Рейтинги: ";
        for (double r : s.rates) cout << r << " ";
        cout << endl;
    }
}

void calcAverageRating() {
    int id;
    cout << "Введите ID песни: ";
    cin >> id;

    // ищем песню в map по ключу
    auto it = songMap.find(id);
    if (it == songMap.end()) {
        cout << "Песня не найдена.\n";
        return;
    }

    Song& s = it->second; // получаем ссылку на найденную песню
    if (s.rates.empty()) {
        cout << "У песни \"" << s.title << "\" нет рейтингов.\n";
        return;
    }

    double sum = accumulate(s.rates.begin(), s.rates.end(), 0.0);
    double avg = sum / s.rates.size();

    cout << "Средний рейтинг \"" << s.title << "\" = " << avg << endl;
}

// Функция поиска песни по конкретному рейтингу
void findByRating() {
    double rating;
    cout << "Введите рейтинг для поиска: ";
    cin >> rating;

    bool found = false;
    for (auto& s : songs) {
        for (double r : s.rates) {
            if (r == rating) {
                cout << "Песня: " << s.title << " (ID: " << s.id << ")\n";
                found = true;
                break;
            }
        }
    }

    if (!found) cout << "Песни с таким рейтингом нет.\n";
}

void updateSong() {
    int id;
    cout << "Введите ID песни для обновления: ";
    cin >> id;

    auto it = songMap.find(id);
    if (it == songMap.end()) {
        cout << "Песня не найдена.\n";
        return;
    }

    double r;
    cout << "Введите новый рейтинг: ";
    cin >> r;

    // обновляем и в map, и в vector
    it->second.rates.push_back(r);

    for (auto& s : songs) {
        if (s.id == id) {
            s.rates.push_back(r);
            break;
        }
    }

    cout << "Рейтинг добавлен!\n";
}

int main() {
    setlocale(LC_ALL, ""); // для русского текста
    int choice;

    do {
        cout << "\n--- МЕНЮ ---\n";
        cout << "1. Добавить песню\n";
        cout << "2. Просмотреть все песни\n";
        cout << "3. Рассчитать средний рейтинг песни\n";
        cout << "4. Найти песню по рейтингу\n";
        cout << "5. Обновить информацию о песне (добавить рейтинг)\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: addSong(); break;
        case 2: showAllSongs(); break;
        case 3: calcAverageRating(); break;
        case 4: findByRating(); break;
        case 5: updateSong(); break;
        case 0: cout << "Выход...\n"; break;
        default: cout << "Неверный ввод!\n";
        }
    } while (choice != 0);

    return 0;
}

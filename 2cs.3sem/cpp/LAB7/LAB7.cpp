/*
Простое управление адресной книгой
-------------------------------------------------------------------------------
Структура данных: Определить структуру или класс Contact,
включающий поля для имени, номера телефона и адреса электронной почты.
-------------------------------------------------------------------------------
Добавить контакт: Разрешить пользователю добавлять новый контакт в адресную книгу,
что позволит добавить контактные данные в файл (например, address_book.txt).
-------------------------------------------------------------------------------
Просмотр контактов: Реализовать функцию для чтения и отображения всех контактов из файла.
Поиск контакта: разрешить пользователю искать контакт по имен
и отображать информацию о нём, если он найден.
-------------------------------------------------------------------------------
Удаление контакта: реализовать функцию удаления контакта по имени.
Это потребует считывания всех контактов в память, удаления указанного
контакта и записи обновлённого списка обратно в файл.
-------------------------------------------------------------------------------
Обработка ошибок: Убедитесь, что программа корректно обрабатывает ошибки файлов,
например, когда невозможно открыть файл адресной книги.
-------------------------------------------------------------------------------
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

struct Contact {
    std::string name;
    std::string phone;
    std::string email;
};

const std::string DB_FILENAME = "address_book.txt";

static std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

static bool iequals(const std::string& a, const std::string& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i)
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])) return false;
    return true;
}

std::vector<Contact> loadContacts() {
    std::vector<Contact> res;
    std::ifstream in(DB_FILENAME);
    if (!in) {
        // File may not exist yet — return empty list
        return res;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string name, phone, email;
        if (!std::getline(ss, name, '|')) continue;
        if (!std::getline(ss, phone, '|')) continue;
        if (!std::getline(ss, email, '|')) email = "";
        res.push_back({ trim(name), trim(phone), trim(email) });
    }
    return res;
}

bool saveContacts(const std::vector<Contact>& contacts) {
    std::ofstream out(DB_FILENAME, std::ios::trunc);
    if (!out) return false;
    for (const auto& c : contacts) {
        // Note: '|' is used as separator. Do not allow it in fields.
        out << c.name << "|" << c.phone << "|" << c.email << "\n";
        if (!out) return false;
    }
    return true;
}

void addContact() {
    Contact c;
    std::cout << "Name: "; std::getline(std::cin, c.name);
    std::cout << "Phone: "; std::getline(std::cin, c.phone);
    std::cout << "Email: "; std::getline(std::cin, c.email);

    if (c.name.find('|') != std::string::npos || c.phone.find('|') != std::string::npos || c.email.find('|') != std::string::npos) {
        std::cout << "Поле не должно содержать символ '|'\n";
        return;
    }

    std::ofstream out(DB_FILENAME, std::ios::app);
    if (!out) {
        std::cerr << "Ошибка: невозможно открыть файл для записи: " << DB_FILENAME << "\n";
        return;
    }
    out << c.name << "|" << c.phone << "|" << c.email << "\n";
    if (!out) std::cerr << "Ошибка при записи в файл.\n";
    else std::cout << "Контакт добавлен.\n";
}

void viewContacts() {
    auto list = loadContacts();
    if (list.empty()) { std::cout << "Список контактов пуст.\n"; return; }
    std::cout << "--- Контакты ---\n";
    for (size_t i = 0; i < list.size(); ++i) {
        const auto& c = list[i];
        std::cout << i + 1 << ") " << c.name << " | " << c.phone << " | " << c.email << "\n";
    }
}

void searchContact() {
    std::cout << "Введите имя для поиска: ";
    std::string query; std::getline(std::cin, query);
    if (query.empty()) { std::cout << "Пустой запрос.\n"; return; }
    auto list = loadContacts();
    bool found = false;
    for (const auto& c : list) {
        if (iequals(trim(c.name), trim(query))) {
            std::cout << "Найден: " << c.name << " | " << c.phone << " | " << c.email << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "Контакт не найден.\n";
}

void deleteContact() {
    std::cout << "Введите имя для удаления: ";
    std::string name; std::getline(std::cin, name);
    if (name.empty()) { std::cout << "Пустое имя.\n"; return; }
    auto list = loadContacts();
    std::vector<Contact> newList;
    bool removed = false;
    for (const auto& c : list) {
        if (iequals(trim(c.name), trim(name))) { removed = true; continue; }
        newList.push_back(c);
    }
    if (!removed) { std::cout << "Контакт не найден.\n"; return; }
    if (!saveContacts(newList)) {
        std::cerr << "Ошибка: не удалось сохранить изменения в файл.\n";
    }
    else std::cout << "Контакт(ы) удалён(ы).\n";
}

void printMenu() {
    std::cout << "\nАдресная книга - меню:\n";
    std::cout << "1. Добавить контакт\n";
    std::cout << "2. Просмотреть все контакты\n";
    std::cout << "3. Найти контакт по имени\n";
    std::cout << "4. Удалить контакт по имени\n";
    std::cout << "5. Выход\n";
    std::cout << "Выберите пункт: ";
}

int main() {
    setlocale(LC_ALL, "russian");
    while (true) {
        printMenu();
        std::string choice;
        std::getline(std::cin, choice);
        if (choice == "1") addContact();
        else if (choice == "2") viewContacts();
        else if (choice == "3") searchContact();
        else if (choice == "4") deleteContact();
        else if (choice == "5") { std::cout << "Выход.\n"; break; }
        else std::cout << "Неверный выбор.\n";
    }
    return 0;
}

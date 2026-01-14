#include <iostream>   // (0) Библиотека ввода-вывода
#include <string>     // (ИСПРАВЛЕНИЕ) Явное подключение string
using namespace std;

// =====================================================
// 1. БАЗОВЫЙ КЛАСС (ОБЩИЙ ИНТЕРФЕЙС)
// =====================================================
class Animal
{
protected:
    string name;
    int age;

public:
    Animal(const string& n, int a)
        : name(n), age(a) {
    }

    virtual void sound() const
    {
        cout << "Animal sound" << endl;
    }

    virtual void info() const
    {
        cout << "Name: " << name
            << ", Age: " << age
            << endl;
    }

    virtual ~Animal() {}
};


// ---------- 2.1 КЛАСС DOG ----------
class Dog : public Animal
{
private:
    string breed;

public:
    Dog(const string& n, int a, const string& b)
        : Animal(n, a),          // вызов конструктора базового класса
        breed(b) {
    }

    void sound() const override
    {
        cout << "Bark!" << endl;
    }

    void info() const override
    {
        Animal::info();
        cout << "Breed: " << breed << endl;
    }
};

// ---------- 2.2 КЛАСС CAT ----------
class Cat : public Animal
{
public:
    Cat(const string& n, int a)
        : Animal(n, a) {
    }

    void sound() const override
    {
        cout << "Meow!" << endl;
    }
};

// =====================================================
// 3. ПОЛИМОРФИЗМ И УПРАВЛЕНИЕ ОБЪЕКТАМИ
// =====================================================
class Zoo
{
private:
    Animal* animals[5];   // 3.1 Массив указателей на базовый класс
    int count;            // 3.2 Текущее количество животных

public:
    // 3.3 Конструктор Zoo
    Zoo() : count(0) {}

    // 3.4 Добавление животного (полиморфизм через указатель)
    void addAnimal(Animal* a)
    {
        if (count < 5)
            animals[count++] = a;
    }

    // 3.5 Демонстрация полиморфного поведения
    void showZoo() const
    {
        for (int i = 0; i < count; i++)
        {
            animals[i]->info();   // вызывается версия реального объекта
            animals[i]->sound();  // динамическое связывание
            cout << endl;
        }
    }

    // 3.6 Деструктор — освобождение памяти
    ~Zoo()
    {
        for (int i = 0; i < count; i++)
        {
            delete animals[i];
        }
    }
};

// =====================================================
// 4. ТОЧКА ВХОДА В ПРОГРАММУ
// =====================================================
int main()
{
    Zoo zoo;

    zoo.addAnimal(new Dog("Sharik", 12, "Gold Retriver"));
    zoo.addAnimal(new Cat("Murzik", 3));
    zoo.addAnimal(new Cat("Barsik", 5));

    zoo.showZoo();

    return 0;
}

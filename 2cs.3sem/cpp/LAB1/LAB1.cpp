#include <iostream>
using namespace std;

// Базовый класс Animal
class Animal {
protected:
    char name[30];
    int age;

public:
    Animal(const char* n, int a) {
        if (a < 0) throw "Age cannot be negative"; // проверка возраста
        int i = 0;
        while (n[i] != '\0' && i < 29) {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0';
        age = a;
        cout << "Animal created: " << name << ", Age: " << age << endl;
    }

    virtual void makeSound() const {
        cout << "Some animal sound!" << endl;
    }

    virtual void displayInfo() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    virtual ~Animal() {}
};

// Класс Dog
class Dog : public Animal {
private:
    char breed[30];

public:
    Dog(const char* n, int a, const char* b) : Animal(n, a) {
        int i = 0;
        while (b[i] != '\0' && i < 29) {
            breed[i] = b[i];
            i++;
        }
        breed[i] = '\0';
        cout << "Dog created: " << name << ", Breed: " << breed << endl;
    }

    void makeSound() const override {
        cout << "Bark!" << endl;
    }

    void displayInfo() const override {
        Animal::displayInfo();
        cout << "Breed: " << breed << endl;
    }
};

// Класс Cat
class Cat : public Animal {
private:
    char color[20];

public:
    Cat(const char* n, int a, const char* c) : Animal(n, a) {
        int i = 0;
        while (c[i] != '\0' && i < 19) {
            color[i] = c[i];
            i++;
        }
        color[i] = '\0';
        cout << "Cat created: " << name << ", Color: " << color << endl;
    }

    void makeSound() const override {
        cout << "Meow!" << endl;
    }

    void displayInfo() const override {
        Animal::displayInfo();
        cout << "Color: " << color << endl;
    }
};

// Класс Bird
class Bird : public Animal {
private:
    char species[20];

public:
    Bird(const char* n, int a, const char* s) : Animal(n, a) {
        int i = 0;
        while (s[i] != '\0' && i < 19) {
            species[i] = s[i];
            i++;
        }
        species[i] = '\0';
        cout << "Bird created: " << name << ", Species: " << species << endl;
    }

    void makeSound() const override {
        cout << "Chirp!" << endl;
    }

    void displayInfo() const override {
        Animal::displayInfo();
        cout << "Species: " << species << endl;
    }
};

// Класс Zoo — хранит динамический массив указателей на животных
class Zoo {
private:
    Animal** animals; // массив указателей на Animal
    int capacity;     // вместимость
    int count;        // текущее количество животных

public:
    Zoo(int cap) {
        capacity = cap;
        count = 0;
        animals = new Animal * [capacity]; // выделяем массив указателей
    }

    ~Zoo() {
        // освобождаем каждое животное
        for (int i = 0; i < count; i++) {
            delete animals[i];
        }
        // освобождаем массив указателей
        delete[] animals;
        cout << "Zoo destroyed, memory freed." << endl;
    }

    void addAnimal(Animal* a) {
        if (count < capacity) {
            animals[count] = a;
            count++;
        }
        else {
            cout << "Zoo is full, cannot add more animals!" << endl;
            delete a; // важно освободить память, если не добавили
        }
    }

    void displayAll() const {
        for (int i = 0; i < count; i++) {
            animals[i]->displayInfo();
            cout << endl;
        }
    }

    void makeAllSounds() const {
        for (int i = 0; i < count; i++) {
            animals[i]->makeSound();
        }
    }
};

// Главная функция
int main() {
    try {
        Zoo zoo(5); // зоопарк на 5 животных

        zoo.addAnimal(new Dog("Buddy", 3, "Retriever"));
        zoo.addAnimal(new Cat("Whiskers", 2, "Black"));
        zoo.addAnimal(new Bird("Tweety", 1, "Canary"));

        cout << "\nAnimals in the Zoo:\n";
        zoo.displayAll();

        cout << "Animal sounds:\n";
        zoo.makeAllSounds();

    }
    catch (const char* msg) {
        cout << "Error: " << msg << endl;
    }

    return 0;
}

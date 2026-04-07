#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

/*
1. Создать программу на основе паттерна Command.
2. Команда передается агенту для исполнения.
3. Команда относится к классу А и может быть связана с созданием
объекта этого класса и выполнением какого-либо метода или
уничтожением ранее созданного объекта класса с указанным
номером.
 */

using namespace std;

// ==================== Класс A ====================
class A {
private:
    int id;          // уникальный номер объекта
    string name;     // дополнительное поле для наглядности
public:
    A(int id, const string& name) : id(id), name(name) {
        cout << "Создан объект A: id=" << id << ", name=" << name << endl;
    }

    ~A() {
        cout << "Уничтожен объект A: id=" << id << ", name=" << name << endl;
    }

    void action() const {
        cout << "Выполняется action() объекта A: id=" << id << ", name=" << name << endl;
    }

    int getId() const { return id; }
    string getName() const { return name; }
};

// ==================== Менеджер объектов A ====================
class AManager {
private:
    vector<A*> objects;  // храним указатели на созданные объекты
public:
    ~AManager() {
        for (A* obj : objects)
            delete obj;
    }

    // Создать новый объект A и добавить в список
    A* createObject(int id, const string& name) {
        A* newObj = new A(id, name);
        objects.push_back(newObj);
        return newObj;
    }

    // Удалить объект по id (если найден)
    bool deleteObject(int id) {
        auto it = find_if(objects.begin(), objects.end(),
                          [id](A* obj) { return obj->getId() == id; });
        if (it != objects.end()) {
            delete *it;
            objects.erase(it);
            return true;
        }
        return false;
    }

    // Для отладки: показать все объекты
    void showObjects() const {
        cout << "Текущие объекты A: ";
        for (auto obj : objects)
            cout << obj->getId() << "(" << obj->getName() << ") ";
        cout << endl;
    }
};

// ==================== Интерфейс команды ====================
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

// ==================== Конкретная команда: создать объект A и выполнить action() ====================
class CreateACommand : public Command {
private:
    AManager& manager;   // ссылка на менеджер
    int id;              // id создаваемого объекта
    string name;         // имя
public:
    CreateACommand(AManager& mgr, int id, const string& name)
        : manager(mgr), id(id), name(name) {}

    void execute() override {
        A* obj = manager.createObject(id, name);
        if (obj) {
            obj->action();   // после создания вызываем метод action()
        }
    }
};

// ==================== Конкретная команда: удалить объект A по номеру ====================
class DeleteACommand : public Command {
private:
    AManager& manager;
    int id;              // id удаляемого объекта
public:
    DeleteACommand(AManager& mgr, int id) : manager(mgr), id(id) {}

    void execute() override {
        bool success = manager.deleteObject(id);
        if (success) {
            cout << "Объект с id=" << id << " удалён." << endl;
        } else {
            cout << "Ошибка: объект с id=" << id << " не найден." << endl;
        }
    }
};

// ==================== Агент (инвокер) ====================
class Agent {
public:
    // Агент просто принимает команду и выполняет её
    void executeCommand(Command* cmd) {
        if (cmd) {
            cmd->execute();
        }
    }
};

// ==================== Демонстрация ====================
int main() {
    setlocale(LC_ALL, "Russian");

    AManager manager;   // хранилище объектов A
    Agent agent;        // агент, который будет выполнять команды

    // Создаём команды
    CreateACommand cmd1(manager, 1, "Alpha");
    CreateACommand cmd2(manager, 2, "Beta");
    CreateACommand cmd3(manager, 3, "Gamma");
    DeleteACommand cmdDel(manager, 2);   // удалить объект с id=2

    // Передаём команды агенту и выполняем их
    cout << "=== Выполняем команды ===" << endl;
    agent.executeCommand(&cmd1);
    agent.executeCommand(&cmd2);
    agent.executeCommand(&cmd3);
    manager.showObjects();

    cout << "\n=== Удаляем объект с id=2 ===" << endl;
    agent.executeCommand(&cmdDel);
    manager.showObjects();

    cout << "\n=== Пытаемся удалить несуществующий объект ===" << endl;
    DeleteACommand cmdDelInvalid(manager, 99);
    agent.executeCommand(&cmdDelInvalid);

    return 0;
}
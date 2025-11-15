/* Шаблон универсального класса очереди с шаблонами функций

Разработайте универсальный класс очереди,
поддерживающий различные типы данных,
и реализуйте шаблоны вспомогательных функций.

Шаблон класса: Создайте шаблон класса Queue<T>,
поддерживающий базовые операции с очередью: enqueue, dequeue и isEmpty.
Убедитесь, что очередь может динамически изменять размер при необходимости.

Шаблон функции: Реализуйте шаблон функции  printQueue,
который выводит содержимое очереди в порядке добавления.

Шаблон функции: Добавьте шаблон функции copyQueue,
который создает копию текущей очереди и возвращает её.

*/
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

template <typename T>
class Queue {
public:
    Queue() = default;

    // Добавить в конец очереди
    void enqueue(const T& value) {
        data.push_back(value);
    }

    // Удалить из начала и вернуть значение
    T dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("dequeue from empty queue");
        }
        T value = data.front();
        data.erase(data.begin());
        return value;
    }

    // Проверка пустоты
    bool isEmpty() const noexcept {
        return data.empty();
    }

    // Число элементов (удобно для печати)
    size_t size() const noexcept {
        return data.size();
    }

    // Доступ к i-му элементу в порядке добавления (0..size-1)
    const T& at_ordered(size_t i) const {
        return data.at(i);
    }

private:
    std::vector<T> data; // внутренний буфер
};

// Печать очереди в порядке добавления
template <typename T>
void printQueue(const Queue<T>& q, std::ostream& os = std::cout) {
    os << "Queue(size=" << q.size() << "): [";
    for (size_t i = 0; i < q.size(); ++i) {
        os << q.at_ordered(i);
        if (i + 1 < q.size()) os << ", ";
    }
    os << "]\n";
}

// Создать копию очереди и вернуть её
template <typename T>
Queue<T> copyQueue(const Queue<T>& q) {
    Queue<T> c;
    for (size_t i = 0; i < q.size(); ++i) {
        c.enqueue(q.at_ordered(i));
    }
    return c;
}
 
int main() {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    printQueue(q); // Queue(size=3): [1, 2, 3]

    auto q2 = copyQueue(q);
    printQueue(q2); // копия

    std::cout << "dequeue: " << q.dequeue() << "\n"; // 1
    printQueue(q); // [2, 3]

    Queue<std::string> qs;
    qs.enqueue("hello");
    qs.enqueue("world");
    printQueue(qs); // [hello, world]

    return 0;
}

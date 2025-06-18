#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* prev;
    Node* next;
};

// Создание нового узла
Node* createNode(int value) {
    Node* node = new Node;
    node->value = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Добавление в конец списка
void append(Node*& head, Node*& tail, Node* node) {
    node->prev = node->next = NULL;
    if (!head) {
        head = tail = node;
    }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

// Печать списка
void printList(Node* head) {
    Node* p = head;
    while (p) {
        cout << p->value << " ";
        p = p->next;
    }
    cout << endl;
}

// Освобождение памяти
void freeList(Node* head) {
    Node* p = head;
    while (p) {
        Node* next = p->next;
        delete p;
        p = next;
    }
}

int main() {
    const int n = 10;
    int data[n] = { 4, 7, 12, 5, 6, 9, 8, 3, 10, 1 };

    // Исходный список
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < n; ++i) {
        append(head, tail, createNode(data[i]));
    }

    // Создание двух новых списков
    Node* evenHead = NULL;
    Node* evenTail = NULL;
    Node* oddHead = NULL;
    Node* oddTail = NULL;

    // Перенос узлов без копирования значений
    Node* p = head;
    while (p) {
        Node* next = p->next;

        // Отключаем текущий узел от исходного списка
        p->prev = p->next = NULL;

        if (p->value % 2 == 0) {
            append(evenHead, evenTail, p);
        }
        else {
            append(oddHead, oddTail, p);
        }

        p = next;
    }

    // Исходный список теперь пуст
    head = tail = NULL;

    // Вывод результатов
    cout << "Chentie chisla: ";
    printList(evenHead);

    cout << "Nechetnie chisla: ";
    printList(oddHead);

    // Освобождение памяти
    freeList(evenHead);
    freeList(oddHead);

    return 0;
}

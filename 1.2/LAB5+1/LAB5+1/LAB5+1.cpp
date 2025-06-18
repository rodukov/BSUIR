#include <iostream>
using namespace std;

// Структура одного элемента стека
struct tlist {
    int inf;
    tlist* a;
};

// Добавление элемента в стек (в вершину)
tlist* AddStack(tlist* sp, int inf) {
    tlist* spt = new tlist;
    spt->inf = inf;
    spt->a = sp;
    return spt;
}

// Вывод стека
void PrintStack(tlist* sp) {
    cout << "Stack: ";
    while (sp != NULL) {
        cout << sp->inf << " ";
        sp = sp->a;
    }
    cout << endl;
}

// Полное удаление стека
tlist* DelStackAll(tlist* sp) {
    tlist* spt;
    while (sp != NULL) {
        spt = sp;
        sp = sp->a;
        delete spt;
    }
    return NULL;
}

void SwapThirdAndSixth(tlist*& head) {
    // Проверяем, что минимум 6 элементов
    tlist* p = head;
    for (int i = 0; i < 5; ++i) {
        if (!p) return;
        p = p->a;
    }

    // Найти 2-й элемент (перед 3-м)
    p = head;
    for (int i = 0; i < 1; ++i) p = p->a; // p - 2-й элемент

    tlist* q = p->a; // q - 3-й

    // Найти 5-й элемент (перед 6-м)
    for (int i = 0; i < 3; ++i) p = p->a; // p - 5-й

    // p - сейчас 5-й элемент
    // q - 3-й элемент

    // 2-й -> 6-й
    head->a->a = p->a;

    // 6-й -> 4-й
    p->a->a = q->a;

    // 5-й -> 3-й
    p->a = q;

    // 3-й -> после 6-го (оставим как есть)
    q->a = nullptr;  // или q->a = p->a->a (если не хотим потерять дальше)
}



// Главная функция
int main() {
    tlist* sp = NULL;
    int n = 6;

    cout << "Enter 6 integers:\n";
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        sp = AddStack(sp, x); // добавление в вершину
    }

    cout << "Original stack:\n";
    PrintStack(sp);

    // Переставляем 3-й и 6-й элементы
    SwapThirdAndSixth(sp);

    cout << "After swapping 3rd and 6th elements:\n";
    PrintStack(sp);

    sp = DelStackAll(sp);
    return 0;
}

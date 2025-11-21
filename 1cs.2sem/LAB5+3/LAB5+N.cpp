#include <iostream>
using namespace std;

struct tlist {
    int inf;
    tlist* a;
};

// Добавление нового элемента в стек (в вершину)
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

// Обмен второго и предпоследнего узлов (без перемещения значений)
void SwapSecondAndBeforeLast(tlist*& sp) {
    if (!sp || !sp->a || !sp->a->a || !sp->a->a->a) return;

    // Указатели на нужные позиции
    tlist* first = sp;
    tlist* second = sp->a; // второй

    tlist* p = sp;
    while (p->a->a->a != NULL) {
        p = p->a; // это предпредпоследи
    }

    tlist* beforeLast = p->a;
    tlist* last = beforeLast->a; // последний

    // Переставляем узлы (second <-> beforeLast)
    first->a = beforeLast;
    p->a = second;
    // ОБМЕН СВЯЗЯМИ
    tlist* temp = beforeLast->a;
    beforeLast->a = second->a;
    second->a = temp;
}

// Очистка памяти
tlist* DelStackAll(tlist* sp) {
    tlist* spt;
    while (sp != NULL) {
        spt = sp;
        sp = sp->a;
        delete spt;
    }
    return NULL;
}

int main() {
    tlist* sp = NULL;
    int n;

    cout << "Enter the number of elements in the stack: ";
    cin >> n;

    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        sp = AddStack(sp, x);
    }

    cout << "Original stack:\n";
    PrintStack(sp);

    SwapSecondAndBeforeLast(sp);

    cout << "After swapping second and before-last elements:\n";
    PrintStack(sp);

    sp = DelStackAll(sp);

    return 0;
}

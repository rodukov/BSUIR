#include <iostream>
using namespace std;

// Структура одного элемента стека
struct tlist {
    int inf;     // информационная часть (целое число)
    tlist* a;    // указатель на следующий элемент (адресная часть)
};

// Функция добавления элемента в стек (в вершину)
tlist* AddStack(tlist* sp, int inf) {
    // Выделяем память под новый элемент
    tlist* spt = new tlist;
    spt->inf = inf; // сохраняем значение
    spt->a = sp;    // новый элемент указывает на прежнюю вершину
    return spt;     // возвращаем новую вершину
}

// Функция вывода стека на экран
void PrintStack(tlist* sp) {
    cout << "Stack: ";
    // Пока указатель не достигнет конца (NULL), выводим элементы
    while (sp != NULL) {
        cout << sp->inf << " ";
        sp = sp->a; // переходим к следующему элементу
    }
    cout << endl;
}

// Обмен значениями между вторым и предпоследним элементами
void SwapSecondAndBeforeLast(tlist* sp) {
    // Проверка: если в стеке меньше 4 элементов, делать нечего
    if (!sp || !sp->a || !sp->a->a || !sp->a->a->a) return;

    tlist* second = sp->a; // указательь второй элемент (после вершины)

    // Поиск элемента, перед которым находится предпоследний
    tlist* p = sp;
    while (p->a->a->a != NULL) {
        p = p->a;
    }
    tlist* beforeLast = p->a; // предпоследний элемент

    // Обмен значениями (информационными частями)
    int temp = second->inf;
    second->inf = beforeLast->inf;
    beforeLast->inf = temp;
}

// Функция полного удаления стека и освобождения памяти
tlist* DelStackAll(tlist* sp) {
    tlist* spt;
    // Пока стек не пуст, удаляем элементы один за другим
    while (sp != NULL) {
        spt = sp;       // сохраняем текущий элемент
        sp = sp->a;     // переходим к следующему
        delete spt;     // освобождаем память
    }
    return NULL; // возвращаем пустой стек
}

// Главная функция
int main() {
    tlist* sp = NULL; // указатель на вершину стека
    int n;

    cout << "Enter the number of elements in the stack: ";
    cin >> n;

    cout << "Enter " << n << " integers:\n";
    // Чтение n чисел и добавление их в стек
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        sp = AddStack(sp, x);
    }

    cout << "Original stack:\n";
    PrintStack(sp);

    // Обмен второго и предпоследнего элемента
    SwapSecondAndBeforeLast(sp);

    cout << "After swapping second and before-last elements:\n";
    PrintStack(sp);

    // Удаление всех элементов и очистка памяти
    sp = DelStackAll(sp);

    return 0;
}

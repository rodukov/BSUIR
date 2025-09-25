#include <iostream>
#include <cmath>
#include <cstring>
#include <cctype>

using namespace std;

const int MAX = 100;

struct Stack {
    double data[MAX];
    int top;
};

void init(Stack& s) {
    s.top = -1;
}

void push(Stack& s, double value) {
    s.data[++s.top] = value;
}

double pop(Stack& s) {
    return s.data[s.top--];
}

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

double applyOperator(char op, double a, double b) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    case '^': return pow(a, b);
    default: return 0;
    }
}

// Заменить символ переменной на значение
double getValue(char var, double x, double y, double a, double b, double w, double c) {
    switch (var) {
    case 'x': return x;
    case 'y': return y;
    case 'a': return a;
    case 'b': return b;
    case 'w': return w;
    case 'c': return c;
    default: return 0;
    }
}

int main() {
    // Обратная польская запись выражения: x y a + * y b w ^ + / c -
    const char* rpn = "x y a + * y b w ^ + / c -";

    double x, y, a, b, w, c;

    // Ввод значений переменных
    cout << "Enter variables\n";
    cout << "x = "; cin >> x;
    cout << "y = "; cin >> y;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "w = "; cin >> w;
    cout << "c = "; cin >> c;

    Stack s;
    init(s);

    int i = 0;
    while (rpn[i]) {
        if (isspace(rpn[i])) {
            ++i;
            continue;
        }

        if (isalpha(rpn[i])) {
            double val = getValue(rpn[i], x, y, a, b, w, c);
            push(s, val);
            ++i;
        }
        else if (isOperator(rpn[i])) {
            double b = pop(s);
            double a = pop(s);
            double res = applyOperator(rpn[i], a, b);
            push(s, res);
            ++i;
        }
        else {
            ++i; // пропуск любых прочих символов
        }
    }

    double result = pop(s);
    cout << "\nResult: " << result << endl;

    return 0;
}

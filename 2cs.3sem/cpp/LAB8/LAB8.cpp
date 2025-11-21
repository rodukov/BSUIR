/*
* Тема: Рисование фигур
*
* Цель:       Нарисовать простые геометрические фигуры в окне.
* Инструкции: Создать окно, рисующее различные фигуры (например, прямоугольники, круги и треугольники).
*             Предоставить пользователю возможность менять цвет фигур нажатием разных клавиш клавиатуры (например, R — красный, G — зелёный, B — синий).
*             Реализовать функцию случайного изменения размера фигур при каждом нажатии определённой клавиши.
*/

#include <windows.h>
#include <cstdlib>
#include <ctime>

// Глобальные переменные для хранения текущего состояния приложения
COLORREF currentColor = RGB(255, 0, 0);  // Текущий цвет фигур (красный по умолчанию)
int rectSize = 100;                       // Размер прямоугольника
int circleRadius = 50;                    // Радиус круга
int triangleSize = 80;                    // Размер треугольника

// Прототип оконной процедуры (обязателен для WinAPI)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Функция для рисования всех фигур
void DrawShapes(HDC hdc, RECT clientRect)
{
    // Вычисляем центр клиентской области окна
    int cx = (clientRect.right - clientRect.left) / 2;
    int cy = (clientRect.bottom - clientRect.top) / 2;

    // Создаем кисть с текущим цветом
    HBRUSH brush = CreateSolidBrush(currentColor);
    SelectObject(hdc, brush);

    // Рисуем прямоугольник (в верхней части окна)
    Rectangle(hdc, cx - rectSize, cy - rectSize - 100, cx + rectSize, cy + rectSize - 100);

    // Рисуем круг (в центральной части окна)
    Ellipse(hdc, cx - circleRadius, cy - circleRadius + 50, cx + circleRadius, cy + circleRadius + 50);

    // Рисуем треугольник (в нижней части окна)
    POINT triangle[3] = {
        {cx, cy + 150 - triangleSize},                    // Верхняя вершина
        {cx - triangleSize, cy + 150 + triangleSize},     // Левая нижняя вершина
        {cx + triangleSize, cy + 150 + triangleSize}      // Правая нижняя вершина
    };
    Polygon(hdc, triangle, 3);

    // Удаляем созданную кисть (освобождаем ресурсы GDI)
    DeleteObject(brush);
}

// Точка входа WinAPI приложения (аналог main() для оконных приложений)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    // Имя класса окна (должно быть уникальным для приложения)
    const wchar_t CLASS_NAME[] = L"ShapesWindowClass";

    // Заполняем структуру WNDCLASS для регистрации класса окна
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;        // Указатель на оконную процедуру
    wc.hInstance = hInstance;           // Экземпляр приложения
    wc.lpszClassName = CLASS_NAME;      // Имя класса окна
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // Цвет фона окна

    // Регистрируем класс окна в системе
    RegisterClass(&wc);

    // Создаем главное окно приложения
    HWND hwnd = CreateWindowEx(
        0,                              // Расширенные стили окна
        CLASS_NAME,                     // Имя класса окна
        L"Рисование фигур — Вариант 1", // Заголовок окна
        WS_OVERLAPPEDWINDOW,            // Стиль окна (стандартное перекрывающееся окно)
        CW_USEDEFAULT, CW_USEDEFAULT,   // Позиция окна (по умолчанию)
        800, 600,                       // Размер окна (ширина x высота)
        NULL, NULL,                     // Родительское окно и меню
        hInstance,                      // Экземпляр приложения
        NULL                            // Дополнительные параметры
    );

    // Проверяем успешность создания окна
    if (!hwnd)
        return 0;

    // Показываем окно на экране
    ShowWindow(hwnd, nCmdShow);

    // Основной цикл обработки сообщений
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);  // Преобразование сообщений клавиатуры
        DispatchMessage(&msg);   // Передача сообщения в оконную процедуру
    }

    return 0;
}

// Дополнительная точка входа для поддержки консольной компиляции
int main()
{
    return WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOW);
}

// Оконная процедура - обрабатывает все сообщения, отправляемые окну
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static RECT clientRect;  // Статическая переменная для хранения размеров клиентской области

    switch (uMsg)
    {
        // Сообщение WM_CREATE отправляется при создании окна
    case WM_CREATE:
        srand((unsigned)time(NULL));  // Инициализация генератора случайных чисел
        GetClientRect(hwnd, &clientRect);  // Получаем размеры клиентской области
        return 0;

        // Сообщение WM_KEYDOWN отправляется при нажатии клавиши
    case WM_KEYDOWN:
        switch (wParam)
        {
        case 'R':  // Клавиша R - красный цвет
            currentColor = RGB(255, 0, 0);
            break;
        case 'G':  // Клавиша G - зеленый цвет
            currentColor = RGB(0, 255, 0);
            break;
        case 'B':  // Клавиша B - синий цвет
            currentColor = RGB(0, 0, 255);
            break;
        case 'S':  // Клавиша S - случайный размер фигур
            rectSize = 50 + rand() % 150;        // Случайный размер прямоугольника: 50-200
            circleRadius = 30 + rand() % 100;    // Случайный радиус круга: 30-130
            triangleSize = 40 + rand() % 120;    // Случайный размер треугольника: 40-160
            break;
        }
        // Запрашиваем перерисовку окна
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

        // Сообщение WM_PAINT отправляется когда нужно перерисовать окно
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        // Получаем контекст устройства для рисования
        HDC hdc = BeginPaint(hwnd, &ps);
        // Рисуем все фигуры
        DrawShapes(hdc, clientRect);
        // Завершаем рисование
        EndPaint(hwnd, &ps);
        return 0;
    }

    // Сообщение WM_SIZE отправляется при изменении размера окна
    case WM_SIZE:
        GetClientRect(hwnd, &clientRect);  // Обновляем размеры клиентской области
        return 0;

        // Сообщение WM_DESTROY отправляется при уничтожении окна
    case WM_DESTROY:
        PostQuitMessage(0);  // Помещаем сообщение WM_QUIT в очередь сообщений
        return 0;
    }

    // Обрабатываем все остальные сообщения стандартной процедурой по умолчанию
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
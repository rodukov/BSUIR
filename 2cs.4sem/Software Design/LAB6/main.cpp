// Лабораторная работа №6: Паттерн Фасад (Вариант 4)
// Цель: скрыть сложность вычисления площади и формул периметра за простым интерфейсом фасада.
// Классы Circle и Triangle не видны клиенту – вся работа идёт через FigureFacade.

#include <iostream>
#include <cmath>
#include <string>

// 1. Абстрактный базовый класс "Фигура"
// Содержит чисто виртуальные методы, которые будут реализованы в конкретных фигурах.
class Figure {
public:
    virtual double area() const = 0;                // площадь фигуры
    virtual std::string perimeterFormula() const = 0; // формула для периметра
    virtual ~Figure() = default;
};

// 2. Конкретный класс "Круг"
class Circle : public Figure {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return M_PI * radius * radius;   // πR²
    }

    std::string perimeterFormula() const override {
        return "2 * π * R";              // формула длины окружности
    }
};

// 3. Конкретный класс "Треугольник" (по трём сторонам)
class Triangle : public Figure {
private:
    double a, b, c;
    bool isValid() const {
        return (a + b > c) && (a + c > b) && (b + c > a);
    }
public:
    Triangle(double side1, double side2, double side3)
        : a(side1), b(side2), c(side3) {}

    double area() const override {
        if (!isValid()) return 0.0;      // невалидный треугольник
        double p = (a + b + c) / 2.0;    // полупериметр
        return std::sqrt(p * (p - a) * (p - b) * (p - c)); // формула Герона
    }

    std::string perimeterFormula() const override {
        return "a + b + c";
    }

    bool valid() const { return isValid(); }
};

// 4. Фасад – скрывает внутренние классы и даёт простые методы для клиента
class FigureFacade {
public:
    // --- Методы для круга ---
    void printCircleArea(double radius) {
        Circle c(radius);
        std::cout << "Площадь круга (R = " << radius << "): " << c.area() << std::endl;
    }

    void printCirclePerimeterFormula() {
        Circle c(1.0); // радиус не важен, формула одинакова
        std::cout << "Формула периметра круга: " << c.perimeterFormula() << std::endl;
    }

    // --- Методы для треугольника ---
    void printTriangleArea(double a, double b, double c) {
        Triangle t(a, b, c);
        if (!t.valid()) {
            std::cout << "Ошибка: треугольник со сторонами " << a << ", " << b << ", " << c << " не существует!" << std::endl;
            return;
        }
        std::cout << "Площадь треугольника (стороны " << a << ", " << b << ", " << c << "): " << t.area() << std::endl;
    }

    void printTrianglePerimeterFormula() {
        Triangle t(1,1,1); // формула не зависит от сторон
        std::cout << "Формула периметра треугольника: " << t.perimeterFormula() << std::endl;
    }
};

// 5. Демонстрация работы фасада
int main() {
    FigureFacade facade;   // создаём фасад

    // Работа с кругом
    facade.printCirclePerimeterFormula();
    facade.printCircleArea(5.0);
    facade.printCircleArea(2.5);

    std::cout << "\n---\n";

    // Работа с треугольником
    facade.printTrianglePerimeterFormula();
    facade.printTriangleArea(3, 4, 5);    // прямоугольный треугольник, площадь = 6
    facade.printTriangleArea(5, 6, 7);    // произвольный
    facade.printTriangleArea(1, 1, 3);    // несуществующий треугольник

    return 0;
}
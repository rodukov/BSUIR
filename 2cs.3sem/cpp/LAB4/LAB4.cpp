#include <iostream>
#include <string>
using namespace std;

// --- Базовый класс CartItem ---
class CartItem {
protected:
    string itemName;
    double price;

public:
    CartItem(const string& name = "", double p = 0.0)
        : itemName(name), price(p) {
    }

    void setItem(const string& name, double p) {
        itemName = name;
        price = p;
    }

    string getName() const { return itemName; }
    double getPrice() const { return price; }
};

// --- Производный класс ShoppingCart ---
class ShoppingCart : public CartItem {
private:
    static int cartCount; // Статическая переменная для количества товаров
    double* prices;       // Динамический массив для цен
    int capacity;         // Вместимость массива
    int size;             // Текущее количество товаров

public:
    ShoppingCart(int cap = 10) : CartItem(), capacity(cap), size(0) {
        prices = new double[capacity];
    }

    ~ShoppingCart() {
        delete[] prices; // Освобождение памяти динамического массива
    }

    void addPrice(double p) {
        if (size < capacity) {
            prices[size++] = p;
            cartCount++; // Увеличиваем общий счетчик товаров
        }
        else {
            cout << "Корзина полна, нельзя добавить товар!\n";
        }
    }

    double totalPrice() const {
        double sum = 0;
        for (int i = 0; i < size; i++)
            sum += prices[i];
        return sum;
    }

    static int getCartCount() {
        return cartCount;
    }

    void showCart() const {
        cout << "Товары в корзине (" << size << "):\n";
        for (int i = 0; i < size; i++)
            cout << i + 1 << ". Цена: " << prices[i] << " руб.\n";
        cout << "Общая стоимость: " << totalPrice() << " руб.\n";
    }
};

// Инициализация статической переменной
int ShoppingCart::cartCount = 0;

// --- Тестирование ---
int main() {
    setlocale(LC_ALL, "");
    ShoppingCart cart(5); // Создаем корзину на 5 товаров

    cart.addPrice(100.5);
    cart.addPrice(250.0);
    cart.addPrice(79.9);

    cart.showCart();

    cout << "Общее количество товаров во всех корзинах: "
        << ShoppingCart::getCartCount() << endl;

    return 0;
}

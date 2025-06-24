#include <iostream>

using namespace std;

int recursion(int a, int b) {
    if (b == 0) return 0;

    if (b % 2 == 0)
        return 2 * recursion(a, b / 2);
    else
        return a + recursion(a, b - 1);
}

int iteration(int a, int b) {
    int result = 0;

    while (b > 0) {
        if (b % 2 == 0) {
            a = a * 2;
            b /= 2;
        }
        else {
            result += a;
            b--;
        }
    }
    return result;
}   

int main() {
    int a, b;
    cout << "Enter a, b: ";
    cin >> a >> b;

    cout << "Result (recursion) " << recursion(a, b) << endl;
    cout << "Result (iteration) " << iteration(a, b) << endl;
    return 0;
}

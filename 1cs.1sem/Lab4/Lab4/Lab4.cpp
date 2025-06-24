#include <iostream>
using namespace std;

int main() {
    int n, pos;
    cout << "Enter size: ";
    cin >> n;

    int* arr = new int[n];
    int* res = new int[n];

    cout << "Enter elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    pos = 0;
    for (int i = 0; i < n; i++) {
        
        int count = 0;
        
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count += 1;
            }
        }
        if (count == 1) {
            res[pos] = arr[i];
            pos += 1;
        }
    }

    for (int i = 0; i < pos; i++) {
        cout << res[i] << " ,";
    }

    delete []arr;
    delete []res;






}

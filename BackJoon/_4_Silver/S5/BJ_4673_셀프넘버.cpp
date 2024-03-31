#include <iostream>
using namespace std;

int func_d(int number) {
    int sum = number;

    while (number != 0) {
        sum = sum + (number % 10);
        number /= 10;
    }

    return sum;
}

int main() {
    bool check[10001]{false};
    for (int i = 1; i < 10001; i++) {
        int res = func_d(i);

        if (res < 10001) {
            check[res] = true;
        }
    }

    for (int i = 1; i < 10001; i++) {
        if (!check[i]) {
            cout << i << endl;
        }
    }
    return 0;
}
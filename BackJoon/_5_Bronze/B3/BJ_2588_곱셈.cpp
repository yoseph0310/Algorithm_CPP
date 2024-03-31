#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int a, b;
    cin >> a;
    cin >> b;

    int _h = b / 100;
    int _t = (b % 100) / 10;
    int _o = (b % 100) % 10;

    int a_mul_3 = a * _o;
    int a_mul_4 = a * _t;
    int a_mul_5 = a * _h;

    cout << a_mul_3 << endl;
    cout << a_mul_4 << endl;
    cout << a_mul_5 << endl;
    cout << a_mul_3 + a_mul_4 * 10 + a_mul_5 * 100 << endl;

    return 0;
}
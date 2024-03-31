#include <iostream>
#include <algorithm>
using namespace std;

int N;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    double sum = 0;
    double arr[1001];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    sort(arr, arr + N);

    for (int i = 0; i < N; i++) {
        sum = sum + (arr[i] / arr[N - 1]) * 100;
    }

    cout << sum / N << endl;

    return 0;
}
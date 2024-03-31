#include <iostream>
#include <stack>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, num;
    string command;
    stack<int> stack;
    int res = 0;

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> command;

        // 1. push
        if (command == "push") {
            cin >> num;
            stack.push(num);
        }

        // 2. pop
        else if (command == "pop") {
            if (stack.empty()) {
                res = -1;
                cout << res << endl;
            } else {
                res = stack.top();
                cout << res << endl;
                stack.pop();
            }
        }

        // 3. size
        else if (command == "size") {
            cout << stack.size() << endl;
        }

        // 4. empty
        else if (command == "empty") {
            if (stack.empty()) {
                res = 1;
                cout << res << endl;
            } else {
                res = 0;
                cout << res << endl;
            }
        }

        // 5. top
        else if (command == "top") {
            if (stack.empty()) {
                res = -1;
                cout << res << endl;
            } else {
                res = stack.top();
                cout << res << endl;
            }
        }
    }

    return 0;
}
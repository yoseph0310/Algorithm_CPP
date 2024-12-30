// #include <iostream>
// #include <list>
// using namespace std;

// // 클래스 어댑터: list를 상속받아서 Queue의 인터페이스를 제공
// template <typename T>
// class Queue : private list<T> {
// public:
//     // Push를 list의 push_back으로 연결
//     void Push(T value) {
//         this->push_back(value);
//     }

//     // Pop을 list의 front와 pop_front로 연결
//     T Pop() {
//         T front = this->front();
//         this->pop_front();
//         return front;
//     }
// };

// int main() {
//     Queue<int> q;
//     q.Push(10);
//     q.Push(20);
//     cout << q.Pop() << endl;   // 10 출력
//     cout << q.Pop() << endl;   // 20 출력
//     return 0;
// }

// #include <iostream>
// #include <list>
// using namespace std;

// // 객체 어댑터: list 객체를 멤버로 가지고 Queue의 인터페이스를 제공
// template <typename T>
// class Queue {
// private:
//     list<T> container;  // 내부적으로 list 사용

// public:
//     // Push를 list의 push_back으로 연결
//     void Push(T value) {
//         container.push_back(value);
//     }

//     // Pop을 list의 front와 pop_front로 연결
//     T Pop() {
//         T front = container.front();
//         container.pop_front();
//         return front;
//     }
// };

// int main() {
//     Queue<int> q;
//     q.Push(10);
//     q.Push(20);
//     cout << q.Pop() << endl;   // 10 출력
//     cout << q.Pop() << endl;   // 20 출력
//     return 0;
// }

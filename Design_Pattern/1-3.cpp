// Policy Base Design
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <tuple>
using namespace std;

template <typename InputGenerator>
class BaseBallGame {
    typedef tuple<int, int, int> INPUT;
    typedef tuple<int, int> RESULT;
    vector<pair<INPUT, RESULT>> v;
    InputGenerator generator; // Policy

public:
    BaseBallGame() { srand((unsigned)time(0)); }

    void run() 
    {
        while(1)
        {
            INPUT input = generator.generate();
            int x = get<0>(input);
            int y = get<1>(input);
            int z = get<2>(input);

            cout << "당신이 생각한 숫자는 " << x << ", " << y << ", " << z << " 인가요 ? " << endl;

            int strike = 0, ball = 0;
            cout << "strike 개수 : ";
            cin >> strike;

            if (strike == 3)
            {
                cout << "SUCCESS ! " << endl;
                break;
            }
            cout << "ball 개수 : ";
            cin >> ball;

            v.push_back(make_pair(input, RESULT(strike, ball)));
            dump();
        }
    }

    void dump() {
        printf("---------------------------------------\n");
        printf("입력값 s b\n");
        for (auto& p : v) {
            printf("%d %d %d  :  %d %d\n", get<0>(p.first), get<1>(p.first), get<2>(p.first), get<0>(p.second), get<1>(p.second));
        }
        printf("---------------------------------------\n");
    }
};

class RandomInputGenerator {
public:
    tuple<int, int, int> generate() {
        int x = 0, y = 0, z = 0;
        do {
            x = rand() % 9 + 1;
            y = rand() % 9 + 1;
            z = rand() % 9 + 1;
        } while(x == y || y == z || x == z);
        return make_tuple(x, y, z);
    }
};

int main(void)
{
    BaseBallGame<RandomInputGenerator> bbg;
    bbg.run();
}

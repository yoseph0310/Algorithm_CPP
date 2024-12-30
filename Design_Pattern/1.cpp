/**
 * 숫자 야구 게임 만들기
 * 1. 컴퓨터가 정수 3개를 사용자에게 보여주고
 * 2. 사용자로부터 strike, ball의 개수를 입력받은 후 3strike 라면 종료된다.
 * 3. 사용자로부터 입력된 결과를 분석하여 다시 3개의 정수를 구한후 1부터 반복한다.
 * 
 * 참고로, 현재 컴퓨터가 사용하는 알고리즘은 무조건 중복되지 않은 난수 3개를 보여준다.
*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <tuple>
using namespace std;

class BaseBallGame {
    typedef tuple<int, int, int> INPUT;
    typedef tuple<int, int> RESULT;
    vector<pair<INPUT, RESULT>> v;
public:
    BaseBallGame() { srand((unsigned)time(0));}

    void run() 
    {
        while(1)
        {
            // ---------------------------------------
            // 이전의 결과가 담긴 vector v를 참고하여
            // 사용자가 생각한 숫자를 예측한다.
            // 현재 구현은 무조건 랜덤이다.
            int x = 0, y = 0, z = 0;
            do {
                x = rand() % 9 + 1;
                y = rand() % 9 + 1;
                z = rand() % 9 + 1;
            } while(x == y || y == z || x == z);
            // ---------------------------------------
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
            // ---------------------------------------
            // 입력된 결과 (strike, ball) 을 기록해뒀다가
            // 다음수를 예측할때 사용한다.
            v.push_back(make_pair(INPUT(x, y, z), RESULT(strike, ball)));
            dump();
        }
    }
    void dump()
    {
        printf("---------------------------------------\n");
        printf("입력값 s b\n");
        for (auto& p : v) {
            printf("%d %d %d  :  %d %d\n", get<0>(p.first), get<1>(p.first), get<2>(p.first), get<0>(p.second), get<1>(p.second));
        }
        printf("---------------------------------------\n");
    }
};

int main(void)
{
    BaseBallGame bbg;
    bbg.run();
}
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> v(100000000);
    std::iota(v.begin(), v.end(), 1);

    long long sum = std::accumulate(v.begin(), v.end(), 0LL);

    std::cout << "단일 스레드 합계 : " << sum << std::endl;
    
    return 0;
}
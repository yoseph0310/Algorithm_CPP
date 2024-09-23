#include <iostream>
#include <vector>
#include <numeric>
#include <future>

long long partial_sum(const std::vector<int>& vec, size_t start, size_t end) {
    return std::accumulate(vec.begin() + start, vec.begin() + end, 0LL);
}

int main() {
    std::vector<int> v(100000000);
    std::iota(v.begin(), v.end(), 1);

    size_t part_size = v.size() / 4;

    // 4개의 구간을 나눠 스레드로 각각 계산
    std::future<long long> f1 = std::async(std::launch::async, partial_sum, std::ref(v), 0, part_size);
    std::future<long long> f2 = std::async(std::launch::async, partial_sum, std::ref(v), part_size, part_size * 2);
    std::future<long long> f3 = std::async(std::launch::async, partial_sum, std::ref(v), part_size * 2, part_size * 3);
    std::future<long long> f4 = std::async(std::launch::async, partial_sum, std::ref(v), part_size * 3, part_size * 4);
    
    // 모든 스레드 결과 합
    long long sum = f1.get() + f2.get() + f3.get() + f4.get();

    std::cout << "멀티 스레드 합계 : " << sum << std::endl;
    
    return 0;
}
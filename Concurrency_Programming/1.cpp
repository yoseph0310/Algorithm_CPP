#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>
using namespace std::literals;

int main()
{
    std::vector<int> v1;
    std::vector<int> v2(1000);

    for (int i = 0; i < 1000; i++) {
        v1.push_back((i+1));
    }

    std::promise<void> pm1;
    std::future<void> ft = pm1.get_future();

    std::promise<int> pm2;
    std::future<int> ft2 = pm2.get_future();

    std::thread t([&]{
        std::partial_sum(v1.begin(), v1.end(), v2.begin());
        pm1.set_value();

        int s = std::accumulate(v2.begin(), v2.end(), 0);
        pm2.set_value(s);
    });


    int ret = ft2.get();
    std::cout << "result : " << ret << std::endl;
    t.join();
}
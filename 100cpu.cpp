#include <iostream>
#include <cmath>
#include <thread>
#include <vector>


using namespace std;

int cpuu() {
        while (true) {
        double result = 0.0;
        for (int i = 0; i < 1000000; ++i) {
            result += std::sin(i) * std::cos(i);
        }
    }
    return 0;
}

int main() {
const int numThreads = std::thread::hardware_concurrency();
std::vector<std::jthread> threads;


for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(cpuu);
        std::cout << std::this_thread::get_id << endl;
    };
}

/*
int main() {
std::thread t2(cpuu);
   t2.join();


const int numThreads = std::thread::hardware_concurrency();
 std::vector<std::thread> threads;

for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(cpuu);
    }

for (auto& thread : threads) {
    thread.join();
}
}

*/
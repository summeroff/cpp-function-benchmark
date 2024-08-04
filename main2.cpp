#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <functional>

// Function to prevent compiler optimization (MSVC compatible)
template<typename T>
void do_not_optimize(T const& value) {
    volatile const T* volatile unused = &value;
    (void)unused;
}

int add(int x) { 
    return x + 1; 
}

int apply(int x, int f(int)) { 
    return f(x); 
}

int g(int x) { 
    return apply(x, add); 
}

// Function to generate random data
std::vector<int> generate_random_data(size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    std::vector<int> data(size);
    std::generate(data.begin(), data.end(), [&]() { return dis(gen); });
    return data;
}

// Benchmark function
template<typename Func>
double benchmark(Func f, const std::vector<int>& data, size_t iterations) {
    std::vector<double> times;
    times.reserve(iterations);

    for (size_t i = 0; i < iterations; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        
        long long sum = 0;
        for (int x : data) {
            sum += f(x);
            do_not_optimize(sum);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        times.push_back(elapsed.count());
    }

    // Remove outliers (top and bottom 10%)
    size_t outliers = iterations / 10;
    std::sort(times.begin(), times.end());
    times.erase(times.begin(), times.begin() + outliers);
    times.erase(times.end() - outliers, times.end());

    // Calculate mean
    double mean = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
    return mean;
}

int main() {
    const size_t data_size = 1000000;
    const size_t iterations = 10;

    std::vector<int> data = generate_random_data(data_size);

    double time_add = benchmark(add, data, iterations);
    double time_g = benchmark(g, data, iterations);

    std::cout << "Average time for add(): " << time_add << " seconds" << std::endl;
    std::cout << "Average time for g(): " << time_g << " seconds" << std::endl;
    std::cout << "Ratio (g/add): " << time_g / time_add << std::endl;

    return 0;
}
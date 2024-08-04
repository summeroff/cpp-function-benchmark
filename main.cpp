#include <iostream>
#include <chrono>

int add(int x) { 
    return x + 1; 
}

int apply(int x, int f(int)) { 
    return f(x); 
}

int g(int x) { 
    return apply(x, add); 
}

void speed_test(long long num_iterations) {
    long long sum = 0;

    // Timing direct call to add()
    auto start_add = std::chrono::high_resolution_clock::now();
    for (long long i = 0; i < num_iterations; ++i) {
        sum += add(static_cast<int>(i));
    }
    auto end_add = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_add = end_add - start_add;

    // Output the sum to prevent optimization
    std::cout << "Sum after add(): " << sum << std::endl;
    std::cout << "Time taken by add(): " << elapsed_add.count() << " seconds" << std::endl;

    // Reset sum
    sum = 0;

    // Timing call to g()
    auto start_g = std::chrono::high_resolution_clock::now();
    for (long long i = 0; i < num_iterations; ++i) {
        sum += g(static_cast<int>(i));
    }
    auto end_g = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_g = end_g - start_g;

    // Output the sum to prevent optimization
    std::cout << "Sum after g(): " << sum << std::endl;
    std::cout << "Time taken by g(): " << elapsed_g.count() << " seconds" << std::endl;
}

int main() {
    long long num_iterations = 10000000000LL; // Use long long and add LL suffix
    speed_test(num_iterations);

    return 0;
}

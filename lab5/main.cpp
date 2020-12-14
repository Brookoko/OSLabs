#include <chrono>
#include <iostream>

void original() {
    int a[10][10][10];
    int res = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                a[k][j][i]++;
            }
        }
    }
}

void optimize() {
    int a[10][10][10];
    int res = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                a[i][j][k]++;
            }
        }
    }
}

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    original();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto durationOriginal = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    auto t3 = std::chrono::high_resolution_clock::now();
    optimize();
    auto t4 = std::chrono::high_resolution_clock::now();
    auto durationOptimize = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();

    std::cout << "Original: " << durationOriginal << "\n";
    std::cout << "Optimize: " << durationOptimize << "\n";
}


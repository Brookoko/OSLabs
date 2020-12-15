#include <chrono>
#include <iostream>

void original() {
    int a[50][50][50];

    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            for (int k = 0; k < 50; k++)
            {
                a[k][j][i]++;
            }
        }
    }
}

void optimize() {
    int a[50][50][50];
    int res = 0;

    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            for (int k = 0; k < 50; k++)
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
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << "Time: " << duration << "\n";
}


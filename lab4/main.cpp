#include "Job.h"
#include "hungarian.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <limits>

void printList(const std::vector<int>& list) {
    for (auto i : list) {
        printf("%*d", 4, i);
    }
    printf("\n");
}

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (auto & row : matrix) {
        printList(row);
    }
    printf("\n");
}

std::vector<int> createNodes(int amount) {
    std::vector<int> nodes = std::vector<int>(amount);
    for (int i = 0; i < amount; ++i) {
        nodes[i] = rand() % 10 + 1;
    }
    return nodes;
}

std::vector<Job> createJobs(int amount) {
    std::vector<Job> jobs;
    std::vector<int> start_time = {0, 0, 0, 0, 0, 0};
    std::vector<int> end_time = {8, 4, 9, 6, 5, 6};
    std::vector<int> time = {3, 1, 2, 8, 2, 1};
    for (int i = 0; i < amount; ++i) {
        Job job{};
        job.startTime = 0;
        job.endTime = end_time[i];
        job.executeTime = time[i];
        jobs.push_back(job);
    }
    return jobs;
}

int sumMatrix(std::vector<std::vector<int>> matrix) {
    int sum = 0;
    for (auto & row : matrix) {
        for (int node : row) {
            sum += node;
        }
    }
    return sum;
}

std::vector<std::vector<int>> createMatrix(std::vector<int> nodes, std::vector<Job> jobs, int time) {
    std::vector<std::vector<int>> matrix;

    int max = *max_element(std::begin(nodes), std::end(nodes));
    std::vector<double> relative = std::vector<double>(nodes.size());
    for (int i = 0; i < nodes.size(); ++i) {
        relative[i] = (double) nodes[i] / max;
    }

    relative = {1.0, 0.9, 0.8, 0.7, 0.6, 0.9};

    for (auto job : jobs) {
        std::vector<int> row = std::vector<int>(relative.size());
        for (int i = 0; i < relative.size(); ++i) {
            row[i] = ceil(job.executeTime / relative[i]);
        }
        matrix.push_back(row);
    }

    printMatrix(matrix);

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            int t = jobs[i].endTime - jobs[i].startTime - time - matrix[i][j];
            matrix[i][j] = t;
        }
    }

    printMatrix(matrix);

    return matrix;
}

int main() {
    srand(time(0));

    int nodeTime = 2;
    std::vector<int> nodes = createNodes(6);
    std::vector<Job> jobs = createJobs(6);
    std::vector<std::vector<int>> matrix = createMatrix(nodes, jobs, nodeTime);
    std::vector<int> solution = findSolution(matrix);

    for (int i = 0; i < solution.size(); ++i) {
        printf("Task %d: node %d\n", i, solution[i]);
    }

    int cost = 0;
    for (int i = 0; i < solution.size(); ++i) {
        cost += matrix[i][solution[i]];
    }
    printf("Cost: %d\n", cost);

    return 0;
}

#include "Job.h"
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
    std::vector<int> nodes(amount);
    for (int i = 0; i < amount; ++i) {
        nodes[i] = 5 + rand() % 5 + 1;
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
        job.endTime = rand() % 15;
        job.executeTime = rand() % 5;
        jobs.push_back(job);
    }
    return jobs;
}

std::vector<std::vector<int>> createMatrix(std::vector<int> nodes, std::vector<Job> jobs, int time) {
    std::vector<std::vector<int>> matrix;

    int max = *max_element(std::begin(nodes), std::end(nodes));
    std::vector<double> relative(nodes.size());
    for (int i = 0; i < nodes.size(); ++i) {
        relative[i] = (double) nodes[i] / max;
    }

//    relative = {1.0, 0.9, 0.8, 0.7, 0.6, 0.9};

    for (auto job : jobs) {
        std::vector<int> row(relative.size());
        for (int i = 0; i < relative.size(); ++i) {
            row[i] = ceil(job.executeTime / relative[i]);
        }
        matrix.push_back(row);
    }

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            int t = jobs[i].endTime - jobs[i].startTime - time - matrix[i][j];
            matrix[i][j] = t;
        }
    }

    return matrix;
}

std::vector<int> findSolution(std::vector<std::vector<int>> matrix) {
    int height = matrix.size();
    int width = matrix[0].size();

    std::vector<int> u(height, 0);
    std::vector<int> v(height, 0);
    std::vector<int> marked(width, -1);

    for(int i = 0; i < height; i++) {
        std::vector<int> links(width, -1);
        std::vector<int> mins(width, std::numeric_limits<int>::max());
        std::vector<int> visited(width, 0);

        int markedI = i;
        int markedJ = -1;
        int j;
        while(markedI != -1) {
            j = -1;
            for(int k = 0; k < width; k++) {
                if(!visited[k]) {
                    int value = matrix[markedI][k] - u[markedI] - v[k];
                    if(value < mins[k]) {
                        mins[k] = value;
                        links[k] = markedJ;
                    }
                    if(j==-1 || mins[k] < mins[j]) j = k;
                }
            }

            int min = mins[j];
            for(int k = 0; k < width; k++) {
                if(visited[k]) {
                    u[marked[k]] += min;
                    v[k] -= min;
                } else {
                    mins[k] -= min;
                }
            }

            u[i] += min;

            visited[j] = 1;
            markedJ = j;
            markedI = marked[j];
        }

        for(; links[j] != -1; j = links[j]) {
            marked[j] = marked[links[j]];
        }
        marked[j] = i;
    }

    return marked;
}

int main() {
    srand(time(0));

    int nodeTime = 2;
    std::vector<int> nodes = createNodes(6);
    std::vector<Job> jobs = createJobs(6);
    std::vector<std::vector<int>> matrix = createMatrix(nodes, jobs, nodeTime);
    std::vector<int> solution = findSolution(matrix);

    printMatrix(matrix);

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

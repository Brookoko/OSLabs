
std::vector<int> findSolution(std::vector<std::vector<int>> matrix) {
    int height = matrix.size();
    int width = matrix[0].size();

    std::vector<int> u = std::vector<int>(height, 0);
    std::vector<int> v = std::vector<int>(height, 0);
    std::vector<int> marked = std::vector<int>(width, -1);

    for(int i = 0; i < height; i++) {
        std::vector<int> links = std::vector<int>(width, -1);
        std::vector<int> mins = std::vector<int>(width, std::numeric_limits<int>::max());
        std::vector<int> visited = std::vector<int>(width, 0);

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

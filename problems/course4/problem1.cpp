#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int INF = 99999;

bool checkNegativeCycle(vector<vector<int>> &graph) {
    int V = graph.size();
    for (int i = 0; i < V; i++) {
        if (graph[i][i] < 0) {
            return true;
        }
    }
    return false;
}

void floydWarshall(vector<vector<int>> &graph) {
    int V = graph.size();

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
}

int main() {
    ifstream file("inputs/course4/week1/g3.txt");
    if (!file.is_open()) {
        cout << "Error: could not open file.\n";
        return 1;
    }

    int V, E;
    file >> V >> E;
    vector<vector<int>> graph(V, vector<int>(V, INF));

    for (int i = 0; i < V; i++) graph[i][i] = 0;

    int u, v, w;
    for (int i = 0; i < E; i++) {
        file >> u >> v >> w;
        graph[u-1][v-1] = w;
    }

    floydWarshall(graph);
    if (checkNegativeCycle(graph)) {
        cout << "Graph contains a negative cycle, shortest shortest path could not be calculated" << endl;
        return 0;
    }

    cout << "The shortest shortest path is: " << endl;
    int min = INF;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] < min) {
                cout << graph[i][j] << " ";
                min = graph[i][j];
            }
        }
        cout << endl;
    }
    cout << "min: " << min << endl;
    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <algorithm>
#include <cmath>
#include <climits>
#include <sys/sysinfo.h>

using namespace std;

int N; // number of cities
pair<double, double> coords[100]; // coordinates of cities
double dist[100][100]; // distance between cities
int bestPath[100]; // best path found so far
double bestDist; // best distance found so far
mutex mtx; // for synchronizing access to bestDist and bestPath

void BFS(vector<int> basePath) {
    queue<vector<int>> q;
    vector<int> path(basePath);
    vector<int> currentBestPath;
    double currentBest = INT_MAX;
    q.push(path);

    while (!q.empty()) {
        path = q.front();
        q.pop();
        int last = path[path.size() - 1];

        if (path.size() == N) {
            // path has visited all cities
            double pathDist = 0;
            for (int i = 0; i < N - 1; i++) {
                pathDist += dist[path[i]][path[i + 1]];
            }
            pathDist += dist[path[N - 1]][basePath[0]];

            mtx.lock();
            if (pathDist < bestDist) {
                bestDist = pathDist;
                for (int i = 0; i < N; i++) {
                    bestPath[i] = path[i];
                }
            }
            mtx.unlock();
        } else {
            for (int i = 0; i < N; i++) {
                if (find(path.begin(), path.end(), i) == path.end())
                {
                    vector<int> newPath(path); // create a new vector to avoid copying the entire path
                    newPath.push_back(i);
                    double pathDist = 0;
                    for (int j = 0; j < newPath.size() - 1; j++) {
                        pathDist += dist[newPath[j]][newPath[j + 1]];
                    }
                    if(pathDist < currentBest) {
                        currentBest = pathDist;
                        currentBestPath = newPath;
                    }
                    if(pathDist < bestDist)
                        q.push(newPath);
                }
            }

        }
    }
}

vector<vector<int>> getNextSizePaths(vector<int> path) {
    vector<vector<int>> nextSizePaths;
    int last = path[path.size() - 1];
    for (int i = 0; i < N; i++) {
        if (find(path.begin(), path.end(), i) == path.end())
        {
            vector<int> newPath(path); // create a new vector to avoid copying the entire path
            newPath.push_back(i);
            nextSizePaths.push_back(newPath);
        }
    }
    return nextSizePaths;
}

vector<vector<int>> getNsizePaths(vector<int> path, int N) {
    vector<vector<int>> nSizePaths;
    queue<vector<int>> q;
    q.push(path);
    while (!q.empty()) {
        path = q.front();
        q.pop();
        int last = path[path.size() - 1];

        if (path.size() == N) {
            nSizePaths.push_back(path);
        } else {
            vector<vector<int>> nextSizePaths = getNextSizePaths(path);
            for (auto& nextSizePath : nextSizePaths) {
                q.push(nextSizePath);
            }
        }
    }
    return nSizePaths;
}

int main() {
    ifstream fin("./inputs/course4/week2/p01_xy.txt");
    fin >> N;

    cout << "Distance Matrix(0) or Coordinates(1) ?"<< endl;
    int choice;
    cin >> choice;
    if(!choice)
    {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                double d;
                fin >> d;
                dist[i][j] = d;
            }
        }
    }
    else {
        for (int i = 0; i < N; i++) {
            double x, y;
            fin >> x >> y;
            coords[i] = make_pair(x, y);
        }
        // calculate distance matrix
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int dx = coords[i].first - coords[j].first;
                int dy = coords[i].second - coords[j].second;
                dist[i][j] = sqrt(dx * dx + dy * dy);
            }
        }
    }
    bestDist = INT_MAX;

    vector<vector<int>> nSizePaths;
    vector<thread> threads;
    for (int i = 0; i < N; i++) {
        nSizePaths = getNsizePaths(vector<int>({i}), 4);
        for (auto& path : nSizePaths) {
            threads.push_back(thread(BFS, path));
        }
    }

    for (auto& thread : threads) {
        thread.join();  
    }

    cout << "Best distance: " << (int) bestDist << endl;
    cout << "Best path: ";
    for (int i = 0; i < N; i++) {
        cout << bestPath[i] + 1 << " ";
    }
    return 0;

}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <specialization_algorithms.h>
#include <utils.h>
#include <limits.h>


#define V_NUM 9

typedef std::vector<std::vector<int>> matrix_t;

matrix_t setDistanceMap(std::string path, unsigned int num_vertex)
{
    matrix_t m = matrix_t(num_vertex);
    std::ifstream file;
    file.open(path);

    std::string line;
    auto _v = std::vector<int>(num_vertex);
    if ( file.is_open() ) {
        while ( getline(file, line)) {
            auto _r = split(line, "\t");
            // print_vector<std::string>(_r);
            for(auto _c : _r)
            {
                if(scontains(_c, ","))
                {
                    auto _pair = split(_c, ",");
                    _v[std::stoi(_pair[0]) - 1] = std::stoi(_pair[1]);
                }
            }
            m[std::stoi(_r[0]) - 1] = _v;
            _v = std::vector<int>(num_vertex);
        }
    }
    file.close();
    return m;
}

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(std::vector<int> dist, bool sptSet[], int vsize)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < vsize; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// A utility function to print the constructed distance
// array
void printSolution(std::vector<int> dist, int vsize)
{
	std::cout << "Vertex \t Distance from Source" << std::endl;
	for (int i = 0; i < vsize; i++)
		std::cout << i << " \t\t\t\t" << dist[i] << std::endl;
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
std::vector<int> dijkstra(matrix_t graph, int src)
{
	std::vector<int> dist(graph.size()); // The output array. dist[i] will hold the
				// shortest
	// distance from src to i

	bool sptSet[graph.size()]; // sptSet[i] will be true if vertex i is
					// included in shortest
	// path tree or shortest distance from src to i is
	// finalized

	// Initialize all distances as INFINITE and stpSet[] as
	// false
	for (int i = 0; i < (int)graph.size(); i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < (int)graph.size() - 1; count++) {
		// Pick the minimum distance vertex from the set of
		// vertices not yet processed. u is always equal to
		// src in the first iteration.
		int u = minDistance(dist, sptSet, graph.size());

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the
		// picked vertex.
		for (int v = 0; v < (int)graph.size(); v++)

			// Update dist[v] only if is not in sptSet,
			// there is an edge from u to v, and total
			// weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v]
				&& dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array
	// printSolution(dist, graph.size());
	return dist;
}

int main()
{
    int size = 200;
	int targets[10] = {7,37,59,82,99,115,133,165,188,197};

    matrix_t graph = setDistanceMap("/mnt/c/Projetos/algorithms-specialization/inputs/course2/week2/dijkstraData.txt", size);

	/* Let us create the example graph discussed above */

	// Function call
	auto dist = dijkstra(graph, 0);
	printSolution(dist, graph.size());
	std::cout << "[ ";
	for (int i = 0; i < 10; i++)
	{
		int j = targets[i];
		std::cout << dist[j - 1] << ", ";
	}
    std::cout << "]\n";
	
	return 0;
}



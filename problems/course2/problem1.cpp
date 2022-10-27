// // C++ Implementation of Kosaraju's algorithm to print all SCCs
// #include <iostream>
// #include <list>
// #include <stack>
// #include <fstream>
// #include <vector>

#include <utils.h>
// #include <specialization_algorithms.h>
// using namespace std;


// // A recursive function to print DFS starting from v
// void DFSUtil(Spec_Graph_v1<int>* g, int v, bool visited[])
// {
// 	// Mark the current node as visited and print it
// 	visited[v] = true;
// 	cout << v << " ";

// 	// Recur for all the vertices adjacent to this vertex
// 	list<int>::iterator i;
// 	for (i = g->adj[v]->begin(); i != g->adj[v]->end(); ++i)
// 		if (!visited[*i])
// 			DFSUtil(g, *i, visited);
// }

// Spec_Graph_v1<int> getTranspose(Spec_Graph_v1<int>* og)
// {
// 	Spec_Graph_v1<int> g(og->num_vertices);
// 	for (int v = 0; v < (int)og->num_vertices; v++)
// 	{
// 		// Recur for all the vertices adjacent to this vertex
// 		list<int>::iterator i;
// 		for(i = og->adj[v]->begin(); i != og->adj[v]->end(); ++i)
// 		{
// 			g.adj[*i]->push_back(v);
// 		}
// 	}
// 	return g;
// }

// void fillOrder(Spec_Graph_v1<int>* g, int v, bool visited[], stack<int> &Stack)
// {
// 	// Mark the current node as visited and print it
// 	visited[v] = true;

// 	// Recur for all the vertices adjacent to this vertex
// 	list<int>::iterator i;
// 	for(i = g->adj[v]->begin(); i != g->adj[v]->end(); ++i)
// 		if(!visited[*i])
// 			fillOrder(g, *i, visited, Stack);

// 	// All vertices reachable from v are processed by now, push v
// 	Stack.push(v);
// }

// // The main function that finds and prints all strongly connected
// // components
// void printSCCs(Spec_Graph_v1<int>* g)
// {
// 	stack<int> Stack;

// 	// Mark all the vertices as not visited (For first DFS)
// 	bool *visited = new bool[g->num_vertices];
// 	for(int i = 0; i < (int)g->num_vertices; i++)
// 		visited[i] = false;

// 	// Fill vertices in stack according to their finishing times
// 	for(int i = 0; i < (int)g->num_vertices; i++)
// 		if(visited[i] == false)
// 			fillOrder(g, i, visited, Stack);

// 	// Create a reversed graph
// 	Spec_Graph_v1<int> gr = getTranspose(g);

// 	// Mark all the vertices as not visited (For second DFS)
// 	for(int i = 0; i < (int)g->num_vertices; i++)
// 		visited[i] = false;

// 	// Now process all vertices in order defined by Stack
// 	while (Stack.empty() == false)
// 	{
// 		// Pop a vertex from stack
// 		int v = Stack.top();
// 		Stack.pop();

// 		// Print Strongly connected component of the popped vertex
// 		if (visited[v] == false)
// 		{
// 			DFSUtil(&gr, v, visited);
// 			cout << endl;
// 		}
// 	}
// }


// Spec_Graph_v1<int>* injectVertices(std::string path, unsigned int num_vertices)
// {
//     Spec_Graph_v1<int>* g = new Spec_Graph_v1<int>((int)num_vertices);
//     std::vector<int> inputs = std::vector<int>();

//     std::ifstream file;
//     file.open(path);

//     std::string line;
// 	int __count = 0;
//     if (file.is_open()) {
//         while (getline(file, line)) {
// 			__count++;
//             auto _vs = split(line, " ");
//             g->addEdge(atoi(_vs[0].c_str()), atoi(_vs[1].c_str()));
//         }
//     }
//     file.close();
//     return g;
// }

// // Driver program to test above functions
// int main()
// {
// 	// Create a graph given in the above diagram
// 	// Graph g(875714);
// 	// g.addEdge(1, 0);
// 	// g.addEdge(0, 2);
// 	// g.addEdge(2, 1);
// 	// g.addEdge(0, 3);
// 	// g.addEdge(3, 4);
// 	Spec_Graph_v1<int>* g = injectVertices("./inputs/course2/week1/scc.txt", 875714);

// 	// cout << "Following are strongly connected components in "
// 	// 		"given graph \n";
// 	// g.printSCCs();

// 	return 0;
// }

#include <bits/stdc++.h>
using namespace std;

void addEdge(vector<int>* adj[], int s, int d) {
  adj[s]->push_back(d);
}
void addEdge(vector<vector<int>*> adj, int s, int d) {
  adj[s] = new vector<int>();
  adj[s]->push_back(d);
}

// Print the graph for debugging purposes
void printGraph(vector<int> adj[], int V) {
  for (int d = 0; d < V; ++d) {
    cout << "\n Vertex "
       << d << ":";
    for (auto x : adj[d])
      cout << "-> " << x;
    printf("\n");
  }
}

void DFS(vector<int>* adj[], int s, int V, int visited[], stack<int> &Stack) {
  visited[s] = 1;
  for (auto x : *(adj[s])) {
    if (visited[x] == 0) {
      DFS(adj, x, V, visited, Stack);
    }
  }
  Stack.push(s);
}

void DFS(vector<vector<int>*> adj, int s, int V, int visited[], stack<int> &Stack) {
  visited[s] = 1;
  for (auto x : *(adj[s])) {
    if (visited[x] == 0) {
      DFS(adj, x, V, visited, Stack);
    }
  }
  Stack.push(s);
}

int DFS2(vector<vector<int>*> adj, int s, int V, int visited[], int size) {
    visited[s] = 1;
    size = 1;
    for (auto x : *(adj[s])) {
        if (visited[x] == 0) {
            size += DFS2(adj, x, V, visited, size);
        }
    }
    return size;
}

int main() {
  int V = 3200;
  // int V = 875714;
  vector<vector<int>*> adj = vector<vector<int>*>(V); 
  vector<vector<int>*> adj2 = vector<vector<int>*>(V); 

  // to test on small test cases, load SCC_small.txt
  // and change V to 3200
  ifstream file;
  file.open("./inputs/course2/week1/scc_small.txt");

//   int a, b;
//   while (file >> a >> b) {
//       addEdge(adj, a-1, b-1);
//       addEdge(adj2, b-1, a-1);
//   }
  //printGraph(adj, V);
  //printGraph(adj2, V);

	std::string line;
	int __count = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            __count++;
            auto _vs = split(line, " ");
            addEdge(adj, atoi(_vs[0].c_str()), atoi(_vs[1].c_str()));
            addEdge(adj2, atoi(_vs[1].c_str()), atoi(_vs[0].c_str()));
        }
    }
   file.close();

  int visited[V] = {0};
  stack<int> Stack;

  for (int i = 0; i < V; i++) {
    if (visited[i] == 0) {
      DFS(adj, i, V, visited, Stack);
    }
  }

  for (int i = 0; i < V; i++) {
      visited[i] = 0;
  }

  int currsize = 0;
  priority_queue<int> pq;

  while (!Stack.empty()) {
    int s = Stack.top();
    Stack.pop();
    if (visited[s] == 0) {
        cout << "visiting node " << s << endl;
        int Size = DFS2(adj2, s, V, visited, currsize);
        if (pq.size() < 5) {
            pq.push(-1 * Size);
        } else {
            if (-1 * Size < pq.top()) {
                pq.pop();
                pq.push(-1 * Size);
            }
        }
    }
    
    currsize = 0;
  }
  
  while (!pq.empty()) {
      cout << -1 * pq.top() << " ";
      pq.pop();
  } 
  cout << endl;

}

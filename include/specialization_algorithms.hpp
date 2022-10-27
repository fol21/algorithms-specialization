#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <stack>
#include <forward_list>


template<class VertexType>
class Spec_Graph_v1
{

public:
	unsigned int num_vertices; // No. of vertices
	std::vector<std::list<VertexType>*> adj; // An array of adjacency lists

	Spec_Graph_v1(unsigned int num_vertices);
	void addEdge(VertexType v1, VertexType v2);

};


template<class VertexType>
Spec_Graph_v1<VertexType>::Spec_Graph_v1(unsigned int num_vertices)
{
	this->num_vertices = num_vertices;
	adj = std::vector<std::list<VertexType>*>(num_vertices);
	for(auto a : adj)
	{
		a = new std::list<VertexType>();
	}
}

template<class VertexType>
void Spec_Graph_v1<VertexType>::addEdge(VertexType v1, VertexType v2)
{
	adj[v1]->push_back(v2); // Add w to v’s list.
}   
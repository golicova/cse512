#include <iostream> 
#include <list> 

using namespace std; 

// directed graph 
class DirectedGraph
{
    // number of vertices 
    int vertex; 

    // points to an array containing adjacency lists 
    list <int> *adjList; 

    public: 
        DirectedGraph(int vertex);                 // constructor
        void addEdge (int v, int w);    // add edge from vertex v to w 
        void BFS (int start);               // BFS traversal sequence startig with s -> starting node  
}; 


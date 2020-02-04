#include <iostream> 
#include <list> 
#include "BFS.h"

using namespace std; 

int main ()
{
    DirectedGraph graph (5); 
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 2);
    graph.addEdge(2, 4);
    graph.addEdge(3, 3);
    graph.addEdge(4, 4);

    cout << "Breadth First Traversal for given graph (with 0 as starting node): "<<endl;

    graph.BFS(0);
    
    return 0; 
}
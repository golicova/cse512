#include <iostream> 
#include <list> 
#include "BFS.h"

using namespace std;

DirectedGraph::DirectedGraph (int vertex)
{
    this -> vertex = vertex; 
    adjList = new list <int> [vertex]; 
}

void DirectedGraph::addEdge(int v, int w) 
{
    adjList[vertex].push_back(w); // add w to v's list 
}

void DirectedGraph::BFS(int start)
{
    bool *visited = new bool [vertex];
    for (int i = 0; i < vertex; i++) {
        visited[i] = false; 
    }

    // queue to hold BFS traversal sequance 
    list <int> queue; 

    visited[start] = true; 
    queue.push_back(start);

    list <int>::iterator i; 

    while (!queue.empty()) {
        // dequeue the vertex
        start = queue.front(); 
        cout << start << " "; 
        queue.pop_front(); 

        // get all adjacent vertice of popped vertex and process each if not already visited 
        for(i = adjList[start].begin(); i != adjList[start].end(); i++) {
            if(!visited[*i]) {
                visited[*i] = true; 
                queue.push_back(*i);
            }
        }

    }
}

int main ()
{
}
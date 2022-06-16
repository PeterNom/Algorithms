#include "Node.h"
#include "Edge.h"
#include "Graph.h"

using namespace std;

Node* maketree(int label)
{
  if(label==0)
  {
  }
}

// Creates a graph with V vertices and E edges
Graph* createGraph(int V, int E)
{
    Graph* graph = new Graph();
    graph->V = V;
    graph->E = E;

    return graph;
}

int main() {
  Node *test = new Node(1);

  cout << "Hello!" << endl;
}

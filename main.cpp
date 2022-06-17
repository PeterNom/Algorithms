#include <iostream>
#include <string>
#include <vector>
#include "Node.h"

using namespace std;

void link(Node *child , Node * father)
{
  child->parent = father;
  father->children.push_back(child);
}

Node * maketree(char label)
{
  if(label==0)
  {
    Node * square = new Node();
    return square;
  }
  else
  {
    Node * round = new Node(label);
    return round;
  }
}

Node* findpath(Node *x , Node * y)
{
  if(x->name == y->name) return x->parent;
}

Node* make_vertex(char label)
{
  Node * square = maketree(0);
  Node * round  = maketree(label);

  link(square, round);

  return square;
}
char find_block(Node * vertex)
{
  return findpath(vertex, vertex)->label;
}

void insert_edge()
{

}

int main() {
  Node *created_Node;
  char block;

  created_Node = make_vertex('A');
  created_Node->printInfo();
  block = find_block(created_Node);
  cout<< "Found the block: " << (char) block << endl;
}

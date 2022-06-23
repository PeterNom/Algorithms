#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
  static int counter;
  //The name of the node for disjoint set
  int name;
  //The value of the disjoint set array
  int fname;
  // Label if the node is Round
  int label;
  // False Round Node, True Square Round
  bool type;
  // Parent Round Node is the Node is Square
  Node * parent;
  // Array to hold the children of the node
  vector<Node*> children;

  Node();

  Node(int label);

  void printInfo();
};

#endif

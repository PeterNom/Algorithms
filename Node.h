#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node
{
public:
  static int name = 1;
  // Label if the node is Round
  int label;
  // False Round Node, True Square Round
  bool type;
  // Parent Round Node is the Node is Square
  Node * parent;

  Node(int label);

};

#endif

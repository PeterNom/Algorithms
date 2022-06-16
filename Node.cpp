#include <iostream>
#include <string>

class Node
{
public:
  static int name;
  // Label if the node is Round
  int label;
  // False Round Node, True Square Round
  bool type;
  // Parent Round Node is the Node is Square
  Node * parent;

  Node(int label):label(label)
  {
    if(label==0)
    {
      name++;
      type = true;
    }
    else
    {
      type = false;
    }
  }

};

int Node::name = 0;

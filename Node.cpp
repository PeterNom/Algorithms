#include "Node.h"

Node::Node(int label)
{
  if(label!=0)
  {
    this->label = label;
    type = false;
  }
  else
  {
    name++;
    type = true;
  }
}

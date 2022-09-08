#include "Node.h"
#include <iostream>
#include <string>

using namespace std;

int Node::counter = 0;

Node::Node(int label, bool n_type): parent(NULL)
{
  //Name of the node is a int incremented with every node created
  this->name = Node::counter++;
  this->type = n_type;
  this->label = label;
}

void Node::printInfo()
{
  if(this->label==0)
  {
    cout<<"Square Node: " << this->name << endl;
    if(this->parent) cout<<"Parent Node: " << this->parent->name << endl;
  }
  else
  {
    cout<<"Round Node: " << this->name << endl;
    if(this->parent) cout<<"Parent Node: " << this->parent->name << endl;
  }

}

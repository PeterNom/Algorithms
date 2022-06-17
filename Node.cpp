#include "Node.h"
#include <iostream>
#include <string>

using namespace std;

int Node::name = 0;

Node::Node(): type(true), label(0)
{
  this->name++;
}

Node::Node(char label): label(label), type(false)
{
}

void Node::printInfo()
{
  if(this->type)
  {
    cout << " This is a square node with name " << this->name << " and this label " << this->label << " and its father is " << (char)this->parent->label << endl;
  }
  else
  {
    cout << " This is a round node with name " << this->name << " and this label " << this->label << " and its father is " << (char)this->parent->label << endl;
  }
}

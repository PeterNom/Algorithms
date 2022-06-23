#include "Node.h"
#include <iostream>
#include <string>

using namespace std;

int Node::counter = 0;

Node::Node(): type(true), label(0), parent(NULL)
{
  //Name of the node is a int incremented with every node created
  this->name = Node::counter++;
  this->fname = this->name;
  cout<<"Square node's name: " << this->name << " and f name: "<< this->fname << endl;
}

Node::Node(int label): label(label), type(false), parent(NULL)
{
  //Name of the node is a int incremented with every node created
  this->name = Node::counter++;
  this->fname = this->name;
  cout<<"Round node's name: " << this->name << " and f name: "<< this->fname << endl;
}

void Node::printInfo()
{
  if(this->label==0)
  {
    cout<<"Square Node: " << this->name << " and f name: "<< this->fname << endl;
  }
  else
  {
    cout<<"Round Node: " << this->name << " and f name: "<< this->fname << endl;
  }

}

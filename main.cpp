#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

void link(Node *vertex , Node * head)
{
  cout << "There" << endl;
  vertex->parent = head;
}

void make_vertex(int label, vector<Node*>* vertex)
{
  Node * temp1 = new Node(label);
  Node * temp2 ;
  vertex->push_back(temp1);
  if(label==0)
  {
    temp2 = new Node(label+1);
    vertex->push_back(temp2);
  }
  link(temp1, temp2);

  cout << "Hello" << endl;
  return ;
}

void findpath(Node *x , Node * y)
{

}

int main() {
  vector<Node*> vertex;

  make_vertex(0, &vertex);

  cout << "Name "<< vertex[0]->name << "Type "<< vertex[0]->type <<" Parent "<< vertex[0]->parent->label << "Type "<< vertex[0]->parent->type  << endl;
}

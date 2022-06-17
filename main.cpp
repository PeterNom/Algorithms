#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Node.h"

using namespace std;

void link(Node *child , Node * father)
{
  child->parent = father;
  father->children.push_back(child);
}

Node* maketree(char label)
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

Node* make_vertex(char label)
{
  Node * square = maketree(0);
  Node * round  = maketree(label);

  link(square, round);

  return square;
}

vector<Node*> findpath(Node* x , Node* y)
{
  if(x == y)
  {
    vector<Node*> path;
    path.push_back(x->parent);
    return path;
  }
  int flag_2 = 1;
  int flag_1 = 1;

  Node *parentx = x->parent;
  Node *parenty = y->parent;

  vector<Node*> path_1;
  vector<Node*> path_2;
  vector<Node*> path_final;

  while(flag_1+flag_2)
  {
    cout << "Parent x Label " << (char) parentx->label << endl;
    path_1.push_back(parentx);
    cout << "Parent y Label " << (char) parenty->label << endl;
    path_2.push_back(parenty);

    if(parentx->parent)
    {
      parentx = parentx->parent;
    }
    else
    {
      flag_1=0;
    }

    if(parenty->parent)
    {
      parenty = parenty->parent;
    }
    else
    {
      flag_2=0;
    }
  }

  Node* nearest_common_ancestor;
  int i = 0;
  for(; i < path_1.size(); i++)
  {
    nearest_common_ancestor = path_1[i];

    if (find(path_2.begin(), path_2.end(), nearest_common_ancestor) != path_2.end()) {
        cout << "Element found";
        break;
    }
  }

  for(int b = 0 ; b < i; b++)
  {
    path_final.push_back(path_1[b]);
  }
  i=0;

  do {
    path_final.push_back(path_2[i]);
  } while(path_2[i++]!=nearest_common_ancestor);

  return path_final;
}

void condensepath(vector<Node*> path, char new_label)
{
  vector<Node*>::iterator ptr;

  Node * condensedvertex = make_vertex(new_label);

  condensedvertex->parent = path[path.size()-1]->parent;

  for (ptr = path.begin(); ptr < path.end(); ptr++)
  {
    cout << (char) ptr[0]->label << " ";

    for (int i=0; i<ptr[0]->children.size(); i++)
    {
      condensedvertex->children.push_back(ptr[0]->children[i]);
    }
  }

}

void evert(Node* vertex)
{
  if(vertex->parent)
  {
    vertex->children.push_back(vertex->parent);
    vertex->parent = NULL;
  }
}

char find_block(Node* vertex)
{
  vector<Node*> path = findpath(vertex, vertex);

  return path[0]->label;
}

void insert_edge()
{

}

int main() {
  Node* created_Node_1;
  Node* created_Node_2;
  vector<Node*> path;
  vector<Node*>::iterator ptr;

  char block;

  created_Node_1 = make_vertex('A');
  created_Node_2 = make_vertex('B');

  created_Node_1->printInfo();

  created_Node_2->printInfo();

  link(created_Node_2->parent, created_Node_1->parent);

  created_Node_1->printInfo();

  created_Node_2->printInfo();

  cout<< "Node B parent : " <<(char) created_Node_2->parent->parent->label << endl;

  block = find_block(created_Node_1);
  cout<< "Found the block of Node 1 : " << (char) block << endl;

  block = find_block(created_Node_2);
  cout<< "Found the block of Node 2 : " << (char) block << endl;

  path = findpath(created_Node_1, created_Node_2);

  for (ptr = path.begin(); ptr < path.end(); ptr++)
        cout << (char) ptr[0]->label << " ";
}

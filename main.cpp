#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Node.h"

using namespace std;

vector<Node*> Array;

//returns true,if A and B are connected, else it will return false.
bool find(int A, int B)
{
  if(Array[A]->name == Array[B]->name)
    return true;
  else
    return false;
}

//change all entries from Array[ A ] to Array[ B ].
void my_union(int A, int B)
{
    int TEMP = Array[A]->fname;
    for(int i = 0; i < Array.size(); i++)
    {
      if(Array[i]->fname == TEMP)
        Array[i]->fname = Array[B]->fname;
    }
}

void link(Node *child , Node * father)
{
  child->parent = father;
  father->children.push_back(child);

  my_union(child->name, father->name);
}

Node* maketree(int label)
{
  if(label==0)
  {
    Node * square = new Node();
    Array.push_back(square);
    return square;
  }
  else
  {
    Node * round = new Node(label);
    Array.push_back(round);
    return round;
  }
}

Node* make_vertex(int label)
{
  Node * square = maketree(0);
  cout<< endl;
  Node * round  = maketree(label);
  cout<< endl;
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
    cout << "Parent x Label " << parentx->label << endl;
    path_1.push_back(parentx);
    cout << "Parent y Label " << parenty->label << endl;
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

void condensepath(vector<Node*> path, int new_label)
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

int find_block(Node* vertex)
{
  vector<Node*> path = findpath(vertex, vertex);

  return path[0]->label;
}

void insert_edge(Node* A, Node* B)
{
  if(find(A->name, B->name))
  {
    int label = 5;

    condensepath(findpath(A, B), label);
  }
  else
  {
    int x = findpath(A, A).size();
    int y = findpath(B, B).size();
    if(x>=y){
      evert(A);
      link(A, B);
    }
    else
    {
      evert(B);
      link(B, A);
    }
  }
}

int main() {
  Node* created_Node_1;
  Node* created_Node_2;
  vector<Node*> path;
  vector<Node*>::iterator ptr;

  int block;

  created_Node_1 = make_vertex(1);
  cout<< endl;
  created_Node_2 = make_vertex(2);
  cout<< endl;

  Array[0]->printInfo();
  Array[1]->printInfo();
  Array[2]->printInfo();
  Array[3]->printInfo();
  cout<< endl;

  insert_edge(created_Node_1, created_Node_2);

  Array[0]->printInfo();
  Array[1]->printInfo();
  Array[2]->printInfo();
  Array[3]->printInfo();
  //link(created_Node_2->parent, created_Node_1->parent);

  //block = find_block(created_Node_1);
  //cout<< "Found the block of Node 1 : " << block << endl;

  //block = find_block(created_Node_2);
  //cout<< "Found the block of Node 2 : " << block << endl;

  //path = findpath(created_Node_1, created_Node_2);

  //for (ptr = path.begin(); ptr < path.end(); ptr++)
        //cout << ptr[0]->label << " ";
}

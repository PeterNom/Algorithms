#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Node.h"

using namespace std;

// disjoint set array
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
    for(int i = 0; i < Array[0]->counter; i++)
    {
      if(Array[i]->fname == TEMP)
      {
        Array[i]->fname = Array[B]->fname;
      }
    }
}

void link(Node *child , Node * father)
{
  // Set the father of the child
  child->parent = father;
  // Add the child to the parent's children list
  father->children.push_back(child);
  std::cout << "Evert 6" << '\n';
  // Update the disjoint union set
  my_union(child->name, father->name);
}

Node* maketree(int label)
{
  // If label==0 we create a square node
  if(label==0)
  {
    Node * square = new Node();
    //Check if we need to increase in size the disjoint set
    if(Array.capacity()<= square->name)
    {
      Array.resize(Array.capacity()+10);
    }
    //populate the disjoined set
    Array[square->name]= square;

    return square;
  }
  else
  {
    Node * round = new Node(label);
    cout<<"Array size " << Array.capacity() << endl;

    //Check if we need to increase in size the disjoint set
    if(Array.capacity()<= round->name)
    {
      Array.resize(Array.capacity()+10);
    }
    //populate the disjoined set
    Array[round->name]= round;
    cout<<"Array size " << Array.capacity() << endl;
    //Array.push_back(round);
    return round;
  }
}

Node* make_vertex(int label)
{
  // First we create the square node
  Node * square = maketree(0);
  cout<< endl;
  // Then we create the round node
  Node * round  = maketree(label);
  cout<< endl;
  // And finaly we link the two nodes with the round node as the father.
  link(square, round);
  // We return the square node.
  return square;
}

vector<Node*> findpath(Node* x , Node* y)
{
  // The nodes are the same
  if(x == y)
  {
    // Simply return it's parent
    vector<Node*> path;
    path.push_back(x->parent);
    return path;
  }

  // Flags to see when we have reached the end of a path
  int flag_2 = 1;
  int flag_1 = 1;

  // The parents of the 2 nodes
  Node *parentx = x->parent;
  Node *parenty = y->parent;

  // The paths
  vector<Node*> path_1;
  vector<Node*> path_2;
  vector<Node*> path_final;

  while(flag_1+flag_2)
  {
    // We start by adding to eaches path their parents.
    path_1.push_back(parentx);
    path_2.push_back(parenty);

    // While their parent has a parent we continue the search
    if(parentx->parent)
    {
      parentx = parentx->parent;
    }
    else
    {
      flag_1=0;
    }

    // While their parent has a parent we continue the search
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
    //We traverse the path from one node and check to see the first
    // node that is also present in the path from the other node
    nearest_common_ancestor = path_1[i];

    if (find(path_2.begin(), path_2.end(), nearest_common_ancestor) != path_2.end())
    {
      // Once found we break the loop and condense the two paths with the nearest_common_ancestor
      // at the end
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
  std::cout << "Condense Path" << '\n';
  Node * condensedvertex = make_vertex(new_label);

  condensedvertex->parent = path[path.size()-1]->parent;

  if(Array.capacity()<= condensedvertex->name)
  {
    Array.resize(Array.capacity()+10);
  }
  //populate the disjoined set
  Array[condensedvertex->name]= condensedvertex;
  if(condensedvertex->parent->name)
  {
    Array[condensedvertex->name]->fname = condensedvertex->parent->name;
  }
  else
  {
    Array[condensedvertex->name]->fname = condensedvertex->name;
  }

  for (ptr = path.begin(); ptr < path.end(); ptr++)
  {
    //cout << (char) ptr[0]->label << " ";
    for (int i=0; i<ptr[0]->children.size(); i++)
    {
      //condensedvertex->children.push_back(ptr[0]->children[i]);
      link(ptr[0]->children[i] , condensedvertex);
    }
  }

}

void evert(Node* vertex)
{
  // If the node has a parent then
  if(vertex->parent->parent)
  {
    for(int i = 0; i < vertex->parent->parent->children.size(); i++)
    {
      // Erase the vertex from a child of its father.
      if(vertex->parent->parent->children[i]==vertex->parent)
      {
        //erase the 7th element
        vertex->parent->parent->children.erase(vertex->parent->parent->children.begin()+i);
        break;
      }
    }

    // Update the disjoint set union
    Array[vertex->parent->name]->fname = vertex->parent->name;

    // And now perform a link of the two nodes
    link(vertex->parent->parent, vertex->parent);
    //The new root node of its previous father.
    vertex->parent->parent = NULL;
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
    int label = B->counter+1;
    std::cout << "Insert Edge" << '\n';
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
  for (int i = 1; i <= 20; i++)
  {
    make_vertex(i);
  }

  insert_edge(Array[0], Array[4]);
  insert_edge(Array[2], Array[16]);
  insert_edge(Array[12], Array[4]);
  insert_edge(Array[8], Array[22]);
  insert_edge(Array[20], Array[2]);
  insert_edge(Array[34], Array[38]);
  insert_edge(Array[4], Array[26]);
  insert_edge(Array[2], Array[10]);

  for (int i = 0; i < 40; i++)
  {
    Array[i]->printInfo();
  }
  /*
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
  */
  //link(created_Node_2->parent, created_Node_1->parent);

  //block = find_block(created_Node_1);
  //cout<< "Found the block of Node 1 : " << block << endl;

  //block = find_block(created_Node_2);
  //cout<< "Found the block of Node 2 : " << block << endl;

  //path = findpath(created_Node_1, created_Node_2);

  //for (ptr = path.begin(); ptr < path.end(); ptr++)
        //cout << ptr[0]->label << " ";
}

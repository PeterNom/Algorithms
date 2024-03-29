#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "Node.h"

using namespace std;

// Disjoint Set Array
unordered_map<int, int> parent;

// Node Array
vector<Node*> Forest;

void makeSet(int A)
{
  parent[A] = A;
}

// Find the root of the set in which element `k` belongs
int Find(int k)
{
    // if `k` is root
    if (parent[k] == k)
    {
        return k;
    }
    // recur for the parent until we find the root
    return Find(parent[k]);
}

// Perform Union of two subsets
void Union(int a, int b)
{
    // find the root of the sets in which elements `x` and `y` belongs
    int x = Find(a);
    int y = Find(b);

    parent[x] = y;
}

void link(Node *child , Node * father)
{
  // Set the father of the child
  child->parent = father;
  // Add the child to the parent's children list
  father->children.push_back(child);

  // Update the disjoint union set
  Union(child->name, father->name);
}

Node* maketree(int label)
{
  // If label==0 we create a square node
  if(label==0)
  {
    Node * square = new Node(label, true);
    //Check if we need to increase in size the disjoint set
    if(Forest.capacity()<= square->name)
    {
      Forest.resize(Forest.capacity()+10);
    }
    //populate the Forest
    Forest[square->name] = square;
    makeSet(square->name);
    //parent[square->name] = square->name;

    return square;
  }
  else
  {
    Node * round = new Node(label, false);
    //Check if we need to increase in size the disjoint set
    if(Forest.capacity()<= round->name)
    {
      Forest.resize(Forest.capacity()+10);
    }
    //populate the Forest
    Forest[round->name]= round;
    makeSet(round->name);
    //parent[round->name] = round->name;

    return round;
  }
}

Node* make_vertex(int label)
{
  // First we create the square node
  Node * square = maketree(0);
  // Then we create the round node
  Node * round  = maketree(label);
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
      cout << "Element found\n";
      nearest_common_ancestor->printInfo();
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
  std::cout << "Condense Path" << '\n';
  vector<Node*>::iterator ptr;
  Node * condensedvertex = maketree(new_label);

  if(path[path.size()-1]->parent)
  {
    condensedvertex->parent = path[path.size()-1]->parent;
  }

  if(Forest.capacity()<= condensedvertex->name)
  {
    Forest.resize(Forest.capacity()+10);
  }

  //populate the disjoined set
  Forest[condensedvertex->name]= condensedvertex;

  for (ptr = path.begin(); ptr < path.end(); ptr++)
  {
    for (int i=0; i<ptr[0]->children.size(); i++)
    {
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
    //vertex->parent->parent->printInfo();
    //vertex->parent->printInfo();
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
  // If the node are on the same compoments
  if(Find(A->name)==Find(B->name))
  {
    int label = B->counter+1;
    // Condese the nodes along their path as a new cycle is created
    condensepath(findpath(A, B), label);
  }
  else
  {
    // Else see which one is the bigger compoment
    findpath(A, A);
    findpath(B, B);
    int x = 0;
    int y = 0;

    for( const std::pair<const int, int>& n : parent )
    {
      if(Find(n.second)==Find(A->name))
      {
        x++;
      }
      else if(Find(n.second)==Find(B->name))
      {
        y++;
      }
    }
    //And link the smaller on to the bigger one after
    //The small one has made its node the root of its componenet

    if(x>=y){
      evert(A);
      link(B->parent, A->parent);
    }
    else
    {
      evert(B);
      link(A->parent, B->parent);
    }
  }
}

int main() {
  // Helper lambda function to print key-value pairs
  auto print_key_value = [](const auto& key, const auto& value)
  {
    std::cout << "Key:[" << key << "] Value:[" << value << "]\n";
  };

  for (int i = 1; i <= 4; i++)
  {
    make_vertex(i);
  }

  insert_edge(Forest[0], Forest[2]);
  for( const std::pair<const int, int>& n : parent )
  {
    print_key_value(n.first, n.second);
  }
  insert_edge(Forest[2], Forest[4]);
  for( const std::pair<const int, int>& n : parent )
  {
    print_key_value(n.first, n.second);
  }
  insert_edge(Forest[4], Forest[6]);
  for( const std::pair<const int, int>& n : parent )
  {
    print_key_value(n.first, n.second);
  }
  insert_edge(Forest[2], Forest[6]);
  for( const std::pair<const int, int>& n : parent )
  {
    print_key_value(n.first, n.second);
  }
/*
  Forest[0]->printInfo();
  Forest[1]->printInfo();
  Forest[2]->printInfo();
  Forest[3]->printInfo();
  Forest[4]->printInfo();
  Forest[5]->printInfo();
  Forest[6]->printInfo();
  Forest[7]->printInfo();
  */
}

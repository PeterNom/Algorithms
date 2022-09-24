#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "Node.h"

using namespace std;

// Disjoint Set Array
unordered_map<int, int> parent;
// stores the depth of trees
unordered_map<int, int> ranking;

// Node Array
vector<Node*> Forest;

void printGraph()
{
  vector<Node*>::iterator ptr;
  vector<Node*>::iterator chl;

  for (ptr = Forest.begin(); ptr < Forest.end(); ptr++)
  {
    if(ptr[0]->type) continue;
    if(parent[ptr[0]->name]==-1) continue;
    for(chl = ptr[0]->children.begin(); chl < ptr[0]->children.end(); chl++)
    {
      std::cout << ptr[0]->name << " -- " << chl[0]->name<<'\n';
    }
    std::cout << ptr[0]->name << "[shape=box, color=yellow];"<<'\n';
  }
}

void makeSet(int A)
{
  parent[A] = A;
  ranking[A] = 1;
}

// Find the root of the set in which element `k` belongs
int Find(int k)
{

  if(parent[k]==-1)
  {
    return -1;
  }
  // if `k` is not the root
  if (parent[k] != k)
  {
    // path compression
    parent[k] = Find(parent[k]);
  }
  // recur for the parent until we find the root
  return parent[k];
}

// Perform Union of two subsets
void Union(int a, int b)
{
  // find the root of the sets in which elements `x` and `y` belongs
  int x = Find(a);
  int y = Find(b);

  // if `x` and `y` are present in the same set
  if (x == y) return;

  parent[x] = y;
  ranking[y]++;
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
    return round;
  }
}

Node* make_vertex(int label)
{
  // First we create the square node
  Node * square = maketree(0);

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

  if(!path[path.size()-1]->type)
  {
      if(path[path.size()-1]->parent)
      {
          link(condensedvertex, path[path.size()-1]->parent);
      }
  }
  else
  {
      link(condensedvertex, path[path.size()-1]);
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
      if(ptr[0]->children[i]->type)
      {
        link(ptr[0]->children[i], condensedvertex);
        ptr[0]->children[i]->printInfo();
        condensedvertex->printInfo();
      }
    }
  }

  for (ptr = path.begin(); ptr < path.end(); ptr++)
  {
    if(!(ptr[0]->type))
    {
      parent[ptr[0]->name] = -1;
    }
  }
}

void evert(Node* vertex)
{
  // If the node is round this node becames root
  // else the parent of the square node becames root
  Node* root;
  int temp, prev;

  root = vertex;
    
  root->printInfo();

  if(parent[root->name]==root->name) return;

  std::cout<<"Step 1"<<std::endl;
  temp = root->parent->name;
  std::cout<<"Temp"<< temp <<std::endl;
  root->parent=NULL;
  root->printInfo();
  root->children.push_back(Forest[temp]);
  root->printInfo();
  prev = root->name;
  std::cout<<"Step 2"<<std::endl;
  while(Forest[temp])
  {
    int ancestor;

    ancestor = Forest[temp]->parent->name;
    Forest[temp]->parent = Forest[prev];
    Forest[temp]->children.push_back(Forest[ancestor]);

    for(int i = 0; i < Forest[temp]->children.size(); i++)
    {
      if(Forest[temp]->children[i] == Forest[ancestor])
      {
        Forest[temp]->children.erase(Forest[temp]->children.begin()+i);
        break;
      }
    }

    parent[temp] = root->name;

    temp = ancestor;
  }
}

int find_block(Node* vertex_1, Node* vertex_1)
{
  vector<Node*> path = findpath(vertex_1, vertex_2);

  return path[0]->label;
}

void insert_edge(Node* A, Node* B, int label)
{
  if(!(A->type) || !(B->type)) return;

  if(A->parent==B->parent) return;

  // If the node are on the same compoments
  if(Find(A->name)==Find(B->name))
  {
    int label = B->counter+1;
    // Condese the nodes along their path as a new cycle is created
    condensepath(findpath(A, B), label);
  }
  else
  {
    //And link the smaller on to the bigger one after
    //The small one has made its node the root of its componenet
    int label = B->counter+1;

    Node *r = maketree(new_label);

    if(ranking[Find(A->name)]>=ranking[Find(B->name)])
    {
      evert(B);
      link(B->parent, r);
      link(r, A->parent);
    }
    else
    {
      evert(A);
      link(A->parent, r);
      link(r, B->parent);
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
  insert_edge(Forest[2], Forest[4]);
  insert_edge(Forest[4], Forest[6]);
  insert_edge(Forest[2], Forest[6]);
  for (int i = 9; i <= 11; i++)
  {
    make_vertex(i);
  }
  for( const std::pair<const int, int>& n : parent )
  {
    print_key_value(n.first, n.second);
  }
  printGraph();
}

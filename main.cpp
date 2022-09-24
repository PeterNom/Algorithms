#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "Node.h"

using namespace std;

// Disjoint Set Array
unordered_map<int, int> parent;

// Stores the depth of trees
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

// Find the root of the set in which vertex `k` belongs
int Find(int k)
{
  // Check if the vertex still exist in the data structure
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

// Link two vertices 
void link(Node *child , Node * father)
{
  // Set the father of the child
  child->parent = father;
  // Add the child to the parent's children list
  father->children.push_back(child);

  // Update the disjoint union set
  Union(child->name, father->name);
}

// Function that actually creates the specified vertex: round or square
Node* maketree(int label)
{
  // If label==0 we create a square node
  if(label==0)
  {
    Node * square = new Node(label, true);
    // Check if we need to increase in size the disjoint set
    if(Forest.capacity()<= square->name)
    {
      Forest.resize(Forest.capacity()+10);
    }
    // Populate the Forest
    Forest[square->name] = square;
    // Populate the Disjoint Union Set with the new vertex
    makeSet(square->name);

    return square;
  }
  else
  {
    Node * round = new Node(label, false);

    // Check if we need to increase in size the disjoint set
    if(Forest.capacity()<= round->name)
    {
      Forest.resize(Forest.capacity()+10);
    }

    // Populate the Forest
    Forest[round->name]= round;
    // Populate the Disjoint Union Set with the new vertex
    makeSet(round->name);

    return round;
  }
}

// Create a square vertex and the round that it will be its parent
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

  // The paths the we will populate 
  vector<Node*> path_1;
  vector<Node*> path_2;

  // The path to hold the joint path
  vector<Node*> path_final;

  // While we can traverse further backward continue
  while(flag_1+flag_2)
  {
    // We start by adding to each path their parents.
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

  do 
  {
    path_final.push_back(path_2[i]);
  } while(path_2[i++]!=nearest_common_ancestor);

  return path_final;
}

void condensepath(vector<Node*> path, int new_label)
{
  std::cout << "Condense Path" << '\n';
  vector<Node*>::iterator ptr;
  
  // We create the node that will condese all the round nodes in the path
  Node * condensedvertex = maketree(new_label);

  // If the common ancestor has a parent we make the new created node child of that same parent
  if(path[path.size()-1]->parent)
  {
    link( condensedvertex, path[path.size()-1]->parent);
  }

  // Update the size of the foreset if neccesairy 
  if(Forest.capacity()<= condensedvertex->name)
  {
    Forest.resize(Forest.capacity()+10);
  }

  // Populate the disjoined set
  Forest[condensedvertex->name]= condensedvertex;

  // We start to iterate the path between the two vertecies
  for (ptr = path.begin(); ptr < path.end(); ptr++)
  {
    // And for each vertex childer
    for (int i=0; i<ptr[0]->children.size(); i++)
    {
      // We reroute their square vertex children to the newly created node that will condese the path
      if(ptr[0]->children[i]->type)
      {
        link(ptr[0]->children[i], condensedvertex);
        ptr[0]->children[i]->printInfo();
        condensedvertex->printInfo();
      }
    }
  }

  // After we finish we update the Disjoint Union Set so all the round vertecies of the path point to nothing
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
  
  
  Node* root;
  int temp, prev;

  // If the node is round this node becames root
  if(!vertex->type)
  {
    std::cout<<"Round"<<std::endl;
    root = vertex;
    root->printInfo();
  }
  // Else the parent of the square node becames root
  else
  {
    std::cout<<"Square"<<std::endl;
    root = vertex->parent;
    root->printInfo();
  }

  // If the node to be made the new root is already the root return
  if(parent[root->name]==root->name) return;

  // we keep the parent of the root before we clear it
  temp = root->parent->name;

  // We clear the new root parent pointer to null
  root->parent=NULL;

  // We make the father of the root its child
  root->children.push_back(Forest[temp]);

  // Erase the root from the child list of its previous parent
  for(int i = 0; i < Forest[temp]->children.size(); i++)
  {
    if(Forest[temp]->children[i] == root)
    {
      Forest[temp]->children.erase(Forest[temp]->children.begin()+i);
      break;
    }
  }

  // we keep track of the vertex we have already process
  prev = root->name;

  // Now moving backwards from the parent of the new root
  while(Forest[temp])
  {
    int ancestor;
    
    if(Forest[temp]->parent)
    {
      // We hold the its parent vertex
      ancestor = Forest[temp]->parent->name;

      // We update the vertex parent that of the previous processed vertex
      Forest[temp]->parent = Forest[prev];
      // We make its previous parent its child
      Forest[temp]->children.push_back(Forest[ancestor]);

      // Then we iterate the children list of its previous father to find and erase its previous child that is now its parent
      for(int i = 0; i < Forest[ancestor]->children.size(); i++)
      {
        if(Forest[ancestor]->children[i] == Forest[temp])
        {
         Forest[ancestor]->children.erase(Forest[ancestor]->children.begin()+i);
         break;
        }
      }
      // We Update the Disjoint Union Set data structure
      parent[temp] = root->name;

      // We update the node so that prev is the node we just processed and temp holds the parent of that node that will be processed next
      prev = temp;
      temp = ancestor;
    }
    else
    {
      // We update the vertex parent that of the previous processed vertex
      Forest[temp]->parent = Forest[prev];
      // We Update the Disjoint Union Set data structure
      parent[temp] = root->name;
      break;
    }
   
  }
}

// Return the block that the vertex belongs to
int find_block(Node* vertex)
{
  vector<Node*> path = findpath(vertex, vertex);

  return path[0]->label;
}

// We create and edge when possible between two vertex and perform the neccesairy operations
void insert_edge(Node* A, Node* B)
{
  // If they are round nodes return
  if(!(A->type) || !(B->type)) return;

  // If they are the same node return
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

    if(ranking[Find(A->name)]>=ranking[Find(B->name)]){
      evert(B);
      link(B->parent, A->parent);
    }
    else
    {
      evert(A);
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

  // Make a number of vertices for testing
  for (int i = 1; i <= 4; i++)
  {
    make_vertex(i);
  }

  // Insert a number of edges for testing
  insert_edge(Forest[0], Forest[2]);
  insert_edge(Forest[2], Forest[4]);
  insert_edge(Forest[4], Forest[6]);
  insert_edge(Forest[2], Forest[6]);

  // Add some more vertices
  for (int i = 9; i <= 11; i++)
  {
    make_vertex(i);
  }

  // Print their Disjoint Set Union Struction for visual debuging
  for( const std::pair<const int, int>& n : parent )
  {
    print_key_value(n.first, n.second);
  }

  // Print the graph in a format that can be used for visualization
  printGraph();
/*
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

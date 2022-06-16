#include <iostream>
#include <string>

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

int main() {
  Node *test_1 = new Node(1);

  cout << "Hello!" << test_1->name << " Type: " << test_1->type << " Label: " <<test_1->label <<endl;

  Node *test_2 = new Node(0);

  cout << "Hello!" << test_2->name << " Type: " <<test_2->type << " Label: " <<test_2->label << endl;
}

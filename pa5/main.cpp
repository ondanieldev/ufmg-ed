#include <iostream>

using namespace std;

class Stack
{
public:
  Stack()
  {
    this->size = 0;
  }

  void stack(int value)
  {
    this->values[this->size] = value;
    this->size++;
  };

  void unstack()
  {
    this->size--;
  };

  int getLast()
  {
    return this->values[this->size - 1];
  };

  void clear()
  {
    this->size = 0;
  };

  int getSize()
  {
    return this->size;
  }

private:
  int size;
  int values[50];
};

int main()
{
  string input;

  while (getline(cin, input))
  {
    //
    int inputSize = input.length();
    int treeSize = 0;

    // calculates tree size
    for (int i = 0; i < inputSize; ++i)
    {
      if (isdigit(input[i]))
      {
        treeSize++;
      }
    }

    //
    int tree[treeSize][treeSize];

    // clear tree
    for (int i = 0; i < treeSize; ++i)
    {
      for (int j = 0; j < treeSize; ++j)
      {
        tree[i][j] = 0;
      }
    }

    //
    int root = -1;
    int node = -1;
    Stack positionStack = Stack();
    int nodePosition = -1;

    // generate tree
    for (int i = 0; i < inputSize; ++i)
    {
      if (isdigit(input[i]))
      {
        nodePosition++;
        positionStack.stack(nodePosition);
      }
      else if (input[i] == ')')
      {
        if (positionStack.getSize() == 1)
        {
          break;
        }
        node = positionStack.getLast();
        positionStack.unstack();
        root = positionStack.getLast();
        cout << root << " " << node << endl;
        if (root > node)
        {
          tree[root][node] = 1;
        }
        else
        {
          tree[node][root] = 1;
        }
      }
    }

    // identify leafs
    int test[treeSize];
    for (int i = 0; i < treeSize; ++i)
    {
      test[i] = 0;
    }
    for (int i = 0; i < treeSize; ++i)
    {
      for (int j = 0; j < treeSize; ++j)
      {
        test[i] += tree[i][j];
        test[i] += tree[j][i];
      }
    }
    for (int i = 0; i < treeSize; ++i)
    {
      cout << test[i] << " ";
    }
  }

  return 0;
}
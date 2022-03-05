#include <iostream>
#define MAX_N 50
#define UNDEFINED -1

using namespace std;

// classe para armazenar os nós da árvore
class Node
{
public:
  Node()
  {
    this->parent = UNDEFINED;
    this->value = UNDEFINED;
  }

  int parent;
  int value;
};

// classe para salvar as raízes em uma pilha e acessar àquela referente a cada nó
class Stack
{
public:
  Stack()
  {
    this->size = 0;
  }

  void stack(Node node)
  {
    this->nodes[this->size] = node;
    this->size++;
  };

  void unstack()
  {
    this->size--;
  };

  Node getLast()
  {
    if (this->size == 0)
    {
      return Node();
    }
    return this->nodes[this->size - 1];
  };

  int getSize()
  {
    return this->size;
  }

  Node *getNodes()
  {
    return this->nodes;
  }

private:
  int size;
  Node nodes[MAX_N];
};

// classe para armazenar métodos úteis
class Helper
{
public:
  static string removeSpaces(string str)
  {
    string result = "";
    for (int i = 0; i < str.length(); ++i)
    {
      if (str[i] != ' ')
      {
        result += str[i];
      }
    }
    return result;
  }
};

// classe para ordenar os nós folha
class QuickSort
{
public:
  static void sort(Node arr[], int start, int end)
  {
    if (start >= end)
      return;
    int p = QuickSort::partition(arr, start, end);
    QuickSort::sort(arr, start, p - 1);
    QuickSort::sort(arr, p + 1, end);
  }

private:
  static int partition(Node arr[], int start, int end)
  {

    Node pivot = arr[start];
    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
      if (arr[i].value >= pivot.value)
        count++;
    }
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
    int i = start, j = end;
    while (i < pivotIndex && j > pivotIndex)
    {
      while (arr[i].value >= pivot.value)
      {
        i++;
      }
      while (arr[j].value < pivot.value)
      {
        j--;
      }
      if (i < pivotIndex && j > pivotIndex)
      {
        swap(arr[i++], arr[j--]);
      }
    }
    return pivotIndex;
  }
};

int main()
{
  // armazenar cada linha inserida pelo usuário
  string testcase;

  // para cada linha inserida
  while (getline(cin, testcase))
  {
    // controlar espaços em branco
    bool isFirstLeaf = true;
    // tamanho do input
    int testcaseSize = testcase.length();

    int testcaseDigits;
    int greaterDigit;
    greaterDigit = -1;

    while (testcase.length() >= 6)
    {
      testcase = Helper::removeSpaces(testcase);
      Node node = Node();
      Stack leafs = Stack();
      Stack roots = Stack();

      int testcaseDigits = 0;

      for (int i = 0; i < testcase.length(); ++i)
      {
        if (isdigit(testcase[i]))
        {
          if (testcase[i] - '0' > greaterDigit)
          {
            greaterDigit = testcase[i] - '0';
          }
          testcaseDigits++;
        }
      }

      if (testcaseDigits == 1)
      {
        break;
      }
      else if (testcaseDigits == 2)
      {
        cout << greaterDigit;
        break;
      }

      for (int i = 0; i < testcase.length(); ++i)
      {
        if (isdigit(testcase[i]))
        {
          string strValue = "";
          strValue += testcase[i];
          if (i != (testcase.length() - 1) && isdigit(testcase[i + 1]))
          {
            strValue += testcase[i + 1];
            ++i;
          }
          node.value = stoi(strValue);
          node.parent = roots.getLast().value;
          if (leafs.getLast().value != UNDEFINED && leafs.getLast().value == node.parent)
          {
            leafs.unstack();
          }
          leafs.stack(node);
          roots.stack(node);
        }
        else if (testcase[i] == ')')
        {
          roots.unstack();
        }
      }
      QuickSort::sort(leafs.getNodes(), 0, leafs.getSize());
      Node minor = leafs.getLast();
      cout << minor.parent << " ";
      leafs.unstack();

      string leaf = "(" + to_string(minor.value) + ")";
      size_t leafPosition = testcase.find(leaf);
      testcase = testcase.substr(0, leafPosition) + testcase.substr(leafPosition + leaf.length());
    }
    cout << endl;
  }
}
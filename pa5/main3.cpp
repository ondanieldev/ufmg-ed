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

    // resolução da árvore
    while (testcaseSize >= 6)
    {
      // update size
      testcaseSize = testcase.length();

      // remover espaços em branco do input
      testcase = Helper::removeSpaces(testcase);

      // armazenar nós folha e raízes
      Stack leafs = Stack();
      Stack roots = Stack();

      // resolver árvores com apenas um nó
      int testcaseDigits = 0;
      int greaterDigit = UNDEFINED;
      for (int i = 0; i < testcaseSize; ++i)
      {
        if (isdigit(testcase[i]))
        {
          string strValue = "";
          strValue += testcase[i];
          if (i != (testcaseSize - 1) && isdigit(testcase[i + 1]))
          {
            ++i;
          }
          int intValue = stoi(strValue);
          if (intValue > greaterDigit)
          {
            greaterDigit = intValue;
          }
          testcaseDigits++;
        }
      }
      if (testcaseDigits == 1)
      {
        break;
      }
      // resolver árvores com apenas dois nós
      // tentativa falha de resolver árvores sem raízes. Até este ponto do código, havia entendido que a única possibilidade de obter árvores sem raízes seria em árvores com apneas dois nós
      else if (testcaseDigits == 2)
      {
        cout << " " << greaterDigit;
        break;
      }

      // lógica principal para obter folhas de árvores com mais de dois nós que possuem raíz
      for (int i = 0; i < testcaseSize; ++i)
      {
        if (isdigit(testcase[i]))
        {
          string strValue = "";
          strValue += testcase[i];
          if (i != (testcaseSize - 1) && isdigit(testcase[i + 1]))
          {
            strValue += testcase[i + 1];
            ++i;
          }
          Node node = Node();
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

      // ordenar folhas e imprimir a menor
      QuickSort::sort(leafs.getNodes(), 0, leafs.getSize());
      Node minor = leafs.getLast();
      if (!isFirstLeaf)
      {
        cout << " ";
      }
      cout << minor.parent;
      isFirstLeaf = false;
      leafs.unstack();

      // atualizar o input do usuário removendo a folha resolvida
      string leaf = "(" + to_string(minor.value) + ")";
      size_t leafPosition = testcase.find(leaf);
      testcase = testcase.substr(0, leafPosition) + testcase.substr(leafPosition + leaf.length());
    }

    // quebrra de linha após cada entrada
    cout << endl;
  }

  cout << endl;
}
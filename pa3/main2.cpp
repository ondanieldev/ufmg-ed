#include <iostream>

using namespace std;

typedef struct
{
  int key = -1, value = 0;
} Branch;

void cutBranch()
{
}

int main()
{
  int n, d, a, b, w;

  cin >> n;

  Branch branch;
  Branch graph[n][n];
  Branch cuts[n];

  int nCuts = 0, pretty = 0;

  for (int i = 0; i < n; ++i)
  {
    cin >> d >> a >> b >> w;
    branch.key = d;
    branch.value = w;
    graph[a][b] = branch;
    graph[b][a] = branch;
  }

  for (int i = 0; i < n; ++i)
  {
    for (int j = i; j < n; ++j)
    {
      branch = graph[i][j];
      if (branch.key == -1)
      {
        continue;
      }
      if (branch.value < 0)
      {
        cout << "NEGATIVE BRANCH: " << branch.key << " " << branch.value << endl;
        int sum = 0;
        for (int k = 0; k < n; ++k)
        {
          if (graph[k][j].key == -1 || graph[k][j].key == branch.key)
          {
            continue;
          }
          cout << "..son: " << graph[k][j].key << " " << graph[k][j].value << endl;
          sum += graph[k][j].value;
        }
        cout << "....sum: " << sum << endl;
        if (sum < abs(branch.value))
        {
          cout << "......cutting" << endl;
          for (int k = 0; k < n; ++k)
          {
            if (graph[k][j].key == -1)
            {
              continue;
            }
            cout << "AAAAAAA" << graph[k][j].key;
            graph[k][j].key = -1;
            graph[k][j].value = 0;
            cout << "AAAAAAA" << graph[k][j].key;
          }
          nCuts++;
        }
        cout << endl;
      }
    }
  }

  for (int i = 0; i < n; ++i)
  {
    for (int j = i; j < n; ++j)
    {
      branch = graph[i][j];
      if (branch.key == -1)
      {
        continue;
      }
      pretty += branch.value;
    }
  }

  cout << pretty << " " << nCuts << endl;
  for (int i = 0; i < nCuts; ++i)
  {
    cout << cuts[i].key;
    if (i < nCuts)
    {
      cout << " ";
    }
  }

  cout << endl
       << endl;

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < i; j++)
    {
      cout << "\t";
    }
    for (int j = i; j < n; ++j)
    {
      cout << graph[i][j].value << "\t";
    }
    cout << endl;
  }

  cout << endl
       << endl;

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < i; j++)
    {
      cout << "\t";
    }
    for (int j = i; j < n; ++j)
    {
      cout << graph[i][j].key << "\t";
    }
    cout << endl;
  }

  return 0;
}
#include <iostream>

using namespace std;

typedef struct
{
  int key = -1, value = 0;
} Branch;

int main()
{
  int n, d, a, b, w;

  scanf("%d", &n);

  Branch branch;
  Branch graph[n][n];
  Branch cuts[n];

  int nCuts = 0, pretty = 0;

  for (int i = 0; i < n - 1; ++i)
  {
    scanf("%d %d %d %d", &d, &a, &b, &w);
    branch.key = d;
    branch.value = w;
    graph[a][b] = branch;
    graph[b][a] = branch;
    pretty += branch.value;
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
        int sum = 0;
        for (int k = 0; k < n; ++k)
        {
          if (graph[k][j].key == -1 || graph[k][j].key == branch.key)
          {
            continue;
          }
          sum += graph[k][j].value;
        }
        if (sum < abs(branch.value))
        {
          cuts[nCuts] = branch;
          for (int k = 0; k < n; ++k)
          {
            if (graph[k][j].key == -1)
            {
              continue;
            }
            pretty -= graph[k][j].value;
            graph[k][j].key = -1;
            graph[k][j].value = 0;
            graph[j][k].key = -1;
            graph[j][k].value = 0;
          }
          nCuts++;
        }
      }
    }
  }

  printf("%d %d\n", pretty, nCuts);
  for (int i = 0; i < nCuts; ++i)
  {
    printf("%d", cuts[i].key);
    if (i < nCuts - 1)
    {
      printf(" ");
    }
  }

  return 0;
}
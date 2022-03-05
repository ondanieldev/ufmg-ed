#include "Quicksort.h"

int getMedianOf3(int *indexes)
{
  int aux;
  for (int i = 0; i < 2; i++)
  {
    for (int j = i + 1; j < 3; j++)
    {
      if (indexes[i] > indexes[j])
      {
        aux = indexes[i];
        indexes[i] = indexes[j];
        indexes[j] = aux;
      }
    }
  }
  return indexes[1];
}

void Quicksort::partition(int left, int right, int *i, int *j, Page *pages)
{
  Page x, w;
  *i = left;
  *j = right;

  int indexes[3] = {*i, (*i + *j) / 2, *j};
  x = pages[getMedianOf3(indexes)];

  do
  {
    while (x.getPopularity() < pages[*i].getPopularity() ||
           (x.getPopularity() == pages[*i].getPopularity() && x.getUrl() > pages[*i].getUrl()))
    {
      (*i)++;
    }
    while (x.getPopularity() > pages[*j].getPopularity() ||
           (x.getPopularity() == pages[*j].getPopularity() && x.getUrl() < pages[*j].getUrl()))
    {
      (*j)--;
    }
    if (*i <= *j)
    {
      w = pages[*i];
      pages[*i] = pages[*j];
      pages[*j] = w;
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);
}

void Quicksort::order(int left, int right, Page *array)
{
  int i, j;

  Quicksort::partition(left, right, &i, &j, array);

  if (left < j)
  {
    Quicksort::order(left, j, array);
  }

  if (i < right)
  {
    Quicksort::order(i, right, array);
  }
}

void Quicksort::quicksort(Page *array, int n)
{
  Quicksort::order(0, n - 1, array);
}
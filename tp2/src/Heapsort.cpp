#include <iostream>
#include <exception>

#include "Page.h"
#include "Heapsort.h"

void Heapsort::heapify(Page *array, int n, int i)
{
  int smallest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  Page aux;

  if (l < n &&
      (array[l].getPopularity() < array[smallest].getPopularity() ||
       (array[l].getPopularity() == array[smallest].getPopularity() &&
        array[l].getUrl() > array[smallest].getUrl())))
  {
    smallest = l;
  }

  if (r < n &&
      (array[r].getPopularity() < array[smallest].getPopularity() ||
       (array[r].getPopularity() == array[smallest].getPopularity() &&
        array[r].getUrl() > array[smallest].getUrl())))
  {
    smallest = r;
  }

  if (smallest != i)
  {
    aux = array[i];
    array[i] = array[smallest];
    array[smallest] = aux;
    Heapsort::heapify(array, n, smallest);
  }
}

void Heapsort::heapsort(Page *array, int n)
{
  Page aux;

  for (int i = n / 2 - 1; i >= 0; i--)
  {
    heapify(array, n, i);
  }

  for (int i = n - 1; i >= 0; i--)
  {
    aux = array[0];
    array[0] = array[i];
    array[i] = aux;
    heapify(array, i, 0);
  }
}

Page Heapsort::pop(Page *array, int *n)
{
  Page max;

  if (*n < 1)
  {
    throw std::invalid_argument("Heap is empty");
  }
  else
  {
    max = array[0];
    array[0] = array[(*n) - 1];
    (*n)--;
    Heapsort::heapsort(array, *n);
  }

  return max;
}
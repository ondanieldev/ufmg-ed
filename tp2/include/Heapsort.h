#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "Page.h"

class Heapsort
{
public:
  static void heapify(Page *array, int n, int i);
  static void heapsort(Page *array, int n);
  static Page pop(Page *array, int *n);
};

#endif
#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "Page.h"

class Quicksort
{
public:
  static void quicksort(Page *array, int n);

private:
  static void partition(int left, int right, int *i, int *j, Page *array);
  static void order(int left, int right, Page *array);
};

#endif
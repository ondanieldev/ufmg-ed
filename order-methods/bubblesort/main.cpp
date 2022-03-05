// Optimized implementation of Bubble sort
#include <stdio.h>

/* Function to print an array */
void printArray(int arr[], int size)
{
  int i;
  for (i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

void swap(int *xp, int *yp)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

// An optimized version of Bubble Sort
void bubbleSort(int arr[], int n)
{
  int i, j;
  bool swapped;
  for (i = 0; i < n - 1; i++)
  {
    swapped = false;
    for (j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        swap(&arr[j], &arr[j + 1]);
        printArray(arr, 10);
        swapped = true;
      }
    }

    // IF no two elements were swapped by inner loop, then break
    if (swapped == false)
      break;
  }
}

void Bolha2(int *v, int n)
{
  int i, j;
  for (i = 0; i < (n - 1); i++)
    for (j = 1; j < (n - i); j++)
      if (v[j] > v[j - 1])
        swap(&v[j], &v[j - 1]); // troca os conteudos dos dois argumentos
}

// Driver program to test above functions
int main()
{
  int arr[] = {45, 5, 35, 15, 20, 10, 25, 30, 40, 50};
  int n = sizeof(arr) / sizeof(arr[0]);
  // bubbleSort(arr, n);
  Bolha2(arr, n);
  printf("Sorted array: \n");
  printArray(arr, n);
  return 0;
}
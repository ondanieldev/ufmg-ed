#include <iostream>

using namespace std;

typedef struct
{
  int key;
  float value;
} Digit;

void bubbleSort(Digit array[], int n)
{
  int i, j;
  bool swapped;
  for (i = 0; i < n - 1; i++)
  {
    swapped = false;
    for (j = 0; j < n - i - 1; j++)
    {
      if (array[j].value < array[j + 1].value || (array[j].value == array[j + 1].value && array[j].key > array[j + 1].key))
      {
        Digit aux = array[j];
        array[j] = array[j + 1];
        array[j + 1] = aux;
        swapped = true;
      }
    }
    if (swapped == false)
    {
      break;
    }
  }
}

void printTestCase(int testcase, int passLength, Digit *digits)
{
  cout << "Caso " << testcase << ": ";
  for (int i = 0; i < passLength; ++i)
  {
    cout << digits[i].key;
  }
  cout << endl;
}

int main()
{
  const int n = 10;
  int testcase = 1, passLength;
  Digit newDigit, digits[n];

  while (cin >> passLength)
  {
    for (int i = 0; i < n; ++i)
    {
      newDigit.key = i;
      cin >> newDigit.value;
      digits[i] = newDigit;
    }
    bubbleSort(digits, n);
    printTestCase(testcase, passLength, digits);
    testcase++;
  }

  return 0;
}
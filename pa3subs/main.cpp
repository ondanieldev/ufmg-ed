#include <iostream>

using namespace std;

class Person
{
public:
  Person()
  {
    this->name = "";
    this->color = "";
    this->size = "";
  }

  string name, color, size;
};

class QuickSort
{
public:
  static void sort(Person arr[], int start, int end)
  {
    if (start >= end)
      return;
    int p = QuickSort::partition(arr, start, end);
    QuickSort::sort(arr, start, p - 1);
    QuickSort::sort(arr, p + 1, end);
  }

private:
  static bool getCondition1(Person item, Person pivot)
  {
    return item.color < pivot.color ||
           (item.color == pivot.color && item.size > pivot.size) ||
           (item.color == pivot.color && item.size == pivot.size && item.name <= pivot.name);
  }

  static bool getCondition2(Person item, Person pivot)
  {
    return item.color > pivot.color ||
           (item.color == pivot.color && item.size < pivot.size) ||
           (item.color == pivot.color && item.size == pivot.size && item.name > pivot.name);
  }

  static int partition(Person arr[], int start, int end)
  {
    Person pivot = arr[start];
    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
      if (getCondition1(arr[i], pivot))
      {
        count++;
      }
    }
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
    int i = start, j = end;
    while (i < pivotIndex && j > pivotIndex)
    {
      while (getCondition1(arr[i], pivot))
      {
        i++;
      }
      while (getCondition2(arr[j], pivot))
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
  int n;
  string trash;
  bool endline = false;
  while (cin >> n && n != 0)
  {
    if (endline)
      cout << endl;
    getline(cin, trash);
    Person people[n];
    for (int i = 0; i < n; ++i)
    {
      string name, info, color, size;
      size_t position;
      getline(cin, name);
      getline(cin, info);
      position = info.find(" ");
      color = info.substr(0, position);
      size = info.substr(position + 1);
      Person person;
      person.color = color;
      person.size = size;
      person.name = name;
      people[i] = person;
    }
    QuickSort::sort(people, 0, n - 1);
    for (int i = 0; i < n; ++i)
    {
      cout << people[i].color << " " << people[i].size << " " << people[i].name << endl;
    }
    endline = true;
  }
  return 0;
}
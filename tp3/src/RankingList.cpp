#include <iostream>
#include <math.h>

#include "RankingList.h"

// instantiate an array using the given size
// as this class doens't use a chained list, it's necessary to use a cursor to know how much of the size was used
RankingList::RankingList(unsigned int size)
{
  this->size = size;
  this->list = new RankingNode *[size];
  this->cursor = 0;
}

RankingList::~RankingList()
{
}

unsigned int RankingList::getSize()
{
  return this->size;
}

RankingNode **RankingList::getList()
{
  return this->list;
}

unsigned int RankingList::getCursor()
{
  return this->cursor;
}

// always add at the end of the list
void RankingList::add(RankingNode *rankingNode)
{
  if (this->cursor >= this->size)
  {
    throw "ranking node cannot be added to the ranking list: ranking list is already full filled";
  }
  this->list[this->cursor] = rankingNode;
  this->cursor++;
}

// search for a ranking node with the same documentId. returns "nullptr" if not found
RankingNode *RankingList::search(int documentId)
{
  RankingNode *result = nullptr;
  for (unsigned int i = 0; i < this->cursor; ++i)
  {
    if (this->list[i]->getDocumentId() == documentId)
    {
      result = this->list[i];
      break;
    }
  }
  return result;
}

void RankingList::print()
{
  for (unsigned int i = 0; i < this->cursor; ++i)
  {
    std::cout << "(" << this->list[i]->getDocumentId() << "," << this->list[i]->getWd2() << "," << sqrt(this->list[i]->getWd2()) << "," << this->list[i]->getSim() << ")"
              << " | ";
  }
}

int RankingList::quicksortPartition(int start, int end)
{
  RankingNode *pivot = this->list[start];

  int count = 0;
  for (int i = start + 1; i <= end; i++)
  {
    if (
        (this->list[i]->getSim() > pivot->getSim()) ||
        (this->list[i]->getSim() == pivot->getSim() && this->list[i]->getDocumentId() < pivot->getDocumentId()))
    {
      count++;
    }
  }

  int pivotIndex = start + count;
  std::swap(this->list[pivotIndex], this->list[start]);

  int i = start, j = end;

  while (i < pivotIndex && j > pivotIndex)
  {

    while (
        (this->list[i]->getSim() > pivot->getSim()) ||
        (this->list[i]->getSim() == pivot->getSim() && this->list[i]->getDocumentId() < pivot->getDocumentId()))
    {
      i++;
    }

    while (this->list[j]->getSim() < pivot->getSim())
    {
      j--;
    }

    if (i < pivotIndex && j > pivotIndex)
    {
      std::swap(this->list[i++], this->list[j--]);
    }
  }

  return pivotIndex;
}

// a generic quicksort function found on internet with few modifiers to order using similarity and document id
void RankingList::quicksort(int start, int end)
{
  if (start < 0 || (end > 0 && end >= this->cursor))
  {
    throw "ranking list cannot be sorted: quicksort index range is invalid";
  }
  if (start >= end)
    return;
  int p = this->quicksortPartition(start, end);
  this->quicksort(start, p - 1);
  this->quicksort(p + 1, end);
}

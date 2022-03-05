#include <iostream>

#include "FrequencyList.h"

FrequencyList::FrequencyList()
{
  this->size = 0;
  this->first = nullptr;
  this->last = nullptr;
}

FrequencyList::~FrequencyList()
{
}

unsigned int FrequencyList::getSize()
{
  return this->size;
}

FrequencyNode *FrequencyList::getFirst()
{
  return this->first;
}

// always add at the end of the list
void FrequencyList::add(FrequencyNode *frequencyNode)
{
  if (this->size == 0)
  {
    this->first = frequencyNode;
    this->last = frequencyNode;
  }
  else
  {
    this->last->setNext(frequencyNode);
    this->last = frequencyNode;
  }
  this->size++;
}

// search for a frequency node with the same documentId. returns "nullptr" if not found
FrequencyNode *FrequencyList::search(int documentId)
{
  FrequencyNode *cursor = this->first;
  for (unsigned int i = 0; i < this->size; ++i)
  {
    if (cursor->getDocumentId() == documentId)
    {
      break;
    }
    cursor = cursor->getNext();
  }
  return cursor;
}

// print function to help while debugging
void FrequencyList::print()
{
  FrequencyNode *cursor = this->first;
  for (unsigned int i = 0; i < this->size; ++i)
  {
    std::cout << "(" << cursor->getDocumentId() << "," << cursor->getTermFrequency() << "," << cursor->getWtd() << ") | ";
    cursor = cursor->getNext();
  }
}

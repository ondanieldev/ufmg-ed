#include <iostream>

#include "TermList.h"

TermList::TermList()
{
  this->size = 0;
  this->first = nullptr;
  this->last = nullptr;
}

TermList::~TermList()
{
}

TermNode *TermList::getFirst()
{
  return this->first;
}

unsigned int TermList::getSize()
{
  return this->size;
}

// always add at the end of the list
void TermList::add(TermNode *termNode)
{
  if (this->size == 0)
  {
    this->first = termNode;
    this->last = termNode;
  }
  else
  {
    this->last->setNext(termNode);
    this->last = termNode;
  }
  this->size++;
}

// search for a frequency node with the same documentId. returns "nullptr" if not found
TermNode *TermList::search(std::string term)
{
  TermNode *cursor = this->first;
  for (unsigned int i = 0; i < this->size; ++i)
  {
    if (cursor->getTerm() == term)
    {
      break;
    }
    cursor = cursor->getNext();
  }
  return cursor;
}

// print function to help while debugging
void TermList::print()
{
  TermNode *cursor = this->first;
  for (unsigned int i = 0; i < this->size; ++i)
  {
    std::cout << "[" << cursor->getTerm() << "] => ";
    cursor->getFrequencyList()->print();
    cursor = cursor->getNext();
  }
  std::cout << std::endl;
}

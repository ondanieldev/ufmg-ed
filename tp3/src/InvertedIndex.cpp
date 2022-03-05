#include <math.h>
#include <iostream>

#include "InvertedIndex.h"

// while constructing, create an array using the given size
InvertedIndex::InvertedIndex(unsigned int size)
{
  this->size = size;
  this->table = new TermList[size];
}

InvertedIndex::~InvertedIndex()
{
}

// uses a polynomial function to convert a term into a hash
int InvertedIndex::hash(std::string term)
{
  const int p = 31;
  unsigned int hash = 0;
  for (unsigned int i = 0; i < term.length(); ++i)
  {
    hash += ((int)term[i] * pow(p, i));
  }
  hash = hash % this->size;
  // this condintion is impossible to occur, but it's implemented to avoid errors if hash function gets edited
  if (hash >= this->size || hash < 0)
  {
    throw "an invalid inverted index hash was generated";
  }
  return hash;
}

unsigned int InvertedIndex::getSize()
{
  return this->size;
}

TermList InvertedIndex::getAtPosition(unsigned int position)
{
  if (position >= this->size)
  {
    throw "trying to access an invalid inverted index position";
  }
  return this->table[position];
}

void InvertedIndex::add(std::string term, int documentId)
{
  int termHash = this->hash(term);

  // if the term is not already in the index, create and add it
  TermNode *termNode = this->table[termHash].search(term);
  if (termNode == nullptr)
  {
    termNode = new TermNode(term);
    this->table[termHash].add(termNode);
  }

  FrequencyList *frequencyList = termNode->getFrequencyList();
  FrequencyNode *frequencyNode = frequencyList->search(documentId);
  // if a term inside the document isn't  added to the index, create and add it
  if (frequencyNode == nullptr)
  {
    frequencyNode = new FrequencyNode(documentId);
    frequencyList->add(frequencyNode);
  }
  // if it's already added, then just increment its frequency
  else
  {
    frequencyNode->incrementTermFrequency();
  }
}

// search for a term node with the same term name. returns "nullptr" if not found
TermNode *InvertedIndex::search(std::string term)
{
  int termHash = this->hash(term);
  return this->table[termHash].search(term);
}

// print function to help while debugging
void InvertedIndex::print()
{
  for (unsigned int i = 0; i < this->size; ++i)
  {
    std::cout << "[" << i << "]: " << std::endl;
    this->table[i].print();
  }
}

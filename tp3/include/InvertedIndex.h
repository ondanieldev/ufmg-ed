#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <string>
#include "TermList.h"

class InvertedIndex
{
public:
  InvertedIndex(unsigned int size);
  ~InvertedIndex();
  unsigned int getSize();
  TermList getAtPosition(unsigned int position);
  void add(std::string term, int documentId);
  TermNode *search(std::string term);
  void print();

private:
  int hash(std::string term);

  unsigned int size;
  TermList *table;
};

#endif
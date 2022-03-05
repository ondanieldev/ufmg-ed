#ifndef TERMLIST_H
#define TERMLIST_H

#include <string>
#include "TermNode.h"

class TermList
{
public:
  TermList();
  ~TermList();
  TermNode *getFirst();
  unsigned int getSize();
  void add(TermNode *termNode);
  TermNode *search(std::string term);
  void print();

private:
  unsigned int size;
  TermNode *first;
  TermNode *last;
};

#endif
#ifndef TERMNODE_H
#define TERMNODE_H

#include <string>
#include "FrequencyList.h"

class TermNode
{
public:
  TermNode(std::string term);
  ~TermNode();
  TermNode *getNext();
  std::string getTerm();
  FrequencyList *getFrequencyList();
  void setNext(TermNode *next);

private:
  std::string term;
  FrequencyList *frequencyList;

  TermNode *next;
};

#endif
#ifndef FREQUENCYLIST_H
#define FREQUENCYLIST_H

#include "FrequencyNode.h"

class FrequencyList
{
public:
  FrequencyList();
  ~FrequencyList();
  unsigned int getSize();
  FrequencyNode *getFirst();
  void add(FrequencyNode *frequencyNode);
  FrequencyNode *search(int documentId);
  void print();

private:
  unsigned int size;
  FrequencyNode *first;
  FrequencyNode *last;
};

#endif
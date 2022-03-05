#ifndef RANKINGLIST_H
#define RANKINGLIST_H

#include "RankingNode.h"

class RankingList
{
public:
  RankingList(unsigned int size);
  ~RankingList();
  unsigned int getSize();
  RankingNode **getList();
  unsigned int getCursor();
  void add(RankingNode *rankingNode);
  RankingNode *search(int documentId);
  void quicksort(int start, int end);
  void print();

private:
  int quicksortPartition(int start, int end);

  unsigned int size;
  unsigned int cursor;
  RankingNode **list;
};

#endif
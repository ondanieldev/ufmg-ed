#ifndef LIST_H
#define LIST_H

#include "Url.h"

class List
{
public:
  List();
  bool isEmpty();
  void add(Url *url);
  Url *removeAtHead();
  void index();

private:
  int size;
  Url *head;
  Url *tail;
  Url *getCursor(int position, bool before);
};

#endif
#ifndef QUEUE_H
#define QUEUE_H

#include <string>

#include "Host.h"

class Queue
{
public:
  Queue();
  Host *search(std::string hostName);
  void enqueue(Host *host);

private:
  int size;
  Host *front;
  Host *rear;
};

#endif
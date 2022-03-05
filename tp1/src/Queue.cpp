#include <stdexcept>

#include "Queue.h"

Queue::Queue()
{
  this->size = 0;
  this->front = NULL;
  this->rear = NULL;
}

Host *Queue::search(std::string hostName)
{
  Host *host;
  host = this->front;
  while (host != NULL)
  {
    if (host->name == hostName)
    {
      return host;
    }
    host = host->next;
  }
  return NULL;
}

void Queue::enqueue(Host *host)
{
  if (this->size != 0)
  {
    this->rear->next = host;
    this->rear = host;
  }
  else
  {
    this->front = host;
    this->rear = host;
  }
  this->size++;
}

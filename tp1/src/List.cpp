#include <algorithm>

#include "List.h"

List::List()
{
  this->size = 0;
  this->head = NULL;
  this->tail = NULL;
}

bool List::isEmpty()
{
  return this->size == 0;
}

void List::add(Url *url)
{
  // list empty: the new url is both head and tail
  if (this->size == 0)
  {
    this->head = url;
    this->tail = url;
    this->size++;
    return;
  }

  size_t depth = getDepth(url->name);

  // avoid duplicates (head)
  if (url->name == this->head->name)
  {
    return;
  }

  // new url has greather priority than head: new url is the new head
  if (depth < getDepth(this->head->name))
  {
    url->next = this->head;
    this->head = url;
    this->size++;
    return;
  }

  // search where it needs to place the new url
  Url *cursor = this->head;
  Url *aux;
  while (cursor->next != NULL)
  {
    // avoid duplicates (middle)
    if (url->name == cursor->next->name)
    {
      return;
    }
    if (depth < getDepth(cursor->next->name))
    {
      aux = cursor->next;
      url->next = aux;
      cursor->next = url;
      this->size++;
      return;
    }
    cursor = cursor->next;
  }

  // the url was not inserted yet: new url is the new tail
  this->tail->next = url;
  this->tail = url;
  this->size++;
}

void List::index()
{
  Url *url = this->head;
  while (url != NULL)
  {
    std::cout << url->name << std::endl;
    url = url->next;
  }
}

Url *List::removeAtHead()
{
  Url *url = this->head;
  this->head = this->head->next;
  this->size--;
  return url;
}
#include <string>

#include "Host.h"

Host::Host()
{
  this->name = "";
  this->next = NULL;
  this->urls = List();
}

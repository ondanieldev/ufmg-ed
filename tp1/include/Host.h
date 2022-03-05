#ifndef HOST_H
#define HOST_H

#include <string>

#include "List.h"

class Host
{
public:
  Host();

private:
  std::string name;
  Host *next;
  List urls;

  friend class Scheduler;
};

#endif